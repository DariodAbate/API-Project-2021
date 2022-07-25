#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


typedef struct{ //struttura dati per classifica
  int id;       //identificativo del grafo
  unsigned long int sum;//somma cammini minimi
}rank_node;

typedef struct{ //struttura dati per coda in dijkstra
  int vertex;       //identificativo del nodo
  unsigned long int dist;//somma cammini minimi da sorgente al nodo
}queue_node;

typedef struct{ //struttura dati per supporto in dijkstra
  int visited; //boolean, indica se nodo è stato visitato
  unsigned long int cost;//costo del nodo da sorgente
}v_node;

//funioni richieste da progetto
void TopK(rank_node* rank, int k, int id);
void add_Graph(unsigned long int ** matrix, rank_node* rank,int d, int k, int id);

//funzioni di supporto input
void parse(char * stringa, unsigned long int * vett, int d);//parsing righe matrice
unsigned long int ** mat_init(int d); //inizializza matrice dXd
int mystr_cmp(char* str1,char* str2);//1 se stringhe uguali, 0 altrimenti
unsigned long int my_strtoul(char* str, int dim);//char -> unsigned long int

//funzioni di gestione della classifica
rank_node * rank_init(int k); //inizializzazione coda di max piorità
void max_heapify(rank_node *rank, int index,int dim);//mantenimento struttura max-heap
void swap(rank_node *rank, int idx1, int idx2);//scambio elementi max-heap
void build_heap(rank_node *rank, int heap_lenght);//costruisce heap da array
void heap_ins(rank_node * rank, int id, unsigned long int sum, int k);//inserimento in root
unsigned long int dijkstra(unsigned long int ** matrix, int d);//calcolo cammini minimi da sorgente

//funzioni di supporto per dijkstra
queue_node* queue_init(int d);//inizializzazione coda di min priorità
v_node* vett_init(int d);//inizializzazione distnce vector
void min_heapify(queue_node* queue, int index, int dim);//mantenimento struttura min-heap
void queue_swap(queue_node* queue, int idx1, int idx2);//scambio elementi min-heap
int min_extract(queue_node* queue,unsigned long int* min_value, int dim);//elemento minimo da min-heap
void queue_ins(queue_node* queue, int dim, int vertex, unsigned long int dist);//inserimento in coda di min-priorità
int parent(int i);//supporto per queue_ins

int main() {

  int d = 0; //numero di nodi dei grafi
  int k = 0; //lunghezza della classifica
  int id = 0;//identificatore di un grafo
  char ag[14] = "AggiungiGrafo";
  char tk[5] = "TopK";
  char * str; //buffer stringa di input
  int len = 0;//lunghezza max stringa di input
  unsigned long int ** mat_adj;//buffer matrice di adiacenza
  int i = 0;//variabile di supporto
  rank_node * rank;//classifica
  int dim = 0;//numero di elementi presenti in classifica

  if(fscanf(stdin,"%d%d\n", &d,&k)){//per non avere warning su return value
    //allocazione per le righe di input
    //valore più alto peso del grafo ha 10 cifre,ho d nodi,d-1 virgole
    len = 10*d*(d-1)+1;
    str = (char *) calloc(len , sizeof(char));
    //allocazione  per matrice di adiacenza
    mat_adj = mat_init(d);
    //allocazione e inizializzazione per max_heap
    rank = rank_init(k);


    if(str != NULL){
      while(fgets(str , len ,stdin)){
        if( mystr_cmp(str,tk)){
          TopK(rank, k, dim);
        }
        else if(mystr_cmp(str,ag)){
          //parse della stringa per righe matrice
          for(i = 0; i < d ; ++i){//matrice dXd
            if(fgets(str , len , stdin)){
              parse(str, mat_adj[i], d);
            }
          }
          add_Graph(mat_adj,rank, d, k, id); //serve un id per ogni grafo
          id++;//parte da 0
          if(dim < k){//classifica di dimensione k
            dim++;
          }
        }
        else{
          break;
        }
      }
    }
    //deallocazione memoria
    free(str);
    for(i = 0; i < d;i++){
      free(mat_adj[i]);
    }
    free(mat_adj);
    free(rank);
  }
  return 0;
}

//inizializzazione di matrice dinamica dXd
unsigned long int** mat_init(int d){
  unsigned long int** mat;
  int i = 0;
  mat = (unsigned long int**) calloc(d, sizeof(unsigned long int));
  for(i = 0; i < d ; ++i){
    mat[i] = (unsigned long int*) calloc(d, sizeof(unsigned long int));
  }
  return mat;
}

//inizializzazione classifica
rank_node* rank_init(int k){
  int i = 0;
  rank_node* new_rank;
  new_rank = (rank_node *) malloc(k * sizeof(rank_node));
  for(i = 0 ; i < k ; ++i){
    new_rank[i].sum = -1;
  }
  return new_rank;
}

