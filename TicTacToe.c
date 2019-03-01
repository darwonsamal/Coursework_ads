/* Author: Darwon Rashid
Matric Number - 40280334
*/

// Libraries to be included for code.
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "CircularQueue.h"

#define HORIZONTAL 3
#define VERTICAL 3

enum Tile 
{
    O = 'O',
    X = 'X',
    Empty = '-'
};

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
char * generateGameBoard(struct Queue *queue);
void undoMove(struct Queue **queue, char **board);
void redoMove(struct Queue **queue, char **board);


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
    
}


void undoMove(struct Queue **queue, char **board)
{

    //temp node for assignment 
    struct node *temp;
    
    // if empty then do nothing
    if((*queue)->front == NULL || (*queue)->rear == NULL)
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
    // get position of the move played
    char charPosition = temp->move[0];
    //convert it to integer
    int position = charPosition - '0';
    //set board position to empty (which is the number of the position);
    (*board)[position - 1] = charPosition;
    // if back to original state (empty) then do not update current for there is no more undos to do
    if(temp->previous == NULL)
    {
        return;
    }

    //update current so it is the previous node which means the next old move played
    (*queue)->current = temp->previous;
    
}

void redoMove(struct Queue **queue, char **board)
{
    //temp node for assignment 
    struct node *temp;

    // flag to check it current needs updating in certain cases
    int flag = 1;

    // if queue is empty then return and do nothing
    if((*queue)->front == NULL || (*queue)->rear == NULL)
    {
        return;
    } // else checking if current node is front
    else if((*queue)->current == (*queue)->front)
    {

        temp = (*queue)->current;

        // CHECK TO see if current (which is front) needs redo or is it the next node that needs redo
        int checkIfOldMove = temp->move[0] - '0';

        // check to see if a move is played at this current node, if so then we redo the next one and not this one
        if((*board)[checkIfOldMove - 1] != temp->move[0])
        {   
            
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

        // if current node is not updated then do so
        if(flag == 1)
        {

           
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

        int checkIfOldMove = temp->move[0] - '0';

        // checking if current node has redone already by seeing if it is empty
        if((*board)[checkIfOldMove - 1] == temp->move[0])
        {   
            // if not update it with the move

            char charPosition = temp->move[0];       

            int position = charPosition - '0';

            (*board)[position - 1] = temp->move[2];

        }
        else
        {
            // then what we have to redo is the next node and we do so here
            char charPosition = temp->next->move[0];

            int position = charPosition - '0';

            (*board)[position - 1] = temp->next->move[2];


            // if we in the end of the queue(rear) this means we got no more moves to redo so we return or check if queue is empty
            if((*queue)->current->next == (*queue)->front)
            {   
               
                return;
            }   

            // update current to the next node 
            (*queue)->current = temp->next;

        }

    }
    
  
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


/*
char * renderGameBoard(char *state)
{
    if(state == NULL || state == "")
    {
        char *newState = "123456789";


        char *board = "";

        board = renderGameBoard(newState);

        return board;

    }
    else
    {
        
        int length = strlen(state);

        int count = 0;

        // char *board = "";

        /*

        for(int i = 0; i < length; i++)
        {   
            if(state[i] == '-')
            {            
                board = concat(board, " ");
                         
            }
            else if(state[i] == '1')
            {              
                board = concat(board, "X");
                 
            }
            else if(state[i] == '0')
            {              
                board = concat(board, "O");
                 
            }
        }
     

        //displayBoard(state);
        return state;
    }  
}

char * saveGameBoard(char *board)
{
    int length = strlen(board);

    char* newState = "";

   
    for(int i = 0; i < length; i++)
    {     
        if(board[i] == '_')
        {            
            newState = concat(newState, "-");         
                   
        }
        else if(board[i] == 'X')
        {              
            newState = concat(newState, "1");
            
        }
        else if(board[i] == 'O')
        {              
            newState = concat(newState, "0");
             
        }              
    }

    return newState;
}

*/

int main(int argc, char ** argv)
{   

    int gameRunning = 1;

    int playerTurn = 1;

    int newMoveFlag = 1;

    int firstMovePlayed = 0;

    char *playerMove = ":X";

    struct Queue * queue; 

    char * board = "123456789";

    initQueue(&queue);

    char  *choice  = (char *)malloc(20);

    displayBoard(board);

    while (gameRunning == 1)
    {   

       
        printf("\nPlease type your choice (1-9), type help for instructions on how to play the game\n>>");

        input(&choice);

        printf("your choice: %s \n", choice);

        //printf("%d -- in main method\n",&choice);
        
        if(strcmp(choice, "help") == 0) /*|| (strcmp(choice, "Help") == 0)*/
        {
            showHelp();
          
        }
        else if(strcmp(choice, "exit") == 0 /*|| (strcmp(choice, "Exit") == 0)*/)
        {
            gameRunning = 0;
            printf("\nExiting game...");
            break;
        }
        else if ((strcmp(choice, "undo") == 0) && (firstMovePlayed == 1)) 
        {
            undoMove(&queue, &board);
            playerTurn--;
        }
        else if(strcmp(choice, "redo") == 0 && (firstMovePlayed == 1))
        {
            redoMove(&queue, &board);

            playerTurn++;
           
        }
        else if (atoi(choice) < 10 && atoi(choice) > 0)
        {   

            if(newMoveFlag == 0)
            {


            }
            if(playerTurn >= 9)
            {
                gameRunning = 0;
                printf("game over");
            }
            if(playerTurn % 2 == 0)
            {
                printf("\nplayer %d\n", 2);

                playerMove = ":O";
            }
            else
            {
               printf("\nplayer %d\n", 1);          

               playerMove = ":X";
            }
            
            
            char * move = concat(choice, playerMove);

            printf("\n -- move played --%s\n",move);

    
            enqueue(&queue, move);

            board = generateGameBoard(queue);


            firstMovePlayed = 1;
            
            playerTurn++;
        }
        else
        {

            if(firstMovePlayed == 0)
            {
                printf("\n You must play a move first to undo or redo\n");
            }
            else
            {
                printf("\nCommand not recognized, try again\n");
            }
               
        }      

       
            displayBoard(board);
       
    }

    return 0;
}

