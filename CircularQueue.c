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
       
        (*queue)->front = temp;
        
    }
    else
    {
        (*queue)->rear->next = temp;
       
    }

    temp->previous = (*queue)->rear;

    (*queue)->rear = temp;

    (*queue)->rear->next = (*queue)->front;
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
        printf("%s\n", temp->move);
        temp = temp->next;
    }

    printf("%s", temp->move);
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
