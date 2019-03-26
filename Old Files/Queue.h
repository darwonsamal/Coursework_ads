#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 10

void enqueue(char ***arr, char *move, int *pfront, int *prear, int *current);
char * dequeue(char ***arr, int *pfront, int *prear);
char ** initQueue();
void updateQueue(char ***queue, int *front, int *rear, int *current, char *board);
void emptyQueue(char ***arr, int rear);