//funzione di parsing righe di file
void parse(char* stringa, unsigned long int* vett, int d){
  char temp[10];
  int i = 0;
  int j = 0;
  int k = 0;
  int len = 0;

  len = 10*d*(d-1)+1;

  for(i = 0;i < d && j < len ; ++i){
    k=0;
    while(k < 10 && stringa[j] >= '0' && stringa[j] <= '9'){
      temp[k] = stringa[j];
      ++j;
      ++k;
    }
    if(stringa[j] == ','){
      ++j;
    }
    vett[i] = my_strtoul(temp, k);
  }
}

//avevo problemi con \n e \0 in str
int mystr_cmp(char* str1,char* str2){
  int i = 0;
  int bool = 1;

  while(str1[i] != '\0' && str2[i] != '\0' && bool){
    if(str1[i] != str2[i]){
      bool = 0;
    }
    ++i;
  }
  return bool;
}


//versione più veloce di strtoul
unsigned long int my_strtoul(char* str, int dim){
  int i;
  unsigned long int num = 0;

  for(i = 0; i < dim; ++i ){
    if(str[i] >= '0' && str[i] <= '9'){
      num = (num * 10) + (str[i]-'0');
    }
  }
  return num;
}



//versione "stabile" di max heapify
void max_heapify(rank_node* rank, int index, int dim){
  int l = 2 * index + 1; //figlio sinistro
  int r = 2 * index + 2; //figlio destro
  int posmax;
  //modifica su heapify originale: a parità di sum, mantengo elementi più vecchi in fondo
  if(l < dim && (rank[l].sum > rank[index].sum || (rank[l].sum == rank[index].sum && rank[l].id > rank[index].id ))){
    posmax = l;
  }
  else
    posmax = index;

  if(r < dim && (rank[r].sum > rank[posmax].sum || (rank[r].sum == rank[posmax].sum && rank[r].id > rank[posmax].id ))){
    posmax = r;
  }

  if(posmax != index || (rank[posmax].sum == rank[index].sum &&  rank[index].id < rank[posmax].id)){
    swap(rank, index , posmax);
    max_heapify(rank , posmax , dim);
  }

}

//scambia due elementi della classifica
void swap(rank_node *rank, int idx1, int idx2){
  int id_temp;
  unsigned long int sum_temp;

  id_temp = rank[idx2].id;
  sum_temp = rank[idx2].sum;

  rank[idx2].id = rank[idx1].id;
  rank[idx2].sum = rank[idx1].sum;

  rank[idx1].id = id_temp;
  rank[idx1].sum = sum_temp;

}

//genera heap da array
void build_heap(rank_node* rank, int heap_lenght){
  int i = 0;
  for(i = (heap_lenght / 2) - 1 ; i >= 0; i--){
      max_heapify(rank , i ,heap_lenght );
  }
}

//inserimento in testa
void heap_ins(rank_node* rank, int new_id, unsigned long int new_sum, int k){
  rank[0].id = new_id;
  rank[0].sum = new_sum;
  //chiamo heap_ins quando classifica è piena, perciò max_heapify su k
  max_heapify(rank, 0, k);
}


void add_Graph(unsigned long int** matrix,rank_node* rank, int d, int k, int id){
  //aggiungo grafi fin quando riempio la classifica, partendo dalla fine
  //chiamo build_heap
  //per ogni nuovo grafo che aggiungerò valuto se inserirlo in classfica e chiamo max_heapify
  unsigned long int sum = dijkstra(matrix, d); //calcolo i cammini minimi del grafo
  unsigned long int max = rank[0].sum; //massimo in rotto di max-heap

  if(id < k){
    //inserisco nella classifica nel posto che gli spetta, partendo dalla fine
    rank[k-1-id].id = id;
    rank[k-1-id].sum = sum;

    if(id == k-1){//ho riempito la classifica per la prima volta
      build_heap(rank, k);//rendo max_heap la classifica
    }
  }
  else{
    //inserisci,se necessario, in cima alla classifica e fai scendere
    if(sum < max){
      heap_ins(rank, id, sum, k);
    }
  }
}

void TopK(rank_node* rank, int k, int dim){
  //stampo id su una ringa, separati da uno spazio in qualunque ordine e \n alla fine
  int i = 0;

  if(dim > 0){
    for(i = k-1; i > (k-1)-(dim-1) && i > 0 ; --i){ //stampo partendo dalla fine solo "celle" piene
      printf("%d ",rank[i].id);
    }
    printf("%d",rank[(k-1)-(dim-1)].id);
  }
  printf("\n");
}



