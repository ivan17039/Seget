#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Polinom* listaPoli;

struct Polinom {
    int Koef;
    int Pot;
    listaPoli next;
};

void Ispis(listaPoli );
void Sortiraj(listaPoli);
listaPoli Zbroj(listaPoli, listaPoli);
listaPoli Umnozak(listaPoli, listaPoli);
void UcitajIzDat(listaPoli);

int main(){
    struct Polinom p1;
    struct Polinom p2;

    UcitajIzDat(&p1);
    Sortiraj(&p1);
    printf("Ispis prvog polinoma:\n");
    Ispis(p1.next);

    UcitajIzDat(&p2);
    Sortiraj(&p2);
    printf("Ispis drugog polinoma:\n");
    Ispis(p2.next);

    listaPoli zbr = Zbroj(&p1, &p2);
    printf("Zbroj polinoma je:\n");
    Ispis(zbr->next);

    listaPoli umn = Umnozak(&p1, &p2);
    printf("Umnozak polinoma je:\n");
    Ispis(umn->next);

    return 0;

}

void UcitajIzDat(listaPoli P)
{
    char dat[50];
    int n = 0;
    P->next = NULL;

    printf("Unesite ime datoteke iz koje zelite ucitat polinom: ");
    scanf(" %s", &dat);
    FILE* fp = NULL;
    fp = fopen(dat, "r");
    if (fp == NULL)
    {
        printf("Greska!\n");
        return;
    }
    while (!feof(fp))
    {
        listaPoli q = NULL;
        q = (listaPoli) malloc(sizeof(struct Polinom));
        fscanf(fp, "%d %d", &q->Koef, &q->Pot);
        q->next = P->next;
        P->next = q;
        P = P->next;
    }
    fclose(fp);
    printf("Lista ucitana iz datoteke.\n");
}

void Ispis(listaPoli P){
    printf("p(x) = ");
    while (P != NULL) {
        printf("%c%dx^%d ", P->Koef > 0 ? '+' : ' ', P->Koef, P->Pot);
        P = P->next;
    }
    printf("\n");
}

void Sortiraj(listaPoli P) {
	listaPoli q = NULL;
	listaPoli preth_q = NULL;
	listaPoli pomocna = NULL;
	listaPoli kraj = NULL;

	while (P->next != kraj)
	{
		preth_q = P;
		q = P->next;
		while (q->next != kraj)
		{
			if (q->Pot > q->next->Pot)
			{
				pomocna = q->next;
				preth_q->next = pomocna;
				q->next = pomocna->next;
				pomocna->next = q;
				q = pomocna;
			}
			preth_q = q;
			q = q->next;
		}
		kraj = q;
	}
}

listaPoli Zbroj(listaPoli p1, listaPoli p2){
    listaPoli zbr = NULL;
    zbr = (listaPoli) malloc(sizeof(struct Polinom));
    if (zbr == NULL) {
        printf("Greska kod alokacije prilikom zbrajanja polinoma!");
        return NULL;
    }
    zbr->next = NULL;

    p1 = p1->next; // preskoci Head, idi na prvi konkretni polinom
    p2 = p2->next;
    listaPoli trenutni = zbr;
/*
    p1(x) = [] -> [x] ---> NULL
                          ^
    p2(x) = [] -> [x] -> [x2] ---> NULL
                         ^
    zbr(x) = [] -> [2x] -> [x2]
*/
    while (p1 != NULL || p2 != NULL) {
        // p1 ili p2 mogu biti NULL
        // ali ne mogu oba biti NULL

        listaPoli q = NULL;
        q = (listaPoli) malloc(sizeof(struct Polinom));
        if (q == NULL) {
            printf("Greska kod alokacije prilikom zbrajanja polinoma!");
            return NULL;
        }
        if (p1 == NULL) {
            q->Pot = p2->Pot;
            q->Koef = p2->Koef;
            p2 = p2->next;
        }
        else if (p2 == NULL) {
            q->Pot = p1->Pot;
            q->Koef = p1->Koef;
            p1 = p1->next;
        }
        // p1 != NULL i p2 != NULL , mozemo ih direktno ispitivati bez provjere != NULL
        else if (p1->Pot == p2->Pot) {
            q->Pot = p1->Pot;
            q->Koef = p1->Koef + p2->Koef;
            p1 = p1->next;
            p2 = p2->next;
        }
        else if (p1->Pot > p2->Pot) {
            q->Pot = p2->Pot;
            q->Koef = p2->Koef;
            p2 = p2->next;
        }
        else if (p1->Pot < p2->Pot) {
            q->Pot = p1->Pot;
            q->Koef = p1->Koef;
            p1 = p1->next;
        }

        q->next = NULL;
        trenutni->next = q;
        trenutni = trenutni->next;
    }

    return zbr;
}

listaPoli Umnozak(listaPoli p1, listaPoli p2){
    p1 = p1->next; // preskoci Head, idi na prvi konkretni polinom
    p2 = p2->next;

    listaPoli umn = NULL;
    umn = (listaPoli) malloc(sizeof(struct Polinom));
    if (umn == NULL) {
        printf("Greska kod alokacije prilikom mnozenja polinoma!");
        return NULL;
    }
    umn->next = NULL;

    listaPoli originalni_p2 = p2;

    while (p1 != NULL) {
        listaPoli parijalni_umn = NULL;
        parijalni_umn = (listaPoli) malloc(sizeof(struct Polinom));
        if (parijalni_umn == NULL) {
            printf("Greska kod alokacije prilikom mnozenja polinoma!");
            return NULL;
        }
        parijalni_umn->next = NULL;

        listaPoli trenutni = parijalni_umn;

        while (p2 != NULL) {
            listaPoli q = NULL;
            q = (listaPoli) malloc(sizeof(struct Polinom));
            if (q == NULL) {
                printf("Greska kod alokacije prilikom mnozenja polinoma!");
                return 0;
            }
            q->Pot = p1->Pot + p2->Pot;
            q->Koef = p1->Koef * p2->Koef;
            q->next = NULL;
            trenutni->next = q;
            trenutni = trenutni->next;
            p2 = p2->next;
        }
        /*printf("Parcijalni umnozak je:");
        Ispis(parijalni_umn->next);
        printf("Trenutni umnozak je:");
        spis(umn->next);
        */
        listaPoli novi_umn = Zbroj(parijalni_umn, umn);
        free(umn);
        umn = novi_umn;

        p1 = p1->next;
        p2 = originalni_p2;
    }

    return umn;
}
