//Cenk Zenginer 2385789

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
   char sequence[81];
   struct node *next;
};

struct pattern{
    char p[81];
    int times;
    int sequences;
};

struct node * readSequences(char filename[]);
void searchPatterns(struct node *head, struct pattern *patterns, int numberOfPatterns);
void sortPatterns(struct pattern *patterns, int numberOfPatterns);
void printPatterns(struct pattern *patterns, int numberOfPatterns);

int main() {

    struct node *head = NULL;
    struct pattern *patterns = NULL;
    char file[100];
    int numberOfPatterns;
    int i;

    printf("Enter the file path containing the DNA sequences: ");
    scanf("%s", file);
    head = readSequences(file);

    printf("Enter the number of patterns: ");
    scanf("%d", &numberOfPatterns);

    patterns = (struct pattern*)malloc(numberOfPatterns*sizeof(struct pattern)); // Allocate memory for patterns

    for (i = 0; i < numberOfPatterns; i++) {
        printf("Enter the pattern: ");
        scanf("%s", patterns[i].p);
        patterns[i].times = 0;
        patterns[i].sequences = 0;
    }

    searchPatterns(head, patterns, numberOfPatterns);
    sortPatterns(patterns, numberOfPatterns);
    printPatterns(patterns, numberOfPatterns);

    free(patterns);
    return 0;
}

struct node * readSequences(char filename[]){

    struct node *head = NULL;
    struct node *current = NULL;
    char sequence[81];
    int length;

    FILE *file = fopen(filename, "r");


    while (fgets(sequence, sizeof(sequence), file) != NULL){ //Reading each line of the file


        length=(int)strlen(sequence);

        if (length > 0 && sequence[length-1] == '\n') {//If the last character is a newline
            sequence[length-1] = '\0';
        }

        struct node *new_node = malloc(sizeof(struct node));  //Allocating the memory for new node

        strcpy(new_node->sequence, sequence); //Copying the sequence into new node
        new_node->next = NULL;

        if (head == NULL){ //If list is empty
            head = new_node;
            current = head;
        } else {
            current->next = new_node;
            current = new_node;
        }
    }

    fclose(file);


	return head;
}

void searchPatterns(struct node *head, struct pattern *patterns, int numberOfPatterns){

    struct node *current = head;
    int i,j,k;
    int p,t,h,d = 4,q = 11;
    int patternLen,sequenceLen;
    int foundInSequence;
    int found;


    while (current != NULL) { //Traverse the list
        for (i = 0; i < numberOfPatterns; i++) {
            patternLen = strlen(patterns[i].p);
            sequenceLen = strlen(current->sequence);
            h = 1;
            p = 0;
            t = 0;
            foundInSequence = 0;//Checking if the pattern is found in the sequence

            for (j = 0; j < patternLen; j++) { //Calculate hash value for pattern
                p = (d * p + patterns[i].p[j]) % q;
                t = (d * t + current->sequence[j]) % q;
            }


            for (j = 0; j < patternLen-1; j++) { //Calculating h=d^(patternlength-1)%q
                h=(h*d)%q;
            }

            for (j = 0; j <= sequenceLen - patternLen; j++) { //Slide the pattern over sequence
                if (p == t) {
                    found = 1;
                    for (k = 0; k < patternLen; k++) {
                        if (current->sequence[j + k] != patterns[i].p[k]) {
                            found = 0;
                            break;
                        }
                    }
                    if (found) { //If pattern found
                        patterns[i].times++;
                        foundInSequence = 1; //if pattern is found set 1
                    }
                }


                if (j < sequenceLen - patternLen) {//If we cannot reached the end of the sequence
                    t = (d * (t - current->sequence[j] * h) + current->sequence[j + patternLen]) % q;

                    if (t < 0) { //If t is negative, converting to positive
                        t = (t + q);
                    }
                }
            }
                    if (foundInSequence) { // If the flag is set, increment the sequences count
                          patterns[i].sequences++;
                    }


        }



        current = current->next;
    }

}

void sortPatterns(struct pattern *patterns, int numberOfPatterns){

    struct pattern val;
    int i,j;

    for (i = 1; i < numberOfPatterns; i++) { //Insertion sort and it starts from second element

        val = patterns[i];
        j = i - 1;

        while (j >= 0 && patterns[j].times < val.times){ //smaller than key move one position
            patterns[j+1] = patterns[j];
            j = j-1;
        }

        patterns[j + 1] = val;
    }

}

void printPatterns(struct pattern *patterns, int numberOfPatterns) {

    int i;

    printf("\n");

    for (i = 0; i < numberOfPatterns; i++) {


        printf("%s is detected %d ", patterns[i].p, patterns[i].times);

        if (patterns[i].times > 1) { //if greater than 1 it should be "times"
            printf("times ");
        } else {
            printf("time ");
        }

        printf("in %d ", patterns[i].sequences); //if greater than 1 it should be "sequences"

        if (patterns[i].sequences > 1) {
            printf("sequences\n");
        } else {
            printf("sequence\n");
        }
    }
}




