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



void renderGameBoard()
{

}

void renderGameBoard();

int main(int argc, char ** argv)
{
    char *state = "---111000";


    int length = strlen(state);

    int count = 0;

    for(int i = 0; i < length; i++)
    {   

        printf("%c", state[i]);
        count++;
/*
        if( i % 3 == 0)
        {
            printf("\n");
        }

        if(state[i] == '-')
        {
            printf("%c", '_');
        }
        else if(state[i] == '1')
        {
            printf("%c", 'X');
        }
        else if(state[i] == '0')
        {
            printf("%c", 'O');
        }
        
        */

      

     
    }

    printf("%d", count);
}