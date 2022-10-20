#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define FILE_DIDNT_OPEN_ERROR (-1)
#define MAX_LINE (1024) // u linuxu 4096
#define MAX_FILE_NAME (256)
typedef struct {
    char ime[10];
    char prezime[10];
    int bodovi;
}student;

int countStudentsFromFile(char* );
void readStudentsFromFile(char*, student*);
void printStudents(student*, int);

int main(void)
{
    char filename[MAX_FILE_NAME] = { 0 };
    int br = 0;
    student* studenti;
    

    printf("Insert filename > ");
    scanf(" %s", filename);
    br = countStudentsFromFile(filename);
    studenti = (student*)malloc(br * sizeof(student));
    printf("Broj studenata u datoteci %s je %d\n\n", filename, br);

    readStudentsFromFile(filename, studenti);
    printStudents(studenti, br);

    return 0;
}

int countStudentsFromFile(char* filename)
{
    FILE* fp = NULL;
    int count = 0;
    char buffer[MAX_LINE] = { 0 };

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Dear customer, the file %s didn't open!\r\n", filename);
        return FILE_DIDNT_OPEN_ERROR;
    }

    while (fgets(buffer, MAX_LINE, fp) != NULL) { //while not found end of file (EOF)

        if (strcmp("\n", buffer) != 0 && strcmp("\r\n", buffer) != 0) {
            count++;
        }

    }


    fclose(fp);
    return count;
}
void readStudentsFromFile(char* filename, student* studenti)
{
    FILE* fp = NULL;
    int i = 0;
    char buffer[MAX_LINE] = { 0 };
    

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Dear customer, the file %s didn't open!\r\n", filename);
        return FILE_DIDNT_OPEN_ERROR;
    }

    while (fscanf(fp, "%s %s %d", studenti[i].ime, studenti[i].prezime, &studenti[i].bodovi) == 3) {
        i++;
    }

    fclose(fp);
    
}
void printStudents(student* studenti, int br)
{
    int i;
    int max_br_bodova=studenti[0].bodovi;
    double r;
    for (i = 1; i < br; i++) {
        if (studenti[i].bodovi > max_br_bodova)
            max_br_bodova = studenti[i].bodovi;
    }



    for (i = 0; i < br; i++) {
        r = (double)studenti[i].bodovi / max_br_bodova * 100;
        printf("%s %s ima %d bodova sto je %.2f relativnih.\n", studenti[i].ime, studenti[i].prezime, studenti[i].bodovi,r);
        
    }
    

}
