
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "graph.h"
#include "arrayList.h"
#include "stack.h"

#define MAX_DIST 2000

// Declare initial structure to store data from the text file
struct text_data {
    char city_1[25]; // First city in each line read from text file
    char city_2[25]; // Second city in each line read from text file
    int distance; // Distance between cities read from text file
};

// Declare counters to be used
int i = 0;
int j = 0;
int n = 0;
int p = 0;
int q = 0;
int r = 0;
int k = 0;
int l = 0;
int m = 0;

//Initialise array of structures to store text file data
struct text_data data_arr[50];

struct list* cityList;

//Declare pointer to file for text to be read from
FILE *fp;

//File for text to be written to
FILE *fw;

//Declare variables
int searchCity1;
int searchCity2;
struct city* addCity1;
struct city* addCity2;
int cityEdge;
int addCityIndex1;
int addCityIndex2;
struct city* bothAddedCity;
struct city* sourceNode;
struct city* destNode;
char scanSource[15];
char scanDest[15];
struct cityConnection* sourceConnection;
struct cityConnection* destConnection;
struct cityConnection* currentConnection;
int searchHeap;
struct connection* passToSPT;
struct connection* pushConnection;
struct connection* sourceHeap;
struct connection* printConnection;
int connectionFound;
int SPTmax;
int solutionWrite;


