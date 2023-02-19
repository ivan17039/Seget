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
PozicijaP insertEmpty(PozicijaP Head,int x);

PozicijaP deleteX(PozicijaP Head,int x);
PozicijaP deleteALL(PozicijaP Head);
void printList(PozicijaP Head);
PozicijaP makeXBegining(PozicijaP Head,int x);
int main() {
    PozicijaP head = NULL;
    head = insertEmpty(head,5);
    head = insertAtBegin(head,1);
    head = insertAtBegin(head,3);
    head = insertAtBegin(head,7);
    head = insertAtEnd(head,0);
    head = insertYAfterX(head,7,2);
    head = insertYBeforeX(head,5,8);
    printList(head);
    head = deleteX(head,0);
    printList(head);
    head = deleteX(head,7);
    printList(head);
    head = deleteALL(head);
    printList(head);
    return 0;
}
PozicijaP insertEmpty(PozicijaP Head,int x) {

    if(Head!=NULL) {
        return Head;
    }
    PozicijaP P =(PozicijaP)malloc(sizeof(Pozicija));
    P->el=x;
    P->next = P;
    Head = P;
    return Head;
}
PozicijaP insertAtBegin(PozicijaP Head,int x) {

    if(Head==NULL) {
        return insertEmpty(Head,x);
    }
    PozicijaP P =(PozicijaP)malloc(sizeof(Pozicija));
    if(P==NULL) {
        printf("Greska pri alokaciji memorije!");
        return Head;
    }
    P->el=x;
    P->next = Head->next;
    Head->next = P;
    return Head;
}
PozicijaP insertAtEnd(PozicijaP Head,int x) {

    if(Head==NULL) {
        return insertEmpty(Head,x);
    }
    PozicijaP P =(PozicijaP)malloc(sizeof(Pozicija));
    if(P==NULL) {
        printf("Greska pri alokaciji memorije!");
        return NULL;
    }
    P->el=x;
    P->next = Head->next;
    Head->next = P;
    Head=P;
    return Head;
}
PozicijaP makeXBegining(PozicijaP Head,int x) {

    PozicijaP temp = Head;
    do {
        if(temp->el==x){
            Head=temp;
        }
        temp = temp->next;
    } while (temp != Head);
    return Head;
}
PozicijaP insertYAfterX(PozicijaP Head,int x,int y) {

    PozicijaP temp = Head->next;
    PozicijaP P =(PozicijaP)malloc(sizeof(Pozicija));
    if(P==NULL) {
        printf("Greska pri alokaciji memorije!");
        return NULL;
    }
    do {
        if(temp->el==x){
            P->el=y;
            P->next=temp->next;
            temp->next=P;
            return Head;
        }
        temp = temp->next;
    } while (temp != Head->next);

    return Head;
}
PozicijaP insertYBeforeX(PozicijaP Head,int x,int y) {

    PozicijaP temp = Head->next;
    PozicijaP P =(PozicijaP)malloc(sizeof(Pozicija));
    if(P==NULL) {
        printf("Greska pri alokaciji memorije!");
        return NULL;
    }
    do {
        if(temp->next->el==x){
            P->el=y;
            P->next=temp->next;
            temp->next=P;
            return Head;
        }
        temp = temp->next;
    } while (temp != Head->next);

    return Head;
}
PozicijaP deleteX(PozicijaP Head,int x) {

    if(Head==NULL) {
        return Head;
    }
    if (Head->el == x && Head->next == Head) {
        free(Head);
        return NULL;
    }
    PozicijaP temp1=Head->next;
    PozicijaP temp2;
    while(temp1->next!=Head->next && temp1->next->el!=x)
    {
        temp1=temp1->next;
    }
    temp2=temp1->next;
    temp1->next=temp2->next;
    free(temp2);
    if(temp2==Head)
        return temp1;
    else
        return Head;
}
PozicijaP deleteALL(PozicijaP Head) {

	PozicijaP temp = Head->next;
	while (temp != Head->next) {
		temp = temp->next;
		free(temp);
	}
    return NULL;
}
void printList(PozicijaP Head) {

    if (Head == NULL){
        printf("List je prazna!\n");
        return;
    }
    PozicijaP temp = Head->next;
    do {
        printf("%d ", temp->el);
        temp = temp->next;
    } while (temp != Head->next);
    printf("\n");
}
