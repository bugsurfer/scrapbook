/* ==========  ========== ========== ========= */
//          Adjacency List Graph Data          //
//          Structure Implementation           //
//           in C using Linked List            //
//                                             //
//         Functions follow Pascal Case        //
//           Convention and Variables      	   //
//         follow Camel Case Convention        //
//                                             //
//            Author - Vamsi Sangam            //
//            Theory of Programming            //
/* ========== ========== ========== ========== */
 
#include <stdio.h>
#include <stdlib.h>
 
struct Edge {
    int vertex;
    struct Edge * next;
};

// Inserts Node to the Linked List by Head Insertion - O(1)
// Returns address of head which is the newly created node.
struct Edge * AddEdge(struct Edge * currentHead, int newVertex)
{
    struct Edge * newHead 
				 = (struct Edge *) malloc(sizeof(struct Edge));
 
    newHead->vertex = newVertex;
    newHead->next = currentHead;
 
    return newHead;
}

int main()
{
    int vertices, edges, i, v1, v2;
 
    printf("Enter the Number of Vertices -\n");
    scanf("%d", &vertices);
 
    printf("\nEnter the Number of Edges -\n");
    scanf("%d", &edges);
 
    struct Edge * adjacencyList[vertices + 1];
    // Size is made (vertices + 1) to use the
    // array as 1-indexed, for simplicity
 
    // Must initialize your array
    for (i = 0; i <= vertices; ++i) {
        adjacencyList[i] = NULL;
    }
 
    for (i = 1; i <= edges; ++i) {
        scanf("%d%d", &v1, &v2);
        
        // Adding edge v1 --> v2
        adjacencyList[v1] = AddEdge(adjacencyList[v1], v2);
		
		// Adding edge v2 --> v1
		// Remove this if you want a Directed Graph
        adjacencyList[v2] = AddEdge(adjacencyList[v2], v1);
    }
 
    // Printing Adjacency List
    printf("\nAdjacency List -\n\n");
    for (i = 1; i <= vertices; ++i) {
        printf("adjacencyList[%d] -> ", i);
 
        struct Edge * traverse = adjacencyList[i];
 
        while (traverse != NULL) {
            printf("%d -> ", traverse->vertex);
            traverse = traverse->next;
        }
 
        printf("NULL\n");
    }
 
    return 0;
}
