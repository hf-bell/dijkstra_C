#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct stack{
    int length;
    int top;
    int tail;
    struct connection* array;
    int isSorted;
};

struct connection{
    int edgeDistance;
    char name[25];
    struct cityConnection* source;
};


struct stack* stackConstructor();
void stackDestructor(struct stack* stack);
struct connection* edgeConstructor(struct cityConnection* connection);
int isEmpty(struct stack* stack);
int isFull(struct stack* stack);
int push(struct stack* stack, struct connection* connection);
struct connection* pop(struct stack* stack);
void display(struct stack* stack);
void heapSwap(struct connection* a, struct connection* b);
struct stack* heapSort(struct stack* heap);
void displayShortestPath(struct stack* stack);
