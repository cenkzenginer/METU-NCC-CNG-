//Cenk Zenginer
//2385789

#include<stdio.h>
#include<stdlib.h>
#include<time.h>


int roll_a_dice (int);
int play_computer (int);
int computer_strategy_decider(int,int,int,int,int,int);
int play_user (int);
void scoresheet(void);
int choose_value(int,int,int);
int choose_value_2(int,int,int);



int choosen_value, choosen_value_2;
int score;

int A,B;


int counter_round=1, round;

int sum_dice;

int comp_turn, user_turn;

char answer, answer_2, answer_3;


int score_comp=0, score_user=0;
int total_score_comp, total_score_user;

int dice_1_comp, dice_2_comp, dice_3_comp;
int dice_4_comp, dice_5_comp, dice_6_comp;

int dice_1_user, dice_2_user, dice_3_user;
int dice_4_user, dice_5_user, dice_6_user;

int first_dice_comp=1, second_dice_comp=2, third_dice_comp=3;
int fourth_dice_comp=4, fifth_dice_comp=5, sixth_dice_comp=6;

int first_dice_user=1, second_dice_user=2, third_dice_user=3;
int fourth_dice_user=4, fifth_dice_user=5, sixth_dice_user=6;

int dice_player, dice_comp;
int bilgisayarin_zari, benim_zarim;

char zar1, zar2, zar3, zar4 ,zar5 ,zar6;
char zar1_user, zar2_user, zar3_user;
char zar4_user, zar5_user, zar6_user;

int main()
{
printf("Welcome to the MidnightDice game.");
printf("\nLets get started!");
printf("\n\nHow many rounds would you like to play? ");

scanf("%d", &round);
srand(time(NULL));





  while(counter_round <= round)
    {
        bilgisayarin_zari = roll_a_dice(dice_comp);
        printf("\n\nI have rolled the dice and got %d !", bilgisayarin_zari);

        printf("\nShall I roll the dice for you (Y/N)? ");

        scanf(" %c", &answer);


          switch (answer)
           {
               case 'Y':
               benim_zarim = roll_a_dice(dice_player);
               printf("\nI have rolled the dice for you and you got %d !", benim_zarim);

               if (bilgisayarin_zari > benim_zarim)
               {
                printf("\nRound %d -- My Turn: ", counter_round);


                 play_computer (comp_turn);
               }

               else if (bilgisayarin_zari < benim_zarim)
               {
                 printf("\nRound %d -- Your Turn: ", counter_round);
                 printf("\nAre you ready to play!");
                 printf("\nShall I roll them for you (Y/N) ?");
                 scanf(" %c", &answer_2);

                 switch(answer_2)
                   {
                     case'Y': ;
                     play_user(user_turn);
                     break;


                     case 'N':
                     printf("\nYou got zero");
                     score_user = 0;
                     break;

                     default:
                     printf("Entered wrong character.");
                   }
               }

               else
              {
                printf("\nSame dices.");
                printf("\nLet's roll again.");
                bilgisayarin_zari = roll_a_dice(dice_comp);
                printf("\n\nI have rolled the dice and got %d !", bilgisayarin_zari);
                benim_zarim = roll_a_dice(dice_player);
                printf("\nI have rolled the dice for you and you got %d !", benim_zarim);
               }

               break;


               case 'N':
               printf("\nBYE");
               break;

               default:
               printf("\nEntered wrong character");

          }




         counter_round++;
    }


    void scoresheet();


return 0;
}


int roll_a_dice(int dice)
{

    dice = (rand()%6 +1);
    return (dice);
}




int play_computer(int score_comp)
{
     dice_1_comp = roll_a_dice(zar1);
     dice_2_comp = roll_a_dice(zar2);
     dice_3_comp = roll_a_dice(zar3);
     dice_4_comp = roll_a_dice(zar4);
     dice_5_comp = roll_a_dice(zar5);
     dice_6_comp = roll_a_dice(zar6);


    printf("\nI got -> [Dice 1]: %d [Dice 2]: %d [Dice 3]: %d [Dice 4]: %d [Dice 5]: %d [Dice 6]: %d\n", dice_1_comp, dice_2_comp, dice_3_comp, dice_4_comp, dice_5_comp, dice_6_comp );

    computer_strategy_decider(dice_1_comp,dice_2_comp,dice_3_comp,dice_4_comp,dice_5_comp,dice_6_comp);

    dice_1_comp = 0;
    dice_2_comp = 0;
    dice_3_comp = roll_a_dice(zar3);
    dice_4_comp = roll_a_dice(zar4);
    dice_5_comp = roll_a_dice(zar5);
    dice_6_comp = roll_a_dice(zar6);

    printf("\nI got ->[Dice 3]: %d [Dice 4]: %d [Dice 5]: %d [Dice 6]: %d\n", dice_3_comp, dice_4_comp, dice_5_comp, dice_6_comp);

    computer_strategy_decider(dice_1_comp,dice_2_comp,dice_3_comp,dice_4_comp,dice_5_comp,dice_6_comp);

    dice_1_comp = 0;
    dice_2_comp = 0;
    dice_3_comp = 0;
    dice_4_comp = 0;
    dice_5_comp = roll_a_dice(zar5);
    dice_6_comp = roll_a_dice(zar6);


    printf("\nI got ->[Dice 5]: %d [Dice 6]: %d", dice_5_comp, dice_6_comp);




}

