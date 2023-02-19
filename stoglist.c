#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#define ER
struct _stogList;
typedef struct _stogList *StogP;
typedef struct _stogList {
    int el;
    StogP next;
} Stog;
void push(int x, StogP top );
void printStog(StogP top);
int topElement(StogP top);
void pop(StogP top);
int is_empty(StogP top);
int main() {
    Stog top;
    top.next=NULL;
    int topEl;
    push(5,&top);
    push(3,&top);
    push(7,&top);
    push(0,&top);
    printStog(top.next);
    topEl=topElement(top.next);
    if(!is_empty(top.next)){
        printf("Element na vrhu je: %d\n",topEl);
    }
    pop(&top);
    printStog(top.next);
    topEl=topElement(top.next);
    if(!is_empty(top.next)){
        printf("Element na vrhu je: %d\n",topEl);
    }
    pop(&top);
    printStog(top.next);
    topEl=topElement(top.next);
    if(!is_empty(top.next)){
        printf("Element na vrhu je: %d\n",topEl);
    }
    pop(&top);
    printStog(top.next);
    topEl=topElement(top.next);
    if(!is_empty(top.next)){
        printf("Element na vrhu je: %d\n",topEl);
    }
    pop(&top);
    printStog(top.next);
    topEl=topElement(top.next);
    if(!is_empty(top.next)){
        printf("Element na vrhu je: %d\n",topEl);
    }
    return 0;
}
int is_empty(StogP top) {
    if(top == 0)
      return 1;
    return 0;
}
int topElement(StogP top){
    if(!is_empty(top)){
        return top->el;
    }
    return is_empty(top);
}
void push(int x, StogP top ) {

    StogP temp=top;
    StogP q=(StogP)malloc(sizeof(Stog));
    if(q==NULL) {
        printf("Problem u alokaciji!\n");
    }
    q->el=x;
    q->next=temp->next;
    temp->next=q;
}
void pop(StogP top){

    StogP temp=top;
    StogP priv=NULL;
    int x;
    if(is_empty(temp)) {
        printf("Stog je prazan!\n");
    }
    else {
        priv=temp->next;
        x=priv->el;
        temp->next=priv->next;
        free(priv);
    }
}
void printStog(StogP top) {

    StogP temp=top;
    if(is_empty(temp)) {
        printf("Stog je prazan!\n");
        return;
    }
    while(!is_empty(temp)) {
        printf("%d\n",temp->el);
        temp=temp->next;
        printf("\n");
    }
}