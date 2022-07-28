# API Project 

The development of this project is part of the algorithms and principles of informatics course at the Polytechnic University of Milan, and as a final examination, it is necessary for the bachelor's degree in computer engineering. The course was held by prof. Matteo Pradella, Davide Martinenghi and Alessandro Barenghi in the academic year 2020-2021 and the project was automatically evaluated by a proprietary platform of the DEIB (Department of Electronics, Information, Bioengineering) of the Polytechnic University of Milan.<br>
***Final score: 30/30 cum laude***

## Project specification

<img src="/assets/graph_image.png" style="width:260px;height:130px;margin-left: 5px;" align="right"></p>
<p>This project establishes a ranking of a set of weighted direct graphs provided as input. The score attributed to each graph is obtained from the sum of the shortest paths between the initial node and all the other nodes.


<p>The program receives two parameters, from the command line, separated by a space:
  <ol>
    <li> <em>d </em>⁓ number of nodes of the graphs</li>
    <li> <em>k </em>⁓ length of the ranking</li>
  </ol>
</p>

<p>Supported commands:
  <ul>
    <li> 
      <p>
        <code>AggiungiGrafo [adjacency_matrix] </code>
      </p>
      <p>
        A graph is added to those considered to draw up the ranking. The command is
        followed by the adjacency matrix of the graph itself, inserted one row at a time,
        with elements separated by commas.
       </p>
       <p><em>Example</em><br>
        3,7,42<br>
        0,7,42<br>
        7,4,3
       </p>
    </li>
    <li> 
      <p>
        <code>TopK </code>
      </p>
      <p>
        The program prints the integer indices of the <em>k</em> graphs having the smallest 
        <em>k</em>values according to the previously described metric. If there are several 
        graphs with the same score, the first to arrive have priority.
      </p>
    </li>
  </ul>
</p>

## Compiling the program with GCC
1. Go to the folder where the source code file is stored
2. Compile the source code file <code>gcc [program_name].c -o [executable_file_name]</code>
3. Run the newly compiled program <code>./[executable_file_name]</code>




