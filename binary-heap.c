/* ==========  ========== ========== ========= */
//        Binary Min Heap Data Structure       //
//           Array Implementation              //
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

struct Vertex
{
	int label, value;
};

// Adds an element to the heap and returns the size - O(log N)
int EnqueueVertex(struct Vertex minHeap[], int size, struct Vertex newValue)
{
    ++size;
    minHeap[size] = newValue;
 
    int i = size;
	struct Vertex temp;
 
    while (i >= 1) {
        if (minHeap[i / 2].value > minHeap[i].value) {
            // Parent node is greater than Child Node
            // Heap Property violated
            // So, swap
            temp = minHeap[i / 2];
            minHeap[i / 2] = minHeap[i];
            minHeap[i] = temp;
 
            i = i / 2;
        } else {
            // Parent is less or equal to the child
            // Heap property not violated
            // So, Insertion is done, break
            break;
        }
    }
 
    return size;
}

// Applies the heapify procedure - O(log N)
void Heapify(struct Vertex minHeap[], int size, int index)
{
    int i = index;
	struct Vertex temp;
 
    while ((2 * i) <= size) {
        // Left Child exists
 
        if ((2 * i) + 1 > size) {
            // Right child does not exist, but left does
            
			if (minHeap[i].value > minHeap[2 * i].value) {
                // Left child is smaller than parent
                temp = minHeap[i];
                minHeap[i] = minHeap[2 * i];
                minHeap[2 * i] = temp;
            }
            
            break;
            // Once you reach this level where it does not
        	// have a right child, the heap ends here
            // taking it to the next iteration is pointless
        }
 
        //Both Children exist
        if (minHeap[i].value > minHeap[2 * i].value || minHeap[i].value > minHeap[2 * i + 1].value) {
            // One of the other child is lesser than parent
            // Now find the least amoung 2 children
 
            if (minHeap[2 * i].value <= minHeap[(2 * i) + 1].value) {
                // Left Child is lesser, so, swap
                temp = minHeap[2 * i];
                minHeap[2 * i] = minHeap[i];
                minHeap[i] = temp;
 
                // And go down the heap
                i = 2 * i;
            } else if (minHeap[2 * i].value > minHeap[(2 * i) + 1].value) {
                // Left Child is lesser, so, swap
                temp = minHeap[(2 * i) + 1];
                minHeap[(2 * i) + 1] = minHeap[i];
                minHeap[i] = temp;
 
                // And go down the heap
                i = (2 * i) + 1;
            }
        } else {
            // Parent is lesser than its children
            break;
        }
    }
}

// Deletes the vertex and returns the size - O(log N)
int DeleteVertex(struct Vertex minHeap[], int size, int index)
{
    // Swap the indexed element with the last
    struct Vertex temp = minHeap[index];
    minHeap[index] = minHeap[size];
    minHeap[size] = temp;
 
    int i = index;
    --size;
 
 	// check conditions
 	struct Vertex swappedElement = minHeap[index];
 	struct Vertex parent = minHeap[index / 2];
 	
 	if (swappedElement.value > parent.value || i == 1) {
 		// Second condition states that, if the node is the
		// root, then simply apply heapify as we don't need to
		// bubble the node up in any case
 		Heapify(minHeap, size, index);
	} else {
	 	while (minHeap[index].value < minHeap[index / 2].value && index != 0) {
	 		temp = 	minHeap[index];
	 		minHeap[index] = minHeap[index / 2];
	 		minHeap[index / 2] = temp;
	 		
			index /= 2;
		}
	}
 	
    return size;
}

// Build Heap Procedure - O(N)
void BuildHeap(struct Vertex minHeap[], int size)
{
    int i;
 
    // Simply call heapify() for all nodes
    // except the last one...!
    for (i = size / 2; i >= 1; --i) {
        Heapify(minHeap, size, i);
    }
}
 
int main()
{
    int n, i;
 
    printf("Enter the Initial size of the Min Heap -\n");
 
    scanf("%d", &n);
 
    struct Vertex minHeap[n + 2];
    // Extra size just to demonstrate Insertion
    // and use the array as 1-indexed
    
    printf("Enter %d elements -\n", n);
 
    for (i = 1; i <= n; ++i) {
        scanf("%d%d", &minHeap[i].label, &minHeap[i].value);
    }
 
    BuildHeap(minHeap, n);
 
    printf("\nHeap -\n");
    for (i = 1; i <= n; ++i) {
        printf("%d, %d\n", minHeap[i].label, minHeap[i].value);
    }
 
	struct Vertex node;
	
    printf("\n\nInsert an element -\n");
    scanf("%d%d", &node.label, &node.value);
    n = EnqueueVertex(minHeap, n, node);
 
    printf("\nHeap After Insert -\n");
    for (i = 1; i <= n; ++i) {
        printf("%d, %d\n", minHeap[i].label, minHeap[i].value);
    }
 
    printf("\n\nDelete an Element at index-\n");
    scanf("%d", &i);
    n = DeleteVertex(minHeap, n, i);
 
    printf("\nHeap After Delete -\n");
    for (i = 1; i <= n; ++i) {
        printf("%d, %d\n", minHeap[i].label, minHeap[i].value);
    }
 
    return 0;
}
