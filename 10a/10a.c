//dat drzava.txt dat sa drzavama
//uz ime drzave se nalazi i ime druge dat grad.txt u kojoj se nalazi ime gradova sa brojom stanovnika u formatu grad - br_stanovnika
//sortirana vezana lista po drzavama svaki cvor sadrzi stablo gradova sortirano po broju stanovnika
//ispisivanje drzava i gradova
//pretraga garadova koji imaju veæi broj stanovnika od unesenog

#define _CRT_SECURE_NO_WARNINGS
#define MAX 100

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct _list;
struct _tree;

typedef struct _list* pozL;
typedef struct _tree* pozT;

typedef struct _list {
	char drzava[MAX];
	char dat_gradovi[MAX];
	pozT root_grad;
	pozL next;
}list;

typedef struct _tree{
	char grad[MAX];
	int stanovnici;
	pozT left;
	pozT right;
}tree;

pozL createList();
pozT createTree();
int readFileDrzava(pozL);
int addSort(pozL, pozL);
pozL findPrev(pozL, pozL);
int printList(pozL);
int addLast(pozL, pozL);
int Listaj(pozL);
int Listaj2(pozL);
int readFileGrad(pozL);
int spremiGraduStablo(pozT, pozT);
int printTree(pozT);

int pretrazi(pozL, char[MAX], int);
int rekurzivnaZaGradove(pozT, int);

int main()
{
	list head;
	head.next = NULL;


	readFileDrzava(&head);
	printList(&head);

	printf("\n\n");

	Listaj(&head);
	Listaj2(&head);

	char drzava[MAX];
	int broj_stanovnika = 0;

	printf("\n\n\nUnesi ime drzave i broj stanovnika: ");
	scanf("%s %d", drzava, &broj_stanovnika);

	pretrazi(&head, drzava, broj_stanovnika);


	return 0;
}

int pretrazi(pozL head, char drzava[MAX], int broj_stanovnika) {
	if (head->next == NULL) {
		printf("prazna lista");
		return 0;
	}
	pozL temp = head->next;

	while (temp != NULL) {
		if (strcmp(temp->drzava, drzava) == 0) {
			rekurzivnaZaGradove(temp->root_grad, broj_stanovnika);
			return 0;
		}
		temp = temp->next;
	}
	printf("\nnema drzave\n");
	return 0;
}

int rekurzivnaZaGradove(pozT temp, int broj_stanovnika) {
	if (temp->left != NULL) rekurzivnaZaGradove(temp->left, broj_stanovnika);

	if (temp->stanovnici > broj_stanovnika) printf("%s - broj stanovnika: %d\n", temp->grad, temp->stanovnici);

	if (temp->right != NULL) rekurzivnaZaGradove(temp->right, broj_stanovnika);

	return 0;
}

pozL createList() {
	pozL temp = (pozL)malloc(sizeof(list));

	if (temp == NULL)
		return NULL;

	temp->next = NULL;
	temp->root_grad = NULL;

	return temp;
}

pozT createTree() {
	pozT temp = (pozT)malloc(sizeof(tree));

	if (temp == NULL)
		return NULL;

	temp->left = NULL;
	temp->right = NULL;

	return temp;
}

int readFileDrzava(pozL head) {
	FILE* fp;

	fp = fopen("drzave.txt", "r");

	pozL temp = NULL;
	char red[60];

	while (!feof(fp)) {
		temp = createList();
		fgets(red, 60, fp);
		sscanf(red, "%s %s", temp->drzava, temp->dat_gradovi);
		addSort(head, temp);
	}

	fclose(fp);

	return 0;
}

int addSort(pozL head, pozL current) {
	if (head->next == NULL) {
		head->next = current;
		return 0;
	}

	pozL temp = head->next;
	pozL prev = NULL;

	while (temp != NULL) {
		if (strcmp(current->drzava, temp->drzava) < 0) {
			prev = findPrev(head, temp);
			current->next = prev->next;
			prev->next = current;
			return 0;
		}

		temp = temp->next;
	}
	addLast(head, current);
	return 0;
}

pozL findPrev(pozL head, pozL current) {
	pozL temp = head;

	while(temp->next!=NULL){
		if (strcmp(temp->next->drzava, current->drzava) == 0)
			return temp;
		else
			temp = temp->next;
	}
	
	return temp;
}

int printList(pozL head) {
	pozL temp = head->next;

	while (temp != NULL) {
		printf("%s  ", temp->drzava);
		temp = temp->next;
	}

	return 0;
}
int addLast(pozL head, pozL current) {
	if (head->next == NULL) {
		head->next = current;
		return 0;
	}

	pozL temp = head->next;

	while (temp->next != NULL)
		temp = temp->next;

	temp->next = current;

	return 0;
}

int Listaj(pozL head) {
	pozL temp = head->next;

	while (temp != NULL) {
		readFileGrad(temp);
		temp = temp->next;
	}

	return 0;
}
int Listaj2(pozL head) {
	pozL temp = head->next;

	while (temp != NULL) {
		printf("\n");
		printTree(temp->root_grad);
		temp = temp->next;
	}

	return 0;
}

int readFileGrad(pozL current) {
	FILE* fp;
	char red[MAX];
	pozT temp = NULL;

	fp = fopen(current->dat_gradovi, "r");
	
	while (!feof(fp)) {
		temp = createTree();
		fgets(red, MAX, fp);
		sscanf(red, "%s %d", temp->grad, &temp->stanovnici);
		if (current->root_grad == NULL) {
			current->root_grad = temp;
		}

		else spremiGraduStablo(current->root_grad, temp);
	
	}

	fclose(fp);

	return 0;
}

int spremiGraduStablo(pozT temp, pozT current) {
	if (current->stanovnici > temp->stanovnici) {
		if (temp->left != NULL)
			spremiGraduStablo(temp->left, current);
		else
			temp->left = current;
	}
	else{
		if (temp->right != NULL)
			spremiGraduStablo(temp->right, current);
		else
			temp->right = current;
	}

	return 0;
}

int printTree(pozT head) {
	if (head->left != NULL)
		printTree(head->left);
	printf("%s ", head->grad);
	if (head->right != NULL)
		printTree(head->right);

	return 0;
}