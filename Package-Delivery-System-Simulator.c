//Cenk Zenginer 2385789
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

#define R 4    //order of
#define O 3            //importance
#define Y 2
#define G 1

//This is project 2 of CNG 213 Data Structre Course. This project is about a package delivery service simulator.
//The program takes the number of packages, number of employees, maximum arrival time and maximum service time from the command line.
//Then it creates a package list with random arrival time, service time, package type and employee ID. Then it creates a queue and adds
//the packages to the queue. Then it delivers the packages to the employees. Finally, it reports the statistics of the simulation.

struct Node          //node plan
{
    int arrivalTime;
    int servicetime;
    int serviceStartTime;
    int ID;
    int packageType;
    struct Node *next;
};

struct QueueRecord{       //queue plan

    struct Node *front;
    struct Node *rear;
    int size;

};

struct ListRecord{    //list plan

    struct Node *head;
    struct Node *tail;
    int size;

};

struct information       //struct of information about package
{
    int noOfPackages;
    int noOfEmployee;
    int maxArrivalTime;
    int maxServiceTime;
};

typedef struct QueueRecord *Queue;    //naming the opened queue and list
typedef struct ListRecord *List;

//function prototypes start below

void parseInput(struct information *Info);
List CreatePackagelist(struct information *Info,int counter);
void MakeEmptyList(List PackageList);
Queue initialiseSimulator();
void newPackage(List PackageList,Queue PackageQueue);
void reportStatistics(List PackageList,int timer,struct information *Info);
int deliverPackage(Queue PackageQueue,List PackageList,int *availableEmp,struct information *Info,int counter);


int main(int argc,char *argv[]) //main function starts here
{
    srand(time(NULL));
    int counter,x,y;

    struct information *Info;
    struct Node *tmp1,*tmp2;

    Info =(struct information*)malloc(sizeof(struct information));  //Creating info with information structure

    /*taking information from command line*/

    Info->noOfPackages=atoi(argv[argc-4]);
    Info->noOfEmployee=atoi(argv[argc-3]);
    Info->maxArrivalTime=atoi(argv[argc-2]);
    Info->maxServiceTime=atoi(argv[argc-1]);


    parseInput(Info);

    int availableEmp[Info->noOfEmployee];  //opening array by number of employee


    for(y=Info->noOfEmployee;y>0;y--)
    {
       availableEmp[y-1]=1;
    }

    List PackageList;

    PackageList=CreatePackagelist(Info,counter);

    Queue PackageQueue;
    PackageQueue=initialiseSimulator();

    x=Info->noOfEmployee;

    while(PackageList->head->next!=NULL)   //this loop opens new package till end of the end of the package list
        newPackage(PackageList,PackageQueue);

    for(counter=0;counter<Info->maxArrivalTime;counter++)
        deliverPackage(PackageQueue,PackageList,availableEmp,Info,counter);

    reportStatistics(PackageList,counter,Info);



    return 0;
}

void parseInput(struct information *Info) //this function takes input
{
    printf("PackagesDeliveryServiceSimulator ");//splits the information
    scanf("%d %d %d %d",&Info->noOfPackages,&Info->noOfEmployee,&Info->maxArrivalTime,&Info->maxServiceTime);
}

List CreatePackagelist(struct information *Info,int counter) //creating package list
{
    List PackageList;

    PackageList=(struct ListRecord*) malloc(sizeof(struct ListRecord)); //opening from listrecord

    if(PackageList==NULL){
        printf("\nOut of Memory!\n");
        exit(1);
        }

    MakeEmptyList(PackageList);

    struct Node *tmp,*Plist;
    tmp=malloc(sizeof(struct Node));
    tmp->next=NULL;

    int x,i,j;

    for(j=0;j<Info->noOfPackages;j++)
    {

    if(PackageList->size==0){
        tmp->arrivalTime=1 + (int)rand()%Info->maxArrivalTime;
        tmp->servicetime=1 + (int)rand()%Info->maxServiceTime;
        tmp->packageType=1+(int)rand()%4;
        tmp->ID=1 + (int)rand()%Info->noOfEmployee;
        PackageList->head->next=tmp;//adds the node from head
        PackageList->tail=tmp;
        }

    else{
        x=0;
        tmp->arrivalTime=1 + (int)rand()%Info->maxArrivalTime;
        tmp->servicetime=1 + (int)rand()%Info->maxServiceTime;
        tmp->packageType=1+(int)rand()%4;
        tmp->ID=1 + (int)rand()%Info->noOfEmployee;

        Plist=PackageList->head->next;

        while(tmp->arrivalTime>Plist->arrivalTime&&Plist->next!=NULL){//finds position
            Plist=Plist->next;
            x++;
            }

        if(PackageList->size==x){//Adds from the end
                Plist=PackageList->head->next;
                while(x>0){
                    Plist=Plist->next;
                    x--;
                    }
                Plist->next=tmp;
                PackageList->tail=tmp;
                }
        else{//Adds the node to the certain position
            if(x==0){
                Plist=PackageList->head;
                tmp->next=PackageList->head->next;
                PackageList->head->next=tmp;
                }

            else{
                Plist=PackageList->head->next;
                while(x-1>0){
                    Plist=Plist->next;
                    x--;
                    }
                tmp->next=Plist->next;
                Plist->next=tmp;
                }
            }
        }
    PackageList->size++;
    }
  return PackageList;
}

