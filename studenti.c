#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define MAX_NAME_LENGTH (64)

struct _listaStudenata;
typedef struct _listaStudenta *ListaP;
typedef struct _listaStudenta {
    char imeStudenta[MAX_NAME_LENGTH];
    char prezimeStudenta[MAX_NAME_LENGTH];
    double postotak;
    ListaP next;
}ListaStudenata;
void createListOfStudents(ListaP Head,char*filename);
void insertToList(ListaP Head, ListaP new);
void printList(ListaP Head);
void createFinalList(ListaP Head,ListaP Head1,ListaP Head2);
ListaP findStudent(ListaP Head,ListaP S);
void insertInFinalList(ListaP Head,ListaP S,double finalProsjek);
void printFinalList(ListaP Head);
int GetGrade(double finalPost);
int main() {

    ListaStudenata Head1;
    Head1.next=NULL;
    ListaStudenata Head2;
    Head2.next=NULL;
    ListaStudenata Head;
    Head.next=NULL;

	createListOfStudents(&Head1, "Subject1.txt");
    createListOfStudents(&Head2, "Subject2.txt");
    createFinalList(&Head,&Head1,&Head2);
    return 0;
}

void createListOfStudents(ListaP Head,char*filename){
    FILE *fp=NULL;
    fp=fopen(filename,"r");
    if(fp==NULL) {
        printf("Datoteka se nije otvorila!\n");
        return;
    }
    while(1) {
        ListaP S=(ListaP)malloc(sizeof(ListaStudenata));
        S->next=NULL;
        if(fscanf(fp,"%s %s %lf%%",S->imeStudenta,S->prezimeStudenta,&S->postotak)!=3){
            free(S);
            break;
        }
        //printf("'%s' '%s' '%lf'\n",S->imeStudenta,S->prezimeStudenta,S->postotak);
		insertToList(Head, S);
    }
    fclose(fp);
	printList(Head);
}

void insertToList(ListaP Head, ListaP new) {
    ListaP temp=Head;
    while(temp->next!=NULL){
        temp=temp->next;
    }
    new->next=temp->next;
    temp->next=new;
}

void printList(ListaP Head){
	printf("\n\n");
    ListaP temp=Head->next;
    if(temp==NULL){
        printf("Lista je prazna!\n");
        return;
    }
    while(temp!=NULL) {
        printf("%s %s %lf\n",temp->imeStudenta,temp->prezimeStudenta,temp->postotak);
        temp=temp->next;
    }
}
void createFinalList(ListaP Head,ListaP Head1,ListaP Head2) {

    ListaP temp=Head1;
    while(temp->next!=NULL) {
		ListaP S1 = temp->next;
		printf("Obradujem studenta iz liste1: %s %s %lf\n", S1->imeStudenta, S1->prezimeStudenta, S1->postotak);
        ListaP S2=findStudent(Head2,S1);
		if (S2 != NULL) {
			printf("Nasao studenta u liste2: %s %s %lf\n", S2->imeStudenta, S2->prezimeStudenta, S2->postotak);
		}
        double finalprosjek=(S1->postotak + S2->postotak)/2;
        if(finalprosjek>=50.00){
            insertInFinalList(Head,S1,finalprosjek);
        }

        temp=temp->next;
    }
	printFinalList(Head);

}
void printFinalList(ListaP Head){
	printf("\n\n");
    ListaP temp=Head->next;
    if(temp==NULL){
        printf("Lista je prazna!\n");
        return;
    }
    while(temp!=NULL) {
        printf("%s %s - %d (%lf)\n",temp->imeStudenta,temp->prezimeStudenta,GetGrade(temp->postotak),temp->postotak);
        temp=temp->next;
    }
}
int GetGrade(double finalPost) {

	if (finalPost<50) {
		return 1;
	}
    if(finalPost>=50 && finalPost <60){
        return 2;
    }
    if(finalPost>=60 && finalPost <74){
        return 3;
    }
    if(finalPost>=74 && finalPost <87){
        return 4;
    }
    return 5;
}
void insertInFinalList(ListaP Head,ListaP S,double finalProsjek) {

    ListaP temp=Head;
    while(temp->next!=NULL && temp->next->postotak>finalProsjek) {
        temp=temp->next;
    }
    ListaP new=(ListaP)malloc(sizeof(ListaStudenata));
    new->postotak=finalProsjek;
    strcpy(new->imeStudenta,S->imeStudenta);
    strcpy(new->prezimeStudenta,S->prezimeStudenta);
    new->next=temp->next;
    temp->next=new;

}
int compareStudent(ListaP S1,ListaP S2) {
	// usporedi po prezimenu pa po imenu, 0 vrati tek na kraju ako je sve isto

    if(strcmp(S1->prezimeStudenta,S2->prezimeStudenta)>0) {
        return 1;
    }
    if(strcmp(S1->prezimeStudenta,S2->prezimeStudenta)<0) {
        return -1;
    }

    if(strcmp(S1->imeStudenta,S2->imeStudenta)>0) {
        return 1;
    }
    if(strcmp(S1->imeStudenta,S2->imeStudenta)<0) {
        return -1;
    }

	return 0;
}
ListaP findStudent(ListaP Head,ListaP S) {

    ListaP temp=Head;
    while(temp->next!=NULL){
        if(compareStudent(temp->next, S) == 0){
            return temp->next;
        }
        temp=temp->next;
    }
	printf("[!] Nisam nasao studenta: %s %s\n", S->imeStudenta, S->prezimeStudenta);
    return NULL;
}