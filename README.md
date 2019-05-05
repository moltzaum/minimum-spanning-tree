### minimum-spanning-tree

**Requirements**
<pre>
1.1 Input File  
  • Test input file will be randomly generated when your program will be tested.  
  • Test input file format: represent current status of entire network  
    o Test input file contains link information and cost of between link  C[i][j] = n if there is direct link from node i to node j,
      where 0 <= n < 100  
      = 1073741824 (=2^30) otherwise  
    o The first line of test input file has the total number of node in the network  
    o Following each line contains link cost between i and j.  
  • Sample test input file:
    6
    1 1 0
    1 2 2
    1 3 1
    1 4 5
    1 5 1073741824
    1 6 1073741824
    2 1 2
    2 2 0
    2 3 5
    2 4 1
    2 5 1073741824
    2 6 1073741824
    3 1 1
    3 2 5
    3 3 0
    3 4 3
    3 5 1
    3 6 1073741824
    4 1 5
    4 2 1
    4 3 3
    4 4 0
    4 5 2
    4 6 5
    5 1 1073741824
    5 2 1073741824
    5 3 1
    5 4 2
    5 5 0
    5 6 2
    6 1 1073741824
    6 2 1073741824
    6 3 1073741824
    6 4 5
    6 5 2
    6 6 0

1.2. Program input arguments
  The program takes intput as follows: prompt$ mst <input-file>
  Where: <input-file> : The graph file

2. Output
  1) Minimum Spanning Tree (T) and Minimum Cost
  2) Display total execution time in ms (millisecond) from reading test input files to find a MST (Minimum Spanning Tree)
  
  Total Execution Time = 0.332000 ms
  Minimum Cost = 7
  Minimum Spanning Tree (T):
  (3, 5)
  (2, 4)
  (1, 3)
  (5, 6)
  (4, 5)
</pre>

