#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define MAX 1024


typedef struct treeNode* treePointer;
struct treeNode
{
	char cityName[MAX];
    int population;
	treePointer left;
	treePointer right;
};
struct statelist;
typedef struct statelist* position;
typedef struct statelist {

    char stateName[MAX];
    treePointer nextTree;
    position next;
}linkedList;

treePointer CreateTreeRoot();
position CreateHeadList();
int PrintList(linkedList );
int InsertionInList(position , position );
position CreateListEl(char []);
int ReadFromStateFILE(char [], linkedList);
int ReadFromCityFILE(position , char []);
int PrintInorder(treePointer );
treePointer CreateTreeEl(char [], int );
position FindState(linkedList , char[]);
treePointer InsertionInTree(treePointer , char [], int) ;
int PrintCitiesLargerThan(treePointer , int );
int Menu(linkedList states);

int main() {

    linkedList states;
    states.next = CreateHeadList();
    states.nextTree = CreateTreeRoot();

    ReadFromStateFILE("drzave.txt", states);

    PrintList(states);

    Menu(states);

    return 0;
}

treePointer CreateTreeRoot() {

    treePointer root = NULL;

    root = malloc(sizeof(struct treeNode));

    if(!root) {

        printf("Problem allocating memory for a tree element!\n");
        return NULL;
    }

    strcpy(root->cityName, "");
    root->left = NULL;
    root->right = NULL;
    root->population = 0;

    return	root;
}

int InsertionInList(position newElement, position head) {

    if(head->next == NULL) {
        head->next = newElement;
        newElement->next = NULL;
    }

    else {
        while (head->next != NULL && (strcmp(head->next->stateName, newElement->stateName) < 0))
            head = head->next;
            newElement->next = head->next;
            head->next = newElement;
    }

    return 0;
}

position CreateListEl(char stateName[]) {

    position newElement = NULL;

    newElement = (position)malloc(sizeof(struct statelist));

    if(!newElement) {

        printf("Problem allocating memory for linked list element!\n");
        return NULL;
    }

    strcpy(newElement->stateName, stateName);
    newElement->next = NULL;
    newElement->nextTree = CreateTreeRoot();

    return newElement;
}

int ReadFromStateFILE(char stateFile[], linkedList states) {

    FILE* fp = NULL;
    char stateName[MAX] = { 0 };
    char cityfile[MAX] = { 0 };
    position newElement = NULL;
    position current = states.next;

    newElement = (position)malloc(sizeof(linkedList));

    if(!newElement) {

        printf("Problem allocating memory for linked list element!\n");
        return -1;
    }

    fp = fopen(stateFile, "r");

    if(!fp) {

        printf("File %s cannot be opened!\n",stateFile);
        return -1;
    }

    while(!feof(fp)) {

            fscanf(fp,"%[^,],%s\n", stateName, cityfile);

            newElement = CreateListEl(stateName);

            InsertionInList(newElement, states.next);

            ReadFromCityFILE(newElement, cityfile);
    }
    fclose(fp);

    return 0;
}

int ReadFromCityFILE(position head, char cityfile[]) {

    FILE* fp = NULL;
    char cityName[MAX] = { 0 };
    int population = 0;
    treePointer newElement = NULL;
    treePointer root = head->nextTree;

    fp = fopen(cityfile, "r");

    if(!fp) {

        printf("File %s cannot be opened!\n", cityfile);
        return -1;
    }

    while(!feof(fp)) {

        fscanf(fp,"%[^,],%d\n", cityName, &population);
        newElement = CreateTreeRoot();
        newElement =  InsertionInTree(root, cityName, population);

    }

    fclose(fp);

    return 0;
}

int PrintInorder(treePointer root) {

    if(root == NULL)
        return 0;

    PrintInorder(root->left);
    if(root->population != 0)
        printf("    %s (%d population)\n", root->cityName, root->population);
    PrintInorder(root->right);
    return 0;
}

