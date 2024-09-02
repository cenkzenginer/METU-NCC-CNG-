//Cenk Zenginer
//2385789
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 25

//This is one of the project done in the Data Structures course. 
//The program reads the earthquake data from a file and stores it in a linked list.
//The program then performs operations such as removing earthquakes with a magnitude below a certain threshold,
//calculating the average magnitude of earthquakes in a given location, and counting the number of earthquakes in
//a given location. The program also displays the number of earthquakes that caused a tsunami in a given location.
//The program displays the results of these operations on the screen.

struct Node //node plan
{
char place[MAX];
char date[MAX];
float magnitude;
float latitude;
float longitude;
int tsunami;
struct Node *next;
};

struct Node *load_data(char filename[],int NumberOfLines); //function prototypes
void remove_earthquake(struct Node *tmp,float,int*);
void average_magnitude(struct Node *tmp,char []);
void count_earthquakes(struct Node *tmp,char []);
void print(struct Node *tmp);
void show_statics(struct Node*tmp,char []);



int main() //main function starts here
{
char filename[MAX],userName[MAX],ch;
int option;
float threshold;
int numberOfLines=1;

FILE *infile;

struct Node *tmp;

printf("Welcome to Earthquakes Data Analysis Program\n");
printf("Enter file name: ");
scanf("%s", &filename);

infile=fopen(filename,"r");

while((ch=fgetc(infile))!=EOF) //finds number of lines for file
{
if(ch=='\n')
numberOfLines++;
}
fclose(infile);

tmp = load_data(filename,numberOfLines);


do //main menu prints options till 3 entered
{
printf("\n---------------------------------------------------------------");
printf("\nOperations Menu");
printf("\n---------------------------------------------------------------");
printf("\n1. Remove Earthquake");
printf("\n2. Show Statistics");
printf("\n3. Exit");
printf("\n---------------------------------------------------------------");
printf("\nEnter your option: ");
fflush(stdin);
scanf("%d",&option);

if(option==1)
{
printf("\nEnter a threshold value for the magnitude:");
scanf("%f",&threshold);
remove_earthquake(tmp,threshold,&numberOfLines);

}
else if(option==2)
{
printf("\nEnter a user name: ");
scanf("%s",&userName);
show_statics(tmp,userName);
}
else //if user selected different than 3, program asks user enter option again
{
while(option!=3)
{
printf("\nYou have selected wrong option.\nPlease try again.");
printf("\nEnter your option: ");
fflush(stdin);
scanf("%d",&option);
}

}while(option!=3);

printf("\n\nSee you, bye bye!");

return 0; //main function ends here
}

struct Node *load_data(char filename[],int numberOfLines)
{
struct Node *tmp, *head=NULL, *last, *first;
int i;
char ch;

FILE *infile;

infile=fopen(filename,"r"); //opening file to the read mode

for(i=0;i<numberOfLines;i++){//copies from file to linked list
tmp=(struct Node *) malloc(sizeof(struct Node));
fscanf(infile,"%[^,],%[^,],%f,%f,%f,%d",tmp->place,tmp->date,&tmp->magnitude,&tmp->latitude,&tmp->longitude,&tmp->tsunami);
tmp->next=NULL;
if(head==NULL){
head=tmp;
last=tmp;
first=last;
}
else{
last->next=tmp;
last=tmp;
}
}
fclose(infile);//close file

printf("\nThe earthquake characteristics is successfully loaded");

return head;
}

void remove_earthquake(struct Node *tmp,float threshold,int *numberOfLines)
{
struct Node *head=tmp;
struct Node *tmp1=tmp;
struct Node *tmp2;
int i=0,removed=0;

while(tmp->next!=NULL) //repeats the nodes to till the end
{
if(tmp->magnitude<threshold && i==0) //if threshold value bigger than first node
{
tmp1=tmp;
tmp=tmp->next;
free(tmp1);
removed++;

}

if(tmp->next->magnitude<threshold && tmp->next->next!=NULL) //threshold value bigger than middle nodes
{
tmp2=tmp->next;
tmp->next->next=tmp->next;
free(tmp2);
removed++;
}

else if(tmp->next->magnitude<threshold && tmp->next->next==NULL) //threshold value bigger than last node
{
tmp2=tmp->next;
tmp->next=NULL;
free(tmp2);
removed++;
}

i++;
}

free(head);

printf("\nThe number of removed nodes: %d",removed);

}

void average_magnitude(struct Node *tmp,char userName[MAX])
{
int i,counter=0;
float sum=0,avg;
struct Node *tmp1=tmp;

while(tmp1!=NULL) //checks till the last node
{
if(strcmp(userName,tmp1->place) == 0) //if names are equal,condition is true
{
sum = sum + tmp->magnitude;
counter++;
}
tmp1=tmp1->next;
}

avg = sum/counter;

printf("The average of earthquake magnitude is: %.1f",avg);

}

void count_earthquakes(struct Node *tmp,char userName[MAX])
{
int tsunami=0;
int earthquake_count=0;
struct Node *tmp1=tmp;

while(tmp1!=NULL)
{
if(strcmp(userName,tmp1->place)==0)
{
earthquake_count++;

if(tmp1->tsunami==1)
{
tsunami++;
}
printf("\n%s",tmp1->place);
}

tmp1=tmp1->next;

}
printf("\nThe number of earthquake is: %d and the Tsunami is %d",earthquake_count,tsunami);
}

void show_statics(struct Node *tmp,char username[MAX])
{ //This function implements these functions
average_magnitude(tmp,username);
count_earthquakes(tmp,username);

}