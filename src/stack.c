#include "stack.h"
#include "arrayList.h"
#include "graph.h"

#define HEAP_SIZE 120

/*
	Stack structure
		length - maximum length of the Stack
		top - position of the current top of the Stack
		array -  an array containing the values on the Stack
*/


/*
	Initialises a Stack of a given size
		returns a pointer to an initialised Stack
*/
struct stack* stackConstructor(){

    struct stack* stack;

    stack = malloc(sizeof(struct stack));
    stack->array =  malloc(HEAP_SIZE* sizeof(struct connection));
    stack->length = 0;
    stack->top = 0;
    stack->isSorted = 0;

    return stack;
}

struct connection* edgeConstructor(struct cityConnection* connection){
    struct connection* newConnection;

    // Reserve memory for a node
    newConnection = malloc(sizeof(struct connection));
    // Set its values
    strcpy(newConnection->name,connection->name);
    newConnection->edgeDistance = connection->srcDistance;
    newConnection->source = connection;
    // And return it
    return newConnection;

}


/*
	Frees the memory associated with the given pointer to a Stack
*/
void stackDestructor(struct stack* stack){

    free(stack->array);
    free(stack);

    stack = NULL;
}


/*
	Returns whether the given Stack is empty
		(1) yes, (0) no
*/
int isEmpty(struct stack* stack){

    if( stack->top == 0)
        return 1;
    else
        return 0;
}


/*
	Returns whether the given Stack is full
		(1) yes, (0) no
*/
int isFull(struct stack* stack){

    if( stack->top == stack->length)
        return 1;
    else
        return 0;
}


/*
	Push the given entity onto the given stack
		Returns whether the operation was successful: (1) yes, (0) no
*/
int push(struct stack* stack, struct connection* connection){

    //struct connection* newConnection;
    //newConnection = edgeConstructor(connection);
    //if( isFull(stack) ) {
      //  return 0;
    //}
    stack->array[stack->top] = *connection;
    stack->top++;
    stack->length++;

    return 1;
}


/*
	Pop the next value from the Stack
		Returns whether the operation was successful: (1) yes, (0) no

	If the operation is successful the entity popped from the stack is
	stored in the address provided by the entity argument
*/
struct connection* pop(struct stack* stack){

    if( isEmpty(stack) )
        return 0;

    stack->top--;
    stack->length--;
    struct connection* popAddress = &stack->array[stack->top];
    return popAddress;
}

/*
	Pop the next value from the tail of the Stack
		Returns whether the operation was successful: (1) yes, (0) no

	If the operation is successful the entity popped from the stack is
	stored in the address provided by the connection argument
*/
int dequeue(struct stack* stack, struct connection* connection){

    if( isEmpty(stack) )
        return 0;

    stack->tail++;
    *connection = stack->array[stack->tail];
    stack->length--;

    return 1;
}

/*
	Display the given Stack to the command prompt
*/
void display(struct stack* stack){

    int i;

    for(i=0; i<stack->top; i++) {
        printf("%s %d,", stack->array[i].name, stack->array[i].edgeDistance);
        }
    if (i == stack->top)
    {
        printf("\n");
    }

}


//Sort function to create Min Heap, whereby the shortest possible cost vertex is assured
struct stack* heapSort(struct stack* heap)
{
    int i;
    int sorted = 0; // Initially, the heap is not sorted
    while (heap->length != 1) {
        while (sorted == 0) {
            sorted = 1;
            for (i = 0; i < heap->length; i++) {
                if (heap->array[i].edgeDistance < heap->array[i - 1].edgeDistance) {
                    sorted = 0;
                    heapSwap(&heap->array[i], &heap->array[i - 1]);
                }
            }
        }
        heapSwap(&heap->array[heap->length - 1], &heap->array[0]);
        sorted = 0;
        heap->length--;
    }

    heap->length = heap->top;

}

//Function to swap positions of array members in the heap
void heapSwap(struct connection* a, struct connection* b)
{
    struct connection t = *a;
    *a = *b;
    *b = t;
}

