// Jing Ming
// ming.j@northeastern.edu
// Implementation of a Social network using graphs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 /*structure represents a node to store the names and pointer to next node*/
typedef struct node{
    char name[50];
    struct node* next;
}node;

/* Structure represents a Graph with an array of adjacency lists. Size of the array will be number of vertices.*/
typedef struct Graph{
    int numberOfVertices;
    struct node** adjLists;
}Graph;

/*A function to create a newnode*/
node* createNode(char* name)
{
    node* newNode = (node*)malloc(sizeof(node));
    if (newNode != NULL) {
    	strcpy(newNode -> name, name); // remember to copy
    	newNode -> next = NULL;
    }
    return newNode;
}

/*A function to create a graph with an array of adjacency lists*/
Graph* createGraph(int vertices)
{
    Graph* newGraph = (Graph*)malloc(sizeof(Graph));
    if (newGraph != NULL) {
    	newGraph -> numberOfVertices = vertices;
        // Size of the array will be number of vertices
    	newGraph -> adjLists = (struct node**)malloc(vertices * sizeof(struct node*));
        if (newGraph->adjLists != NULL) {
        	int i;
        	for(i = 0; i < vertices; i++) {
        	    newGraph -> adjLists[i] = NULL; // initially, each list contains no elements
        	}
        }
    }
    return newGraph;
}

/* function to count Number of listspresent in the graph */
int numberoflistspresent(Graph* graph){
    int i, count = 0;
    for(i = 0; i < graph -> numberOfVertices; i++) {
        if (graph -> adjLists[i]) {
            count++;
        }
    }
    return count;
}

/*searching the persons who are already there in the list and return its position */
int search(char* name, Graph* graph)
{
   int p;
   for(p = 0; p < numberoflistspresent(graph); p++) {
        // strcmp() == 0 means two string are equal, >0 means larger, <0 means smaller
        if (strcmp(graph -> adjLists[p] -> name, name) == 0) {
            return p; // person is found at position p
        }
   }
   return -1; // when person is not found
}

/*adds an edge to an undirected graph*/
void addConnection(Graph* graph, char* person, char* friend){
    int n = numberoflistspresent(graph); // number of lists which already there
    int p = search(person, graph);//search for the person in the graph p-> position of person in the list

    //insert your code here
    if (n == 0) { // graph is empty, create person and friend
        node* personNode = createNode(person);
        graph -> adjLists[n] = personNode;
        node* friendNode = createNode(friend);
        personNode -> next = friendNode;
    } else { // graph is not empty
    	if (p == -1) { // person is not in the graph, create person and friend
    	    node* personNode = createNode(person);
    	    graph -> adjLists[n] = personNode;
    	    node* friendNode = createNode(friend);
    	    personNode -> next = friendNode;
    	} else { // person is in the graph
    	    node* pointer = graph->adjLists[p];
    	    while(pointer != NULL && pointer -> next != NULL) {
                if (strcmp(pointer->name, friend) == 0) {
                    return; // friend is already in the list
                } else {
                    pointer = pointer -> next;
                }
    	    }
    	    // friend is not in the list
    	    node* friendNode = createNode(friend);
    	    pointer -> next = friendNode;
    	}
    }
}

/*function to print the adjacency list representation of a graph*/
void printGraph(Graph* graph) {
    int i;
    for (i = 0; i < graph->numberOfVertices; i++) {
        //print the current vertex and all its neighbors
        struct node* temp = graph->adjLists[i];
        printf("\n%s---", graph->adjLists[i]->name);
        while((temp->next) != NULL) {
            printf("%s-", temp->next->name);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

/*   CONVERSION TO MATRIX*/
int getIndex(Graph* graph, char* name){
    int N = graph->numberOfVertices;
    int i, j = 0;
    for(i = 0; i < N && strcmp(name, graph->adjLists[i]->name) != 0; i++) {
        j++;
    }
    return j;
}

void matrixForm(Graph* graph, int emptyMatrix[50][50], int N) {
    int i,j;
    for(i = 0; i < N; i++){
        struct node* temp = graph->adjLists[i]->next;
        while (temp!= NULL) {
            j = getIndex(graph, temp->name);
            emptyMatrix[i][j] = 1;
            temp = temp->next;
        }
    }
}

void graphDestroy(Graph* graph){
    int i;
    for(i = 0; i < graph->numberOfVertices; i++){
        struct node* temp;
        while (graph->adjLists[i] != NULL) {
            temp = graph->adjLists[i];
            graph->adjLists[i] = temp->next;
            free(temp);
        }
    }
    free(graph->adjLists);
    free(graph);
}

void printMatrix(int matrix[50][50], Graph* graph)
{
    int row,col;
    int nodes = graph->numberOfVertices;
    printf("\nAdjacent matrix:\n");
    printf("        ");
    // print the column index, which is the name
    for (col = 0; col < nodes; col++){
        printf("%6s ", graph->adjLists[col]->name);
    }
    printf("\n");
    // print -----------------------------------
    for (col = 0; col < nodes; col++){
        printf("-------------");
    }
    printf("\n");
    // print matrix by row, each row contains `name| 0 1 0 0 1 ...`
    for (row = 0; row < nodes; row++) {
        printf("%7s| ", graph->adjLists[row]->name);
        for (col = 0; col < nodes; col++) {
            printf("  %2d    ", matrix[row][col]);
        }
        printf("\n");
    }
}


int main() {

    int Num=7;
    //construct a graph
    Graph* graph = createGraph(Num);
    if (graph == NULL) {
        printf("Error Allocating Memory.\n");
        exit(1);
    }

    addConnection(graph, "personA", "personB");
    addConnection(graph, "personA", "personG");
    addConnection(graph, "personA", "personE");
    addConnection(graph, "personB", "personA");
    addConnection(graph, "personB", "personE");
    addConnection(graph, "personB", "personC");
    addConnection(graph, "personB", "personG");
    addConnection(graph, "personC", "personB");
    addConnection(graph, "personC", "personD");
    addConnection(graph, "personC", "personE");
    addConnection(graph, "personD", "personC");
    addConnection(graph, "personD", "personE");
    addConnection(graph, "personD", "personF");
    addConnection(graph, "personE", "personA");
    addConnection(graph, "personE", "personB");
    addConnection(graph, "personE", "personC");
    addConnection(graph, "personE", "personD");
    addConnection(graph, "personE", "personF");
    addConnection(graph, "personE", "personG");
    addConnection(graph, "personF", "personE");
    addConnection(graph, "personF", "personG");
    addConnection(graph, "personF", "personD");
    addConnection(graph, "personG", "personB");
    addConnection(graph, "personG", "personA");
    addConnection(graph, "personG", "personE");
    addConnection(graph, "personG", "personF");

    //function to print the adjacency list representation of a graph
    printGraph(graph);

    /*Initialising adjacency matrix with values NULL*/
    int N = graph->numberOfVertices;
    int adj_matrix[50][50];
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            adj_matrix[i][j] = 0;
        }
    }
    matrixForm(graph, adj_matrix, N);
    printMatrix(adj_matrix, graph);
    graphDestroy(graph);
    return 0;
}
