//Cenk Zenginer 2385789

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 25

//This is the code of proect 3 Indexing Earthquakes
//This code reads the data from the file and puts it in the AVL tree
//Then it displays the earthquakes in the tree
//Then it finds the most dangerous place and displays the earthquakes in that place
//Then it finds the weakest earthquake and displays the earthquakes with that magnitude


typedef struct Node *AvlTree;
struct Node   //main structre
{
    char place[MAX];
    float magnitude;
    float latitude;
    float longitude;
    int tsunami;
    AvlTree left;
    AvlTree right;
    int height;
    struct Node *next;
};
                                               //Function declerations
AvlTree *ReadData(AvlTree T, char *filename);
int Treeheight(AvlTree T);
int Max(int N1, int N2);
int NumberOfFileLines(char *filename);
AvlTree InsertEarthquake(struct Node *x, AvlTree T);
struct Node *single_rotate_left(struct Node *T);
struct Node *single_rotate_right(struct Node *T);
struct Node *double_rotate_right(struct Node *T);
struct Node *double_rotate_left(struct Node *T);
void DisplayEarthquakes(AvlTree T);
void dangerousPlace(struct Node *T,int eqCount,struct Node *q);
void countryFinder(struct Node *T, char country[]);
float weakestEarthquake(struct Node *T,float weakEQ,char country[],float latitude,float longitude,int tsunami);
void EarthquakeWithMagnitude(AvlTree T,float weakEQ);


int main(int argc,char *argv[])
{
    AvlTree *T;
    int select,eqcounter=0;
    struct Node *tmp;
    float weakEarthquake;
    char country;


if(argv[1] == "earthquakes.txt") //takes filename from the command line
{
    T = ReadData(T,argv[1]); //Creates an empty tree


    printf("Welcome to Earthquake Indexing :) :)\n");
    printf("------------------------------------------------------------------------------------------------\n");

    do  //main menu starts
    {
        printf("Menu\n1. Display the full index of earthquakes\n2. Display the earthquakes of the most dangerous place\n3. Display the weakest earthquake\n4. Exit\n");
        printf("------------------------------------------------------------------------------------------------\n");
        printf("Enter your opinion: ");
        scanf("%d",&select);
        fflush(stdin);

        if(select==1)
        {
            DisplayEarthquakes(T);
        }
        else if(select==2) //display the dangerous place
        {
            tmp = (struct Node*)malloc(sizeof(struct Node));
            dangerousPlace(T,eqcounter,tmp);
        }
        else if(select==3)  //display the weakest earthquakes
        {
            weakEarthquake = weakestEarthquake(T,weakEarthquake,country,0,0,0);
            EarthquakeWithMagnitude(T,weakEarthquake);
        }

    }while(select!=4);

    printf("\n\nbye bye !!!");

}

    return 0;
}


AvlTree *ReadData(AvlTree T, char *filename) //takes data and puts it in the order
{

    int i,numberOFlines;
    char ch;

    FILE *infile;
    infile=fopen(filename,"r");
    if(infile==NULL)
    {
        return NULL;
    }

    numberOFlines=NumberOfFileLines(filename);

    for(i=0;i<numberOFlines;i++){
        struct Node *tmp;
        tmp=malloc(sizeof(struct Node));
        fscanf(infile,"%[^,],%f,%f,%f,%d",tmp->place,&tmp->magnitude,&tmp->latitude,&tmp->longitude,&tmp->tsunami);

        T=InsertEarthquake(tmp,T);
        }
    fclose(infile);

    return T;
}
int NumberOfFileLines(char *filename){//finds the number of lines in the file

    int numberOFlines=1;
    char ch;

    FILE *infile;
    infile=fopen(filename,"r");

    while((ch=fgetc(infile))!=EOF){
        if(ch=='\n')
            numberOFlines++;
        }

    fclose(infile);

    return numberOFlines;

}
AvlTree InsertEarthquake(struct Node *x, AvlTree T) //Inserts earthquake and rotate
{

	if(T==NULL){//if the node is NULL inserts otherwise finds a suitable leaf
		T=malloc(sizeof(struct Node));
		if(T==NULL)
			printf("Out of memory space!!!\n");
		else{
			strcpy(T->place,x->place);
			T->magnitude=x->magnitude;
			T->longitude=x->longitude;
			T->latitude=x->latitude;
			T->tsunami=x->tsunami;
			T->height=0;
			T->left=NULL;
			T->right=NULL;
            }
        }
    else if(strcmp(x->place,T->place)==0)
        {
            T = InsertEarthquake(x,T);

        }

	else if(strcmp(x->place,T->place)<=0)
        {

		T->left=InsertEarthquake(x,T->left);

		if (Treeheight(T->left)-Treeheight(T->right)>=2)
            {
            if(strcmp(x->place,T->left->place)<=0)
                T=single_rotate_left(T);
            else
                T=double_rotate_left(T);
			}
        }

	else if(strcmp(x->place,T->place)>0)
        {

		T->right=InsertEarthquake(x,T->right);

		if(Treeheight(T->right)-Treeheight(T->left)>=2){
            if(strcmp(x->place,T->right->place)>0)
                T=single_rotate_right(T);
            else
                T=double_rotate_right(T);
            }
        }

	T->height=Max(Treeheight(T->left),Treeheight(T->right))+1;

	return T;
}

