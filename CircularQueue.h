#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


struct node
{
    char *move;

    struct node *next;
    struct node *previous;
};

struct Queue
{
    struct node *front, *rear, *current;
};


void initQueue(struct Queue **queue);
void enqueue(struct Queue **queue, char *move);
char * dequeue(struct Queue **queue);
void displayQueue(struct Queue *queue);
