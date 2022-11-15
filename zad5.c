#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct stog* pozicija;
struct stog {
	int el;
	pozicija next;
};
int push(pozicija head, int element);
int pop(pozicija head, int* element);
int dat(pozicija head);
int main()
{
	struct stog Head;
	Head.next = NULL;
	dat(&Head);
	printf("Rezultat je %d\n", Head.next->el);

    while (1) {
        int el;
        int izbacio = pop(&Head, &el);
        if (izbacio == 0) // nisam nista izbacio, tj stog je prazan
            break;
    }

	return 0;
}
int dat(pozicija head)
{
	FILE* fp = NULL;
	fp = fopen("postfix.txt", "r");
	if (fp == NULL)
	{
		printf("Neuspjesno otvaranje datoteke!\n");
		return 1;
	}
    char token[10];
    int x, y;

	while (!feof(fp))
	{
        // 2 3 1 * + 9 -
		fscanf(fp, " %s", token);
        printf("token = %s\n", token);

        if (strcmp(token, "+") == 0) {
            pop(head, &x), pop(head, &y);
            push(head, y + x);
        }
        else if (strcmp(token, "-") == 0) {
            pop(head, &x), pop(head, &y);
            push(head, y - x);
        }
        else if (strcmp(token, "*") == 0) {
            pop(head, &x), pop(head, &y);
            push(head, y * x);
        }
        else if (strcmp(token, "/") == 0) {
            pop(head, &x), pop(head, &y);
            push(head, y / x);
        }
        else
            push(head, atoi(token));
	}
	return 0;

}
int push(pozicija head, int element)
{
	pozicija novi;
	novi = (pozicija)malloc(sizeof(struct stog));
	if (novi == NULL)
	{
		printf("Neuspjesna alokacija memorije!\n");
		return 1;
	}
	novi->el = element;
	novi->next = head->next;
	head->next = novi;

	return 0;
}
int pop(pozicija head, int* element)
{
	pozicija temp = NULL;
	if (head->next == NULL) {
		printf("Stog je prazan!\n");
        return 0;
    }
	else {
		temp = head->next;
		*element = temp->el;
        head->next = temp->next;
		free(temp);
        return 1;
	}
}
