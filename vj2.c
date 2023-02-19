#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
#define MAX_NAME_LEN (64)
#define MAX_ID_LEN (64)

struct _stabloRacuna;
typedef struct _stabloRacuna* StabloR;
typedef struct _stabloRacuna {
    char imeRacuna[MAX_NAME_LEN];
    char valuta[MAX_NAME_LEN];
    double iznos;
    StabloR lijevo;
    StabloR desno;
} StabloRacuna;

struct _stabloKlijenata;
typedef struct _stabloKlijenata* StabloK;
typedef struct _stabloKlijenata {
    char imeKlijenta[MAX_NAME_LEN];
    char prezimeKlijenta[MAX_NAME_LEN];
    char OIB[MAX_ID_LEN];
    char dodatniFILE[MAX_NAME_LEN];
    StabloK lijevo;
    StabloK desno;
    StabloR dijete;
} StabloKlijenta;

StabloK insertInTreeOfClients(StabloK root,StabloK K);
StabloK createTreeOfClients(StabloK root);
int compareClients(StabloK K1,StabloK K2);
void printTreeOfClients(StabloK root);
void printTreeOfBills(StabloR root);
void createTreeOfBills(StabloK rootKlijenata);
StabloR insertInBillsTree(StabloR rootRacuna,StabloR R);
void findClientsByValute(StabloK root,char* valute);
int clientHasValute(StabloR root,char* valute);
void printTreeOfBillsWithValuete(StabloR rootRacuna,char*valute);
int main() {
    StabloK rootKlijenata = NULL;
    rootKlijenata=createTreeOfClients(rootKlijenata);
    printTreeOfClients(rootKlijenata);
  	printf("-----------------");
  	char valute[MAX_NAME_LEN];
  	printf("Unesite vaultu:\n");
  	scanf("%s",valute);
  	findClientsByValute(rootKlijenata,valute);
    return 0;
}

StabloK createTreeOfClients(StabloK root) {
    FILE *fp = NULL;
    fp=fopen("klijenti.txt","r");
    if(fp==NULL) {
        printf("Datoteka se nije otvorila!");
        return NULL;
    }
    while(1) {
        StabloK K =(StabloK)malloc(sizeof(StabloKlijenta));
        K->desno=K->lijevo=NULL;
        K->dijete=NULL;
        if(fscanf(fp,"%s %s %s %s",K->imeKlijenta,K->prezimeKlijenta,K->OIB,K->dodatniFILE)!=4) {
            free(K);
            break;
        }
        root = insertInTreeOfClients(root,K);
      	createTreeOfBills(K);
    }
    fclose(fp);
    return root;
}
void createTreeOfBills(StabloK K) {
    FILE *fp = NULL;
    fp=fopen(K->dodatniFILE,"r");
    if(fp==NULL) {
        printf("Datoteka se nije otvorila!");
        return;
    }
    while(1) {
        StabloR R =(StabloR)malloc(sizeof(StabloRacuna));
        R->desno=R->lijevo=NULL;
        if(fscanf(fp," %[^,],%[^,],%lf",R->imeRacuna,R->valuta,&R->iznos)!=3) {
            free(R);
            break;
        }
      	printf("Racun: %s %s %lf\n", R->imeRacuna, R->valuta, R->iznos);
        K->dijete=insertInBillsTree(K->dijete,R);
    }
    fclose(fp);
}
StabloR insertInBillsTree(StabloR rootRacuna,StabloR R) {
    if (rootRacuna == NULL)
        return R;
    if(strcmp(rootRacuna->valuta,R->valuta)>0){
        rootRacuna->lijevo=insertInBillsTree(rootRacuna->lijevo,R);
    }
    if(strcmp(rootRacuna->valuta,R->valuta)<0){
        rootRacuna->desno=insertInBillsTree(rootRacuna->desno,R);
    }
    return rootRacuna;
}
int compareClients(StabloK K1,StabloK K2) {

    if(strcmp(K1->imeKlijenta,K2->imeKlijenta)>0){
        return 1;
    }
    if(strcmp(K1->imeKlijenta,K2->imeKlijenta)<0){
        return -1;
    }
    if(strcmp(K1->prezimeKlijenta,K2->prezimeKlijenta)>0){
        return 1;
    }
    if(strcmp(K1->prezimeKlijenta,K2->prezimeKlijenta)<0){
        return -1;
    }
    if(K1->OIB>K2->OIB){
        return 1;
    }
    if(K1->OIB<K2->OIB){
        return -1;
    }
    return 0;

}
StabloK insertInTreeOfClients(StabloK root,StabloK K) {
    if (root == NULL)
        return K;
    if(compareClients(root,K)>0){
        root->lijevo=insertInTreeOfClients(root->lijevo,K);
    }
    if(compareClients(root,K)<0){
        root->desno=insertInTreeOfClients(root->desno,K);
    }

    return root;
}

void printTreeOfClients(StabloK rootKlijenata) {
    if(rootKlijenata==NULL) {
        return;
    }
    printTreeOfClients(rootKlijenata->lijevo);

    printf("\nKlijent:%s %s %s\n",rootKlijenata->imeKlijenta,rootKlijenata->prezimeKlijenta,rootKlijenata->OIB);
  	printf("Racuni:\n");
    printTreeOfBills(rootKlijenata->dijete);
  	printTreeOfClients(rootKlijenata->desno);
}
void printTreeOfBillsWithValuete(StabloR rootRacuna,char*valute) {
    if(rootRacuna==NULL) {
        return;
    }
    printTreeOfBillsWithValuete(rootRacuna->lijevo,valute);
    //
  	if(strcmp(rootRacuna->valuta,valute)==0){
    	printf("- %s: %lf %s\n",rootRacuna->imeRacuna,rootRacuna->iznos,rootRacuna->valuta);
    }
    //
    printTreeOfBillsWithValuete(rootRacuna->desno,valute);
}
void printTreeOfBills(StabloR rootRacuna) {
    if(rootRacuna==NULL) {
        return;
    }
    printTreeOfBills(rootRacuna->lijevo);
    printf("- %s: %lf %s\n",rootRacuna->imeRacuna,rootRacuna->iznos,rootRacuna->valuta);
    printTreeOfBills(rootRacuna->desno);
}
void findClientsByValute(StabloK root,char* valute) {

  if(root==NULL) {
    return;
  }
  findClientsByValute(root->lijevo,valute);

  if(clientHasValute(root->dijete,valute)){
    printf("\nKlijent:%s %s %s\n",root->imeKlijenta,root->prezimeKlijenta,root->OIB);
  	printf("Racuni:\n");
    printTreeOfBillsWithValuete(root->dijete, valute);
  }

  findClientsByValute(root->desno,valute);
}
int clientHasValute(StabloR root,char* valute) {
  if(root==NULL) {
    return 0;
  }

  int hasInLeft = clientHasValute(root->lijevo,valute);
  if (hasInLeft == 1)
    return 1;

  if(strcmp(root->valuta,valute)==0)
    return 1;

  int hasInRight = clientHadValute(root->desno,valute);
  if (hasInRight == 1)
    return 1;

  return 0;
}






















