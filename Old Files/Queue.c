/* Author: Darwon Rashid
Matric Number - 40280334
*/

// Libraries to be included for code.
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 10


char ** initQueue()
{
    char **array = malloc(MAX * sizeof(char*));

    for(int i = 0; i < MAX; i++)
    {
        array[i] = malloc(2 * sizeof(char) + 1);

    }

    return array;
}


void enqueue(char ***arr, char *move , int *pfront, int *prear, int *current)
{

    if(*prear == MAX)
    {
        printf("Queue is full\n");
        return;
    }
    else
    {

        if((*prear) < 0)
        {
            (*prear) = 0;
        }

      
        (*prear)++;
        (*arr)[*prear] = move;

        printf("%sQUEUE\n", (*arr)[*prear]);
        

        *current = *prear;

        if(*pfront == -1)
        {
            *pfront = 0;
        }
    }
    
}

int empty(int *pfront)
{

    if(*pfront == 1)
    {
        printf("Queue is empty\n");
        return 1;
    }
    else
    {
        return 0;
    }
    
}

void emptyQueue(char ***arr, int rear)
{

    printf("Emptying Queue\n");

    for(int i = 1; i < MAX; i++)
    {   

        (*arr)[i] = NULL;
        free((*arr)[i]);    
       
    }
   
    free((*arr));
}

char * dequeue(char ***arr, int *pfront, int *prear)
{
    char *data = (*arr)[*pfront];

    (*arr)[*pfront] = 0;

    if(*pfront == *prear)
    {
        *pfront = *prear = -1;
    }
    else
    {
        (*pfront)++;
    }
    
    return data;
    
}

void updateQueue(char ***queue, int *front, int *rear, int *current, char *board)
{

    if((*queue)[*current] == (*queue)[*rear])
    {
        return;
    }

    for(int i = *current + 1; i <= *rear; i++)
    {

        (*queue)[i] = "";

       
    } 

    *rear = *current;

    char checkCharPosition = (*queue)[*current][0];

    int checkPosition = checkCharPosition - '0';

   

    if((*queue)[*current] == (*queue)[*front] && board[checkPosition - 1] == checkCharPosition )
    {
        (*queue)[*current] = "";
        (*queue)[*front] = "";
        (*queue)[*rear] = "";

        *rear = -1;
        *current = 0;
        *front = 1;
    }

      
}