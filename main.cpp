#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <forward_list>
#include <fstream>

void handle_error(const char* str) {
    printf("error: %s\n", str);
    exit(1);
}

struct Edge;

typedef int Node;
typedef std::forward_list<Edge> Bucket;
typedef Edge Graph[5000];

struct Edge {
    Node N1;
    Node N2;
    int weight;
    int subtree;
};

// node_subtree[node] yeilds the initial subtree for a node
// the returned result is probably stale. See follow_tree
int node_subtree[101] = {};

// initially, follow_tree[n] = n
// After some merges, follow_tree[n] = ?
// the returned result MAY be stale, so iterate until
// follow_tree[n] = n
int follow_tree[50] = {};

void merge_subtree(int s1, int s2) {
    follow_tree[s1] = follow_tree[s2];
}

// before lookup_subtree is used, node_subtree should be initialized
// in parallel to follow_tree. This is so that '0' means uninitialized
// instead of indicating the original subtree was valid, or the lookup
// did not need to be looped.
int lookup_subtree(Node n) {
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

namespace WeightIterator {
    int num_weights = 0;
    Bucket buckets[500] = {};
};

const int INF = 1073741824;

inline void skip_lines(std::istream& in, size_t n) {
    for (; n; --n)
        in.ignore(32, '\n');
}

void print_mst(Graph mst, int edges) {
    for (int i = 0; i < edges; i++) {
        //printf("(%d, %d)\n", mst[i].N1, mst[i].N2);
        //printf("(%d, %d) = %d\n", mst[i].N1, mst[i].N2, mst[i].weight);
    }
}

// populates the mst and total number of edges
// returns: mst cost
int get_mst(Graph mst, int &edges) {
    using namespace WeightIterator;
    
    int cost = 0;
    int num_edges = 0;
    int next_subtree = 1;
    Edge e = {};
    
    for (int i = 0; i < num_weights; i++) {
        auto b = buckets[i];
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

int ld_weights(char const *fname) {
    
    using namespace WeightIterator;
    std::ifstream in(fname);
    if (!in)
        handle_error("file not found");
    
    int skip = 0;
    int i, j, weight;
    int nodes, lines;
    in >> nodes;
    lines = nodes * nodes;
     
    Edge e = {};
    
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
        
        if (weight == INF) {
            continue;
        }
        
        num_weights = (num_weights < weight ? weight : num_weights);
        e = {i, j, weight};
        buckets[weight].push_front(e);
    }
    in.close();
    return nodes;
}

// usage: mst <filename>
int main(int argc, char*argv[]) {
    
    if (argc == 1) {
        handle_error("usage: mst <filename>");
    }

    clock_t start, end;
    double cpu_time_used;
    start = clock();
    
    Graph mst = {};
    char* filename = argv[1];
    int nodes = ld_weights(filename);
    int edges;
    int cost = get_mst(mst, edges);
    
    end = clock();
    cpu_time_used = 1000 * ((double) (end - start)) / CLOCKS_PER_SEC;
    
    printf("Total Execution Time = %f ms\n", cpu_time_used);
    printf("Minimum Cost = %d\n", cost);
    //printf("Minimum Spanning Tree (T): (1,2) -> (2,4), (1,3) -> (3,5) -> (5,6)\n");
    printf("Minimum Spanning Tree (T):\n");
    print_mst(mst, edges);
    
    // 1) What would it take to print the MST like how the example gives it?
    // 2) I should get rid of global variables
    // 3) I should organize files
}
