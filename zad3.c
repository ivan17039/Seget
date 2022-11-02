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
int brisi_sve(Pozicija P);
int unos_iza(Pozicija P);
int unos_ispred(Pozicija P);
int sort(Pozicija P);
int upis_U_Dat(Pozicija P);

int main()
{
	struct osoba Head;
	Head.next = NULL;
	int broj;
	while(1){
		printf("Unesi broj za:\n1{umetanje na pocetak}\n2{umetanje na kraj}\n3{ispis osoba}\n4{trazi osobu po prezimenu}\n5{brisi osobu po prezimenu}\n6{brisi sve}\n7{unos osobe iza}\n8{unos osobe ispred}\n9{sortiraj po prezimenima}\n10{umetanje u datoteku}\n0{izlaz iz programa}\n");
		scanf(" %d", &broj);
		if (broj == 1)
			unos_P(&Head);
		else if (broj == 2)
			unos_K(&Head);
		else if (broj == 3)
			ispis_I(Head.next);
		else if (broj == 4)
			trazi_T(Head.next);
		else if (broj == 5)
			brisi_B(&Head);
		else if (broj == 6)
			brisi_sve(&Head);
		else if (broj == 7)
			unos_iza(&Head);
		else if (broj == 8)
			unos_ispred(&Head);
		else if (broj == 9)
			sort(&Head);
		else if (broj == 10)
			upis_U_Dat(Head.next);
		else if (broj == 0)
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
	scanf(" %s", q->ime);
	printf("Unesi prezime osobe:");
	scanf(" %s", q->prezime);
	printf("Unesi godinu rodenja osobe:");
	scanf(" %d", &q->god);

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
	char Prez[50];

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
int brisi_sve(Pozicija Head){

	Pozicija privremena = NULL;

    while(Head->next != NULL) {
        privremena = Head;
        Head = Head->next;
        free(privremena);
    }
    printf("Vasa lista je izbrisana!\n");
    return 0;
}
int unos_iza(Pozicija P){

	Pozicija new = NULL;

	new = (Pozicija)malloc(sizeof(struct osoba));

	printf("Unesi ime osobe:");
	scanf(" %s", new->ime);
	printf("Unesi prezime osobe:");
	scanf(" %s", new->prezime);
	printf("Unesi godinu rodenja osobe:");
	scanf(" %d", &new->god);

	char Prez[50];
	printf("Unesi prezime osobe iza koje zelite dodati novu osobu:\n");
	scanf(" %c",Prez);
	while (P->next != NULL && strcmp(Prez, P->prezime) != 0)
	{
		P = P->next;
	}
	new->next = P->next;
	P->next = new;

	return 0;

}
int unos_ispred(Pozicija P){

	Pozicija new = NULL;

	new = (Pozicija)malloc(sizeof(struct osoba));

	printf("Unesi ime osobe:");
	scanf(" %s", new->ime);
	printf("Unesi prezime osobe:");
	scanf(" %s", new->prezime);
	printf("Unesi godinu rodenja osobe:");
	scanf(" %d", &new->god);

	char Prez[50];
	printf("Unesi prezime osobe ispred koje zelite dodati novu osobu:\n");
	scanf(" %c",Prez);
	while (P->next != NULL && strcmp(Prez, P->next->prezime) != 0)
	{
		P = P->next;
	}
	if(P->next != NULL){

		new->next = P->next;
		P->next = new;

	}


	return 0;

}
int sort(Pozicija p)
{
	Pozicija q = NULL;
	Pozicija prev_q = NULL;
	Pozicija temp = NULL;
	Pozicija end = NULL;
	while (p->next != end)
	{
		prev_q = p;
		q = p->next;
		while (q->next != end)
		{
			if (strcmp(q->prezime, q->next->prezime) > 0)
			{
				temp = q->next;
				prev_q->next = temp;
				q->next = temp->next;
				temp->next = q;

				q = temp;
			}

			prev_q = q;
			q = q->next;
		}
		end = q;
	}
	ispis_I(p->next);
	return 0;
}
int upis_U_Dat(Pozicija P)
{
	FILE* fp = NULL;
	fp = fopen("osoba.txt", "w");
	if (fp == NULL)
	{
		printf("Greska!\n");
		return 1;
	}
	while (P != NULL)
	{
		fprintf(fp, "%s\t %s\t %d\t\n", P->ime, P->prezime, P->god);
		P = P->next;
	}
	fclose(fp);
	return 0;
}