int main() {

    // Construct linked list to hold city nodes
    cityList = listConstructor();

    //Assign file pointer to the open text file containing city pairs data and relative distances
    fp = fopen("M:\Algorithms and Numerical Methods labs\Algorithms_codeblocks_final\graph_data.txt", "r");

    while (fscanf(fp, " %s %s %d ", &data_arr[i].city_1, &data_arr[i].city_2, &data_arr[i].distance) == 3) {

        printf("%s -> %s is %d\n", &data_arr[i].city_1, &data_arr[i].city_2, data_arr[i].distance);
        i++;

    }


    for (j = 0; j < 40; j++) {

        printf("\n");

        printf("%s -> %s is %d\n", &data_arr[j].city_1, data_arr[j].city_2, data_arr[j].distance);

        searchCity1 = listSearch(cityList, &data_arr[j].city_1);
        searchCity2 = listSearch(cityList, &data_arr[j].city_2);

        printf("searchCity1 = %d\n", searchCity1);
        printf("searchCity2 = %d\n", searchCity2);


        if (searchCity1 == 1) {
            addCityIndex1 = listGetIndex(cityList, &data_arr[j].city_1);

        }


        if (searchCity2 == 1) {
            addCityIndex2 = listGetIndex(cityList, &data_arr[j].city_2);

        }

        if (searchCity1 == -1 && searchCity2 == -1) {
            addCity1 = addVertex(cityList, data_arr[j].city_1);
            addCity2 = addVertex(cityList, data_arr[j].city_2);
            cityEdge = addEdge(addCity1, addCity2, data_arr[j].distance);
            printf("%d\n", cityEdge);
            //listDisplay(cityList);
        }

        if (searchCity1 == -1 && searchCity2 == 1) {
            addEdge(addVertex(cityList, data_arr[j].city_1),
                    listGetCity(cityList, addCityIndex2, searchCity1, searchCity2), data_arr[j].distance);
            printf("%d\n", cityEdge);
        }

        if (searchCity1 == 1 && searchCity2 == -1) {
            addEdge(listGetCity(cityList, addCityIndex1, searchCity1, searchCity2),
                    addVertex(cityList, data_arr[j].city_2), data_arr[j].distance);
            printf("%d\n", cityEdge);
        }

        if (searchCity1 == 1 && searchCity2 == 1) {
            addEdge(listGetCity(cityList, addCityIndex1, searchCity1, searchCity2),
                    listGetCity(cityList, addCityIndex2, searchCity1, searchCity2), data_arr[j].distance);
            printf("%d\n", cityEdge);
        }
    }

    listDisplay(cityList);

    // Construct new stack to hold heap
    struct stack *heap = stackConstructor();

    // Construct new stack to hold Shortest Path Tree
    struct stack *SPT = stackConstructor();


        // Scan user input source and destination nodes
        printf("\nEnter source node: ");
        //scanf("%s", scanSource);
        printf("Enter destination node:");
        //scanf("%s", scanDest);

        strcpy(scanSource, "Glasgow");
        strcpy(scanDest, "Oxford");

        // Create sourceNode corresponding to user input to put in heap
        sourceNode = listGetCity(cityList, listGetIndex(cityList, scanSource), -1, -1);
        destNode = listGetCity(cityList, listGetIndex(cityList, scanDest), -1, -1);


        // Create corresponding source connection structure so it can be pushed onto heap
        sourceConnection = connectionConstructor(sourceNode, sourceNode, 0);
        sourceHeap = edgeConstructor(sourceConnection);

        //destConnection = connectionConstructor(destNode, 0);

        push(heap, sourceHeap); // Push source onto heap


        for (n = 0; n < cityList->size; n++) {
            searchHeap = 0;
            sourceNode = heap->array[n].source->city;
            printf("%s\n", heap->array[n].source->city->name);


            for (k = 0; k < sourceNode->connections->size; k++) {
                searchHeap = 0;
                for (l = 0; l < heap->length; l++) {

                    // If node added is already in heap
                    if (strcmp(heap->array[l].name, sourceNode->connections->connections[k].name) == 0) {
                        searchHeap = 1;
                    }
                }

                if (searchHeap != 1) {
                    pushConnection = edgeConstructor(&sourceNode->connections->connections[k]);
                    push(heap, pushConnection);
                    heap->array[heap->top -
                                1].edgeDistance = MAX_DIST; // Initially, for all vertices apart from the source,
                    printf("%s , %d\n", heap->array[k].name, heap->array[k].edgeDistance); // set distance to infinite
                }
            }

        }
        printf("%s\n", sourceNode->connections->connections[n].name);

        heapSort(heap); // Sort heap so source node is at root
        passToSPT = pop(heap); // Pop source node from Min Heap
        push(SPT, passToSPT); // Push source node to Shortest Path Tree

        passToSPT->source->city->isVisited = 1; // Mark node as visited

        currentConnection = sourceConnection; // Update current connection we are looking at to be source connection

        display(SPT);


        while (p < currentConnection->city->connections->size) {

            for (q = 0; q <= heap->length; q++) {

                if (p >= currentConnection->city->connections->size) {
                    break;
                }

                connectionFound = 0;
                if (strcmp(currentConnection->city->connections->connections[p].name, heap->array[q].name) == 0) {
                    // Find the edge weight(u,v)
                    for (m = 0; m < SPT->length; m++) {
                        // Iterate through Shortest Path Tree to find edge that current node is connected to
                        if (strcmp(SPT->array[m].name, currentConnection->name) == 0) {
                            // If distance to node from current node is shorter than that held in heap
                            if (currentConnection->city->connections->connections[p].srcDistance +
                                SPT->array[m].edgeDistance <= heap->array[q].edgeDistance) {
                                heap->array[q].edgeDistance =
                                        currentConnection->city->connections->connections[p].srcDistance +
                                        SPT->array[m].edgeDistance; // update distance

                                connectionFound = 1;
                            }
                            connectionFound = 1;
                        }

                    }

                }

                if (connectionFound == 1) { // If an edge has been found in heap
                    p++; // Move onto next source connection
                    q = 0; // Reset index in heap so that every heap node is searched

                } else if (connectionFound == 0 && q == heap->length -
                                                        1) { // If whole heap has been searched and connection does not exist in heap
                    p++; // Move onto next connection in Source connections list
                    q = 0; // Reset heap index
                } else if (SPT->length >= 21) { // If every node has been added to the Shortest Path Tree
                    SPTmax = 1; // Update value to break out of loop performing Dijkstra's Algorithm
                }


            }

            if (SPTmax != 1) { // As long as SPT is not full

                heapSort(heap); // Perform heap sort to move minority nodes to top of heap
                currentConnection->city->isVisited = 1;

                if (destNode->isVisited == 1)// If we are at the destination
                {
                    break; // stop searching the heap
                }

                passToSPT = pop(heap); // Pop shortest path from heap
                push(SPT, passToSPT); // Push shortest path onto SPT
                currentConnection = SPT->array[SPT->top -
                                               1].source; // Update the connection we are searching edges from
                p = 0;
                q = 0;  // Reset counter values
                display(SPT);


            } else if (SPTmax == 1) {
                break; // Break out of Dijkstra's algorithm loop
            }

        }

        if (destNode->isVisited == 0) // If whole heap has been searched and destination node has not been found
        {
            printf("Destination is unreachable by network\n");
        }


        display(SPT);

        //Clear file and close
        fw = fopen("M:\Algorithms and Numerical Methods labs\Algorithms_codeblocks_final\algorithms_shortest_path_write1.txt", "w");
        fclose(fw);

        //Re-open file and set to append to add print statements to file
        fw = fopen("M:\Algorithms and Numerical Methods labs\Algorithms_codeblocks_final\algorithms_shortest_path_write.txt", "a");
        fprintf(fw, "\nDistance from %s -> %s is %d km\n", SPT->array[0].name, SPT->array[SPT->top - 1].name,
                SPT->array[SPT->top - 1].edgeDistance);
        printf("\nDistance from %s -> %s is %d km\n", SPT->array[0].name, SPT->array[SPT->top - 1].name,
               SPT->array[SPT->top - 1].edgeDistance);
        printConnection = &SPT->array[SPT->length - 1];
        for (r = SPT->top; r >= 0; r--) {
            if (strcmp(printConnection->source->sourceCity->name, SPT->array[r].name) == 0) {
                fprintf(fw, "%s <- ", printConnection->name);
                printf("%s <- ", printConnection->name);
                printConnection = &SPT->array[r];

                if (strcmp(printConnection->source->sourceCity->name, printConnection->name) == 0) {
                    fprintf(fw, "%s", printConnection->name);
                    printf("%s", printConnection->name);
                    break;
                }
            }


        }
}
