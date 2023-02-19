#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
#define MAX_NAME_LEN (64)
#define MAX_ID_LEN (64)
#define HASH_SIZE (5)

struct _stabloRacuna;
typedef struct _stabloRacuna* StabloR;
typedef struct _stabloRacuna {
    char imeRacuna[MAX_NAME_LEN];
    char valuta[MAX_NAME_LEN];
    double iznos;
    double tecaj_hrk;
    StabloR lijevo;
    StabloR desno;
} StabloRacuna;

struct _listaKlijenata;
typedef struct _listaKlijenata* ListaK;
typedef struct _listaKlijenata {
    char imeKlijenta[MAX_NAME_LEN];
    char prezimeKlijenta[MAX_NAME_LEN];
    char OIB[MAX_ID_LEN];
    char dodatniFILE[MAX_NAME_LEN];
    ListaK next;
    StabloR dijete;
} ListaKlijenta;

void readClients(ListaKlijenta* HashTable);
void insertIntoList(ListaK Head,ListaK new);
void printList(ListaK Head);
void printHashTable(ListaKlijenta*HashTable);
int main() {
    ListaKlijenta HashTable[HASH_SIZE];
    for(int i=0;i<5;i++) {
        HashTable[i].next = NULL;
    }
    readClients(HashTable);
    printHashTable(HashTable);
    return 0;
}

void readClients(ListaKlijenta* HashTable) {
    FILE *fp = NULL;
    fp=fopen("klijenti.txt","r");
    if(fp==NULL) {
        printf("Datoteka se nije otvorila!");
        return;
    }
    while(1) {
        ListaK K=(ListaK)malloc(sizeof(ListaKlijenta));
        K->next=NULL;
        K->dijete=NULL;
        if(fscanf(fp,"%s %s %s %s", K->imeKlijenta,K->prezimeKlijenta,K->OIB,K->dodatniFILE)!=4) {
            free(K);
            break;
        }
        int Khash=hash(K);
        printf("%d\n",Khash);
        insertIntoList(&HashTable[Khash],K);

    }
    fclose(fp);
}
void insertIntoList(ListaK Head,ListaK new){

    ListaK temp=Head;
    new->next=temp->next;
    temp->next=new;
}
int hash(ListaK K) {
    int sum = 0;
    int br=strlen(K->OIB);
    for(int i=0;i<br;i++) {
        sum+=K->OIB[i];
    }
    return sum % HASH_SIZE;
}
void printHashTable(ListaKlijenta*HashTable){

    for(int i=0;i<HASH_SIZE;i++) {
        printf("Bucket %d:--\n",i);
        printList(&HashTable[i]);
    }
}

void printClientWithValute(StabloKlijenata* HashTable, char* valuta) {
    for(int i=0;i<HASH_SIZE;i++) {
        printClientsWithValuteInList(&HashTable[i], valuta);
    }
}
int hasClientWithOib(ListaKlijenta*HashTable, char* OIB) {
    int hashIdx = hash(OIB);
    return hasClientWithOibInList(&HashTable[hashIdx], OIB);
}
int hasClientWithOibInList(ListaK Head, char* OIB) {

}

void printList(ListaK Head) {

    ListaK temp=Head->next;
    while(temp!=NULL) {
        printf("%s %s %s %s\n", temp->imeKlijenta,temp->prezimeKlijenta,temp->OIB,temp->dodatniFILE);
        temp=temp->next;
    }

}