void MakeEmptyList(List PackageList)
{
    PackageList->head=(struct Node*) malloc(sizeof(struct Node));
    if(PackageList->head==NULL){
        printf("\nOut of Memory!\n");
        exit(1);
        }
    PackageList->head->next=NULL;

    PackageList->tail=PackageList->head;
    PackageList->size=0;
}
void newPackage(List PackageList,Queue PackageQueue)
{
    struct Node *tmp;

    tmp=malloc(sizeof(struct Node));
    tmp=PackageList->head->next;
    PackageList->head->next=PackageList->head->next->next;

    tmp->next=NULL;

    if(PackageQueue==0)
        PackageQueue->front=PackageQueue->rear=tmp;
    else{
        PackageQueue->rear->next=tmp;
        PackageQueue->rear=tmp;
        }
    PackageQueue->size++;
    free(tmp);
}

void reportStatistics(List PackageList,int timer,struct information *Info)
{
    struct Node *tmp;

    int x=0,maxWaittime=0,red=0,orange=0,yellow=0,green=0;
    int EmpArr[Info->noOfEmployee],y;
    float averageTimespent=0;//variables to calculate the info

    for(y=0;y<Info->noOfEmployee;y++)
        EmpArr[y]=0;


    tmp=malloc(sizeof(struct Node)); //opening tmp by using node

    tmp=PackageList->head->next;

    maxWaittime=tmp->serviceStartTime - tmp->arrivalTime;

    while(tmp!=NULL)
    {//calculates the info and finds the final info
        averageTimespent+=(tmp->serviceStartTime - tmp->arrivalTime);

        if(maxWaittime< tmp->serviceStartTime - tmp->arrivalTime)
            maxWaittime=tmp->serviceStartTime- tmp->arrivalTime;

        if(tmp->packageType=R)
            red++;
        else if(tmp->packageType=O)
            orange++;
        else if(tmp->packageType=Y)
            yellow++;
        else if(tmp->packageType=G)
            green++;
        EmpArr[tmp->ID]++;
        x++;
    }
    averageTimespent=averageTimespent/x; //finds the final info

    printf("\n****************Report*****************\n");//And prints all the info
    printf("The number of Delivery Employees: %d\n",Info->noOfEmployee);
    printf("The number of package: %d\n",Info->noOfPackages);
    printf("Number of packages for each Package Label:\n");
    printf("\tRed: %d\n",red);
    printf("\tOrange: %d\n",orange);
    printf("\tYellow: %d\n",yellow);
    printf("\tGreen: %d\n",green);
    printf("Number of packages for each Delivery Employee:\n");

    for(y=0;y<Info->noOfEmployee;y++)
        printf("Delivery Employee %d: %d\n",y+1,EmpArr[y]);


    printf("Completion time: %d\n",timer);
    printf("Average time spent in the queue: %f\n",averageTimespent);
    printf("Maximum waiting time: %d\n",maxWaittime);

}
Queue initialiseSimulator(){

    Queue Q=(struct QueueRecord*)malloc(sizeof(struct QueueRecord));   //open queue from using queuerecord

    if (Q==NULL){
        printf("\n\n\nOut of memory!!!\n\n");
        exit(1);
        }

    Q->size=0;
    Q->front=(struct Node*)malloc(sizeof(struct Node));

    if(Q->front==NULL){
        printf("\n\n\nOut of memory!!!\n\n");
        exit(1);}


    Q->front->next=NULL;
    Q->rear=Q->front;

    return(Q);
}
int deliverPackage(Queue PackageQueue,List PackageList,int *availableEmp,struct information *Info,int counter)
{
    int time;

    struct Node *tmp;
    tmp=malloc(sizeof(struct Node));
    tmp=PackageQueue->front;

    time=PackageQueue->front->servicetime;

    if(availableEmp[tmp->ID-1==1])
        {
         tmp->next=PackageList->head->next->next;
         PackageList->head->next=tmp;
        }

    PackageQueue->front=PackageQueue->front->next;

    return time;
}
