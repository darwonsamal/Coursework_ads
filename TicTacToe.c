/* Author: Darwon Rashid
Matric Number - 40280334
*/

// Libraries to be included for code.
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Queue.h"

#define MAX 9

//path
// C:\Users\darwo\Desktop\All Workspace\Workspace\C and C++ Workspace\Data Structures and Algortihms\Coursework

// METHODS
//char * renderGameBoard();
//char * saveGameBoard();

char * concat(const char *string1, const char *string2);
void displayBoard(char *board);
void showHelp();
void input(char **choice);
void removeNewline(char **str);
void saveToFile(char *totalMoves);
void loadFile(char *fileName);

int checkValidMove(char *move, char *board);
int checkIfGameIsWon(char *board);

//char * generateGameBoard(struct Queue *queue);
//void undoMove(struct Queue **queue, char **board, char **totalMoves);
//void redoMove(struct Queue **queue, char **board, char **totalMoves);

void generateGameBoard(char ***queue, char **board, int rear);
void undoMove(char ***queue, int *front, int *rear, int *current, char **board, char **totalMoves);
void redoMove(char ***queue, int *front, int *rear, int *current, char **board, char **totalMoves);


//TODO:ask about input function (passing values , potential memory leak)


char * concat(const char *string1, const char *string2)
{

    
    const size_t len1 = strlen(string1);

    const size_t len2 = strlen(string2);

    char *result = malloc(len1 + len2 + 1); // +1 for the null-terminator

    memcpy(result, string1, len1);
    
    memcpy(result + len1, string2, len2 + 1); // +1 to copy the null-terminator

    return result;
}

void displayBoard(char *board)
{
    
    printf("\n\n\t\t          Tic Tac Toe\n\n");

    printf("\t\tPlayer 1 (X)  -  Player 2 (O)\n\n\n");


    printf("\t\t\t  %c | %c  | %c  \n", board[0], board[1], board[2]); 
    printf("\t\t\t--------------\n"); 
    printf("\t\t\t  %c | %c  | %c  \n", board[3], board[4], board[5]); 
    printf("\t\t\t--------------\n"); 
    printf("\t\t\t  %c | %c  | %c  \n\n", board[6], board[7], board[8]); 
}



void showHelp()
{
    
    printf("\n\n\t\tThe way this game works is that you\n");
    printf("\t\tchoose a block numbered \n\t\tfrom 1 to 9 as below"
            " and play. \n\n"); 
      
    printf("\t\t\t  1 | 2  | 3  \n"); 
    printf("\t\t\t--------------\n"); 
    printf("\t\t\t  4 | 5  | 6  \n"); 
    printf("\t\t\t--------------\n"); 
    printf("\t\t\t  7 | 8  | 9  \n\n"); 
      

}


void input(char **choice)
{   
      
    fgets(*choice, 20, stdin);

    removeNewline(&(*choice));   

    //printf("%d -- inside method\n",&(*choice));

}

void removeNewline(char **str)
{
    int len = strlen(*str);

    if (len > 0 && (*str)[len - 1] == '\n')
    {
      //printf("remive new line\n");
      (*str)[len - 1] = '\0';
    }
        
}


void saveToFile(char *totalMoves)
{
    FILE *outputFile = fopen("save.txt", "w");

    int length = strlen(totalMoves);

    fprintf(outputFile, "%s", totalMoves, length + 1);

    fclose(outputFile);
    
}


void loadFile(char *fileName)
{
    FILE *inputFile = fopen(fileName, "r");

    char buffer[4];

    while(!feof(inputFile))
    {
        fgets(buffer,4, inputFile);

        printf("%s", buffer);
    }
}


int checkValidMove(char *move, char *board)
{
    char checkCharPosition = move[0];

    int checkPosition = checkCharPosition - '0';

    if(board[checkPosition - 1] == 'O' || board[checkPosition - 1] == 'X')
    {
        return 1;
    }
    else
    {
        return 0;
    }
    
    return 0;

}

int checkIfGameIsWon(char *move)
{

    char position = move[0];

    char movePlayed = move[1];

    int checkPosition = position - '0';

    //check if won by every move played not the board

    return 0;
}


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

// FOR QUEUE


void generateGameBoard(char ***queue, char **board, int rear)
{
    
    char *move = (*queue)[rear];
    char position = move[0]; 

    char charMove = move[1];
    
    int comparePosition = position - '0';

    (*board)[comparePosition - 1] = charMove;

    printf((*board));
    
}

void undoMove(char ***queue, int *front, int *rear, int *current, char **board, char **totalMoves)
{
    
    

    char checkCharPosition = (*queue)[*current][0];

    int checkPosition = checkCharPosition - '0';

    

    if((*queue)[*current] == (*queue)[1] && (*board)[checkPosition - 1] == checkCharPosition)
    {   
     
        return;

    }

    (*board)[checkPosition - 1] = (*queue)[*current][0];

    

    if((*queue)[*current] != (*queue)[1])
    {
        *current = *current - 1;
    }
   

    


}

