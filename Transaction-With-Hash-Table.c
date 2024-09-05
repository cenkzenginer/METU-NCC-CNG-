/**Cenk Zenginer
   ID:2385789**/
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

//DO NOT CHANGE FUNCTION PROTOTYPES
void menu();
void printCustomers(customer *, int);
int countCustomers(FILE*);
void readTransactions(FILE*, customer* ,int);
customer* createHashTable();
customer* addCustomer(customer*, customer, int, int*, int);
customer* rehash(customer*, int*, int);
void printTable(customer*, int);
void searchTable(customer*, int, char[], int);

//DO NOT CHANGE THE main FUNCTION
int main() {

    FILE *inFile;
    int no_of_customers = 0;
    customer *customers;
    customer *hashTable;

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

    hashTable = createHashTable();
    int hashTableSize = 11;
    char criteria;

    printf("Enter your hashing criteria: ");
    fflush(stdin);
    scanf("%c", &criteria);

    while (criteria != '1' && criteria != '2' && criteria != '3'){
        printf("Error! Please enter a valid hashing criteria: ");
        fflush(stdin);
        scanf("%c", &criteria);
    }
    fflush(stdin);

    int i;
    for (i = 0; i < no_of_customers; i++){
        hashTable = addCustomer(hashTable, customers[i], i, &hashTableSize, criteria - '0');
        printf("%s has been added to the table, the hash table now can be seen below:", customers[i].name);
        printTable(hashTable, hashTableSize);
    }

    char command = 0;
    int exit = 0;
    char searchName[81];
    while (exit != 1) {
        menu();
        printf("\nCommand: ");
        fflush(stdin);
        scanf("%c", &command);

        if (command == '1') {
            printf("Enter the customer's name: ");
            fflush(stdin);
            scanf("%s", searchName);
            searchTable(hashTable, hashTableSize, searchName, criteria - '0');
        }
        else if (command == '2'){
            printTable(hashTable, hashTableSize);
        }
        else if (command == '3'){
            exit = 1;
            printf("Goodbye!\n");
        }
        else{
            printf("Please enter a valid command!\n");
        }
    }
    free(customers);
    free(hashTable);
    return 0;
}