treePointer CreateTreeEl(char cityName[], int population) {

    treePointer newElement = NULL;

    newElement = (treePointer)malloc(sizeof(struct treeNode));

    if(!newElement) {

        printf("Problem allocating memory for a tree element!\n");
        return NULL;
    }

    strcpy(newElement->cityName, cityName);
    newElement->population = population;
    newElement->left = NULL;
    newElement->right = NULL;

    return newElement;
}

position FindState(linkedList states, char stateName[]) {

    position current = NULL;

    current = (position)malloc(sizeof(linkedList));

    if(!current) {

        printf("Problem allocating memory for linked list element!\n");
        return NULL;
    }

    current = states.next;

    while (current->next != NULL && (strcmp(current->next->stateName, stateName)))
        current = current->next;

    if((current->next == NULL || strcmp(stateName, current->next->stateName))) {
        return NULL;
    }

    current = current->next;

    return current;
}

int Menu(linkedList states) {

    int choice=0;
    int population=0;
    char stateName[MAX] = { 0 };
    char cityName[MAX] = { 0 };
    position currentList = NULL;
    treePointer currentTree = NULL;
    treePointer temp = NULL;

    currentList = (position)malloc(sizeof(linkedList));

    if(!currentList) {

        printf("Problem allocating memory for linked list element!\n");
        return -1;
    }

    currentTree = (treePointer)malloc(sizeof(struct treeNode));

    if(!currentTree) {

        printf("Problem allocating memory for a tree element!\n");
        return -1;
    }

    temp = (treePointer)malloc(sizeof(struct treeNode));

    while(1) {
        printf("---------------------------------\n");
        printf("Enter 1 (to start the program)\n");
        printf("Enter 2 (to exit the program)\n");
        printf("---------------------------------\n");
        printf("Choice:");
        scanf(" %d",&choice);
        if(choice == 1) {
            printf("Enter the name of the country: ");
            scanf(" %s", stateName);
            currentList = FindState(states, stateName);

            if(!currentList){
                printf("That country does not exist!\n");
            }
            else {
                printf("State: %s is found!\n", currentList->stateName);
                printf("The cities of the country are:\n");
                PrintInorder(currentList->nextTree);

                temp = currentList->nextTree;
                printf("\nEnter the number of inhabitants of the city: ");
                scanf(" %d", &population);
                printf("Cities with more than %d inhabitants in %s are:\n",population,stateName);
                PrintCitiesLargerThan(temp, population);
            }
            printf("\n");
        }
        else if(choice==2) {
            printf("End of program!\nGoodbye!\n\n");
            break;
        }
        else{
            printf("The entered choice is incorrect!!!\n\n");
        }
    }

    return 0;
}

treePointer InsertionInTree(treePointer root, char cityName[], int population) {

    if(root == NULL) {

        root = (treePointer)malloc(sizeof(struct treeNode));
        strcpy(root->cityName, cityName);
        root->population = population;
        root->left = NULL;
        root->right = NULL;
    }

    if(root->population > population)
        root->left = InsertionInTree(root->left, cityName, population);

    else if (root->population < population)
        root->right = InsertionInTree(root->right, cityName, population);

    else if (strcmp(root->cityName,cityName) > 0)
        root->left = InsertionInTree(root->left, cityName, population);

    else if (strcmp(root->cityName,cityName) < 0 )
        root->right = InsertionInTree(root->right, cityName, population);

    return root;
}

position CreateHeadList() {

    position head = NULL;
    head = (position)malloc(sizeof(linkedList));

    if(!head) {
        printf("Problem allocating memory for head element!\n");
        return NULL;
    }

    strcpy(head->stateName, "");
    head->next = NULL;
    head->nextTree = NULL;
    head->next = NULL;

    return head;
}

int PrintList(linkedList states) {

    position current = states.next;

    while (current->next != NULL) {
        current = current->next;
        printf("State: %s \nCities:\n", current->stateName);
        PrintInorder(current->nextTree);
        printf("\n");

    }

    return 0;
}
int PrintCitiesLargerThan(treePointer current, int population){

    if(current == NULL){
        return 0;
    }
    PrintCitiesLargerThan(current->left,population);
    if(current->population >= population)
        printf("    %s (%d population)\n", current->cityName, current->population);
    PrintCitiesLargerThan(current->right,population);
    return 0;

}