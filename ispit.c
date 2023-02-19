#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

#define _CRT_SECURE_NO_WARNINGS
#define MAX_NAME_LEN (64)
struct _student;
typedef struct _student * StudentP;
typedef struct _student {
    char firstName[MAX_NAME_LEN];
    char lastName[MAX_NAME_LEN];
    int Subject1;
    int Subject2;
    int Subject3;
    StudentP next;
}Student;
void createListOfStudents(char* fileName,StudentP Head);
void printList(StudentP Head, char* subject);
void mergeSubjects(StudentP Head, StudentP Head1, StudentP Head2, StudentP Head3) ;
void insertStudent(StudentP Head, StudentP S);
void insertSorted(StudentP Head, StudentP S);
StudentP findStudent(StudentP Head, StudentP S);
double prosjek(StudentP S);
void deleteALL(StudentP Head);
void deleteStudentsByName(StudentP Head,char *nameToBeDeleted);
void moveToFront(StudentP Head, int randomOcjena);
int cntMalloc = 0;
int cntFree = 0;

int main() {
    srand(time(NULL));

    char fileName1[MAX_NAME_LEN]="Subject1.txt";
    char fileName2[MAX_NAME_LEN]="Subject2.txt";
    char fileName3[MAX_NAME_LEN]="Subject3.txt";
    Student Head1;
    Head1.next=NULL;
    Student Head2;
    Head2.next=NULL;
    Student Head3;
    Head3.next=NULL;
    createListOfStudents(fileName1,&Head1);
    printList(Head1.next, "Subject1");
    createListOfStudents(fileName2,&Head2);
    printList(Head2.next, "Subject2");
    createListOfStudents(fileName3,&Head3);
    printList(Head3.next, "Subject3");

    Student Head;
    Head.next=NULL;
    mergeSubjects(&Head, &Head1, &Head2, &Head3);
    printList(Head.next, "AllSubjects");

    char nameToBeDeleted[MAX_NAME_LEN];
    printf("Unesite ime: \n");
    scanf(" %s",nameToBeDeleted);
    deleteStudentsByName(&Head,nameToBeDeleted);
    printList(Head.next, "AllSubjects");

    int randomOcjena = 1 + (rand() % 5); // [1-5]
    printf("Micemo na pocetak liste sve studente s ocjenom %d.\n", randomOcjena);
    moveToFront(&Head, randomOcjena);
    printList(Head.next, "AllSubjects");

    deleteALL(&Head);
    deleteALL(&Head1);
    deleteALL(&Head2);
    deleteALL(&Head3);
    printList(Head.next, "AllSubjects");
    printList(Head1.next, "Subject1");
    printList(Head2.next, "Subject2");
    printList(Head3.next, "Subject3");
	printf("Sve liste su izbrisane!\n");

    printf("Broj alokacija: %d, broj dealokacija: %d\n", cntMalloc, cntFree);
    return 0;
}
double prosjek(StudentP S) {
    return (S->Subject1 + S->Subject2 + S->Subject3)/3.0;
}
int compareStudent(StudentP S1,StudentP S2){
    // -1 ako je S1<S2
    // 0  ako je S1=S2
    // 1  ako je S1>S2

    if(prosjek(S1)>prosjek(S2)){
        return 1;
    }
    if(prosjek(S1)<prosjek(S2)){
        return -1;
    }
    // prosjek ==
    return strcmp(S2->lastName,S1->lastName);
}
void createListOfStudents(char *fileName,StudentP Head) {

    FILE *fp=NULL;
    fp=fopen(fileName,"r");
    if (fp == NULL)
    {
        printf("File didn't open!\r\n");
        return;
    }
    while(1) {
        StudentP S =(StudentP)malloc(sizeof(Student)); cntMalloc++;
        S->Subject1 = S->Subject2 = S->Subject3 = 1;
        S->next=NULL;
        if (strcmp(fileName, "Subject1.txt") == 0) {
            if(fscanf(fp,"%s %s %d\n",S->lastName,S->firstName,&S->Subject1)!=3){
                free(S); cntFree++;
                break;
            }
        }
        else if (strcmp(fileName, "Subject2.txt") == 0) {
            if(fscanf(fp,"%s %s %d\n",S->lastName,S->firstName,&S->Subject2)!=3){
                free(S); cntFree++;
                break;
            }
        }
        else if (strcmp(fileName, "Subject3.txt") == 0) {
            if(fscanf(fp,"%s %s %d\n",S->lastName,S->firstName,&S->Subject3)!=3){
                free(S); cntFree++;
                break;
            }
        }
        StudentP temp=Head;
        while(temp->next!=NULL) {
            temp=temp->next;
        }
        S->next=temp->next;
        temp->next=S;
    }
    fclose(fp);
}

