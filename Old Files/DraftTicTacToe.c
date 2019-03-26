
            /*

            if(queue->current != queue->rear)
            {

                printf("\n BACCCCKKKKKK \n");
                redoMove(&queue, &board, &totalMoves);

                playerTurn++;
            }
            else if(queue->current == queue->front && queue->current == queue->rear)
            {
                printf("\n BACCCCKKKKKK 22 \n");
                redoMove(&queue, &board, &totalMoves);

                playerTurn++;
            }
            else
            {
                printf("\n BACCCCKKKKKK 3 %s \n", queue->current->move);

                redoMove(&queue, &board, &totalMoves);
                


            }
            */
            


            


// FOR CIRCULAR QUEUE


/*

char * generateGameBoard(struct Queue *queue)
{
    char * board = "123456789";

    if(queue->front == NULL || queue->rear == NULL)
    {
        return board;
    }

    struct node *temp = queue->rear;  

    char position = temp->move[0];

       // printf("\n -- position --%c\n", position);

    char move = temp->move[2];

        //printf("\n -- move --%c\n", move);      

    int comparePosition = position - '0';

        //printf("%d\n", comparePosition);

    board[comparePosition - 1] = move;

    printf(board);
    return board;
    
}*/

/*
void undoMove(struct Queue **queue, char **board, char **totalMoves)
{

    //temp node for assignment 
    struct node *temp;

    int flag = 1;


    
    // if empty then do nothing
    if((*queue)->front == NULL || (*queue)->rear == NULL)
    {
        return;
    }

  
    char checkCharPosition = (*queue)->current->move[0];
    //convert it to integer
    int checkPosition = checkCharPosition - '0';

    if((*queue)->current == (*queue)->front && (*board)[checkPosition - 1] == checkCharPosition)
    {
        return;
    }

    // if undo has not been done in game yet then initialize it 
    if((*queue)->current == NULL)
    {

        //make it the last move played as current
        (*queue)->current = (*queue)->rear;

        //set temp as current

        temp = (*queue)->current;
         

    }
    else // else then set temp to current
    {
        temp = (*queue)->current;

        
     
       
        
    }

    int checkIfOldMove = temp->move[0] - '0';

    if((*board)[checkIfOldMove - 1] == temp->move[0])
    {   
            
        temp = temp->previous;  

        
    char *redoMove = "";

    strcpy(redoMove, temp->move);

    redoMove[2] = redoMove[0];

    (*totalMoves) = concat((*totalMoves), redoMove);
    (*totalMoves) = concat((*totalMoves), "\n");

        (*queue)->current = temp;


    }

    // get position of the move played
    char charPosition = temp->move[0];
    //convert it to integer
    int position = charPosition - '0';
    //set board position to empty (which is the number of the position);
    (*board)[position - 1] = charPosition;


    char *redoMove = "";

    strcpy(redoMove, temp->move);

    redoMove[2] = redoMove[0];

    (*totalMoves) = concat((*totalMoves), redoMove);
    (*totalMoves) = concat((*totalMoves), "\n");
    
    // if back to original state (empty) then do not update current for there is no more undos to do
    if(temp->previous == NULL || temp->previous == (*queue)->rear)
    {

        printf("ENNETERED\n");
        return;
    }

   

    //update current so it is the previous node which means the next old move played
   
    (*queue)->current = temp->previous;
   
    

    
    
}

void redoMove(struct Queue **queue, char **board, char **totalMoves)
{
    //temp node for assignment 
    struct node *temp;

    // flag to check it current needs updating in certain cases
    int flag = 1;

    char checkCharPosition = (*queue)->current->move[0];
  
    int checkPosition = checkCharPosition - '0';

    if((*queue)->current == (*queue)->rear && (*board)[checkPosition - 1] == (*queue)->current->move[2])
    {

        return;
    }

    // if queue is empty then return and do nothing
    if((*queue)->front == NULL || (*queue)->rear == NULL)
    {    
        return;
    } // else checking if current node is front
    else if((*queue)->current == (*queue)->front)
    {

        temp = (*queue)->current;

        printf("\n temp -> %s \n", temp->move);
        printf("\n temp -> %s \n", temp->previous->move);
        printf("\n temp -> %s \n", temp->next->move);

        // CHECK TO see if current (which is front) needs redo or is it the next node that needs redo
        int checkIfOldMove = temp->move[0] - '0';

           printf("\n temp -> %c \n", temp->move[0]);
              printf("\n temp -> %c \n", (*board)[checkIfOldMove - 1]);
        // check to see if a move is played at this current node, if so then we redo the next one and not this one
        if((*board)[checkIfOldMove - 1] != temp->move[0])
        {   

             printf("\n temp -> %s \n", temp->move);
        printf("\n temp -> %s \n", temp->previous->move);
        printf("\n temp -> %s \n", temp->next->move);
            
            temp = temp->next;

            //raise flag so that current is updated correctly
            flag = 0;
        }

        // checking position
        char charPosition = temp->move[0];

        //convert to char
        int position = charPosition - '0';

        //redo empty position with the move 
        (*board)[position - 1] = temp->move[2];


        char *redoMove = "";

        strcpy(redoMove, temp->move);

        (*totalMoves) = concat((*totalMoves), redoMove);
        (*totalMoves) = concat((*totalMoves), "\n");
        
        

        // if current node is not updated then do so
        if(flag == 1)
        {

            printf("FOund you bug 2");

            
           
            (*queue)->current = temp->next;
        }
        else // this means the current node did not need redo and the one after it did, and since we updated
        {    // the next move anyways we do not update current to the next state but the one we just redid
             // so the next time we do redo, we do not skip the next state.

           
            (*queue)->current = temp;
        }
        
        
    }// current node is not in the front of the queue
    else
    {

        temp = (*queue)->current;

          printf("\n temp -> %s \n", temp->move);
        printf("\n temp -> %s \n", temp->previous->move);
        printf("\n temp -> %s \n", temp->next->move);

        int checkIfOldMove = temp->move[0] - '0';

        // checking if current node has redone already by seeing if it is empty
        if((*board)[checkIfOldMove - 1] == temp->move[0])
        {   
            // if not update it with the move

            char charPosition = temp->move[0];       

            int position = charPosition - '0';

            (*board)[position - 1] = temp->move[2];

            char *redoMove = "";

            strcpy(redoMove, temp->move);

            (*totalMoves) = concat((*totalMoves), redoMove);
            (*totalMoves) = concat((*totalMoves), "\n");



        }
        else
        {
            // then what we have to redo is the next node and we do so here
            char charPosition = temp->next->move[0];

            int position = charPosition - '0';

            (*board)[position - 1] = temp->next->move[2];

            char *redoMove = "";

            strcpy(redoMove, temp->next->move);

            (*totalMoves) = concat((*totalMoves), redoMove);
            (*totalMoves) = concat((*totalMoves), "\n");


            // if we in the end of the queue(rear) this means we got no more moves to redo so we return or check if queue is empty
            if((*queue)->current->next == (*queue)->front)
            {   
               
                return;
            }   

            // update current to the next node 
            (*queue)->current = temp->next;

        }

    }

     printf("\n temp -> %s \n", (*queue)->current->move);
        printf("\n temp -> %s \n", (*queue)->current->previous->move);
        printf("\n temp -> %s \n", (*queue)->current->next->move);
    
  
}
*/