int play_user(int i)
{

    dice_1_user = roll_a_dice(zar1_user);
    dice_2_user = roll_a_dice(zar2_user);
    dice_3_user = roll_a_dice(zar3_user);
    dice_4_user = roll_a_dice(zar4_user);
    dice_5_user = roll_a_dice(zar5_user);
    dice_6_user = roll_a_dice(zar6_user);





    printf("\nYou got -> [Dice %d]: %d [Dice %d]: %d [Dice %d]: %d [Dice %d]: %d [Dice %d]: %d [Dice %d]: %d",first_dice_user,dice_1_user,second_dice_user,dice_2_user,third_dice_user,dice_3_user,fourth_dice_user,dice_4_user,fifth_dice_user,dice_5_user,sixth_dice_user,dice_6_user);

    printf("\nWhich ones you want to keep?");
    scanf("%d %d", &first_dice_user,&second_dice_user);

    sum_dice = first_dice_user + second_dice_user;

    if (sum_dice = 5)
    {

        score_user = dice_3_user + dice_4_user + dice_5_user + dice_6_user;

    }
    else
    {
        score_user = 0;
    }

    printf("\nShall I roll them for you (Y/N) ?");

    switch(answer_3)
    {
        case'Y':{
    dice_1_user = 0;
    dice_2_user = 0;
    dice_3_user = roll_a_dice(zar3_user);
    dice_4_user = roll_a_dice(zar4_user);
    dice_5_user = roll_a_dice(zar5_user);
    dice_6_user = roll_a_dice(zar6_user);

    printf("\nYou got ->[Dice %d]: %d [Dice %d]: %d [Dice %d]: %d [Dice %d]: %d ",third_dice_user,dice_3_user,fourth_dice_user,dice_4_user,fifth_dice_user,dice_5_user,sixth_dice_user,dice_6_user);

    printf("Which ones you want to keep?");
    scanf(" %d %d",&third_dice_user,&fourth_dice_user);

    sum_dice = third_dice_user + fourth_dice_user;

    if(sum_dice = 10)
    {
        score_user = score_user + dice_5_comp + dice_6_comp;
    }
    else
    {
        score_user = score_user;
    }

    dice_1_user = 0;
    dice_2_user = 0;
    dice_3_user = 0;
    dice_4_user = 0;
    dice_5_user = roll_a_dice(zar5_user);
    dice_6_user = roll_a_dice(zar6_user);

    printf("\nYou got -> [Dice %d]: %c [Dice %d]: %c",fifth_dice_user,dice_5_user,sixth_dice_user,dice_6_user);
    printf("\nYour Score: %d",score_user);
    break;
   }

        case'N':{
            score_user = score_user + 0;
            printf("\nYour score:%d",score_user);
        break;
        }

        default:
            printf("\nYou entered wrong character");
    }
return (score_user);
}