StudentP findStudent(StudentP Head, StudentP S) {
    // nadji studenta S u listi Head
    // ako ga nema, vrati NULL
    StudentP temp=Head->next;
    while(temp!=NULL){
        if(strcmp(temp->lastName,S->lastName)==0 && strcmp(temp->firstName,S->firstName)==0){
            return temp;
        }
        temp=temp->next;
    }
    return NULL;
}

void insertStudent(StudentP Head, StudentP S) {
    // dodaj studenta S u listu Head
    StudentP temp=Head;
    StudentP new=(StudentP)malloc(sizeof(Student)); cntMalloc++;
    while(temp->next!=NULL) {
        temp=temp->next;
    }
    new->Subject1=S->Subject1;
    new->Subject2=S->Subject2;
    new->Subject3=S->Subject3;
    strcpy(new->firstName,S->firstName);
    strcpy(new->lastName,S->lastName);
    new->next=temp->next;
    temp->next=new;
}
void insertSorted(StudentP Head,StudentP S) {

    StudentP temp=Head;
    StudentP new=(StudentP)malloc(sizeof(Student)); cntMalloc++;
    while(temp->next!=NULL && compareStudent(temp->next,S)>0) {
        temp=temp->next;
    }
    new->Subject1=S->Subject1;
    new->Subject2=S->Subject2;
    new->Subject3=S->Subject3;
    strcpy(new->firstName,S->firstName);
    strcpy(new->lastName,S->lastName);
    new->next=temp->next;
    temp->next=new;

}
void mergeSubjects(StudentP Head, StudentP Head1, StudentP Head2, StudentP Head3) {
    Student pomocnaLista;
    pomocnaLista.next = NULL;
    StudentP Pomocna = &pomocnaLista;

    StudentP temp;
    temp = Head1->next;
    while (temp!=NULL) {
        StudentP S = findStudent(Pomocna, temp);
        if (S == NULL ){
            insertStudent(Pomocna, temp);
        }
        else{
            S->Subject1 = temp->Subject1;
        }
        temp=temp->next;
    }
    temp = Head2->next;
    while (temp!=NULL) {
        StudentP S = findStudent(Pomocna, temp);
        if (S == NULL){
            insertStudent(Pomocna, temp);
        }
        else{
            S->Subject2 = temp->Subject2;
        }
        temp=temp->next;
    }
    temp = Head3->next;
    while (temp!=NULL) {
        StudentP S = findStudent(Pomocna, temp);
        if (S == NULL){
            insertStudent(Pomocna, temp);
        }
        else{
            S->Subject3 = temp->Subject3;
        }
        temp=temp->next;
    }

    // trci po elementima pomocne liste i ubacuj ih sortirano u Head
    temp=Pomocna->next;
    while(temp!=NULL) {
        insertSorted(Head,temp);
        temp = temp->next;
    }
    //
    deleteALL(&pomocnaLista);
}
void deleteStudentsByName(StudentP Head,char *nameToBeDeleted){

    StudentP temp=Head->next;
    StudentP prev=Head;
    while(temp!=NULL){
        if(strcmp(temp->firstName,nameToBeDeleted)==0){
            prev->next=temp->next;
            free(temp);cntFree++;
        }
        else{
            prev=temp;
        }
        // prev gleda na dobrog studenta (prethodnog)
        temp=prev->next;
    }

}
void printList(StudentP Head, char* subject) {

    StudentP temp=Head;
    if(temp==NULL) {
        printf("Lista je prazna!\n");
        return;
    }
    while(temp!=NULL) {
        if (strcmp(subject, "Subject1") == 0)
            printf("%s %s %d\n",temp->lastName,temp->firstName,temp->Subject1);
        else if (strcmp(subject, "Subject2") == 0)
            printf("%s %s %d\n",temp->lastName,temp->firstName,temp->Subject2);
        else if (strcmp(subject, "Subject3") == 0)
            printf("%s %s %d\n",temp->lastName,temp->firstName,temp->Subject3);
        else if (strcmp(subject, "AllSubjects") == 0)
            printf("%s %s (%d, %d, %d)-{%lf}\n",temp->lastName,temp->firstName,temp->Subject1,temp->Subject2,temp->Subject3,prosjek(temp));
        temp=temp->next;
    }
    printf("------------------------------\n");

}
void deleteALL(StudentP Head) {

	StudentP temp = Head->next;
    StudentP prev = NULL;
	while (temp != NULL) {
        prev = temp;
		temp = temp->next; // tu ce temp postat NULL na kraju liste
		free(prev);
        if(prev!=NULL) cntFree++;
	}
	Head->next = NULL;
}

void moveToFront(StudentP Head, int randomOcjena) {
    StudentP prev = Head;
	StudentP temp = Head->next;
    while (temp != NULL) {
        StudentP next = temp->next;

        if (temp->Subject1 == randomOcjena || temp->Subject2 == randomOcjena || temp->Subject3 == randomOcjena) {
            prev->next = temp->next;
            temp->next = Head->next;
            Head->next = temp;
        }
        else {
            prev = temp;
        }

        temp = next;
    }
}