struct Node* single_rotate_left(struct Node* T)
{

    if(T->left!=NULL){
        struct Node *Tmp;
        Tmp=malloc(sizeof(struct Node*));
        Tmp->right=malloc(sizeof(struct Node*));
        T->left=Tmp->right;
        Tmp->right=T;

        T->height=Max(Treeheight(T->left),Treeheight(T->right))+1;
        Tmp->height=Max(Treeheight(Tmp->left),T->height)+1;

        return Tmp;
        }
    return T;

}

struct Node* single_rotate_right(struct Node* T)
{
    if(T->right!=NULL){
        struct Node *Tmp;
        Tmp=malloc(sizeof(struct Node*));
        Tmp->left=malloc(sizeof(struct Node*));
        T->right=Tmp->left;
        Tmp->left=T;

        T->height=Max(Treeheight(T->left),Treeheight(T->right))+1;
        Tmp->height=Max(Treeheight(Tmp->right),T->height)+1;

        return Tmp;
        }
    return T;
}

struct Node* double_rotate_right(struct Node *p)
{
  p->left = single_rotate_left(p->left);
  return single_rotate_right(p);
}

struct Node* double_rotate_left(struct Node *p)
{
  p->right = single_rotate_right(p->right);
  return single_rotate_left(p);
}

int Treeheight(AvlTree T)
{

	if(T==NULL)
		return -1;
	else
		return T->height;

}
int Max(int N1, int N2)
{

	if (N1>=N2)
		return N1;
	else
		return N2;

}
void DisplayEarthquakes(AvlTree T) //display the earthquakes in AVL tree
{
        if(T!=NULL){
        DisplayEarthquakes(T->left);
        printf("\n%s;",T->place);
        printf("%.1f;",T->magnitude);
        printf("%.4f;",T->latitude);
        printf("%.4f;",T->longitude);
        printf("%d;",T->tsunami);
        DisplayEarthquakes(T->right);
        }
}
void dangerousPlace(struct Node *T,int eqCount,struct Node *q)
{
//finds the number of earthquakes then according the info's calls the country finder function
///time complexity is O(N)
 int current=0;
 char country[MAX];

        if(T!=NULL)
        {
              dangerousPlace(T->left,eqCount,q);
              while(T->next!=NULL)
              {
                  current++;
                  T=T->next;
              }
              if(eqCount<current)
              {
                  eqCount = current;
                  strcpy(country,T->place);

              }


              dangerousPlace(T->right,eqCount,q);
              countryFinder(q, country);
        }

}
void countryFinder(struct Node *T, char country[]) //find the country and print
{
    if(T!=NULL)
        {
            if(strcmp(country,T->place)==0){
                while(T!=NULL){
                    printf("\n%s;",T->place);
                    printf("%.1f;",T->magnitude);
                    printf("%.4f;",T->latitude);
                    printf("%.4f;",T->longitude);
                    printf("%d;",T->tsunami);
                    T=T->next;
                    }
                }
        countryFinder(T->left,country);
        countryFinder(T->right,country);
        }

}


float weakestEarthquake(struct Node *T,float weakEQ,char country[],float latitude,float longitude,int tsunami)
{//finds the weakest earthquakes and returns the float
///time complexity is O(N)
    if(T!=NULL){
        weakestEarthquake(T->left,weakEQ,country,latitude,longitude,tsunami);
        while(T!=NULL){
            if(T->magnitude<weakEQ){
                weakEQ=T->magnitude;
                }
            T=T->next;
            }
        weakestEarthquake(T->right,weakEQ,country,latitude,longitude,tsunami);
        return weakEQ;
        }
}

void EarthquakeWithMagnitude(AvlTree T,float weakEQ)
{//prints the earthquakes according the float info
        if(T!=NULL){
            if(weakEQ==T->magnitude){
                printf("\n%s;",T->place);
                printf("%.1f;",T->magnitude);
                printf("%.4f;",T->latitude);
                printf("%.4f;",T->longitude);
                printf("%d;",T->tsunami);
                }
            EarthquakeWithMagnitude(T->left ,weakEQ);

            EarthquakeWithMagnitude(T->right,weakEQ);
        }
}





