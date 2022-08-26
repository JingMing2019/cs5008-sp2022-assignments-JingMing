// name: Jing Ming
// email: ming.j@northeastern.edu
// Kruskal Algorithm - mine version

#include <stdio.h>
#include <stdlib.h> 		// for qsrot
#include <stdbool.h>		// for true, false
#define VSIZE 9
#define INF 99999

typedef struct Fedge { 		// F: edge set
	int weight;
	int u;
	int v;
} Fedge;

// Untility function to compare
int compare(const void *a, const void *b) {
	Fedge *m = (Fedge *)a;
	Fedge *n = (Fedge *)b;
	if (m->weight < n->weight) return -1; 	    // -1 when a < b
	if (m->weight > n->weight) return 1; 	     //  1 when a > b
	return 0; 				                     //  0 when a = b
}

int parent[VSIZE];
int edge_num = 0;

// Iniitalizing to create a set
void make_set(int n) {
	parent[n] = -1;
}

// Returning a set including v
int find_set(int v) {
	while (parent[v] >= 0) {
		v = parent[v];
	}
	return v;
}

void updateSet(int largerSetRoot, int smallerSetRoot) {
    parent[largerSetRoot] += parent[smallerSetRoot];
    // Set the parent of child and its child to root.
    parent[smallerSetRoot] = largerSetRoot;
    for (int k = 0; k < VSIZE; k++) {
        if (parent[k] == smallerSetRoot) {
            parent[k] = largerSetRoot;
        }
    }
}

// merge 2 sets
void union_set(int n1, int n2) {
    int root1 = parent[n1] < 0 ? n1 : parent[n1];
    int root2 = parent[n2] < 0 ? n2 : parent[n2];
    int i;

    if (parent[root1] <= parent[root2]) {
        updateSet(root1, root2);
    } else {
        updateSet(root2, root1);
    }

    printf("Union edge %d and edge %d. parent --> ", n1, n2);

    for (i = 0; i < VSIZE; ++i){
        printf("%3d", parent[i]);
    }
    printf("\n");
}

// Kruskal Algorithm
int kruskal(Fedge e[],int n) {
    int i, u, v;
    int mst_e = 0; 				    // min cost
    int mst_e_n = 0; 			    // # of edges for mst

    qsort(e, edge_num, sizeof(Fedge), compare); // sort edges using quick sort

    // Add Your code here
    for(v = 0; v < n; v++) {
        make_set(v);
    }
    // here use mst_e_n to terminate the for loop.
    for(i = 0; mst_e_n < n - 1; i++) {
        u = e[i].u;
        v = e[i].v;
        if(find_set(u) != find_set(v)) {
            mst_e += e[i].weight;
            mst_e_n++;  // to terminate the for loop, after n - 2 union step, the whole graph is connected.
            union_set(u, v);
        } else {
            printf("Edge %d and edge %d cause Cycle!!\n", u, v);
        }
    }
   return mst_e;
}

int main() {
    int mst;
    int graph[VSIZE][VSIZE] = { // input_graph, 2-dimensional array
	{   0,  4,INF,INF,INF,INF,INF,  8,INF},
	{   4,  0,  8,INF,INF,INF,INF, 11,INF},
	{ INF,  8,  0,  7,INF,  4,INF,INF,  2},
	{ INF,INF,  7,  0,  9, 14,INF,INF,INF},
	{ INF,INF,INF,  9,  0, 10,INF,INF,INF},
	{ INF,INF,  4, 14, 10,  0,  2,INF,INF},
	{ INF,INF,INF,INF,INF,  2,  0,  1,  6},
	{   8, 11,INF,INF,INF,INF,  1,  0,  7},
	{ INF,INF,  2,INF,INF,INF,  6,  7, 0 }};

    Fedge edge_set[INF];

    int i,j;

     // Add your code here to create edge_set
    // cause this is undirected, just visit half
    for(i = 0; i < VSIZE; i++) {
    	for(j = i; j < VSIZE; j++) {
    	    if (graph[i][j] != INF && graph[i][j] != 0) {
        		edge_set[edge_num].weight = graph[i][j];
        		edge_set[edge_num].u = i;
        		edge_set[edge_num].v = j;
        		edge_num++;
    	    }
    	}
    }

    mst = kruskal(edge_set, VSIZE);
    printf("Min cost is %d.\n", mst);
}
