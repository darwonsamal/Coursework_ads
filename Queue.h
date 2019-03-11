#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 9

void enqueue(char ***arr, char *move, int *pfront, int *prear, int *current);
int empty(int *pfront);
char * dequeue(char ***arr, int *pfront, int *prear);
char ** initQueue();
void updateQueue(char ***queue, int *front, int *rear, int *current, char *board);