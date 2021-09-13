#include "arrayList.h"
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_LIST_CAPACITY 128



// Reserves and initialises memory for a new list
struct listConnect* listConnectConstructor()
{
    // The value we will return. This is a pointer to a List structure.
    struct listConnect* arrayList;

    // Reserve memory for the list structure and for the elements we want to store
    arrayList = malloc(sizeof(struct listConnect));
    arrayList->connections = malloc(ARRAY_LIST_CAPACITY*sizeof(struct cityConnection));

    // Set sensible default values
    arrayList->capacity = ARRAY_LIST_CAPACITY;
    arrayList->size = 0;
    arrayList->isSorted = 0;

    // And return the created list
    return arrayList;
}

void listConnectDestructor(struct listConnect* list)
{
    // Free the memory where entities are stored
    // This must happen before we release the list structure memory
    free(list->connections);

    // Now we can free the list itself
    free(list);
}

struct cityConnection* connectionConstructor(struct city* city1, struct city* city2, int distance)
{
    struct cityConnection* newConnection;

    // Reserve memory for a node
    newConnection = malloc(sizeof(struct cityConnection));
    // Set its values
    strcpy(newConnection->name,city1->name);
    newConnection->srcDistance = distance;
    newConnection->city = city1;
    newConnection->sourceCity = city2;
    // And return it
    return newConnection;
}

void connectDestructor(struct cityConnection* city)
{
    free(city);

}

void listResize(struct listConnect* list, int newSize)
{
    // The list is already big enough to store the number of elements requested
    if(newSize <= list->capacity)
    {
        // In this case do nothing
        return;
    }

    // Otherwise reallocate the connections array
    list->connections = realloc(list->connections, newSize * sizeof(list->connections));

    // And update our capacity
    list->capacity = newSize;
}


// Add a new element to our list
struct cityConnection* addConnection(struct city* city1, struct city* city2, int distance)
{
    struct cityConnection* newConnection = connectionConstructor(city2,city1,distance);
    int searchConnection;
    //if (searchConnection == 1)
    //{
      //  listRemove(list, listGetIndex(list, city->name));

    //}

     //If our list is already full then we cannot add a new item
    if(city1->connections->size >= city1->connections->capacity)
    {
        listResize(city1->connections, city1->connections->capacity * 2);
    }
    // Set the slot of the next free entity to the value we are given
    // If we current have 0 elements stored then we save in slot 0 and so on

        city1->connections->connections[city1->connections->size] = *newConnection;


    city1->connections->size++; // Update our entity count



    return newConnection;
}




int listRead(struct listConnect* list, int index, struct cityConnection* connection)
{
    // If the requested index is invalid then return 0 to indicate failure
    if(index < 0 || index >= list->size)
    {
        return 0;
    }

    // Otherwise set entity to the requested element
    *connection = list->connections[index];

    // And return 1 to indicate success
    return 1;
}


void listConnectDisplay(struct listConnect* list)
{
    int i;
    listConnectBubbleSort(list);

    // Start by printing an opening square bracket to denote the start of our list
    printf("\n[");

    // We know that our list is filled from element 0 to element list->numEntities
    // so we can simply iterate over those values and print them
    for(i = 0; i < list->size; i++)
    {
        // Print a comma before the value after element 0
        //if(i > 0)
        //{
          //  printf(",");
        //]

        // Print the current value
        printf(" %s", list->connections[i].name);
        printf(" %d ", list->connections[i].srcDistance);

    }

    // Finally print a closing square bracket
    printf(", Total list size: %d ]\n", list->size);

}


void listConnectBubbleSort(struct listConnect* list)
{
    int i;

    if(listIsSorted(list) == 1)
    {
        return;
    }

    // Ensure that we enter the while loop below
    int sorted = 0;

    while(sorted == 0)
    {
        // Assume the list is sorted
        sorted = 1;

        // Check each pair of elements in turn
        for(i = 1; i < list->size; i++)
        {
            // If we find one out of order
            if(list->connections[i-1].srcDistance > list->connections[i].srcDistance)
            {
                // Mark our array array as not sorted
                sorted = 0;

                // And put the elements in the correct position
                swap(&list->connections[i-1], &list->connections[i]);
            }
        }
    }

    list->isSorted = 1;
}


int listIsSorted(struct listConnect* list)
{
    return list->isSorted;
}

// Swap 2 the integer values stored in 2 provided addresses
void swap(struct cityConnection* a, struct cityConnection* b)
{
    struct cityConnection t = *a;
    *a = *b;
    *b = t;
}

int listRemove(struct listConnect* list, int index)
{
    // If the index is invalid then do nothing
    if(index < 0 || index >= list->size)
    {
        return 0;
    }

    // memmove takes the address to move data to, the address to take data from
    // and the number of bytes to move. The number of bytes is given by
    // (number of elements)*sizeof(element type)
    int elementCount = list->size - index;
    memmove(&list->connections[index], &list->connections[index+1], elementCount * sizeof(struct cityConnection));

    // Now update the number of elements in our list
    list->size--;

    return 1;
}

int listConnectSearch(struct listConnect* list, char name[14])
{
    int i;
    // Check each occupied element in the list in turn
    for(i = 0; i < list->size; i++)
    {
        // If the current element matches the requested one
        if(strcmp(list->connections[i].name, name) == 0)
        {
            // Return its index
            return 1;
        }
    }

    // If we didn't execute the return in the loop above then the
    // entity was not found. In this case we return -1.
    return -1;
}