int computer_strategy_decider(int dice_1_comp, int dice_2_comp, int dice_3_comp, int dice_4_comp, int dice_5_comp, int dice_6_comp )
{




if (dice_1_comp==1 || dice_2_comp==1 || dice_3_comp==1 || dice_4_comp==1 || dice_5_comp==1 || dice_6_comp==1)
{
    if (dice_1_comp==4 || dice_2_comp==4 || dice_3_comp==4 || dice_4_comp==4 || dice_5_comp==4 || dice_6_comp==4)
    {
        if (dice_1_comp == 1 && dice_2_comp == 4)
            {
            printf("Kept 1 and 2");
            score_comp = score_comp + dice_3_comp + dice_4_comp + dice_5_comp + dice_6_comp;
            }
        else if (dice_1_comp==1 && dice_3_comp == 4)
            {
              printf("Kept 1 and 3");
              score_comp = score_comp + dice_2_comp + dice_4_comp + dice_5_comp + dice_6_comp;
            }
        else if (dice_1_comp==1 && dice_4_comp==4)
            {
              printf("Kept 1 and 4");
              score_comp = score_comp + dice_2_comp + dice_3_comp + dice_5_comp + dice_6_comp;
            }
        else if (dice_1_comp==1 && dice_5_comp==4)
            {
              printf("Kept 1 and 5");
              score_comp = score_comp + dice_2_comp + dice_3_comp + dice_4_comp + dice_6_comp;
            }
        else if (dice_1_comp==1 && dice_6_comp==4)
            {
              printf("Kept 1 and 6");
              score_comp = score_comp + dice_2_comp + dice_3_comp + dice_4_comp + dice_5_comp;
            }
        else if (dice_2_comp==1 && dice_1_comp==4)
            {
             printf("Kept 2 and 2");
             score_comp = score_comp + dice_3_comp + dice_4_comp + dice_5_comp + dice_6_comp;

            }
        else if (dice_2_comp==1 && dice_3_comp==4)
            {
             printf("Kept 2 and 3");
             score_comp = score_comp + dice_1_comp + dice_4_comp + dice_5_comp + dice_6_comp;
            }
        else if(dice_2_comp==1 && dice_4_comp==4)
            {
             printf("Kept 2 and 4");
             score_comp = score_comp + dice_1_comp + dice_3_comp + dice_5_comp + dice_6_comp;
            }
        else if (dice_2_comp==1 && dice_5_comp==4)
            {
             printf("Kept 2 and 5");
             score_comp = score_comp + dice_1_comp + dice_3_comp + dice_4_comp + dice_6_comp;
            }
        else if(dice_2_comp==1 && dice_6_comp==4)
            {
             printf("Kept 2 and 6");
             score_comp = score_comp + dice_1_comp + dice_3_comp + dice_4_comp + dice_5_comp;
            }
        else if (dice_3_comp==1 && dice_1_comp==4)
            {
            printf("Kept 3 and 1");
            score_comp =score_comp + dice_2_comp + dice_4_comp + dice_5_comp + dice_6_comp;
            }
        else if (dice_3_comp==1 && dice_2_comp==4)
            {
            printf("Kept 3 and 2");
            score_comp =score_comp + dice_1_comp + dice_4_comp + dice_5_comp + dice_6_comp;
            }
        else if (dice_3_comp==1 && dice_4_comp==4)
            {
            printf("Kept 3 and 4");
            score_comp = score_comp + dice_1_comp + dice_2_comp + dice_5_comp + dice_6_comp;
            }
        else if (dice_3_comp==1 && dice_5_comp==4)
            {
            printf("Kept 3 and 5");
            score_comp = score_comp + dice_1_comp + dice_2_comp + dice_4_comp + dice_6_comp;
            }
        else if (dice_3_comp==1 && dice_6_comp==4)
            {
            printf("Kept 3 and 6");
            score_comp =score_comp + dice_1_comp + dice_2_comp + dice_4_comp + dice_5_comp;
            }
       else if (dice_4_comp==1 && dice_1_comp==4)
            {
            printf("Kept 4 and 1");
            score_comp = score_comp + dice_2_comp + dice_3_comp + dice_5_comp + dice_6_comp;
            }
         else if (dice_4_comp==1 && dice_2_comp==4)
            {
            printf("Kept 4 and 2");
            score_comp = score_comp + dice_1_comp + dice_3_comp + dice_5_comp + dice_6_comp;
            }
        else if (dice_4_comp==1 && dice_3_comp==4)
            {
            printf("Kept 4 and 3");
            score_comp = score_comp + dice_1_comp + dice_2_comp + dice_5_comp + dice_6_comp;
            }
         else if (dice_4_comp==1 && dice_5_comp==4)
            {
            printf("Kept 4 and 5");
            score_comp =score_comp + dice_1_comp + dice_2_comp + dice_3_comp + dice_6_comp;
            }
         else if (dice_4_comp==1 && dice_6_comp==4)
            {
            printf("Kept 4 and 6");
            score_comp = score_comp + dice_1_comp + dice_2_comp + dice_3_comp + dice_5_comp;
            }
         else if (dice_5_comp==1 && dice_2_comp==4)
            {
            printf("Kept 5 and 2");
            score_comp = score_comp + dice_1_comp + dice_3_comp + dice_4_comp + dice_6_comp;
            }
        else if (dice_5_comp==1 && dice_3_comp==4)
            {
            printf("Kept 5 and 3");
            score_comp = score_comp + dice_1_comp + dice_2_comp + dice_4_comp + dice_6_comp;
            }
        else if(dice_5_comp==1 && dice_4_comp==4)
            {
            printf("Kept 5 and 4");
            score_comp = score_comp + dice_1_comp + dice_2_comp + dice_3_comp + dice_6_comp;
            }
        else if(dice_5_comp==1 && dice_6_comp==4)
            {
            printf("Kept 5 and 6");
            score_comp = score_comp + dice_1_comp + dice_2_comp + dice_3_comp + dice_4_comp;
            }
        else if (dice_6_comp==1 && dice_1_comp==4)
            {
            printf("Kept 6 and 1");
            score_comp = score_comp + dice_2_comp + dice_3_comp + dice_4_comp + dice_5_comp;
            }
        else if(dice_6_comp==1 && dice_2_comp==4)
            {
             printf("Kept 6 and 2");
             score_comp = score_comp + dice_1_comp + dice_3_comp + dice_4_comp + dice_5_comp;
            }
        else if(dice_6_comp==1 && dice_3_comp==4)
            {
             printf("Kept 6 and 3");
             score_comp = score_comp + dice_1_comp + dice_2_comp + dice_4_comp + dice_5_comp;
            }
        else if(dice_6_comp==1 && dice_4_comp==4)
            {
             printf("Kept 6 and 4");
             score_comp = score_comp + dice_1_comp + dice_2_comp + dice_3_comp + dice_5_comp;
            }
        else if(dice_6_comp==1 && dice_5_comp==4)
            {
             printf("Kept 6 and 5");
             score_comp = score_comp + dice_1_comp + dice_2_comp + dice_3_comp + dice_4_comp;
            }
    }
    else
    {
        choosen_value= choose_value (dice_1_comp, A, B);
        choosen_value= choose_value(dice_2_comp, choosen_value, choosen_value_2);
        choosen_value= choose_value(dice_3_comp, choosen_value, choosen_value_2);
        choosen_value= choose_value(dice_4_comp, choosen_value, choosen_value_2);
        choosen_value= choose_value(dice_5_comp, choosen_value, choosen_value_2);
        choosen_value= choose_value(dice_6_comp, choosen_value, choosen_value_2);

        choosen_value_2= choose_value_2 (dice_1_comp, choosen_value, A);
        choosen_value_2= choose_value_2 (dice_2_comp, choosen_value, choosen_value_2);
        choosen_value_2= choose_value_2 (dice_3_comp, choosen_value, choosen_value_2);
        choosen_value_2= choose_value_2 (dice_4_comp, choosen_value, choosen_value_2);
        choosen_value_2= choose_value_2 (dice_5_comp, choosen_value, choosen_value_2);
        choosen_value_2= choose_value_2 (dice_6_comp, choosen_value, choosen_value_2);






    }




}

}


