#include <time.h>
#include <stdio.h>  // print  
#include <stdlib.h> // exit
#include <fcntl.h>  // posix_fadvise
#include <unistd.h> // read
#include <string.h> // memchr

void handle_error(const char* str) {
    printf("%s\n", str);
    exit(1);
}

// if time: compare read, fread, mmap, and read into posix_fadvise
// read uses open instead of fopen
//
// if time: create specialized scan function
//
// if time: what if I read the file in such a way so that I stopped at 6
// I access the array with either the ordered set, or the unordered set
// gets ordered on access.
//

/* ld loads the file into the first argument.
 * The fist number in the file will be used
 * to allocate the length portion of the array.
 *
 * The length of the arrays are returned.
 */
static int ld(int* matrix[3], char const *fname)
{
    static const auto BUFFER_SIZE = 16*1024;
    FILE* f = fopen(fname, "r");
    if (f == NULL)
        handle_error("open");
    
    int i, j, weight;
    int nodes, lines;
    fscanf(f, "%d", &nodes);
    lines = nodes * nodes;
    
    matrix[0] = (int*) malloc(lines * sizeof(int));
    matrix[1] = (int*) malloc(lines * sizeof(int));
    matrix[2] = (int*) malloc(lines * sizeof(int));
    
    int k;
    for (k = 0; k < lines; k++) {
        if (3 != fscanf(f, "%d %d %d", &i, &j, &weight)) {
            printf("scan error");
            fclose(f);
            return -1;
        }
        matrix[0][k] = i;
        matrix[1][k] = j;
        matrix[2][k] = weight;
    }
    fclose(f);
    return k;
}

// 1) Create a set mstSet that keeps track of vertices already included in MST.
// 2) Assign a key value to all vertices in the input graph. Initialize all key values as INFINITE. 
//  Assign key value as 0 for the first vertex so that it is picked first.
// 3) While mstSet doesn’t include all vertices
// ….a) Pick a vertex u which is not there in mstSet and has minimum key value.
// ….b) Include u to mstSet.
// ….c) Update key value of all adjacent vertices of u. To update the key values, iterate through
//      all adjacent vertices. For every adjacent vertex v, if weight of edge u-v is less than the
//      previous key value of v, update the key value as weight of u-v

struct Edge {
    int N1;
    int N2;
    int weight;
}

// usage: mst <filename> <time>
int main()
{
    const int INF = 1073741824;
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    
    // The file we read in has 3 columns
    // The format is: <N1> <N2> <W>, where
    // N denotes a node, and W is the weight between the nodes
    int* column[3];
    int lines = ld(column, "data/input.txt");
    
    // DEBUG
    //for (int i = 0; i < lines; i++) {
    //    printf("%d %d %d\n", column[0][i], column[1][i], column[2][i]);
    //}
    
    // An existence array (set) of verticies that we have included in the MST
    // All nodes MUST be in the range 1 <= n <= 100
    bool mstSet[101] = {false};

    typedef 
    
    // Do stuff here
    
    free(column[0]);
    free(column[1]);
    free(column[2]);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    
    printf("DEBUG: The cpu time is %f\n", cpu_time_used);
    // Total Execution Time = 10ms
    // Minimum Cost = 7
    // Minimum Spanning Tree (T): (1,2) -> (2,4), (1,3) -> (3,5) -> (5,6)
    //
    // E<N,N>
    //
}

// Plan: Implement Prim's Algorith using a Fibanocchi heap
// 
// I kindof need a set.
// Specifically, I can have an array of #node elements.
// I wonder if I can have other uses?
//
// Note: All nodes MUST be in the range 0 <= n < 100

// 1 1
// 1 2
// 1 3
// 1 4
// 1 5
// 1 6
// 1 7
// 1 8
// 1 9
// 1 10
//
// 2 1 (done)
// 2 2
// 2 3
// 2 4
// 2 5
// 2 6
// 2 7
// 2 8
// 2 9
// 2 10
//
// 3 1 (done)
// 3 2 (done)
// 3 3 
// 3 4
// 3 5 
// 3 6
// 3 7
// 3 8
// 3 9
// 3 10
//
// 4 1 (done)
// 4 2 (done)
// 4 3 (done)
// 4 4
// ...