//DO NOT CHANGE THE menu FUNCTION
void menu () {
    printf("Please choose one of the following options:\n"
           "(1) Search a customer\n"
           "(2) Display hashtable\n"
           "(3) Exit\n");
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

//DO NOT CHANGE THE countCustomers FUNCTION
int countCustomers (FILE *inFile){
    int no_of_customers = 0;
    char **names;
    char **temp;
    char userName[100];
    int transactionId;
    char transactionTime[100];
    char itemDescription[100];
    int numberOfItemsPurchased;
    float costPerItem;
    char country[100];
    int exists = 0;
    char c;
    while ((c = fgetc(inFile)) != EOF) {
        if (c == '\n') {
            break;
        }
    }
    fscanf(inFile, "%[^;];%d;%[^;];%[^;];%d;%f;%[^\n]\n",
           userName, &transactionId, transactionTime,  itemDescription,
           &numberOfItemsPurchased, &costPerItem, country);
    no_of_customers++;
    names = (char**) malloc (sizeof(char*) * (no_of_customers));
    names[no_of_customers-1] = (char*) malloc(100 * sizeof (char));
    strcpy(names[no_of_customers - 1], userName);

    while (fscanf(inFile, "%[^;];%d;%[^;];%[^;];%d;%f;%[^\n]\n",
                  userName, &transactionId, transactionTime, itemDescription,
                  &numberOfItemsPurchased, &costPerItem, country) != EOF) {
        exists = 0;
        for (int i = 0; i < no_of_customers; ++i) {
            if (strncmp(names[i], userName, strlen(userName)) == 0){
                exists = 1;
                break;
            }
        }
        if (exists)
            continue;
        temp = (char**) malloc (sizeof(char*) * (no_of_customers));
        for (int i = 0; i < no_of_customers; ++i) {
            temp[i] = (char*) malloc(100 * sizeof (char));
            strcpy(temp[i], names[i]);
        }
        free(names);

        names = (char**) malloc (sizeof(char*) * (no_of_customers + 1));
        for (int i = 0; i < no_of_customers; ++i) {
            names[i] = (char*) malloc(100 * sizeof (char));
            strcpy(names[i], temp[i]);
        }
        free(temp);
        names[no_of_customers] = (char*) malloc(100 * sizeof (char));
        strcpy(names[no_of_customers], userName);
        no_of_customers++;

    }
    return no_of_customers;
}

//DO NOT CHANGE THE readTransactions FUNCTION
void readTransactions (FILE* inFile, customer* customers, int no_of_customers) {
    char userName[100];
    int transactionId;
    char transactionTime[100];
    char itemDescription[100];
    int numberOfItemsPurchased;
    float costPerItem;
    char country[100];
    int exists = 0;
    int filled = 0;
    char c;

    for (int i = 0; i < no_of_customers; ++i) {
        strcpy(customers[i].name, "unassigned");
        customers[i].amount_paid = 0;
        customers[i].items_purchased = 0;
        customers[i].transactions = 0;
    }

    while ((c = fgetc(inFile)) != EOF) {
        if (c == '\n') {
            break;
        }
    }

    while (fscanf(inFile, "%[^;];%d;%[^;];%[^;];%d;%f;%[^\n]\n",
                  userName, &transactionId, transactionTime, itemDescription,
                  &numberOfItemsPurchased, &costPerItem, country) != EOF) {
        exists = 0; // n
        int i; // n
        for (i = 0; i < no_of_customers; ++i) {
            if(strcmp(userName, customers[i].name) == 0){
                exists = 1;
                break;
            }
        }
        if (exists){
            customers[i].transactions ++;
            customers[i].items_purchased += numberOfItemsPurchased;
            customers[i].amount_paid += (numberOfItemsPurchased * costPerItem);
        }
        else{
            strcpy(customers[filled].name, userName);
            customers[filled].transactions ++;
            customers[filled].items_purchased += numberOfItemsPurchased;
            customers[filled].amount_paid += (numberOfItemsPurchased * costPerItem);
            filled++;
        }
    }
}

customer* createHashTable(){

    int j=0;
    customer *hashTable = (customer*)malloc(11*sizeof(customer));


    while(j<11){
        strcpy(hashTable[j].name,"\0");
        hashTable[j].transactions = 0;
        hashTable[j].items_purchased = 0;
        hashTable[j].amount_paid = 0;
        j++;
    }


    return hashTable;

}

customer* addCustomer(customer* hashTable, customer addedCustomer, int hashTableCapacity, int *hashTableSize, int criteria){

    int i = 0; //index
    int j = 0; //counter
    int s = 0; //step
    int hashfunction2;

    if(criteria==1){ //linear probing
        while(hashTable[i].name[0] != '\0'){
            i=(i+1)%hashTableCapacity;
            s = s+1;
        }
    }
    else if(criteria == 2){//quadratic probing

        while(hashTable[i].name[0] != '\0')
        {
            i = (i+s*s)%hashTableCapacity;
            s=s+1;
        }
    }
    else if(criteria == 3) //double hashing
    {
            hashfunction2 = 7 - (addedCustomer.name[strlen(addedCustomer.name) - 1] - addedCustomer.name[0]) % 7;

            while(hashTable[i].name[0]!='\0')
            {
                i = (i+hashfunction2) % hashTableCapacity;
                s=s+1;
            }
    }

    hashTable[i] = addedCustomer;
    *hashTableSize = *hashTableSize + 1;

    if((float)(*hashTableSize) / hashTableCapacity > 0.5) // checking load factor if it is bigger than 0.5 rehash
    {
        hashTable = rehash(hashTable,&hashTableCapacity,criteria);
    }


    return hashTable;

}

customer* rehash(customer* hashTable, int *hashTableSize, int criteria){

    int currentSize,SizeFurther,prime;
    int i = 0;

    currentSize = *hashTableSize;
    SizeFurther = 2*currentSize;

    do{ //Finding next prime number greater than or equal to new size
         prime = 1;

         for(i = 2; i*i <= SizeFurther; i++)
            {
                if(SizeFurther % i == 0){
                    prime = 0;
                    break;
            }
         }
            if(prime)
         {
                break;
         }

         SizeFurther++;

    }while(1);

    customer *newHashTable = (customer*)malloc(SizeFurther * sizeof(customer));


    for(i=0; i<SizeFurther;i++)
    {
        strcpy(newHashTable[i].name,"\0");
        newHashTable[i].transactions = 0;
        newHashTable[i].items_purchased = 0;
        newHashTable[i].amount_paid = 0;
    }

    for(i=0;i<currentSize;i++)   //Rehashing part
    {
            if(hashTable[i].name[0]!='\0')
                addCustomer(newHashTable,hashTable[i],SizeFurther,hashTableSize,criteria);
    }

    free(hashTable);
    *hashTableSize = currentSize;



    return newHashTable;


}

void printTable(customer *hashTable, int hashTableSize){

    int i;
    printf("%s %5s %10s %12s %10s" ,"\nIndex","Name","Transactions","Items Purchased","Amount Paid");

    for(i=0;i<hashTableSize;i++)
    {
        printf("\n%d",i);

        if(hashTable[i].name != '\0')
            {
                printf("%10S %10d %10d %10.2f ",hashTable[i].name,hashTable[i].transactions,hashTable[i].items_purchased,hashTable[i].amount_paid);
            }

    }

}

void searchTable(customer *hashTable, int hashTableSize, char searchName[], int criteria){

    int i = 0; //i for index
    int s = 0; // s for step
    int hashfunction2;

    if(criteria == 1)           //linear probing
    {
        while(strcmp(hashTable[i].name, searchName) != 0 && hashTable[i].name[0] != '\0')
        {
            i = (i+1) % hashTableSize;
            s = s + 1;
        }
    }
    else if(criteria == 2)      //quadratic probing
    {
        while (strcmp(hashTable[i].name,searchName)!= 0 && hashTable[i].name[0] != '\0')
        {
            i = (i+s*s)%hashTableSize;
            s = s + 1;
        }
    }
    else if(criteria == 3)      //double hashing
    {
            hashfunction2 = 7 - (searchName[strlen(searchName) - 1] - searchName[0]) % 7;

            while(strcmp(hashTable[i].name,searchName) != 0 && hashTable[i].name[0] != '\0')
             {
                i = (i + hashfunction2) % hashTableSize;
                s = s + 1;
             }

    }

    if(strcmp(hashTable[i].name,searchName) == 0)      //found the customer then print it
    {
        printf("\nInformation for customer %s:",hashTable[i].name);
        printf("\nNumber of transactions: %d\nItems purchased:%d\nTotal Amount Paid:%.2f",hashTable[i].transactions,hashTable[i].items_purchased,hashTable[i].amount_paid);
    }
    else
        printf("\nCustomer not found\n");





}


