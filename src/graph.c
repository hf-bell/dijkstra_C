#include "graph.h"
#include "arrayList.h"

struct city* cityConstructor(char name[25])
{
    struct city* newCity;

    // Reserve memory for a node
    newCity = malloc(sizeof(struct city));
    // Set its values
    newCity->next = NULL;
    newCity->prev = NULL;
    strcpy(newCity->name,name);
    newCity->connections = listConnectConstructor();
    newCity->distance = 0;

    // And return it
    return newCity;
}

void cityDestructor(struct city* city)
{
    free(city);

}

struct list* listConstructor()
{
    // Check we are using the right list implementation

    // Reserve memory for the list
    struct list* newCities;
    newCities = malloc(sizeof(struct list));

    // Initialise it appropriately
    newCities->size = 0;
    newCities->head = NULL;
    newCities->tail = NULL;


    // And return it
    return newCities;
}

void listDestructor(struct list* list)
{
    printf("Linked list destructor\n");

    // We need these to traverse the list
    struct city* currentRecord;
    struct city* nextRecord = list->head;

    // As long as the record to process exists
    while(nextRecord != NULL)
    {
        // Move to it
        currentRecord = nextRecord;

        // And update where to go next
        nextRecord = currentRecord->next;

        // And release the memory associated with this node
        cityDestructor(currentRecord);
    }

    // Now all of the nodes have been release so we can release the list too
    free(list);
}


int listSearch(struct list* list, char name[14])
{
    int i;
    printf("\n%s\n", name);
    struct city* city = list->tail;
    printf("\n%s\n", city->name);

    if (list->tail == NULL)
    {
        printf("no cities in list\n");
        return -1;
    }

    for (i = 0; i < list->size; i++)
    {
        if (strcmp(city->name,name) == 0)
        {
            return 1;
        }

        city = city->prev;
        printf("\n");
        printf("%s\n", city->name);
        printf("\n");
    }
    return -1;
}


int listGetIndex(struct list* list, char name[25])
{
    struct city* searchCity = list->tail;
    int index = 0;

    if (list->head == NULL)
    {
        printf("no cities in list\n");
        return -1;
    }

    for (index = 0; index < list->size; index++)
    {
        if (strcmp(searchCity->name,name) == 0)
        {
            return index;
        }

        searchCity = searchCity->prev;
    }
    return -1;



}


 //Add a new item to the end of the list
struct city* addVertex(struct list* list, char name[14])
{
    // Build our new node
    struct city* newCity = cityConstructor(name);
    // The node that will come before this node is currently the list tail
    // Note that this also works if the list is empty
    newCity->prev = list->tail;

    // And we will not have a next element
    newCity->next = NULL;

    // If the list is not empty
    if(list->tail != NULL)
    {
        // Tell the current tail that it now has a next element
        list->tail->next = newCity;

    }

    // And update the list to make the new node the tail
    list->tail = newCity;

    // List is empty
    if(list->head == NULL)
    {
        // So we are also the head
        list->head = newCity;
    }

    // Update the element count
    list->size++;


    // And indicate success
    return newCity;
}


int addEdge(struct city* city1, struct city* city2, int distance)
{

    addConnection(city2, city1, distance);
    addConnection(city1, city2, distance);

    //city1->connections->connections->srcDistance = distance;
    //city2->connections->connections->srcDistance = distance;

    return city1->connections->connections->srcDistance;

}


void listDisplay(struct list* list)
{
    // Start by printing an opening square bracket to denote the start of our list
    printf("[ ");

    // We start with the head of the list
    struct city* currentCity = list->head;

    // And print each element in turn until we are looking at NULL
    while(currentCity != NULL)
    {
        // Print a comma before the values after the first
        if(currentCity != list->head)
        {
            printf("\n");
        }

        // Print the current value
        printf("%s, with connections:\n", currentCity->name);
        listConnectDisplay(currentCity->connections);
        // Move to the next node
        currentCity = currentCity->next;
    }

    // Finally print a closing square bracket
    printf(" ]\n");
}


void cityDisplay(struct city* city)
{
    printf("This Vertex -> %s\n", city->name);
    printf("The next Vertex -> %s\n", city->next->name);
    printf("The last vertex -> %s\n", city->prev->name);
    printf("Distance -> %d\n", city->distance);

    //listDisplay(city->connections);
}





struct city* listGetCity(struct list* list, int index, int searchCity1, int searcHCity2)
{
    int i;
    // Sanity check the index
    if(index < 0 || index >= list->size)
    {
        printf("LISTGETCITY failed\n");
        // And indicate failure if it is invalid
        return NULL;

    }

        // We are closer to the end of the list so start at the tail and move backwards
        struct city* currentItem = list->head;

        // How many items should we move through?
        // If the index is size-1 then we move through 0 items
        // so we should move through (size-1) - index items
        int elementsToMoveThrough = (list->size - 1) - index;

        if (searchCity1 == -1 && searcHCity2 == 1)
        {
            elementsToMoveThrough = elementsToMoveThrough -1;
        }

        // Move through the elements in reverse
        for(i = 0; i < elementsToMoveThrough; i++)
        {
            // Make sure our links are not corrupt
            if(currentItem->next == NULL)
            {
                printf("LISTGETCITY current item has no next\n");
                // And indicate failure if they are
                return NULL;
            }

            // Otherwise move back through the list
            currentItem = currentItem->next;
        }

        // We have moved to the required element so can return it
         return currentItem;
}





