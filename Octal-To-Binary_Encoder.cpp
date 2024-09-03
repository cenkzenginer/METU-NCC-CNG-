//Cenk Zenginer
//2385789

#include<stdio.h>
int main()
{

int unchanged_base2_input;

int D0_10, D1_10, D2_10, D3_10;
int D4_10, D5_10, D6_10, D7_10;
int Y0_10=0, Y1_10=0, Y2_10=0;

int choose, base;
int counter_base2 = 0;

int remainder;
int base2_input;
int D0_2, D1_2, D2_2, D3_2;
int D4_2, D5_2, D6_2, D7_2;
int Y0_2=0, Y1_2=0, Y2_2=0;

int base10_input;

printf("Welcome to Octal-to-Binary Encoder!");
printf("\n\n(1) Compute and display the outputs");
printf("\n(2) Quit");
printf("\nYou choose: ");
scanf("%d", &choose);



while (choose !=1 && choose !=2)
{
printf("\n\nYou have entered invalid number.\nPlease try again");
printf("\n\nWelcome to Octal-to-Binary Encoder!");
printf("\n\n(1) Compute and display the outputs");
printf("\n(2) Quit");
printf("\nYou choose: ");
scanf("%d", &choose);
}

printf("\n\n");
if (choose==2)
{

printf("You have chosen option 2");
printf("\nBYE!!");
}



else if (choose==1)
{
printf("\nYou have chosen option 1");
printf("\nWhich base will you use to enter input (base 2 or base 10)?" );
scanf("%d", &base);



while (base != 2 && base != 10)
{
printf("\nInvalid number in base 2/10");
printf("\nPlease re-enter again.");
printf("\n\nWhich base will you use to enter input (base 2 or base 10)?" );
scanf("%d", &base);
}



if (base==2)
{
printf("\nPlease enter your input: ");
scanf("%d", &base2_input);


unchanged_base2_input = base2_input;
while (base2_input != 0)
{

base2_input = base2_input/10;
counter_base2++;



while (base2_input % 10 != 0 && base2_input % 10 != 1)
{
printf(" %d is not a valid number in base 2! Please try again!", base2_input);

scanf("%d", &base2_input);
counter_base2 = 0;

}



}
while (counter_base2 < 8 )
{
printf("\nYou entered less than 8 bits!\nPlease try again!");
scanf("%d", &base2_input);
}
while (counter_base2 > 8)
{
printf("\nYou entered more than 8 bits!\nPlease try again!");
scanf("%d", &base2_input);
}
while (counter_base2 == 8 )
{
D0_2 = unchanged_base2_input % 10;
unchanged_base2_input = unchanged_base2_input / 10;

D1_2 = unchanged_base2_input % 10;
unchanged_base2_input = unchanged_base2_input / 10;

D2_2 = unchanged_base2_input % 10;
unchanged_base2_input = unchanged_base2_input / 10;

D3_2 = unchanged_base2_input % 10;
unchanged_base2_input = unchanged_base2_input / 10;

D4_2 = unchanged_base2_input % 10;
unchanged_base2_input = unchanged_base2_input / 10;

D5_2 = unchanged_base2_input % 10;
unchanged_base2_input = unchanged_base2_input / 10;

D6_2 = unchanged_base2_input % 10;
unchanged_base2_input = unchanged_base2_input / 10;

D7_2 = unchanged_base2_input % 10;
unchanged_base2_input = unchanged_base2_input / 10;


if (unchanged_base2_input == 0)
{
break;
}
}
if (D2_2 == 1 || D3_2 == 1 || D6_2 == 1 || D7_2 == 1)
{
Y1_2 = 1;
}
if (D7_2 == 1 || D6_2 == 1 || D5_2 == 1 || D4_2 == 1)
{
Y2_2 = 1;
}
if (D1_2 == 1 || D3_2 == 1 || D5_2 == 1 || D7_2 == 1)
{
Y0_2 = 1;
}


printf("Y2 is %d, Y1 is %d, Y0 is %d", Y2_2,Y1_2,Y0_2);



}


}


if (base==10)
{
printf("\nPlease enter your input: ");
scanf("%d", &base10_input);

while (base10_input > 255)
{
printf("This value not possible to convert it to 8-digit binary number");
printf("\nPlease re-enter the value:");
scanf("%d",base10_input);
}

while (base10_input <= 255 && base10_input!=0)
{
D0_10 = base10_input % 2;
base10_input = base10_input/2;

D1_10 = base10_input % 2;
base10_input = base10_input/2;

D2_10 = base10_input % 2;
base10_input = base10_input/2;

D3_10 = base10_input % 2;
base10_input = base10_input/2;

D4_10 = base10_input % 2;
base10_input = base10_input/2;

D5_10 = base10_input % 2;
base10_input = base10_input/2;

D6_10 = base10_input % 2;
base10_input = base10_input/2;

D7_10 = base10_input % 2;
base10_input = base10_input/2;

if(base10_input == 0)
{
break;
}
}
if(D2_10 == 1 || D3_10 == 1 || D6_10 == 1 || D7_10 == 1 )
{
Y1_10=1;
}
if (D7_10 == 1 || D6_10 == 1 || D5_10 == 1 || D4_10 == 1)
{
Y2_10=1;
}
if (D1_10 == 1 || D3_10 == 1 || D5_10 == 1 || D7_10 == 1)
{
Y0_10=1;
}

printf("Y2 is %d, Y1 is %d, Y0 is %d", Y2_10,Y1_10,Y0_10);



}


return 0;
}