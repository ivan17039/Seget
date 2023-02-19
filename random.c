#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define MAX 10
struct _list;
typedef struct _list* ListaP;
typedef struct _list {
    int paran;
    ListaP next;
} Lista;

struct _stablo;
typedef struct _stablo* StabloP;
typedef struct _stablo {
    int neparan;
    StabloP lijevo;
    StabloP desno;
} Stablo;
void insertInList(ListaP Head,int num);
void printList(ListaP Head);
StabloP insertInTree(StabloP root,int num);
void printTree(StabloP root);
StabloP AllocateNew(int num);
int listEL=0;
int treeEl=0;
int main() {
    Lista Head;
    Head.next=NULL;
    StabloP root=NULL;
    srand(time(NULL));
    int randomNum;
    printf("Random brojevi:\n");
    while(listEL<4 || treeEl<6){
        randomNum = (rand() % (213 - 123  + 1)) + 123;
        if(randomNum%2==0 && listEL < 4){
            insertInList(&Head,randomNum);
        }
        else if (randomNum%2==1 && treeEl<6) {
            root=insertInTree(root,randomNum);

        }
        printf("%d ",randomNum);
    }
    printf("\nParni: \n");
    printList(Head.next);
    printf("\nNeparni: \n");
    printTree(root);

    return 0;
}
int compare(ListaP L1,ListaP L2) {

    if(L1->paran < L2->paran){
        return 1;
    }
    if(L1->paran > L2->paran){
        return -1;
    }
    return 0;
}
void insertInList(ListaP Head,int num) {
  ListaP q=(ListaP)malloc(sizeof(Lista));
  q->paran = num;

  ListaP temp = Head;
  while (temp->next != NULL && compare(temp->next, q) > 0) {
    temp = temp->next;
  }
  // izasli smo iz while petlje
  	// 1. temp->next == NULL -- dosli smo do kraja liste -- ubaci na kraj
    // 2. temp->next->paran >= num


  if (temp->next != NULL && temp->next->paran == num) {
    free(q);
    return;
  }

  listEL++;
  q->next = temp->next;
  temp->next = q;
}
void printList(ListaP Head) {

    ListaP temp=Head;
    while(temp!=NULL) {
        printf("%d  ",temp->paran);
        temp=temp->next;
    }
}
StabloP AllocateNew(int num)
{
	StabloP newNode = malloc(sizeof( Stablo));++treeEl;
    if (newNode == NULL) {
        printf("Nije moguce alocirati memoriju!");
        return NULL;
    }
  	newNode->neparan = num;
  	newNode->lijevo = NULL;
  	newNode->desno = NULL;
  	return newNode;
}
StabloP insertInTree(StabloP root,int num) {

    if(root==NULL){
        return AllocateNew(num);
    }
    if(root->neparan>num){
        root->lijevo=insertInTree(root->lijevo,num);
    }
    else if(root->neparan<num) {
        root->desno=insertInTree(root->desno,num);
    }

    return root;
}
void printTree(StabloP root) {

    if(root==NULL){
        return;
    }
    printTree(root->lijevo);
    printf("%d ",root->neparan);
    printTree(root->desno);

}