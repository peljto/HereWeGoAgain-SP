//dat drzave.txt u kojoj su drzave
//drzave.txt - drzava grad.txt
//grad.txt - grad broj_stanovnika
//stablo drzava po nazivu
//svaki cvor stabla sadrzi vezanu listu gradova sortiranu po br stanovnika
//pretraga po tastaturi kao a)

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
	char grad[MAX];
	int stanovnici;
	pozL next;
}list;
typedef struct _tree {
	char drzava[MAX];
	char dat_gradovi[MAX];
	pozT left;
	pozT right;
	pozL head_grad;
}tree;

pozT createTree();
pozL createList();
int addToTree(pozT, pozT);
int readFileDrzava(pozT);
int readFileGrad(pozT);
int addLast(pozL, pozL);
int addSort(pozL, pozL);
pozL findPrev(pozL, pozL);
int printList(pozL);
int printTree(pozT);
int listaj(pozT);


int main()
{
	pozT root = createTree();
	readFileDrzava(root);
	printTree(root->left);
	readFileGrad(root->left);
	listaj(root->left);

	return 0;
}

pozT createTree() {
	pozT temp = (pozT)malloc(sizeof(tree));

	if (temp == NULL)
		return NULL;

	temp->left = NULL;
	temp->right = NULL;

	return temp;
}

pozL createList() {
	pozL temp = (pozL)malloc(sizeof(list));

	if (temp == NULL)
		return NULL;

	temp->next = NULL;

	return temp;
}

int addToTree(pozT temp, pozT current) {
	if (strcmp(current->drzava, temp->drzava) < 0) {
		if (temp->left != NULL)
			addToTree(temp->left, current);
		else temp->left = current;
	}

	else {
		if (temp->right != NULL)
			addToTree(temp->right, current);
		else
			temp->right = current;
	}

	return 0;
}

int readFileDrzava(pozT root) {
	FILE* fp;

	fp = fopen("drzave.txt", "r");

	char red[MAX];
	pozT temp = NULL;

	while (!feof(fp)) {
		temp = createTree();
		fgets(red, MAX, fp);
		sscanf(red, "%s %s", temp->drzava, temp->dat_gradovi);

		if (root->left == NULL)
			root->left = temp;
		else
			addToTree(root->left, temp);
	}
	fclose(fp);

	return 0;
}

int readFileGrad(pozT root) {
	FILE* fp;

	fp = fopen(root->dat_gradovi, "r");

	char red[MAX];
	pozL temp = NULL;

	while (!feof(fp)) {
		fgets(red, MAX, fp);
		temp = createList();
		sscanf(red, "%s %d", temp->grad, &temp->stanovnici);

		addSort(root->head_grad, temp);
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
		if (strcmp(current->grad, temp->grad) < 0) {
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

pozL findPrev(pozL head, pozL current) {
	if (head->next = NULL) {
		printf("\nLista je prazna!!");
		return NULL;
	}
	
	pozL temp = head;

	while (temp != NULL) {
		if (strcmp(current->grad, temp->next->grad) == 0)
			return temp;
		temp = temp->next;
	}

	printf("\nNije pronaden prethodni clan!\n");

	return NULL;
}

int printList(pozL head) {
	if (head->next == NULL) {
		printf("\nPrazna lista!");
		return -1;
	}

	pozL temp = head->next;
	while (temp != NULL) {
		printf("%s\n", temp->grad);
		temp = temp->next;
	}

	return 0;
}
int printTree(pozT temp) {
	if (temp->left != NULL)
		printTree(temp->left);
	
	printf("%s ", temp->drzava);
	
	if (temp->right != NULL)
		printTree(temp->right);

	return 0;
}
int listaj(pozT temp) {
	if (temp->left != NULL)
		listaj(temp->left);

	printf("\n\n\t----- %s -----\n\n", temp->drzava);
	printList(temp->head_grad);

	if (temp->right != NULL)
		listaj(temp->right);

	return 0;
}
