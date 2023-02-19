#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#define MAX_NAME_LEN (64)

struct _stogList;
typedef struct _stogList *StogP;
typedef struct _stogList {
    char el;
    StogP next;
} Stog;

struct _stogDoubleList;
typedef struct _stogDoubleList *StogDoubleP;
typedef struct _stogDoubleList {
    double el;
    StogDoubleP next;
} StogDouble;


void push(char x, StogP s);
void printStog(StogP s);
int topElement(StogP s);
int pop(StogP s);
int is_empty(StogP s);


void pushD(double x, StogDoubleP s);
double topElementD(StogDoubleP s);
int popD(StogDoubleP s);
int is_emptyD(StogDoubleP s);

int prioritet(char c);
void covertInfixToPostfix(char *expression);
int main() {
    FILE *fp=NULL;
    fp=fopen("infix.txt","r");
    char expression[MAX_NAME_LEN];
    fscanf(fp,"%s",expression);
    covertInfixToPostfix(expression);
    fclose(fp);
    eval();
    return 0;
}
int prioritet(char c) {
    if (c == '+' || c == '-')
        return 1;
    if (c == '*' || c == '/')
        return 2;
    return 0;
}
void covertInfixToPostfix(char *expression) {

    Stog ss;
    ss.next=NULL;
    StogP s = &ss;
    FILE *fp=NULL;
    fp=fopen("postfix.txt","w");
    for(int i=0;i<strlen(expression);++i) {
        char c = expression[i];
        if(c=='+' || c=='-' || c=='*' || c=='/') {
            fprintf(fp, " ");
            // izbaci sve operatore >= prioriteta sa stoga
            while (1) {
                if (is_empty(s))
                    break;

                char ch = topElement(s);
                if (prioritet(ch) < prioritet(c))
                    break;

                // >=
                fprintf(fp," %c ", ch);
                pop(s);
            }
            push(c,s);
        }
        else if(c=='(' ){
            fprintf(fp, " ");
            push(c,s);
        }
        else if(c==')'){
            fprintf(fp, " ");
            while (1) {
                char ch = topElement(s);
                pop(s);
                if (ch == '(')
                    break;

                fprintf(fp," %c " , ch);
            }
            /*
            char ch = topElement(s);
            while(ch!='('){
                printf("%c", ch);
                pop(s);
                ch = topElement(s);
            }
            pop(s); // izbaci i '('
            */
        }
        else {
            fprintf(fp,"%c", c);
        }

    }
    while(!is_empty(s)){
        fprintf(fp," %c ", topElement(s));
        pop(s);
    }
    fclose(fp);
}
int is_empty(StogP top) {
    if(top->next == NULL)
      return 1;
    return 0;
}
int topElement(StogP top){
    if(!is_empty(top)){
        return top->next->el;
    }
    return 0;
}
void push(char x, StogP top ) {

    StogP temp=top;
    StogP q=(StogP)malloc(sizeof(Stog));
    if(q==NULL) {
        printf("Problem u alokaciji!\n");
    }
    q->el=x;
    q->next=temp->next;
    temp->next=q;
}
int pop(StogP top){

    StogP temp=top;
    StogP priv=NULL;
    char x;
    if(is_empty(temp)) {
        return 0;
    }
    else {
        priv=temp->next;
        x=priv->el;
        temp->next=priv->next;
        free(priv);
    }
    return 1;
}


int is_emptyD(StogDoubleP top) {
    if(top->next == NULL)
      return 1;
    return 0;
}
double topElementD(StogDoubleP top){
    if(!is_emptyD(top)){
        return top->next->el;
    }
    return 0;
}
void pushD(double x, StogDoubleP top ) {

    StogDoubleP temp=top;
    StogDoubleP q=(StogDoubleP)malloc(sizeof(StogDouble));
    if(q==NULL) {
        printf("Problem u alokaciji!\n");
    }
    q->el=x;
    q->next=temp->next;
    temp->next=q;
}
int popD(StogDoubleP top){

    StogDoubleP temp=top;
    StogDoubleP priv=NULL;
    double x;
    if(is_emptyD(temp)) {
        return 0;
    }
    else {
        priv=temp->next;
        x=priv->el;
        temp->next=priv->next;
        free(priv);
    }
    return 1;
}

int eval()
{
	FILE* fp = NULL;
	fp = fopen("postfix.txt", "r");
	if (fp == NULL)
	{
		printf("Neuspjesno otvaranje datoteke!\n");
		return 1;
	}
    StogDouble st;
    st.next = NULL;
    StogDoubleP s = &st;

    char token[10];
    double x, y;

	while (!feof(fp))
	{
        // 2 3 1 * + 9 -
		fscanf(fp, " %s", token);
        printf("token = %s\n", token);

        if (strcmp(token, "+") == 0) {
            x = topElementD(s); popD(s);
            y = topElementD(s); popD(s);
            pushD(y + x,s);
        }
        else if (strcmp(token, "-") == 0) {
            x = topElementD(s); popD(s);
            y = topElementD(s); popD(s);
            pushD( y - x,s);
        }
        else if (strcmp(token, "*") == 0) {
            x = topElementD(s); popD(s);
            y = topElementD(s); popD(s);
            pushD(y * x,s );
        }
        else if (strcmp(token, "/") == 0) {
            x = topElementD(s); popD(s);
            y = topElementD(s); popD(s);
            pushD( y / x,s);
        }
        else
            pushD(atof(token),s);
	}
    printf("Rezultat je %lf\n", topElementD(s));
	return 0;
}