void redoMove(char ***queue, int *front, int *rear, int *current, char **board, char **totalMoves)
{
    char checkCharPosition = (*queue)[*current][0];

    int flag = 0;


    int checkPosition = checkCharPosition - '0';
    
    if((*queue)[*current] == (*queue)[1] && (*board)[checkPosition - 1] == checkCharPosition)
    {
   
        flag = 1;

    }



    if((*queue)[*current] == (*queue)[*rear] && (*board)[checkPosition - 1] == (*queue)[*current][1])
    {
       
        return;
    }


    if(flag == 0 && (*queue)[*current] != (*queue)[*rear])
    {
        
        *current = *current + 1;

    }
    

    checkCharPosition =  (*queue)[*current][0];

    checkPosition = checkCharPosition - '0';

    (*board)[checkPosition - 1] = (*queue)[*current][1];
    
    

  

}



int main(int argc, char ** argv)
{   

    int gameRunning = 0;

    int checkIfGameIsWonFlag = 1;

    char *totalMoves = "";

    int playerTurn = 1;

    int newMoveFlag = 1;

    int firstMovePlayed = 0;

    char *playerMove = ":X";

    char *move;

    char **queue = initQueue();

    int rear = -1;
    int current = 0;
    int front = 1;

    char * board = "123456789";

    char  *choice  = (char *)malloc(20);

    displayBoard(board);
    
    while (gameRunning == 0)
    {   

       
        printf("\nPlease type your choice (1-9), type help for instructions on how to play the game\n>>");

        input(&choice);

        printf("your choice: %s \n", choice);

        //printf("%d -- in main method\n",&choice);

        
        
        if((strcmp(choice, "help") == 0) || (strcmp(choice, "Help") == 0))
        {
            showHelp();
          
        }
        else if(strcmp(choice, "save") == 0)
        {
            saveToFile(totalMoves);
        }
        else if(strcmp(choice, "load") == 0)
        {
            loadFile("save.txt");
        }
        else if((strcmp(choice, "exit") == 0) || (strcmp(choice, "Exit") == 0))
        {
            gameRunning = 1;
            printf("\nExiting game...");
            break;
        }
        else if (strcmp(choice, "undo") == 0) 
        {
            if(rear == -1)
            {
                printf("Nothing to undo.\n");
                continue;
            }
           
            newMoveFlag = 0;

            undoMove(&queue, &front, &rear, &current, &board, &totalMoves);

            playerTurn--;
        }
        else if(strcmp(choice, "redo") == 0)
        {

            if(rear == -1)
            {
                printf("Nothing to redo.\n");
                continue;
            }
         
            newMoveFlag = 0;

            char checkCharPosition = queue[current][0];

            int checkPosition = checkCharPosition - '0';
      
            if(queue[current] != queue[rear] || (queue[front] == queue[current] && board[checkPosition - 1] == checkCharPosition))
            {
                playerTurn++;
            }


            redoMove(&queue, &front, &rear, &current, &board, &totalMoves);


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
            
                   
           
        }
        else if (atoi(choice) < 10 && atoi(choice) > 0)
        {   

            if(newMoveFlag == 0)
            {

                newMoveFlag = 1;

                
                if(queue[current] != queue[rear])
                {
                    updateQueue(&queue, &front, &rear, &current, board);
                }
                
               


            }
            if(playerTurn >= 9)
            {
                break;
            }
            if(playerTurn % 2 == 0)
            {
                printf("\nplayer %d\n", 2);

                playerMove = "O";
            }
            else
            {
               printf("\nplayer %d\n", 1);          

               playerMove = "X";
            }
            
            
            move = concat(choice, playerMove);

            int checkValidMoveFlag = checkValidMove(move, board);

            printf("\n -- move played --%s\n",move);

            if (checkValidMoveFlag == 0)
            {
                totalMoves = concat(totalMoves, move);

                totalMoves = concat(totalMoves, "\n");

                enqueue(&queue, move, &front, &rear, &current);

                generateGameBoard(&queue, &board, rear);

                firstMovePlayed = 1;
            
                playerTurn++;


            }
            else
            {
                printf("Invalid move!\n");
            }

          
        }
        else
        {

            
            printf("\nCommand not recognized, try again\n");
            
               
        }  

        

        if(playerTurn >= 9)
        {
            playerTurn = 9;

            gameRunning = 1;


        }
        else if(playerTurn <= 0)
        {
            playerTurn = 1;
        }

        checkIfGameIsWonFlag = checkIfGameIsWon(move);

        if(checkIfGameIsWonFlag == 0)
        {
            
        }
        displayBoard(board);
       
        printf("\nplayerTurn == %d\n", playerTurn);
       
    }
    
    

    return 0;
}

