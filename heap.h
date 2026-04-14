#ifndef HEAP_H
#define HEAP_H

#include "helper.h"

// max number of nodes in open list
#define MAX_OPEN 1000

void swap(point **a, point **b);
void heapifyUp(int index);
void heapifyDown(int index);
void addOpen(point *node);
point *popLowestF();
int isOpenEmpty();
void printOpenList();
void clearOpen();

#endif