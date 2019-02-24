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
char * renderGameBoard();
char * saveGameBoard();
char * concat(const char *s1, const char *s2);
void displayBoard(char * board);

char * concat(const char *s1, const char *s2)
{

    const size_t len1 = strlen(s1);

    const size_t len2 = strlen(s2);

    char *result = malloc(len1 + len2 + 1); // +1 for the null-terminator

    
    memcpy(result, s1, len1);
    
    memcpy(result + len1, s2, len2 + 1); // +1 to copy the null-terminator

    return result;
}

void displayBoard(char * board)
{
    
    printf("\n\n\tTic Tac Toe\n\n");

    printf("Player 1 (X)  -  Player 2 (O)\n\n\n");


    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c \n", board[0], board[1], board[2]);

    printf("_____|_____|_____\n");
    printf("     |     |     \n");

    printf("  %c  |  %c  |  %c \n", board[3], board[4], board[5]);

    printf("_____|_____|_____\n");
    printf("     |     |     \n");

    printf("  %c  |  %c  |  %c \n", board[6], board[7], board[8]);

    printf("     |     |     \n\n");
}



char * renderGameBoard(char *state)
{
    if(state == NULL || state == "")
    {
        char *newState = "---------";


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
        */

        displayBoard(state);
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



int main(int argc, char ** argv)
{   


    char *state = "---X-XOOO";

    int array[9] = {4,5,8,3,2,1};


    char* board;
    
    //printf(" before method %d\n",&board);

    board = renderGameBoard(state);

    //printf(" after method %d\n",&board);

   // char* newState;
    
    //newState = saveGameBoard(board);

    struct Queue *q;

    initQueue(&q);

    enqueue(&q, "2:X");

    enqueue(&q, "8:X");

    enqueue(&q, "4:X");

    displayQueue(q);

   
    //free(newState);
    free(board);
    free(state);

    return 0;
}

