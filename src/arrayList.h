#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct listConnect{
    int size;
    int capacity;
    struct cityConnection* connections;
    int isSorted;
};

struct cityConnection {
    char name[14];
    int srcDistance;
    struct city* city;
    struct city* sourceCity;
};

struct city;
struct listConnect* listConnectConstructor();
void listConnectDestructor(struct listConnect* list);
struct cityConnection* connectionConstructor(struct city* city1, struct city* city2, int distance);
void connectionDestructor(struct cityConnection* city);
void listResize(struct listConnect* list, int newSize);
struct cityConnection* addConnection(struct city* city1, struct city* city2, int distance);
int listConnectSearch(struct listConnect* list, char name[14]);
void listConnectDisplay(struct listConnect* list);
int listIsSorted(struct listConnect* list);
void listConnectBubbleSort(struct listConnect* list);
void swap(struct cityConnection* a, struct cityConnection* b);
int listRemove(struct listConnect* list, int index);


