/* ==========  ========== ========== ========= */
//             Binary Min Heap based           //
//         Priority Queue Data Structure       //
//                                             //
//         Functions follow Pascal Case        //
//           Convention and Variables      	   //
//         follow Camel Case Convention        //
//        The Data Structure is 1-indexed      //
//											   //
//            Author - Vamsi Sangam            //
//            Theory of Programming            //
/* ========== ========== ========== ========== */
 
#include <stdio.h>
#include <stdlib.h>

struct Vertex
{
	int label, value;
};

// Applies the heapify procedure - O(log N)
void Heapify(struct Vertex minHeap[], int size, int index, int hashTable[])
{
    int i = index;
	struct Vertex temp;
 
    while ((2 * i) <= size) {
        // Left Child exists
 
        if ((2 * i) + 1 > size) {
            // Right child does not exist, but left does
            
			if (minHeap[i].value > minHeap[2 * i].value) {
				hashTable[minHeap[i].label] = 2 * i;
				hashTable[minHeap[2 * i].label] = i;
				
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
 
        // Both Children exist
        if (minHeap[i].value > minHeap[2 * i].value || minHeap[i].value > minHeap[2 * i + 1].value) {
            // One of the other child is lesser than parent
            // Now find the least amoung 2 children
 
            if (minHeap[2 * i].value <= minHeap[(2 * i) + 1].value) {
                hashTable[minHeap[i].label] = 2 * i;
				hashTable[minHeap[2 * i].label] = i;
				
				// Left Child is lesser, so, swap
                temp = minHeap[2 * i];
                minHeap[2 * i] = minHeap[i];
                minHeap[i] = temp;
 
                // And go down the heap
                i = 2 * i;
            } else if (minHeap[2 * i].value > minHeap[(2 * i) + 1].value) {
                hashTable[minHeap[i].label] = 2 * i + 1;
				hashTable[minHeap[2 * i + 1].label] = i;
				
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
int DeleteVertex(struct Vertex minHeap[], int size, int index, int hashTable[])
{
    hashTable[minHeap[index].label] = size;
	hashTable[minHeap[size].label] = index;
	
	// Swap the indexed element with the last
    struct Vertex temp = minHeap[index];
    minHeap[index] = minHeap[size];
    minHeap[size] = temp;
 
    int i = index;
    --size;
 
    Heapify(minHeap, size - 1, i, hashTable);
 
    return size;
}

// Build Heap Procedure - O(N)
void BuildHeap(struct Vertex minHeap[], int size, int hashTable[])
{
    int i;
 
    // Simply call heapify() for all nodes
    // except the last one...!
    for (i = size / 2; i >= 1; --i) {
        Heapify(minHeap, size, i, hashTable);
    }
}

// Searches for a Node in the Heap in O(1) time and Decreases its value
// Then calls Heapify() on it's parent to adjust heap -> totally takes O(log N) time
void DecreaseKey(struct Vertex minHeap[], struct Vertex newNode, int hashTable[])
{
	minHeap[hashTable[newNode.label]].value = newNode.value;
	
	int i = hashTable[newNode.label];
	struct Vertex temp;
 
    while (i > 1) {
        if (minHeap[i / 2].value > minHeap[i].value) {
            hashTable[minHeap[i].label] = i / 2;
			hashTable[minHeap[i / 2].label] = i;
			
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
}

// Removes and Returns the topmost element - O (log N)
struct Vertex ExtractMin(struct Vertex minHeap[], int size, int hashTable[])
{
	hashTable[minHeap[1].label] = size;
	hashTable[minHeap[size].label] = 1;
	
	struct Vertex min = minHeap[1];
	
	minHeap[1] = minHeap[size];
	--size;
	Heapify(minHeap, size, 1, hashTable);
	
	return min;
}
 
int main()
{
    int n, i;
 	
    scanf("%d", &n);
 	
    struct Vertex minHeap[n + 1];	// To use the array as 1-indexed
    
    // Stores the location of Vi in hashTable[i] 
    int hashTable[n + 1];	// To use the array as 1-indexed
 	
    for (i = 1; i <= n; ++i) {
        scanf("%d%d", &minHeap[i].label, &minHeap[i].value);
        hashTable[i] = minHeap[i].label;
    }
 	
    BuildHeap(minHeap, n, hashTable);
    
	struct Vertex node;
	
    // Demonstrating Decrease Key
    scanf("%d", &node.label);	// Vertex
    scanf("%d", &node.value);	// New Value of vertex
    
    DecreaseKey(minHeap, node, hashTable);
    
    // Demonstrating Extract Min
    node = ExtractMin(minHeap, n, hashTable);	// 1-indexed
    printf("\n\nExtract Min - Vertex = %d, Value = %d\n", node.label, node.value);
    --n;
    
    printf("\n\nHeap After Extract Min -\n");
    for (i = 1; i <= n; ++i) {
        printf("minHeap[%d] => Vertex = %d, Value = %d\n", i, minHeap[i].label, minHeap[i].value);
    }
 	
    return 0;
}
