//10 zadatak hash tablica 11 nizova
//suma prvih 5 ascii vrijednosti mod 11
//cvor ima stablo gradova

#define _CRT_SECURE_NO_WARNINGS
#define MAX_LIST (3)
#define MAX_WORD (32)

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct _tree;
struct _list;

typedef struct _tree* pozT;
typedef struct _list* pozL;

typedef struct _tree {
	char* grad;
	int stanovnici;
	pozT left;
	pozT right;
}tree;

typedef struct _list {
	char* drzava;
	char* dat_gradova;
	pozL next;
	pozT root_grad;
}list;

pozL createList();
pozT createTree();
char* createString(int);
pozL createHash(int);
int inputIntoHashTable(pozL, int, pozL);
int addSortHashTable(pozL, pozL);
pozL findPrev(pozL, pozL);
int addLast(pozL, pozL);
int inputDrzaveNode(pozL, char*, char*);
int createHashKey(pozL, int);
int inputGradInfo(pozT, char*, int);
int addGradTree(pozT, pozT);
int readFileDrzave(pozL);
int readFileGrad(pozL);
int printHash(pozL, int);
int printList(pozL);
int printTree(pozT);

int main()
{
	pozL head = createHash(MAX_LIST);
	readFileDrzave(head);
	printHash(head, MAX_LIST);

	printf("\n\n");

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

	temp->stanovnici = 0;
	temp->left = NULL;
	temp->right = NULL;

	return temp;
}

char* createString(int length) {
	char* string = (char*)malloc(length * sizeof(char));
	return string;
}

pozL createHash(int hash_rows) {
	int i = 0;

	pozL head_hash_table = (pozL)malloc(hash_rows * sizeof(list));
	if (head_hash_table == NULL)
		return 0;

	for (i = 0; i < hash_rows; i++) {
		(head_hash_table + i)->next = NULL;
		(head_hash_table + i)->root_grad = NULL;
	}

	return head_hash_table;
}

int inputIntoHashTable(pozL head, int row, pozL drzava) {
	addSortHashTable(head + row, drzava);

	return 0;
}

int addSortHashTable(pozL head, pozL drzava) {
	if (head->next == NULL) {
		head->next = drzava;
		return 0;
	}

	pozL temp = NULL;
	pozL prev = NULL;

	for (temp = head->next; temp != NULL; temp = temp->next) {
		if (strcmp(drzava->drzava, temp->drzava) < 0) {
			prev = findPrev(head, temp);
			drzava->next = prev->next;
			prev->next = drzava;
			return 0;
		}
	}
	addLast(head, drzava);
	return 0;
}

pozL findPrev(pozL head, pozL node) {
	pozL prev = NULL;
	pozL temp = NULL;

	for (temp = head; temp->next != NULL; temp = temp->next) {
		if (temp->next == node)
			return temp;
	}

	return temp;
}

int addLast(pozL head, pozL node) {
	pozL temp = NULL;
	for (temp = head; temp->next != NULL; temp = temp->next);
	temp->next = node;

	return 0;
}

int inputDrzaveNode(pozL _drzava, char* ime_drzave, char* filename) {
	_drzava->drzava = ime_drzave;
	_drzava->dat_gradova = filename;

	return 0;
}

int createHashKey(pozL drzava, int hash_rows) {
	int sum = 0;
	int i = 0;
	int letter_value = 0;

	char letter;

	for (i = 0; i < 5; i++) {
		letter = *(drzava->drzava + i);
		letter_value = (int)letter;
		sum += letter_value;
	}

	return sum % hash_rows;
}

int inputGradInfo(pozT grad, char* ime, int stanovnici) {
	grad->grad = ime;
	grad->stanovnici = stanovnici;

	return 0;
}

int addGradTree(pozT branch, pozT grad) {
	if (grad->stanovnici > branch->stanovnici) {
		if (branch->left == NULL) {
			branch->left = grad;
			return 0;
		}
		else
			addGradTree(branch->left, grad);
	}

	else {
		if (branch->right == NULL) {
			branch->right = grad;
			return 0;
		}
		else
			addGradTree(branch->right, grad);
	}

	return 0;
}

int readFileDrzave(pozL head) {
	
	FILE* fp;

	fp = fopen("drzave.txt", "r");

	pozL newDrzava = NULL;
	int hash_key = 0;
	char* file_row;
	char* filename;
	char* drzava_ime;

	while (!feof(fp)) {
		newDrzava = createList();
		drzava_ime = createString(MAX_WORD);
		filename = createString(MAX_WORD);
		file_row = createString(MAX_WORD);
	
		fgets(file_row, MAX_WORD, fp);
		sscanf(file_row, "%s %s", drzava_ime, filename);
		
		inputDrzaveNode(newDrzava, drzava_ime, filename);
		
		hash_key = createHashKey(newDrzava, MAX_LIST);
		
		inputIntoHashTable(head, hash_key, newDrzava);
		
		readFileGrad(newDrzava);
	}

	fclose(fp);

	return 0;
}

int readFileGrad(pozL drzava) {
	FILE* fp;
	
	fp = fopen(drzava->dat_gradova, "r");
	
	pozT newGrad = NULL;
	char* ime_grad = NULL;
	int stanovnici = 0;
	char* file_row = NULL;

	while (!feof(fp)) {
		newGrad = createTree();
		ime_grad = createString(MAX_WORD);
		file_row = createString(MAX_WORD);
		
		fgets(file_row, MAX_WORD, fp);
		sscanf(file_row, "%s %d", ime_grad, &stanovnici);
		inputGradInfo(newGrad, ime_grad, stanovnici);
		
		if (drzava->root_grad == NULL)
			drzava->root_grad = newGrad;
		else {
			addGradTree(drzava->root_grad, newGrad);
		}
	}
	
	fclose(fp);
	return 0;
}

int printHash(pozL head, int hash_rows) {
	int i = 0;
	printf("\n\n\n-------HASH TABLE-------");
	for (i = 0; i < hash_rows; i++) {
		printf("\n\n%d. row:", i + 1);
		printList(head + i);
	}
	return 0;
}

int printList(pozL head) {
	pozL temp = NULL;
	for (temp = head->next; temp != NULL; temp = temp->next) {
		printf("\n\n%s\n", temp->drzava);
		printTree(temp->root_grad);
	}
	return 0;
}

int printTree(pozT branch) {
	if (branch->left != NULL)
		printTree(branch->left);
	printf("\ngrad: %s, stanovnici: %d", branch->grad, branch->stanovnici);
	if (branch->right != NULL)
		printTree(branch->right);

	return 0;
}