/**CENK ZENGINER
   ID: 2385789**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//DO NOT CHANGE DATA STRUCTURE
struct Customer {
    char name[81];
    int transactions;
    int items_purchased;
    float amount_paid;
};

typedef struct Customer customer;
//I USED LINKED LIST FOR countCustomers FUNCTION
struct CustomerNode{
    char name[81];
    struct CustomerNode *next;
};
typedef struct CustomerNode customerNode;

//DO NOT CHANGE FUNCTION PROTOTYPES
void menu();
void printCustomers(customer *, int);
int countCustomers(FILE*);
void readTransactions(FILE*, customer* ,int);
void heapify(customer*, int, int, int);
void heapSort(customer*, int,int);
 //I ADDED SWAP FUNCTION PROTOTYPE
void swap(customer *L,int x, int y);

//DO NOT CHANGE THE main FUNCTION
int main() {
    FILE *inFile;
    int no_of_customers = 0;
    customer *customers;

    inFile = fopen("transactions.txt", "r");
    if (inFile == NULL){
        printf("File could not be opened.\n");
        exit(1);
    }
    no_of_customers = countCustomers(inFile);
    printf("There are %d unique customers\n", no_of_customers);

    customers = (customer*) malloc(no_of_customers * sizeof (customer));
    fclose(inFile);
    inFile = fopen("transactions.txt", "r");
    if (inFile == NULL){
        printf("File could not be opened.\n");
        exit(1);
    }

    readTransactions(inFile, customers, no_of_customers);
    if (customers == NULL) {
        printf("\nCustomers have NOT been read successfully!\n");
        exit(1);
    }
    printCustomers(customers, no_of_customers);

    char command = 0;
    int exit = 0;
    while (exit != 1) {
        menu();
        printf("\nCommand: ");
        fflush(stdin);
        scanf("%c", &command);

        if (command == '1' || command == '2' || command == '3' || command == '4') {
            heapSort(customers, no_of_customers, command - '0');
            printCustomers(customers, no_of_customers);
        }
        else if (command == '5'){
            exit = 1;
            printf("Goodbye!\n");
        }
        else{
            printf("Please enter a valid command!\n");
        }
    }
    free(customers);
    return 0;
}

//DO NOT CHANGE THE menu FUNCTION
void menu () {
    printf("Please choose one of the following options:\n"
           "(1) Display customers sorted by number of transactions\n"
           "(2) Display customers sorted by number of items purchased\n"
           "(3) Display customers sorted by total amount paid\n"
           "(4) Display customers sorted by average amount paid per transaction\n"
           "(5) Exit\n");
}

//DO NOT CHANGE THE printCustomers FUNCTION

void printCustomers (customer* customers, int no_of_customers) {
    printf("List of customers:\n");
    int i;
    for (i = 0; i < no_of_customers; ++i) {
        printf("Name: %s, number of transactions = %d, number of items = %d, total amount paid = %.2f,"
               " average amount paid per transaction = %.2f\n",
               customers[i].name, customers[i].transactions, customers[i].items_purchased, customers[i].amount_paid,
               customers[i].amount_paid/customers[i].transactions);
    }
}

int countCustomers (FILE *inFile){

    //Rewind the file pointer to the beginning of the file
    rewind(inFile);
    //Iterate each line in the file
    customerNode* head = NULL; //Created linked list to store unique customer name
    char line[256];

    while(fgets(line,sizeof(line),inFile)){
        char *name = strtok(line,",");

        customerNode *currentNode = head;
        while(currentNode != NULL){
            if(strcmp(currentNode->name,name) == 0)
                break;
            currentNode = currentNode->next;
        }

        //If customer name doesn't exist in linked list then add
        if(currentNode == NULL){
            customerNode* newNode = malloc(sizeof(customerNode));
            strcpy(newNode->name,name);
            newNode->next = head;
            head = newNode;
        }

    }
    //Counting the number of nodes in linked list
    int numCustomers = 0;
    customerNode *currentNode = head;
    while(currentNode != NULL){
        numCustomers++;
        currentNode = currentNode->next;
    }
    //Free memory allocation
    while(head!=NULL){
        customerNode *nextNode = head->next;
        free(head);
        head = nextNode;
    }

    return numCustomers;



}

void readTransactions (FILE* inFile, customer* customers, int no_of_customers) {

    char line[256];

    //Rewind the file pointer to the beginning of the file
    rewind(inFile);

    while(fgets(line,sizeof(line),inFile)){
        //Split the line into individual fields
        char *name = strtok(line, ",");
        int transactions = atoi(strtok(NULL,","));
        int items_purchased = atoi(strtok(NULL,","));
        float amount_paid = atof(strtok(NULL,","));

        int customerIndex = -1;
        int i;
        //Checking if the customer already exists in the customers array
        for(i = 0;i<no_of_customers;i++){
            if(strcmp(customers[i].name,name) == 0){
                customerIndex = i;
                break;
            }
        }
        //If the customer doesn't exist in the array,add
        if(customerIndex == -1){
            no_of_customers++;
            strcpy(customers[customerIndex].name,name);
            customers[customerIndex].transactions = 0;
            customers[customerIndex].items_purchased = 0;
            customers[customerIndex].amount_paid = 0;
        }

        customers[customerIndex].transactions += transactions;
        customers[customerIndex].items_purchased += items_purchased;
        customers[customerIndex].amount_paid += amount_paid;
    }
    //Updating the customers info


}

void heapify(customer* customers, int no_of_customers, int i, int criteria) {

    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    switch(criteria){
    case 1:
        if(left < no_of_customers && customers[left].transactions > customers[largest].transactions)
            largest = left;
        if (right < no_of_customers && customers[right].transactions > customers[largest].transactions)
            largest = right;
        if(largest != i)
            swap(customers,i, largest),
            heapify(customers, no_of_customers, largest, criteria);
        break;

    case 2:
        if(left < no_of_customers && customers[left].items_purchased > customers[largest].items_purchased)
            largest = left;
        if(right < no_of_customers && customers[right].items_purchased > customers[largest].items_purchased)
            largest = right;
        if(largest != i)
            swap(customers,i, largest),
            heapify(customers, no_of_customers, largest, criteria);
        break;

    case 3:
        if(left < no_of_customers && customers[left].amount_paid > customers[largest].amount_paid)
            largest = left;
        if(right < no_of_customers && customers[right].amount_paid > customers[largest].amount_paid)
            largest = right;
        if(largest != i)
            swap(customers,i, largest),
            heapify(customers, no_of_customers, largest, criteria);
        break;
    }



}

void heapSort(customer* customers, int no_of_customers, int criteria) {

    int i;

    for(i=(no_of_customers/2)-1;i>=0;i--)
        heapify(customers,no_of_customers,i,criteria);

    for(i=no_of_customers-1;i>=0;i--){
        swap(customers,0,i);
        heapify(customers, i, 0, criteria);

    }

}
void swap(customer *L,int x, int y)
{
    int tmp;
    char chartmp[51];


    strcpy(chartmp,L[x].name);
    strcpy(L[x].name,L[y].name);
    strcpy(L[y].name,chartmp);

    tmp=L[x].transactions;
    L[x].transactions=L[y].transactions;
    L[y].transactions=tmp;

    tmp=L[x].items_purchased;
    L[x].items_purchased=L[y].items_purchased;
    L[y].items_purchased=tmp;

    tmp=L[x].amount_paid;
    L[x].amount_paid=L[y].amount_paid;
    L[y].amount_paid=tmp;

}

