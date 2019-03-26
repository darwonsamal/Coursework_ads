/* Author: Darwon Rashid
Matric Number - 40280334
*/

// Libraries to be included for code.
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

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
void updateQueue(struct Queue **queue, char *board);



void initQueue(struct Queue **queue)
{
    *queue =  (struct Queue *)malloc(sizeof(struct Queue));
    
    (*queue)->front = NULL;
    (*queue)->rear = NULL;
    (*queue)->current = NULL;


}



void enqueue(struct Queue **queue, char *move)
{

    struct node* temp = (struct node *)malloc(sizeof(struct node));

    temp->move = move;

    
    if((*queue)->front == NULL)
    {   
       
        temp->next = temp->previous = temp;

        (*queue)->front = temp;
        
        (*queue)->rear = temp;

        (*queue)->rear->next = (*queue)->front;
      
        return;
        
    }
   
 
    temp->next = (*queue)->front;

    (*queue)->front->previous = temp;

    temp->previous = (*queue)->rear;

    (*queue)->rear->next = temp;

    (*queue)->rear = temp;
   
}


// Works but idk why or how
/*
void enqueue(struct Queue *queue, char *move)
{


    struct node* temp = (struct node *)malloc(sizeof(struct node));

    temp->move = move;


    if(queue->front == NULL)
    {   
       
        queue->front = temp;
    }
    else
    {
        queue->rear->next = temp;
    }

    queue->rear = temp;
    queue->rear->next = queue->front;
    
    
    
}

*/




char * dequeue(struct Queue **queue)
{
    
    if((*queue)->front == NULL)
    {
        printf("Queue is empty");
        return "";
    }

    char *move;

    if((*queue)->front == (*queue)->rear)
    {
        move = (*queue)->front->move;

        free((*queue)->front);

        (*queue)->front = NULL;

        (*queue)->rear = NULL;
    }
    else
    {
        struct node *temp = (*queue)->front;

        move = temp->move;

        (*queue)->front = (*queue)->front->next;

        (*queue)->rear->next = (*queue)->front;

        free(temp);
    }

    return move;

}


void displayQueue(struct Queue *queue)
{
    struct node *temp = queue->front;

    printf("\n Elements in Circular Queue are: ");

    while(temp->next != queue->front)
    {
       printf("%s", temp->move);
        temp = temp->next;
    }

    printf("%s", temp->move);
}

// FIX ISSUE WITH WHEN IF YOU DO REDO (one move done only) and then play new move, it overrides it, thinking no
// moves played
void updateQueue(struct Queue **queue, char *board)
{
    struct node *temp = (*queue)->current;

    
        printf("\n temp -> %s \n", temp->move);
        printf("\n temp -> %s \n", temp->previous->move);
        printf("\n temp -> %s \n", temp->next->move);

    struct node *next;

    //(temp->next == (*queue)->front)

    if( temp->next == NULL)
    {
      
        return;
    }

    temp = temp->next;

    while(temp->next != (*queue)->front)
    {
        
        next = temp->next;

        next->previous = temp->previous;

        //printf("\n TEMP MOVEE %s \n", next->previous->move);
        //printf("\n TEMP MOVEE %s \n", next->next->move);
        //printf("\n TEMP MOVEE %s \n", next->move);

        free(temp);
        temp = next;
    }


    if((*queue)->front != temp)
    {
          
        if((*queue)->front == temp->previous)
        {
            
            struct node *front = temp->previous;

            free(front);

            temp->previous = NULL;
            temp->next = NULL;

            free(temp);

            (*queue)->rear = NULL;
            (*queue)->front = NULL;
             
            (*queue)->current = NULL;

        
        }
        else
        {
            (*queue)->rear = temp->previous;
            (*queue)->rear->next = temp->next;

            free(temp);

            (*queue)->current = (*queue)->rear;
           
        }
        
    }
    else
    {   

        int checkIfOldMove = temp->move[0] - '0';

        if(board[checkIfOldMove - 1] == temp->move[0])
        {   
           
             
            temp->previous = NULL;
            temp->next = NULL;

            free(temp);
           
            (*queue)->rear = NULL;
            (*queue)->front = NULL;          
            (*queue)->current = NULL;


        }
       
        
    }
    
  
    
    
}



 /* //TESTING PURPOSE

int main()
{
    struct Queue *q;

    initQueue(&q);

    enqueue(&q, "2:X");

    enqueue(&q, "1:O");

    displayQueue(q);

   


}
*/

