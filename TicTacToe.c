/* Author: Darwon Rashid
Matric Number - 40280334
*/

// Libraries to be included for code.
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define MAX 9

// METHODS

//Helper methods
char * concat(const char *string1, const char *string2);
void input(char **choice);
void removeNewline(char **str);
void saveToFile(char *totalMoves, char *fileName, int mode);
void loadFile(char *fileName);

// Methods for game
void displayBoard(char *board);
void showHelp();
int checkValidMove(char move, char *board);
char checkWin(char * board);
void initializeBoard(char **board);
void generateGameBoard(char ***list, char **board, int rear);
void undoMove(char ***list, int *front, int *rear, int *current, char **board);
void redoMove(char ***list, int *front, int *rear, int *current, char **board);
void askToSaveGame(char **list, int rear, int mode);
void askToLoadGame();
void TicTacToeGame(int mode, char **loadGameFile);

//AI methods
int minimaxAlgorithm(char **board, int player);
char * computerTurn(char **board);

// list methods
void append(char ***list, char *move, int *front, int *rear, int *current);
char ** initList();
void updateList(char ***list, int *front, int *rear, int *current, char *board);
void emptyList(char ***list, int rear);


// START

char * concat(const char *string1, const char *string2)
{  
    const size_t len1 = strlen(string1);
    const size_t len2 = strlen(string2);

    char *result = calloc(1, len1 + len2 + 1); // +1 for the null-terminator

    memcpy(result, string1, len1);  
    memcpy(result + len1, string2, len2 + 1); // +1 to copy the null-terminator

    return result;
}


void input(char **choice)
{   
      
    fgets(*choice, 20, stdin);

    removeNewline(&(*choice));   

}


void removeNewline(char **str)
{
    int len = strlen(*str);

    if (len > 0 && (*str)[len - 1] == '\n')
    {
        (*str)[len - 1] = '\0';
    }
        
}


void saveToFile(char *totalMoves, char *fileName, int mode)
{
    FILE *outputFile = fopen(fileName, "w");

    int length = strlen(totalMoves);

    fprintf(outputFile, "%d\n", mode, 2);
    fprintf(outputFile, "%s", totalMoves, length + 1);
    
    fclose(outputFile);  
}


void loadFile(char *fileName)
{
    FILE *inputFile = fopen(fileName, "r");

    char *buffer = (char *)calloc(1, 3);
    char *movesPlayed = (char *)calloc(1, 20);

    while(!feof(inputFile))
    {
        fgets(buffer,3, inputFile);

        movesPlayed = concat(movesPlayed, buffer);

    }

    char mode = movesPlayed[0];

    TicTacToeGame(mode - '0', &movesPlayed);

    free(buffer);

    free(movesPlayed);


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

    printf("\n\t\tYou can also undo and redo moves by \n\t\ttyping undo or redo.\n");
    printf("\t\tYou can also save the game to be played \n\t\tlater if you exit the game or\n\t\tif the game is done.\n");
    printf("\t\tYou can exit anytime by typing exit.\n");
      

}


