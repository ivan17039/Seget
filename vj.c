#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_ID_LEN (8)
#define MAX_NAME_LEN (64)
#define FILE_DIDNT_OPEN_ERROR (-1)

struct _date;
typedef struct _date *DateP;
typedef struct _date {
    int year;
    int month;
    int day;
} Date;

struct _vehicle;
typedef struct _vehicle *VehicleP;
typedef struct _vehicle {
    char brandName [MAX_NAME_LEN];
    char modelName [MAX_NAME_LEN];
    DateP date;
    VehicleP next;
} Vehicle;

struct _person; // forward deklaracija
typedef struct _person *PersonP;
typedef struct _person {
    char id [MAX_ID_LEN];
    char firstName [MAX_NAME_LEN];
    char lastName [MAX_NAME_LEN];
    PersonP next;
    VehicleP child;
} Person;

void createListOfPeople(PersonP head);
void readVehicles(PersonP head);
void printList(PersonP head);
PersonP findPersonByID(PersonP head,char id[MAX_ID_LEN]);

int main(){
    Person head;
    head.next=NULL;
    createListOfPeople(&head);
    readVehicles(&head);
    printList(head.next);
    return 0;
}

int compare(PersonP a, PersonP b) {
    int lastNameCmp = strcmp(a->lastName, b->lastName); // -1
    if (lastNameCmp != 0)
        return lastNameCmp; // -1

    // lastNameCmp == 0 -- prezime su ista, uporedi imena
    return strcmp(a->firstName, b->firstName);
}

void createListOfPeople(PersonP head) {
    int i=0;
    FILE *fp=NULL;
    fp=fopen("people.txt","r");
    if (fp == NULL)
    {
        printf("Dear customer, the file people.txt didn't open!\r\n");
        return;
    }
    while (1) {
        PersonP P = (PersonP)malloc(sizeof(Person));
        if (fscanf(fp, "%s %s %s", P->firstName, P->lastName, P->id) != 3)
            break;

        PersonP temp = head;
        while (temp->next!=NULL && compare(temp->next, P) < 0) {
            temp = temp->next;
        }
        P->next = temp->next;
        temp->next = P;
        P->child=NULL;
    }
    fclose(fp);
}
void printList(PersonP head) {

    if(head==NULL) {
        printf("Lista je prazna!");
        return;
    }
    while(head!=NULL) {
        printf("%s %s %s\n",head->firstName,head->lastName,head->id);

        // ispis sva vozila
        if(head->child==NULL) {
            printf("  NEMA VOZILA!\n");
        }
        else {
            VehicleP temp=head->child;
            while(temp!=NULL) {
                printf("  %s %s %d %d %d\n",temp->brandName,temp->modelName,temp->date->year,temp->date->month,temp->date->day);
                temp=temp->next;
            }
        }
        head=head->next;
        printf("\n");
    }
}
void readVehicles(PersonP head) {
    int i=0;
    FILE *fp=NULL;
    fp=fopen("vehicle.txt","r");
    if (fp == NULL)
    {
        printf("Dear customer, the file people.txt didn't open!\r\n");
        return;
    }
    while (1) {
        char id[MAX_ID_LEN];
        VehicleP V = (VehicleP)malloc(sizeof(Vehicle));
        DateP D = (DateP)malloc(sizeof(Date));
        V->date = D;
        if (fscanf(fp, "%s %s %d %d %d %s",
            V->brandName, V->modelName, &V->date->year, &V->date->month, &V->date->day, id) != 6)
        {
            break;
        }
        PersonP P = findPersonByID(head,id);
        if(P==NULL) {
            printf("Nema te osobe!\n");
            continue;
        }
        // dodaj V u listu vozila osobe P
        V->next=P->child;
        P->child = V;
    }
}
PersonP findPersonByID(PersonP head,char id[MAX_ID_LEN]) {

    while(head!=NULL) {
        if(strcmp(head->id,id)==0){
            return head;
        }
        head=head->next;
    }
    return NULL;
}