//calcolo dei cammini minimi
unsigned long int dijkstra(unsigned long int** mat, int d){
  queue_node* queue = queue_init(d);//coda di min priorità
  v_node* dist_vect = vett_init(d);//vettore distanze minime da sorgente
  unsigned long int sum = 0; //somma cammini minimi da sorgente
  unsigned long int temp;
  unsigned long int u_val;// valore elemento minimo estratto
  int u; // indice elemento minimo estratto
  int dim_queue = 0; //ho solo nodo sorgente
  int adj; //per nodi adiacenti

  //inserisco sorgente nella coda
  ++dim_queue;
  queue[0].dist = 0;

  while(dim_queue > 0){
    u = min_extract(queue, &u_val, dim_queue);
    --dim_queue;
    dist_vect[u].visited = 1; //ho visitato il nodo appena estratto

    if(dist_vect[u].cost >=  u_val ){//non controllo elementi che hanno già distanza minima

      for(adj = 0; adj < d ; ++adj){
        if(mat[u][adj] > 0 && u != adj && (dist_vect[adj].visited == 0) ){//nodi adiacenti non visitati

          temp = dist_vect[u].cost + mat[u][adj];
          if(temp < dist_vect[adj].cost){
            dist_vect[adj].cost = temp;
            ++dim_queue;//faccio inserimento in coda
            queue_ins(queue, dim_queue, adj, temp);
          }
        }
      }
    }
  }

  //recupero variabile per ciclare
  for(adj = 0; adj < d; ++adj){
    if(dist_vect[adj].cost != UINT_MAX){
      sum = sum + dist_vect[adj].cost;
    }
  }

  free(queue);
  free(dist_vect);
  return sum;
}

//inizializzazione coda di min priorità
queue_node* queue_init(int d){
  queue_node* new_queue;
  int i = 0;
  //d^2 dovrebbe bastare come dimensione heap
  new_queue = (queue_node *) malloc((d*d) * sizeof(queue_node));
  for(i = 0; i < d; ++i){
    new_queue[i].vertex = 0;
    new_queue[i].dist = UINT_MAX;
  }
  return new_queue;
}

//inizializzazione distance vector
v_node* vett_init(int d){
  int i = 0;
  v_node* new;

  new = (v_node*) malloc(d * sizeof(v_node) );

  for(i = 0; i< d; i++ ){//nodi a infinito,anche sorgente
    new[i].cost = UINT_MAX;
    new[i].visited = 0;//nessun nodo visitato
  }
  new[0].cost = 0;//sorgente a distanza zero
  return new;
}

//mantenimento struttura di min-heap
void min_heapify(queue_node* queue, int index, int dim){
  int l = 2 * index + 1; //figlio sinistro
  int r = 2 * index + 2; //figlio destro
  int posmin;

  if(l < dim && queue[l].dist < queue[index].dist ){
    posmin = l;
  }
  else
    posmin = index;

  if(r < dim && queue[r].dist < queue[posmin].dist ){
    posmin = r;
  }

  if(posmin != index ){
    queue_swap(queue, index , posmin);
    min_heapify(queue, posmin , dim);
  }

}

//scambio di due elementi di min-heap
void queue_swap(queue_node* queue, int idx1, int idx2){
  int vertex_temp;
  unsigned long int dist_temp;

  vertex_temp = queue[idx2].vertex;
  dist_temp = queue[idx2].dist;

  queue[idx2].vertex = queue[idx1].vertex;
  queue[idx2].dist = queue[idx1].dist;

  queue[idx1].vertex = vertex_temp;
  queue[idx1].dist = dist_temp;
}

//estrazione di elemento minimo
int min_extract(queue_node* queue,unsigned long int* min_value, int dim){
  int min ;

  min  = queue[0].vertex;//per def di min-heap
  *min_value = queue[0].dist;//per ottimizzazione in dijkstra

  queue[0].vertex = queue[dim-1].vertex;
  queue[0].dist = queue[dim-1].dist;
  min_heapify(queue, 0, dim-1);//preservo struttura di min-heap

  return min;
}

//supporto per queue_ins
int parent(int i){//calcolata su i-1 !
  int p;
  p = i/2;
  return p;
}

//inserimento in queue
//è meglio continuare a inserire in heap che decrementare la priorità dei nodi,se non ho riferimento ad essi
void queue_ins(queue_node* queue, int dim, int vertex, unsigned long int dist){
  int i = dim-1 ;
  int p = parent(i);
  //sto considerando dim già incrementata da chiamante
  queue[dim-1].vertex = vertex;
  queue[dim-1].dist = dist;

  while(i > 0 && queue[p].dist > queue[i].dist){
    queue_swap(queue, p, i); //parent è calcolato su i-1, non i!!
    i = p;
    p = parent(i-1);
  }
}
