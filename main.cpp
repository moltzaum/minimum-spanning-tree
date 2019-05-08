#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <forward_list>
#include <fstream>

void handle_error(const char* str) {
    printf("error: %s\n", str);
    exit(1);
}

// -----------------
// Type declarations

struct Edge;
typedef int Node;
typedef Edge Graph[100];
typedef std::forward_list<Edge> EdgeList;

struct Edge {
    Node N1;
    Node N2;
    int weight;
};

// ---------------
// Weight Iterator

// The WeightIterator namespace simply qualifies two global variables.
// It essentially allows me to group all edges with the same weight
// without sorting by weight. The maximum weight should not extend
// beyond 100 according to the requirements, and the maximum weight
// in the largest given file is 290. I presume 500 will be enough.
//
namespace WeightIterator {
    int num_weights = 0;
    EdgeList buckets[500] = {};
};

// --------------------------------
// Union-Find methods and variables


// node_subtree[node] yeilds the initial subtree for a given node.
// The returned result is probably stale. Use follow_tree to find
// the real subtree.
//
// 101 elements because the maximum index is the node 100
//
int node_subtree[101] = {};

// follow_tree[subtree] == subtree
// if that is not true, we follow the result of follow_tree[subtree]
//
int follow_tree[50] = {};

// This method in itself leaves stale entries. This method was made
// for readability. Some of the merging magic happens later when
// stale entries get updated.
//
inline void merge_subtree(int s1, int s2) {
    follow_tree[s1] = follow_tree[s2];
}

// Before lookup_subtree is used, the result of node_subtree should
// be initialized for follow_tree. This is so that a result of '0'
// indicates the node does not belong to a subtree yet.
//
inline int lookup_subtree(Node n) {
    int subtree;
    int result = node_subtree[n];
    do {
        subtree = result;
        result = follow_tree[subtree];
    } while (result != subtree);
    
    // update cached result
    node_subtree[n] = result;
    
    return result;
}

// -------------------------------
// Minimum Spanning Tree Algorithm


// get_mst populates the graph and total number of edges 
//
// I am using a varient of Kruskal's algorithm.
//
// A few global variables are referenced, namely:
//  node_subtree,
//  follow_tree,
//  WeightIterator::buckets
//  WeightIterator::num_weights
//
// Normally I'd group these into objects then pass them as reference,
// but I'm avoiding objects because of a percieved speed disadvantage.
// Normally, I wouldn't be concerned about something so miniscule, but
// this lab is competitively graded for speed.
//
// I realize premature optimization and global variables are evil.
// Anyways..
//
// The cost of all the edges in the graph is returned.
//
int get_mst(Graph mst, int &edges) {
    
    int cost = 0;
    int num_edges = 0;
    int next_subtree = 1;
    Edge e = {};
    
    for (int i = 0; i < WeightIterator::num_weights; i++) {
        auto b = WeightIterator::buckets[i];
        for (auto it = b.begin(); it != b.end(); ++it) {
            e = *it;
            
            int s1 = lookup_subtree(e.N1);
            int s2 = lookup_subtree(e.N2);
            
            if (s1 == 0 && s2 == 0) {
                node_subtree[e.N1] = next_subtree;
                node_subtree[e.N2] = next_subtree;
                follow_tree[next_subtree] = next_subtree;
                next_subtree++;
                
            } else if (s1 == 0) {
                node_subtree[e.N1] = s2;
                
            } else if (s2 == 0) {
                node_subtree[e.N2] = s1;
                
            } else if (s1 == s2) {
                // adding edge will make a cycle
                continue;
            } else {
                merge_subtree(s1, s2);
            }
            
            mst[num_edges++] = e;
            cost += e.weight;
        }
    }
    
    edges = num_edges;
    return cost;
}

// ----------------------
// Reading the Input File


// For efficient reading of the file.
inline void skip_lines(std::istream& in, size_t n) {
    for (; n; --n) in.ignore(32, '\n');
}

// ld_weights reads from the file fname
// 
// The file is expected to have the general format:
//
// num_nodes
// 1 1   weight
// 1 2   weight
// 1 3   weight
// 1 ... weight
// .
// .
// .
// n n   weight
//
// The weight will have a value of 1073741824 if no connection between
// nodes i and j exists.
//
// While reading the file in, the result is stored in a global array
// of buckets indexed by weight (the maximum weight is reasonably low,
// so we can index it in a normal array).
//
// This is how the buckets are indexed:
//   WeightIterator::buckets[weight]
//
// The number of nodes is returned.
//
int ld_weights(char const *fname) {
    
    std::ifstream in(fname);
    if (!in)
        handle_error("file not found");
    
    Edge e = {};
    int skip = 0;
    int max_weight = 0;
    int i, j, weight;
    const int NONE = 1073741824;
    
    int nodes, lines;
    in >> nodes;
    lines = nodes * nodes;
    
    for (int k = 0; k < lines; k++) {
        
        if (k % nodes == 0) {
            k += skip;
            skip_lines(in, skip+1);
            skip++;
        }
        
        if (!(in >> i >> j >> weight)) {
            printf("scan error\n");
            printf("{%d, %d, %d}\n", i, j, weight);
            in.close();
            return -1;
        }
        
        if (i == j) continue;
        if (weight == NONE) continue;
        
        max_weight = (max_weight < weight ? weight : max_weight);
        e = {i, j, weight};
        WeightIterator::buckets[weight].push_front(e);
    }
    WeightIterator::num_weights = max_weight;
    in.close();
    return nodes;
}

// ------
// Driver

void print_mst(Graph mst, int edges) {
    for (int i = 0; i < edges; i++) 
        printf("(%d, %d)\n", mst[i].N1, mst[i].N2);
}

// usage: mst <filename>
int main(int argc, char*argv[]) {
    
    if (argc == 1) 
        handle_error("usage: mst <filename>");
    
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);

    Graph mst = {};
    char* filename = argv[1];
    int nodes = ld_weights(filename);
    int edges;
    int cost = get_mst(mst, edges);
    
    clock_gettime(CLOCK_REALTIME, &end);
    
    double result = 0;
    result = 1000 * (end.tv_sec - start.tv_sec);
    result += (end.tv_nsec - start.tv_nsec) / 1e6;
    printf("Total Execution Time = %f ms\n", result);
    
    printf("Minimum Cost = %d\n", cost);
    printf("Minimum Spanning Tree (T):\n");
    //print_mst(mst, edges);
}
