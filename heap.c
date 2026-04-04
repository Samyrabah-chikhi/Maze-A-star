#include "heap.h"

// Min-Heap for A* (open list)
point *openList[MAX_OPEN];
int openSize = 0;

// Swap two nodes in the heap
void swap(point **a, point **b)
{
    point *temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify up (used when inserting)
void heapifyUp(int index)
{
    while (index > 0 && openList[(index - 1) / 2]->fCost > openList[index]->fCost)
    {
        swap(&openList[index], &openList[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

// Heapify down (used when extracting min)
void heapifyDown(int index)
{
    while (1)
    {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < openSize && openList[left]->fCost < openList[smallest]->fCost)
            smallest = left;
        if (right < openSize && openList[right]->fCost < openList[smallest]->fCost)
            smallest = right;

        if (smallest != index)
        {
            swap(&openList[index], &openList[smallest]);
            index = smallest;
        }
        else
        {
            break;
        }
    }
}

// Add node to open list
void addOpen(point *node)
{
    if (openSize >= MAX_OPEN)
    {
        printf("Open list full!\n");
        return;
    }
    openList[openSize] = node;
    heapifyUp(openSize);
    openSize++;
}

// Extract node with lowest fCost
point *popLowestF()
{
    if (openSize == 0)
        return NULL;

    point *minNode = openList[0];
    openList[0] = openList[openSize - 1];
    openSize--;
    heapifyDown(0);
    
    return minNode;
}

// Check if open list is empty
int isOpenEmpty()
{
    return openSize == 0;
}

// Debug: print open list fCosts
void printOpenList()
{
    printf("Open list fCosts: ");
    for (int i = 0; i < openSize; i++)
        printf("%d ", openList[i]->fCost);
    printf("\n");
}