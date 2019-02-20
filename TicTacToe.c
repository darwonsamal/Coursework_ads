/* Author: Darwon Rashid
Matric Number - 40280334
*/

// Libraries to be included for code.
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define HORIZONTAL 3
#define VERTICAL 3


//path
// C:\Users\darwo\Desktop\All Workspace\Workspace\C and C++ Workspace\Data Structures and Algortihms\Coursework



char * concat(const char *s1, const char *s2)
{

    const size_t len1 = strlen(s1);

    const size_t len2 = strlen(s2);

    char *result = malloc(len1 + len2 + 1); // +1 for the null-terminator

    
    memcpy(result, s1, len1);
    
    memcpy(result + len1, s2, len2 + 1); // +1 to copy the null-terminator

    return result;
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

        char *board = "";

        for(int i = 0; i < length; i++)
        {   
            if( i % 3 == 0)
            {             
               board = concat(board, "\n");        
            }

            if(state[i] == '-')
            {            
                board = concat(board, "_");
                board = concat(board, "|");              
            }
            else if(state[i] == '1')
            {              
                board = concat(board, "X");
                board = concat(board, "|");    
            }
            else if(state[i] == '0')
            {              
                board = concat(board, "O");
                board = concat(board, "|");    
            }

        }

    
        return board;
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

char * renderGameBoard();
char * saveGameBoard();
char * concat(const char *s1, const char *s2);

int main(int argc, char ** argv)
{
    char *state = NULL;

    char* board;
    
    printf(" before method %d\n",&board);

    board = renderGameBoard(state);

    printf(" after method %d\n",&board);

    char* newState;
    
    newState = saveGameBoard(board);

    
   
    free(newState);
    free(board);
    free(state);

    return 0;
}

