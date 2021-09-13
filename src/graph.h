#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct city {
    char name[14];
    struct city* next;
    struct city* prev;
    struct listConnect* connections;
    int distance;
    int isVisited;
};

struct list{
    int size;
    struct city* head;
    struct city* tail;
};

struct city* cityConstructor(char name[14]);
void cityDestructor(struct city* city);
struct list* listConstructor();
void listDestructor(struct list* list);
int listSearch(struct list* list, char name[14]);
int listGetIndex(struct list* list, char name[25]);
struct city* addVertex(struct list* list, char name[14]);
int addEdge(struct city* city1, struct city* city2, int distance);
void listDisplay(struct list* list);
void cityDisplay(struct city* city);
struct city* listGetCity(struct list* list, int index, int searchCity1, int searchCity2);

