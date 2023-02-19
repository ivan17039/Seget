#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#define MAX_NAME_LEN (64)
struct HnlList;
typedef struct HnlList * Klub;
typedef struct HnlList {
    char imeKluba[MAX_NAME_LEN];
    int br_utakmica;
    int br_pobjeda;
    int br_nerijesenih;
    int br_poraza;
    int postignutih_g;
    int primljenih_g;
    int bodova;
    Klub next;
}HNL;
struct _utakmica;
typedef struct _utakmica *UtakmicaP;
typedef struct _utakmica {
    char imedomacina[MAX_NAME_LEN];
    char imegosta[MAX_NAME_LEN];
    int rezultat_d;
    int rezultat_g;
}Utakmica;
void createListOfKlubs(Klub Head);
void printList(Klub Head);
void sortListOfKlubs(Klub Head);
void readFromRezultatiFile(Klub Head,UtakmicaP U);
Klub findKlub(Klub Head,char *imeKl) ;
void rezultatiUtakmice(Klub domacin,Klub gost,int rezultat_d,int rezultat_g);
int main() {
    HNL Head;
    Head.next=NULL;
    Utakmica * utakmica;
    utakmica =(UtakmicaP)malloc(sizeof(Utakmica));
    createListOfKlubs(&Head);
    readFromRezultatiFile(&Head,utakmica);
    sortListOfKlubs(&Head);
    printList(Head.next);
    return 0;
}
void createListOfKlubs(Klub Head) {

    FILE *fp=NULL;
    fp=fopen("hnl4.txt","r");
    if (fp == NULL)
    {
        printf("File didn't open!\r\n");
        return;
    }
    while(1) {
        Klub K =(Klub)malloc(sizeof(HNL));
        K->next=NULL;
        if(fscanf(fp,"%s %d %d %d %d %d %d %d",K->imeKluba,&K->br_utakmica,&K->br_pobjeda,&K->br_nerijesenih,&K->br_poraza,&K->postignutih_g,&K->primljenih_g,&K->bodova)!=8){
            break;
        }
        Klub temp=Head;
        while(temp->next!=NULL) {
            temp=temp->next;
        }
        K->next=temp->next;
        temp->next=K;
    }
    fclose(fp);
}
Klub findKlub(Klub Head,char *imeKl) {

    Klub temp=Head;
    while(temp!=NULL && strcmp(temp->imeKluba,imeKl)!=0){
        temp=temp->next;
    }
    return temp;
}
void readFromRezultatiFile(Klub Head,UtakmicaP start){

    FILE *fp=NULL;
    fp=fopen("rezultati.txt","r");
    if (fp == NULL)
    {
        printf("File didn't open!\r\n");
        return;
    }
    while(1) {
        UtakmicaP U = start;
        if(fscanf(fp,"%s %d-%d %s",U->imedomacina,&U->rezultat_d,&U->rezultat_g,U->imegosta)!=4){
            break;
        }
        printf("%s %d-%d %s\n",U->imedomacina,U->rezultat_d,U->rezultat_g,U->imegosta);
        printf("----------------------------\n");
        Klub domacin=findKlub(Head,U->imedomacina);
        Klub gost=findKlub(Head,U->imegosta);
        rezultatiUtakmice(domacin,gost,U->rezultat_d,U->rezultat_g);
    }

}
void rezultatiUtakmice(Klub domacin,Klub gost,int rezultat_d,int rezultat_g) {
    if(rezultat_d==rezultat_g) {
        ++domacin->br_nerijesenih;
        ++gost->br_nerijesenih;
        ++domacin->br_utakmica;
        ++gost->br_utakmica;
        ++domacin->bodova;
        ++gost->bodova;
        domacin->primljenih_g+=rezultat_g;
        gost->primljenih_g+=rezultat_d;
        domacin->postignutih_g+=rezultat_d;
        gost->postignutih_g+=rezultat_g;
    }
    if(rezultat_d>rezultat_g) {
        domacin->bodova+=3;
        ++domacin->br_pobjeda;
        ++gost->br_poraza;
        ++domacin->br_utakmica;
        ++gost->br_utakmica;
        domacin->primljenih_g+=rezultat_g;
        gost->primljenih_g+=rezultat_d;
        domacin->postignutih_g+=rezultat_d;
        gost->postignutih_g+=rezultat_g;
    }
    if(rezultat_d<rezultat_g) {
        gost->bodova+=3;
        ++gost->br_pobjeda;
        ++domacin->br_poraza;
        ++domacin->br_utakmica;
        ++gost->br_utakmica;
        domacin->primljenih_g+=rezultat_g;
        gost->primljenih_g+=rezultat_d;
        domacin->postignutih_g+=rezultat_d;
        gost->postignutih_g+=rezultat_g;
    }
}
void sortListOfKlubs(Klub Head)
{
	Klub K = NULL;
	Klub preth_K = NULL;
	Klub pomocna = NULL;
	Klub kraj = NULL;
	while (Head->next != kraj)
	{
		preth_K = Head;
		K = Head->next;
		while (K->next != kraj)
		{
			if (K->bodova < K->next->bodova)
			{
				pomocna = K->next;
				preth_K->next = pomocna;
				K->next = pomocna->next;
				pomocna->next = K;
				K = pomocna;
			}
            int razlika1=K->postignutih_g - K->primljenih_g;
            int razlika2=K->next->postignutih_g - K->next->primljenih_g;
            if(K->bodova == K->next->bodova){
                if(razlika1 < razlika2) {
                    pomocna = K->next;
    				preth_K->next = pomocna;
    				K->next = pomocna->next;
    				pomocna->next = K;
    				K = pomocna;
                }
            }
            else if(K->bodova == K->next->bodova && razlika1 == razlika2) {
                if(strcmp(K->imeKluba,K->next->imeKluba)>0){
                    pomocna = K->next;
    				preth_K->next = pomocna;
    				K->next = pomocna->next;
    				pomocna->next = K;
    				K = pomocna;
                }
            }
			preth_K = K;
			K = K->next;
		}
		kraj = K;
	}
}
void printList(Klub Head) {

    Klub temp=Head;
    if(temp==NULL) {
        printf("Lista je prazna!\n");
        return;
    }
    while(temp!=NULL) {
        printf("%s %d %d %d %d %d %d %d\n",temp->imeKluba,temp->br_utakmica,temp->br_pobjeda,temp->br_nerijesenih,temp->br_poraza,temp->postignutih_g,temp->primljenih_g,temp->bodova);
        temp=temp->next;
    }
}