#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Patients
{
    int id;
    int age;
    int gender;
    char risk[30];
};

struct Patients *load_data(char filename[30],int *line_no)
{
    int i;
    char character;

    FILE *inFile;

    inFile = fopen(filename,"r");

    if(inFile == NULL)
    {
        printf("File was not open.");
        exit(1);
    }

    while((character=fgetc(inFile))!=EOF)
    {
        if(character=='\n')
            *line_no = *line_no + 1;
    }

    *line_no = *line_no + 1;

    fclose(inFile);

    struct Patients *arr;

    arr = (struct Patients*)malloc(sizeof(struct Patients)*(*line_no));


    inFile = fopen(inFile,"r");

    for(i=0;i<line_no;i++)
    {
        fscanf(inFile,"%d %d %d %s",&arr[i].id,&arr[i].age,&arr[i].gender,arr[i].risk);
    }

    fclose(inFile);

    printf("Your data is successfully processed and looks as follows:");

    return(arr);


}
void display_data(struct Patients *arr,int line_no)
{
    int i;

    printf("\n%-10s %-10s %-10s %-10s","ID","Age","Gender","Risk");

    for(i=0;i<line_no;i++)
    {
        printf("\n%d %d %d %s",arr[i].id,arr[i].age,arr[i].gender,arr[i].risk);
    }
}

void process_data(struct Patients *arr, int line_no, char filename[30])
{
    int i;
    float avg_age,total_age=0;
    int low=0,medium=0,high=0;
    int male=0,female=0;

    for(i=0;i<line_no;i++)
    {
        total_age = total_age + arr[i].age;
    }

    for(i=0;i<line_no;i++)
    {
        if(arr[i].gender == 1)
            male++;
        else
            female++;
    }

    for(i=0;i<line_no;i++)
    {
        if(arr[i].risk == "Low")
            low++;
        else if(arr[i].risk == "Medium")
            medium++;
        else
            high++;
    }

    avg_age = total_age/line_no;

    FILE *statFile;

    statFile = fopen(filename,"w");

    if(statFile == NULL)
    {
        printf("File was not open");
        exit(1);
    }

    fprintf(statFile,"%s %.1f","Average age: ",avg_age);
    fprintf(statFile,"%d %s %d %s",male,"Male and",female,"Female patients");
    fprintf(statFile,"%d %s %d %s %d %s",low,"Low,",medium,"Medium and",high,"High risk patients");

    fclose(statFile);

    printf("Average age: %.1f",avg_age);
    printf("\n%d Male and %d Female patients",male,female);
    printf("\n%d Low, %d Medium and %d High risk patients",low,medium,high);
    printf("%s is also updated",filename);

}


int main(int argc,char *argv[])
{
    int *line_no=0;

    char filename[30] = "input.txt";
    char filename2[30] = "stats.txt";

    struct Patients *apatients; //apatiets means all-patients

    apatients = load_data(filename,&line_no);
    display_data(apatients,line_no);
    process_data(apatients,line_no,filename2);



    return 0;
}
