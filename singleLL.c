#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
struct Node;
typedef struct Node*PozicijaP;
typedef struct Node {
    int el;
    PozicijaP next;
}Pozicija;
PozicijaP insertAtBegin(PozicijaP Head,int x);
PozicijaP insertAtEnd(PozicijaP Head,int x) ;
PozicijaP insertYAfterX(PozicijaP Head,int x,int y);
PozicijaP insertYBeforeX(PozicijaP Head,int x,int y);
void delete(PozicijaP Head,int x);
void deleteALL(PozicijaP Head);
void printList(PozicijaP Head);
int main() {
    Pozicija head;
    head.next=NULL;
    insertAtBegin(&head,5);
    insertAtBegin(&head,3);
    insertAtBegin(&head,4);
    insertAtBegin(&head,1);
    insertAtEnd(&head,9);
    insertYAfterX(&head,4,2);
    insertYBeforeX(&head,1,0);
    delete(&head,3);
    printList(head.next);
    deleteALL(&head);
    printList(head.next);
    return 0;
}
PozicijaP insertAtBegin(PozicijaP Head,int x) {

    PozicijaP P =(PozicijaP)malloc(sizeof(Pozicija));
    if(P==NULL) {
        printf("Greska pri alokaciji memorije!");
        return NULL;
    }
    P->el=x;
    P->next=Head->next;
    Head->next=P;

    return 0;
}
PozicijaP insertAtEnd(PozicijaP Head,int x) {

    while(Head->next!=NULL) {
        Head=Head->next;
    }
    PozicijaP P =(PozicijaP)malloc(sizeof(Pozicija));
    if(P==NULL) {
        printf("Greska pri alokaciji memorije!");
        return NULL;
    }
    P->el=x;
    P->next=Head->next;
    Head->next=P;

    return 0;
}
PozicijaP insertYAfterX(PozicijaP Head,int x,int y) {

    while(Head->next!=NULL&& Head->el!=x) {
        Head=Head->next;
    }
    PozicijaP P =(PozicijaP)malloc(sizeof(Pozicija));
    if(P==NULL) {
        printf("Greska pri alokaciji memorije!");
        return NULL;
    }
    P->el=y;
    P->next=Head->next;
    Head->next=P;

    return 0;
}
PozicijaP insertYBeforeX(PozicijaP Head,int x,int y) {

    while(Head->next!=NULL&& Head->next->el!=x) {
        Head=Head->next;
    }
    PozicijaP P =(PozicijaP)malloc(sizeof(Pozicija));
    if(P==NULL) {
        printf("Greska pri alokaciji memorije!");
        return NULL;
    }
    P->el=y;
    P->next=Head->next;
    Head->next=P;

    return 0;
}
void delete(PozicijaP Head,int x) {

    PozicijaP prev=NULL;
    if(Head==NULL) {
        printf("Lista je prazna!");
        return;
    }
    while(Head!=NULL && Head->el!=x) {
        prev=Head;
        Head=Head->next;
    }
    prev->next = Head->next;
    free(Head);
}
void deleteALL(PozicijaP Head) {

    PozicijaP privremena = NULL;
	PozicijaP temp = Head->next;

	while (temp != NULL) {
		privremena = temp;
		temp = temp->next;
		free(privremena);
	}

	Head->next = NULL;
	printf("Lista je izbrisana!\n");
}
void printList(PozicijaP Head) {

    if(Head==NULL) {
        printf("Lista prazna!\n");
        return;
    }
    while(Head!=NULL) {
        printf("%d\n",Head->el);
        Head=Head->next;
    }
}