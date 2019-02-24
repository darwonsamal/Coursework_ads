#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


struct node
{
    char *move;

    struct node *link;
};

struct Queue
{
    struct node *front, *rear;
};


void initQueue(struct Queue **queue);
void enqueue(struct Queue **queue, char *move);
char * dequeue(struct Queue **queue);
void displayQueue(struct Queue *queue);
