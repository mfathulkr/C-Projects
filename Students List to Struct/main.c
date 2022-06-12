#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define str_size 50

const char* perform_out = ": %s, %s, %s, %d, %s\n";

typedef struct 
{

    int id;
    char name[str_size];
    char surname[str_size];
    char program[str_size];
    int year;
    char email[str_size];
    char status[1];

} student_t;

void find_i(student_t s1[], student_t s2[], char oname[]);
void find_u(student_t s1[], student_t s2[], char oname[]);
void printFile(char oname[], student_t s[], int total);

int main()
{
    char inp_name1[str_size];
    char inp_name2[str_size];
    char oup_name[str_size];

    scanf("%s", inp_name1);
    scanf("%s", inp_name2);
    scanf("%s", oup_name);

    student_t students1[500];
    student_t students2[500];

    int inpcount1 = 0;
    int inpcount2 = 0;

    char *item;

    FILE *inp1 = fopen(inp_name1, "r");
    FILE *inp2 = fopen(inp_name2, "r");
    char lyne1[301];
    char lyne2[301];

    while (fgets(lyne1, 300, inp1))
    {

        item = strtok(lyne1, ";");
        students1[inpcount1].id = atoi(item);

        item = strtok(NULL, ";");
        strcpy(students1[inpcount1].name, item);

        item = strtok(NULL, ";");
        strcpy(students1[inpcount1].surname, item);

        item = strtok(NULL, ";");
        strcpy(students1[inpcount1].program, item);

        item = strtok(NULL, ";");
        students1[inpcount1].year = atoi(item);

        item = strtok(NULL, ";");
        strcpy(students1[inpcount1].email, item);

        item = strtok(NULL, "");
        strcpy(students1[inpcount1].status, item);
    }

    char *item2;

    while (fgets(lyne2, 300, inp2))
    {

        item2 = strtok(lyne2, ";");
        students2[inpcount2].id = atoi(item2);

        item2 = strtok(NULL, ";");
        strcpy(students2[inpcount2].name, item2);

        item2 = strtok(NULL, ";");
        strcpy(students2[inpcount2].surname, item2);

        item2 = strtok(NULL, ";");
        strcpy(students2[inpcount2].program, item2);

        item2 = strtok(NULL, ";");
        students2[inpcount2].year = atoi(item2);

        item2 = strtok(NULL, ";");
        strcpy(students2[inpcount2].email, item2);

        item2 = strtok(NULL, "");
        strcpy(students2[inpcount2].status, item2);
    }

    fclose(inp1);
    fclose(inp2);

    char opr[2];
    scanf("%s", opr);

    if (strcmp(opr, "-i") == 0)
    {
        find_i(students1, students2, oup_name);
    }
    else if (strcmp(opr, "-u") == 0)
    {
        find_u(students1, students2, oup_name);
    }
    else
    {
        printf("Wrong operation");
    }

    return 0;
}

void find_i(student_t s1[], student_t s2[], char oname[])
{

    student_t inter[500];

    int intercount = 0;

    for (int i = 0; i < 500; i++)
    {

        if (s1[i].id == NULL)
        {
            break;
        }

        for (int k = 0; k < 500; k++)
        {
            if (s1[i].id == s2[k].id)
            {
                inter[intercount] = s1[i];
                intercount++;
            }
            if (s2[k].id == NULL)
            {
                break;
            }
        }
    }

    int leninter = sizeof(inter)/sizeof(inter[0]);

    printFile(oname, inter, leninter);
}
void find_u(student_t s1[], student_t s2[], char oname[])
{

    int len1 = sizeof(s1) / sizeof(s1[0]);
    int len2 = sizeof(s2) / sizeof(s2[0]);

    student_t uni[500];

    int unicount = 0;

    int i = 0;
    int j = 0;

    while (i < len1 && j < len2)
    {
        if (s1[i].id < s2[j].id)
        {
            uni[unicount] = s1[i++];
            unicount++;
        }
        else if (s2[j].id < s1[i].id)
        {
            uni[unicount] = s2[j++];
            unicount++;
        }
        else
        {
            uni[unicount] = s2[j++];
            i++;
            unicount++;
        }
    }

    while (i < len1)
    {
        uni[unicount] = s1[i++];
    }
    while(j < len2){
        uni[unicount] = s2[j++];
    }
    
    int lenuni = sizeof(uni)/ sizeof(uni[0]);

    printFile(oname, uni, lenuni);
}
void printFile(char oname[], student_t s[], int total){

    FILE * oup;

    student_t * stu;
    stu = malloc(sizeof(student_t) * total);

    if((oup = fopen(oname, "wb")) == NULL)
    {
        return ;
    }

    for(int i = 0; i < total; i++){
        printf("%d", i);
        fprintf(oup, perform_out, s[i].surname, s[i].name, s[i].program, s[i].year, s[i].email);
    }

}