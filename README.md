# API Project 
:it: Lo sviluppo di questo progetto è parte del corso di algoritmi e principi dell'informatica del Politecnico di Milano, e in qualità di prova finale è necessario per il conseguimento della laurea triennale in ingegneria informatica. Il corso è stato tenuto dai prof. Matteo Pradella, Davide Martinenghi e Alessandro Barenghi nell'a.a. 2020-2021 e il progetto  è stato valutato automaticamente da una piattaforma proprietaria del DEIB (Dipartimento di Elettronica, Informazione, Bioingegneria) del Politecnico di Milano. <br>
***Valutazione finale: 30/30 cum laude***

:uk: The development of this project is part of the algorithms and principles of informatics course at the Polytechnic University of Milan, and as a final examination, it is necessary for the bachelor's degree in computer engineering. The course was held by prof. Matteo Pradella, Davide Martinenghi and Alessandro Barenghi in the academic year 2020-2021 and the project was automatically evaluated by a proprietary platform of the DEIB (Department of Electronics, Information, Bioengineering) of the Polytechnic University of Milan.<br>
***Final score: 30/30 cum laude***

## Project specification

<p>Questo progetto stila una classifica di un insieme di grafi diretti pesati forniti in input. Il punteggio che viene attribuito ad ogni grafo è ottenuto dalla somma dei cammini più brevi tra il nodo iniziale e tutti gli altri nodi.</p>

<p>Il programma riceve in ingresso  due parametri, da linea di comando, separati da uno spazio:
  <ol>
    <li> <em>d </em>⁓ numero di nodi dei grafi</li>
    <li> <em>k </em>⁓ lunghezza della classifica</li>
  </ol>
</p>

<p>Si può successivamente inserire una sequenza di comandi:
  <ul>
    <li> 
      <p>
        <em>AggiungiGrafo MATRICE DI ADIACENZA </em>
      </p>
      <p>
        Viene aggiunto un grafo a quelli considerati per stilare la classifica. Il comando è 
        seguito dalla matrice di adiacena del grafo stesso, stampata una riga per ogni rigo, 
        con gli elementi separati da virgole.
       </p>
       <p><em>Esempio<em><br>
        3,7,42<br>
        0,7,42<br>
        7,4,3
       </p>
    </li>
    <li> 
      <p>
        <em>TopK </em>
      </p>
      <p>
        Vengono stampati gli indici interi dei <em>k</em> grafi aventi i <em>k</em> valori più 
        piccoli secondo la metrica precedentemente descritta. Se ci soo più grafi con lo 
        stesso punteggio, si dà la precedenza ai primi arrivati.
       </p>
    </li>
  </ul>
</p>