void scoresheet ()
{


    total_score_comp = score_comp;
    total_score_user = score_user;



    printf("\nOur Scoresheet");
    printf("\n--------------");
    printf("\n--------------");
    printf("\nMy Score       Your Score");
    printf("\n%d                 %d",total_score_comp, total_score_user);


    if (total_score_comp > total_score_user)
    {
        printf("\nI am the winner!");
    }
    else if(total_score_comp < total_score_user)
    {
        printf("\nYou are the winner!");
    }
    else{
        printf("\nDraw");}


}



 int choose_value( int input, int choosen_value, int choosen_value_2 )
{



    if ( input >= choosen_value )
        {
            choosen_value_2 = choosen_value;
            choosen_value = input;

        }
    else
        {
            if ( input >= choosen_value_2 )
            {
            choosen_value = choosen_value;
            choosen_value_2 = input;
            }
           else
            {
                choosen_value = choosen_value;
                choosen_value_2 = choosen_value_2;
            }
        }

    return (choosen_value);
}

int choose_value_2( int input, int choosen_value, int choosen_value_2 )
{




    if ( input >= choosen_value )
        {
            choosen_value_2 = choosen_value;
            choosen_value = input;

        }
    else
        {
            if ( input >= choosen_value_2 )
            {
            choosen_value = choosen_value;
            choosen_value_2 = input;
            }
           else
            {
                choosen_value = choosen_value;
                choosen_value_2 = choosen_value_2;
            }
        }

    return (choosen_value_2);
}




