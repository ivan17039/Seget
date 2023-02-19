#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

struct _stabloStudenata;
typedef struct _stabloStudenata*StabloP;
typedef struct _stabloStudenata {
    char ime[128];
    char prezime[128];
    int broj_bodova;
    double relativni_broj_bodova;
    StabloP left;
    StabloP right;
}StabloStudenata;
StabloP createBSTOfStudent(StabloP root);
void printInOrder(StabloP root);
StabloP insertInBST(StabloP root,StabloP temp);
void calcRelNumb(StabloP root,int max);
void printPreOrder(StabloP root);
void printLevelOrder(StabloP root);
int height(StabloP root);
void printLevel(StabloP root, int rootLevel, int i);
int main() {
    StabloP root=NULL;
    root=createBSTOfStudent(root);
    printInOrder(root);
    int max=findMAXbr_bod(root);
    printf("Max br bodova:%d\n",max);
	calcRelNumb(root,max);
    printf("-------------------\n");
    printPreOrder(root);
    printf("-------------------\n");
	printLevelOrder(root);
	return 0;
}
StabloP createBSTOfStudent(StabloP root) {

    FILE *fp=NULL;
    fp=fopen("Subject1.txt","r");
    if(fp==NULL) {
        printf("Datoteka se nije otvorila!\n");
        return NULL;
    }
    while(1){
        StabloP temp=(StabloP)malloc(sizeof(StabloStudenata));
        temp->left=temp->right=NULL;
        if(fscanf(fp,"%s %s %d",temp->ime,temp->prezime,&temp->broj_bodova)!=3){
            free(temp);
            break;
        }
        root=insertInBST(root,temp);
    }
    fclose(fp);
    return root;
}
StabloP insertInBST(StabloP root,StabloP temp){

    if(root==NULL)
        return temp;

    if(root->broj_bodova >= temp->broj_bodova){
        root->left=insertInBST(root->left,temp);
    }
    if(root->broj_bodova < temp->broj_bodova){
        root->right=insertInBST(root->right,temp);
    }
    return root;
}

void printInOrder(StabloP root) {
    if(root==NULL){
        return;
    }
    printInOrder(root->left);
    printf("%s %s %d\n",root->ime,root->prezime,root->broj_bodova);
    printInOrder(root->right);
}
void printPreOrder(StabloP root) {
    if(root==NULL){
        return;
    }
    printf("%s %s %d %lf\n",root->ime,root->prezime,root->broj_bodova,root->relativni_broj_bodova);
    printPreOrder(root->left);
    printPreOrder(root->right);
}
void calcRelNumb(StabloP root,int max) {

    if(root==NULL) {
        return;
    }
    calcRelNumb(root->left,max);

    root->relativni_broj_bodova=(1.0 * root->broj_bodova)/max;

    calcRelNumb(root->right,max);
}
int findMAXbr_bod(StabloP root){

    if(root==NULL){
        return 0;
    }
    int leftMAX=findMAXbr_bod(root->left);

    int rootMAX=root->broj_bodova;

    int rightMAX=findMAXbr_bod(root->right);

    if (leftMAX >= rootMAX && leftMAX >= rightMAX)
		return leftMAX;

	if (rootMAX >= leftMAX && rootMAX >= rightMAX)
		return rootMAX;

	return rightMAX;
}
int height(StabloP root) {

    if(root==NULL) {
        return 0;
    }
    int leftHeight=height(root->left);

    int rightHeight=height(root->right);

    if(leftHeight > rightHeight){
        return leftHeight+1;
    }
    else
        return rightHeight+1;
}
void printLevelOrder(StabloP root){

    int h = height(root);
    for(int i=1;i<=h;i++) {
		printf("Level %d: \n", i);
        printLevel(root, 1, i);
    }
}
void printLevel(StabloP root, int rootLevel, int i){

    if(root==NULL){
        return;
    }
    printLevel(root->left, rootLevel+1, i);

	if (rootLevel == i)
		printf("%s %s %d %lf\n",root->ime,root->prezime,root->broj_bodova,root->relativni_broj_bodova);

    printLevel(root->right, rootLevel+1, i);
}