int checkValidMove(char move, char *board)
{
    char checkCharPosition = move;

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


char checkWin(char * board) 
{
    unsigned wins[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};

    int i;

    for(i = 0; i < 8; ++i) 
    {
        if(board[wins[i][0]] != '0' && board[wins[i][0]] == board[wins[i][1]] && board[wins[i][0]] == board[wins[i][2]])
        {               
            return board[wins[i][2]];
        }           
    }
    
    return '0';
}


void initializeBoard(char **board)
{
    for(int i = 0; i < 9; i++)
    {
        (*board)[i] = '0' + i + 1;
    }
}


void generateGameBoard(char ***list, char **board, int rear)
{
    
    char *move = (*list)[rear];
    char position = move[0]; 

    char charMove = move[1];
    
    int comparePosition = position - '0';
    (*board)[comparePosition - 1] = charMove;
    
}


void undoMove(char ***list, int *front, int *rear, int *current, char **board)
{

    char checkCharPosition = (*list)[*current][0];

    int checkPosition = checkCharPosition - '0';

    if((*list)[*current] == (*list)[*front] && (*board)[checkPosition - 1] == checkCharPosition)
    {   
        
        return;
    }

    (*board)[checkPosition - 1] = (*list)[*current][0];

    if((*list)[*current] != (*list)[*front])
    {
        
        *current = *current - 1;
    }

}


void redoMove(char ***list, int *front, int *rear, int *current, char **board)
{
    char checkCharPosition = (*list)[*current][0];

    int flag = 0;
    int checkPosition = checkCharPosition - '0';
    
    if((*list)[*current] == (*list)[*front] && (*board)[checkPosition - 1] == checkCharPosition)
    {
        flag = 1;
    }

    if((*list)[*current] == (*list)[*rear] && (*board)[checkPosition - 1] == (*list)[*current][1])
    {    
        return;
    }


    if(flag == 0 && (*list)[*current] != (*list)[*rear])
    {    
         *current = *current + 1;
    }
    
    checkCharPosition =  (*list)[*current][0];

    checkPosition = checkCharPosition - '0';

    (*board)[checkPosition - 1] = (*list)[*current][1];

}

// method to prompt user to save game
void askToSaveGame(char **list, int rear, int mode)
{
    printf("\nWould you like to save the game to a file? yes/no\n>>");

    char *choice = (char *)calloc(1, 25);

    char *totalMoves = (char *)calloc(1, 25);

    totalMoves = strcpy(totalMoves, "");

    int flag = 0;

    input(&choice);

    if(strcmp(choice, "Yes") == 0 || strcmp(choice, "yes") == 0)
    {
        while(flag == 0)
        {
            printf("\nName the file (must have .txt extension)\n>>");
            input(&choice);

            if(strstr(choice, ".txt") != NULL)
            {
                for(int i = 0; i <= rear  && i < MAX; i++ )
                {
                
                    totalMoves = concat(totalMoves, list[i]);
                 
                    totalMoves = concat(totalMoves, "\n");
                }

                saveToFile(totalMoves, choice, mode);

                printf("\nThe file has been saved!\nGoing back to the Main Menu...\n");
                flag = 1;
                break;
            }
            else
            {
                printf("filename is invalid!\n");
            }
        }       
    }

    free(choice);
    free(totalMoves); 

}

void askToLoadGame()
{
    printf("\nPlease type in the name of the file (must have .txt extenshion)\n>>");

    char *choice = (char *)calloc(1, 25);

    input(&choice);

    loadFile(choice);

    free(choice);
}


void TicTacToeGame(int mode, char **loadGameFile)
{
    int gameRunning = 0;

    char *totalMoves = (char*)calloc(1, 20);

    int playerTurn = 1;

    int newMoveFlag = 1;

    int firstMovePlayed = 0;

    char *playerMove = (char *)calloc(1, 3);

    char *move;

    char **list = initList();

    int rear = -1;
    int current = 0;
    int front = -1;

    char * board = (char *)calloc(1, 10);
    
    initializeBoard(&board);

    char  *choice  = (char *)calloc(1, 20);

    // if game is being loaded 
    
    if(strcmp((*loadGameFile), "NA") != 0)
    {
        char * buffer = (char*)calloc(1, 3);

        totalMoves = strcpy(totalMoves, "");

        char * buffer2 = (char*)calloc(1, 3);


        if(strlen((*loadGameFile)) > 4)
        {

            for(int i = 2; i < strlen((*loadGameFile)); i++)
            {      

                if((*loadGameFile)[i] == '\n' )
                {
                    buffer[0] = (*loadGameFile)[i - 2];
                    buffer[1] = (*loadGameFile)[i - 1];
                    buffer[2] = '\0';

                    char * buffer2 = (char*)calloc(1, 3);

                    strcpy(buffer2, buffer);

                    int check = buffer[0] - '0';

                    if(check < 9 && check > 0)
                    {
                    
                        board[check - 1] = buffer[1];                            

                        append(&list, buffer2, &front, &rear, &current);

                        playerTurn++;

                        firstMovePlayed = 0;
                    }               
                }
                      
            }

            free(buffer2);

            if(list[rear][1] == 'X' && playerTurn < 9 && mode == 0)
            {

                printf("Last turn was player 1 so computer made a move.\n");

                char * compMove = computerTurn(&board);

                append(&list, compMove, &front, &rear, &current);

                generateGameBoard(&list, &board, rear);

                playerTurn++;

            }

            if(checkWin(board) != '0')
            {
                printf("\nThis game has been won by %c, you can undo and redo through the game for replay.\nUndo or it will be won.", checkWin(board));
            }
        }
      
        free(buffer);
    }

    displayBoard(board);

    while (gameRunning == 0)
    {   
        if(firstMovePlayed == 0 && (*loadGameFile) == "NA")
        {
            printf("Player Turn: 1\n");
        }
        else if(firstMovePlayed == 0 && (*loadGameFile) != "NA")
        {
            printf("Player Turn: 1\n");
            firstMovePlayed = 1;
        }
       
        printf("\nPlease type your choice (1-9), type help for instructions on how to play the game\n>>");

        input(&choice);

        printf("your choice: %s \n", choice);

        
        if((strcmp(choice, "help") == 0) || (strcmp(choice, "Help") == 0))
        {
            showHelp();
          
        }
        else if((strcmp(choice, "exit") == 0) || (strcmp(choice, "Exit") == 0) || (strcmp(choice, "Save") == 0) || (strcmp(choice, "save") == 0))
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

            undoMove(&list, &front, &rear, &current, &board);

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

            char checkCharPosition = list[current][0];

            int checkPosition = checkCharPosition - '0';
      
            if(list[current] != list[rear] || (list[front] == list[current] && board[checkPosition - 1] == checkCharPosition))
            {
                playerTurn++;
            }


            redoMove(&list, &front, &rear, &current, &board);
                   
           
        }
        else if (atoi(choice) < 10 && atoi(choice) > 0)
        {   

            if(newMoveFlag == 0)
            {

                newMoveFlag = 1;

                
                if(list[current] != list[rear])
                {
                    updateList(&list, &front, &rear, &current, board);
                }
                
            }
            if(playerTurn % 2 == 0 && mode == 1)
            {
               
                strcpy(playerMove, "O");
            }
            else
            {      

                strcpy(playerMove, "X");
            }       
            
            move = concat(choice, playerMove);

            int checkValidMoveFlag = checkValidMove(move[0], board);

            if (checkValidMoveFlag == 0)
            {

                append(&list, move, &front, &rear, &current);

                generateGameBoard(&list, &board, rear);

                firstMovePlayed = 1;
            
                playerTurn++;

                
                if(mode == 0 && playerTurn < 10)
                {
                    char * compMove = computerTurn(&board);

                    append(&list, compMove, &front, &rear, &current);

                    generateGameBoard(&list, &board, rear);

                    playerTurn++;
                }
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
        
        
        displayBoard(board);

        char winner = checkWin(board);

        if(winner != '0')
        {
            printf("\nThe Winner is %c!\n", winner);

            gameRunning = 1;
            break;
        }
        else if(playerTurn > 9 && winner == '0')
        {

            printf("\nIt is a draw!\n");
            gameRunning = 1;
            break;
        }

        if(playerTurn % 2 == 0 && mode == 1)
        {
               
            printf("Player Turn: 2\n");
        }
        else
        {      

           printf("Player Turn: 1\n");
        }       
       
    }

    if(firstMovePlayed == 1)
    {
        
        if(newMoveFlag == 0)
        {
            updateList(&list, &front, &rear, &current, board);          

        }

        askToSaveGame(list, rear, mode);     
        emptyList(&list, rear);
           
        free(board);        
        free(choice);
        free(totalMoves);
        free(playerMove);
       
    }
}

// AI Methods


int minimaxAlgorithm(char **board, int player)
{

    char winner = checkWin((*board));

    if(winner != '0')
    {
        if(winner == 'X')
        {
            return -1 * player;
        }
        else
        {
            return 1 * player;
        }
        
    }
    
    int move = -1;

    int score = -2;

    for(int i = 0; i < 9; i++)
    {

        if((*board)[i] != 'X' && (*board)[i] != 'O')
        {
            char tempBoardValue = (*board)[i];

            if(player == -1)
            {
                (*board)[i] = 'X';

            }
            else
            {
                (*board)[i] = 'O';
            }
            

            int tempScore = -minimaxAlgorithm(&(*board), player * -1);

            if(tempScore > score)
            {
                score = tempScore;
                move = i;
            }
            (*board)[i] = tempBoardValue;

        }
    }

    if(move == -1)
    {
        return 0;
    }
    
    return score;
}


char *computerTurn(char **board)
{
    int score = -2;
    int move = -1;


    for (int i = 0; i < 9; i++)
    {
        char moveC = '0' + i + 1;
       
        if(checkValidMove(moveC,(*board)) == 0)
        {
            char tempBoardValue = (*board)[i];
            (*board)[i] = 'O';

            int tempScore = -minimaxAlgorithm(&(*board), -1);

            (*board)[i] = tempBoardValue;

            if(tempScore > score)
            {
                score = tempScore;
                move = i;
            }
        }
    }

    char tempMoveChar = '0' + move + 1; 

    char * finalMove = (char*)calloc(1, sizeof(char) * 3);

    finalMove[0] = tempMoveChar;
    finalMove[1] = 'O';
    finalMove[2] = '\0';

    return finalMove;
    
}

// FOR list


char ** initList()
{
    char **list = calloc(1, MAX * sizeof(char*));

    for(int i = 0; i < MAX; i++)
    {
        list[i] = calloc(1, 2 * sizeof(char) + 1);       
    }

    return list;
}


void append(char ***list, char *move , int *front, int *rear, int *current)
{

    if(*rear == MAX)
    {
        printf("list is full\n");
        return;
    }
    else
    {

       
        if((*rear) < 0)
        {
            (*rear) = 0;
            (*list)[*rear] = move;

        }
        else
        {
            (*rear)++;
            (*list)[*rear] = move;
        }
        
        *current = *rear;

    

        if(*front == -1)
        {
            *front = 0;
        }
    }
    
}


void emptyList(char ***list, int rear)
{
    
    for(int i = 0; i < MAX; i++)
    {         
     
        free((*list)[i]);  
    }   

    free((*list));
}


void updateList(char ***list, int *front, int *rear, int *current, char *board)
{
   

    if((*list)[*current] == (*list)[*rear])
    {
        return;
    }

    for(int i = *current + 1; i <= *rear; i++)
    {
    
        strcpy((*list)[i], "\0\0\0");
    } 

    *rear = *current;

    char checkCharPosition = (*list)[*current][0];

    int checkPosition = checkCharPosition - '0';

    if((*list)[*current] == (*list)[*front] && board[checkPosition - 1] == checkCharPosition )
    {
    
        strcpy((*list)[*current], "\0\0\0");
        strcpy((*list)[*front], "\0\0\0");
        strcpy((*list)[*rear], "\0\0\0");
        
        *rear = -1;
        *current = 0;
        *front = -1;
    }

   
}


int main(int argc, char ** argv)
{   

    int mainMenu = 0;

    char *choice  = (char *)calloc(1, 2);

    while(mainMenu == 0)
    {
        printf("\n Welcome to TicTacToe!\n1) Single-Player\n2) Two-Players\n3) Load Game\n4) Exit\n");

        printf("\nPlease type your choice! (Integers 1-4) \n>>");

        input(&choice);

        int switchChoice = atoi(choice);

        char * gameFile = "NA";

        switch (switchChoice)
        {
            case 1:
                printf("singlePlayer\n");
                TicTacToeGame(0, &gameFile);
                break;
        
            case 2:
                printf("multiPlayer\n");
                TicTacToeGame(1, &gameFile);
                break;
            case 3:
                askToLoadGame();
                break;
            case 4:
                printf("Exiting...\n");
                mainMenu = 1;
                break;
        }
    }

    free(choice);

    return 0;
}

