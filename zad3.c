#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct osoba* Pozicija;
struct osoba{
	char ime[50];
	char prezime[50];
	int god;
	Pozicija next;
};

int unos_P(Pozicija P);
int unos_K(Pozicija P);
int ispis_I(Pozicija P);
int trazi_T(Pozicija P);
int brisi_B(Pozicija P);


int main()
{
	struct osoba Head;
	Head.next = NULL;
	char slovo;
	while(1){
		printf("Unesi slovo za:\n1{umetanje na pocetak}\n2{umetanje na kraj}\n3{ispis osoba}\n4{trazi osobu po prezimenu}\n5{brisi osobu po prezimenu}\n0{izlaz iz programa}\n");
		scanf(" %c", &slovo);
		if (slovo == 'P')
			unos_P(&Head);
		else if (slovo == 'K')
			unos_K(&Head);
		else if (slovo == 'I')
			ispis_I(Head.next);
		else if (slovo == 'T')
			trazi_T(Head.next);
		else if (slovo == 'B')
			brisi_B(&Head);
		else if (slovo == 'X')
			break;
		else
			printf("Greska!\n");
	}
	return 0;
}

int unos_P(Pozicija P)
{
	Pozicija q = NULL;

	q = (Pozicija)malloc(sizeof(struct osoba));

	if (q == NULL)
	{
		printf("Greska!\n");
		return 1;
	}

	printf("Unesi ime osobe:");
	scanf("%s", q->ime);
	printf("Unesi prezime osobe:");
	scanf("%s", q->prezime);
	printf("Unesi godinu rodenja osobe:");
	scanf("%d", &q->god);

	q->next = P->next;
	P->next = q;


	return 0;
}
int unos_K(Pozicija P)
{
	while (P->next != NULL)
	{
		P = P->next;
	}
	Pozicija q = NULL;
	q = (Pozicija)malloc(sizeof(struct osoba));
	if (q == NULL)
	{
		printf("Greska!\n");
		return 1;
	}
	printf("Unesi ime osobe: ");
	scanf(" %s", q->ime);
	printf("Unesi Prezime osobe: ");
	scanf(" %s", q->prezime);
	printf("Unesi godinu rodenja osobe: ");
	scanf(" %d", &q->god);

	q->next = P->next;
	P->next = q;
	return 0;
}

int ispis_I(Pozicija P)
{
	while (P != NULL)
	{
		printf("%s %s %d \n", P->ime, P->prezime, P->god);
		P = P->next;
	}
	return 0;
}

int trazi_T(Pozicija P)
{
	char Prez[50];
	printf("Unos prezimena osobe za Pronaci: \n");
	scanf(" %s", Prez);
	while (P != NULL && strcmp(Prez, P->prezime) != 0)
	{
		P = P->next;
	}
	if (P == NULL)
		printf("Greska!\n");
	else
		printf("Adresa osobe %p\n", P);
	return 0;
}

int brisi_B(Pozicija P)
{
	Pozicija Pret = NULL;
	char Prez[30];

	printf("Unos prezimena osobe za izbrisati\n");
	scanf(" %s", Prez);

	while (P->next != NULL && strcmp(Prez, P->prezime) != 0)
	{
		Pret = P;
		P = P->next;
	}
	if (Pret != NULL && strcmp(Prez, P->prezime) == 0)
	{
		Pret->next = P->next;
		free(P);
	}
	return 0;
}
