//Cenk Zenginer
//2385789
#include<stdio.h>
#include<time.h>
#include<stdlib.h>

#define ROWS 7
#define COLUMNS 6

int RollDice(void);
void placeCompToken(char**,int,int,int);
void placeUserToken(char**,int,int,int);
void checkMatch(char**,int,int,int,int*);
void displayBoard(char**,int,int);

int main()
{

    printf("Welcome to the PopThree :)");
    printf("\nLet's get started!");
    printf("\n-----------------------------------------------");

    int player_dice;
    int computer_dice;
    char answer,**board;


    do
    {

        srand(time(NULL));

        int i,j; int round; int round_column;

        board = malloc(ROWS*sizeof*board);                       /* opening the board  */

        for(i=0;i<ROWS;i++)
        {
            board[i] = malloc(COLUMNS*sizeof*board[i]);
        }

        for(i=0;i<ROWS;i++)
        {
            for(j=0;j<COLUMNS;j++)
                board[i][j] = '\0';
        }

        int *scoreboard;
        int row_number_comp=6, row_number_user=6;



        scoreboard = malloc(2*sizeof*scoreboard); /*opening the scoreboard*/





        player_dice = RollDice();        /*generating random numbers between 1-6*/
        computer_dice = RollDice();

        printf("\n\nI have rolled the dice and got %d!",computer_dice);
        printf("\nI have rolled the dice for you and you got %d!",player_dice);

        while(player_dice == computer_dice)  /*if dices are equal, roll again*/
        {
          printf("\nWe got same dices!");
          player_dice = RollDice();
          computer_dice = RollDice();

          printf("\nI have rolled the dice again and got %d!",computer_dice);
          printf("\nI have rolled the dice for you again and you got %d!",player_dice);

        }

        if(player_dice>computer_dice)   /*big dice start*/ /*player start*/
        {


            for(round=1;round<=7;round++)
            {
                printf("\n------------------Round %d----------------------",round);

                for(round_column=0;round_column<6;round_column)
                {
                    placeUserToken(board,row_number_user,round_column,round);
                    placeCompToken(board,row_number_comp,round_column,round);
                    displayBoard(board,ROWS,COLUMNS);



                }

                row_number_comp--;   //these are current row numbers
                row_number_user--;

            }


        }
        else      /*big dice start*/  /*comp. start*/
        {

            for(round=1;round<=7;round++)
            {
                printf("\n------------------Round %d----------------------\n",round);

                for(round_column=0;round_column<6;round_column++)
                {
                    placeCompToken(board,row_number_comp,round_column,round);
                    placeUserToken(board,row_number_user,round_column,round);
                    displayBoard(board,ROWS,COLUMNS);
                    checkMatch(board,ROWS,COLUMNS,round,scoreboard);

                }



                row_number_comp--; //current row numbers
                row_number_user--;
            }

        }





        for(i=0;i<ROWS;i++)                   /*free memory allocations*/
        {
            free(board[i]);
        }

        free(board);
        free(scoreboard);



        fflush(stdin);        /*clean the buffer*/

        printf("\n--------------------End------------------------");

        printf("\nWould you like to play again (Y/N) ? ");
        scanf(" %c",&answer);

    }while(answer == 'Y' || answer == 'y');



    return 0;
}

int RollDice(void)
{
    return rand()%6+1;
}
void placeCompToken(char **board,int rows,int columns,int round)
{
    printf("\nMy turn ->");

    if(board[rows][columns] == '\0')                    /*If that value of the board is empty, it places it there*/
    {
        board[rows][columns] = '*';
        printf("I placed token to location (%d,%d)",rows+1,columns+1);

    }
    else                                                 /*If not empty it places column + 1*/
    {
        board[rows][columns+1] = '*';
        printf("I placed token to location (%d,%d)",rows+1,columns+2);
    }






}

void placeUserToken(char **board,int entered_rows, int entered_columns, int round)
{
    int user_choice_row,user_choice_column;

    printf("\nYour turn -> Enter location to place your token: ");          /*choices where locates token*/
    scanf("(%d,%d)",&user_choice_row,&user_choice_column);

    while(user_choice_row>ROWS ||user_choice_column>COLUMNS)                 /* if choices outside the board*/
    {
        printf("\nYou cannot place a token outside the board.");
        printf("\nYour turn -> Enter location to place your token:");
        scanf(" (%d,%d)",&user_choice_row,&user_choice_column);
    }

    while(user_choice_row != entered_rows)                                  /* if choices wrong location*/
    {
        printf("\nAt this turn you can only place token to row %d!",entered_rows);
        printf("\nYour turn -> Enter location to place your token: ");
        scanf(" (%d,%d)",&user_choice_row,&user_choice_column);
    }

    while(board[user_choice_row][user_choice_column] != '\0')              /* if chosen location is not empty*/
    {
        printf("\nA token is already placed here!");
        printf("\nYour turn -> Enter location to place your token: ");
        scanf(" (%d,%d)",&user_choice_row,&user_choice_column);
    }

    if(user_choice_row == entered_rows)
    {
        board[user_choice_row][user_choice_column] = '+';
    }


}

void checkMatch(char **board,int rows,int columns,int round,int *scoreboard)
{
    board[rows][columns];

    int score_comp,score_user;

    scoreboard[2] = (score_comp,score_user);

    int i,counter_for_point_comp=0,counter_for_point_user=0;

    for(i=0;i<columns;i++)                            /*check all locations of that row if find 3 '*' or 3 '+' score computer or score user increase by 1 */
    {
        if(board[rows][i] == '*')
        {
            counter_for_point_comp++;
            counter_for_point_user = 0;

            if(counter_for_point_comp == 3)
            {
                score_comp = score_comp + 1;
            }
            else if(counter_for_point_comp == 6)
            {
                score_comp = score_comp + 2;
            }


        }

        else if(board[rows][i] == '+');
        {
            counter_for_point_user++;
            counter_for_point_comp = 0;

            if(counter_for_point_user == 3)
            {
                score_user = score_user + 1;
            }
            else if(counter_for_point_user == 6)
            {
                score_user = score_user + 2;
            }

        }
    }




    printf("\nScores  [My  Yours]: [%d %d]",score_comp,score_user);

    if(round == 7)                            //in round 7 which is end of the game it prints who win
    {
        if(score_comp>score_user)
        {
            printf("\nI won!!");
        }
        else
        {
            printf("\nYou won!!");
        }
    }


}
void displayBoard(char**board,int rows,int columns)
{
    board[rows][columns];

    int i,j;

    printf("\n\n  1  2  3  4  5  6 ");

    for(i=0;i<7;i++)
    {                                                       //its check all locations of board and print them
        printf("\n%d",i+1);
        for(j=0;j<6;j++)
        {
            printf(" %c ",board[i][j]);
        }
    }


}

