### minimum-spanning-tree

**Data Structures and Algorithms**

While loading the file, I skip a number of lines that are duplicates. This greatly speeds up the program since IO is the bottleneck.

```
1 1 (skip)
1 2
1 3
2 1 (skip)
2 2 (skip)
2 3
3 1 (skip)
3 2 (skip)
3 3 (skip)
```

For the implementation of the mst, I use a variant of Kruskal's algorithm. Because the requirements specify that the weights are restricted from 0 to 100, I use them to index the edges with the smallest weights first.

In order to find the minimum spanning tree, we must know if adding an edge will create a loop. Suppose in the graph below, we have already added (4, 5) and (2, 4), then adding (2, 5) would create a loop. We can determine if adding an edge will create a loop by using subtrees. If nodes 2, 4, and 5 belong to a subtree of '0', then making a new edge between any of the points 2, 4, and 5 will create a loop within the subtree of '0'.

```
 (1)
 |  \
 |   (2) -- (4)
 \   /  \   /
  (3) -- (5)
```

If two subtrees exist, we should be able to join them. If (1, 3) is a subtree of '0' and (2, 4) is a subtree of '1', how do I do I make a connection between (1, 2)? I can update node 2 to have the subtree of node 1 (or vice versa), but we should be able to update all nodes in the subtree if that subtree number has changed.

In order to do this, I have an array called `follow_tree` that is initialied like so: `follow_tree[subtree] = subtree`. When I merge two subtrees I will update the entry for `tree1` to point to the entry for `tree2` like so: `follow_tree[tree1] = follow_tree[tree2]`. Then, on subsequent references to `follow_tree[tree1]`, we will go to the updated subtree. Sometimes this isn't the tree we need, so we loop until `follow_tree[n] = n`.

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

