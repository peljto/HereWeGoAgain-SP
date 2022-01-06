//testni podatci - 2,5,7,8,11,1,4,2,3,7
//insert ali livo su veci, desno su manji, i ima duplih
//replace sa sumom potomaka
//rand 10-90, upisat u datoteku, inorder


#define _CRT_SECURE_NO_WARNINGS
#define MAX 100

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct _tree;
typedef struct _tree* poz;
typedef struct _tree {
	int el;
	poz left;
	poz right;
}tree;
//upisujemo stablo u listu u inorder obliku i onda listu u datoteku

struct _list;
typedef struct _list* pos;
typedef struct _list {
	int el;
	pos next;
}list;

poz createTree(int);
poz insert(poz, int);
poz printTree(poz, int);
int replace(poz);
pos createList(int);
int push(pos, int);
pos inorder(poz, pos);
int writeFile(poz, pos);

int main() {
	srand(time(NULL));

	poz head = NULL;
	list head1;
	list head2;

	head1.next = NULL;
	head2.next = NULL;

	int i = 0;
	int el = 0;

	for (i = 0; i < 10; i++) {
		//scanf("%d", &el); - zad a) i b)
		el = (rand() % 81) + 10;
		head = insert(head, el);
	}

	printTree(head, 0);

	writeFile(head, &head1);

	replace(head);

	printf("\n\n");

	printTree(head, 0);
	writeFile(head, &head2);

	
	return 0;
}

poz createTree(int el) {
	poz temp = (poz)malloc(sizeof(tree));

	if (temp == NULL)
		return NULL;

	temp->left = NULL;
	temp->right = NULL;
	temp->el = el;

	return temp;
}

poz insert(poz temp, int el) {
	if (temp == NULL)
		temp = createTree(el);

	else if (el < temp->el)
		temp->right = insert(temp->right, el);

	else if (el >= temp->el)
		temp->left = insert(temp->left, el);

	return temp;
}

poz printTree(poz temp, int num) {
	int i = 0;

	if (temp->right != NULL)
		printTree(temp->right, num + 1);

	for (i = 0; i < num; i++)
		printf("\t");

	printf("%d\n", temp->el);

	if (temp->left != NULL)
		printTree(temp->left, num + 1);

	return 0;
}

int replace(poz temp) {
	int el;
	
	int sumR = 0;
	int sumL = 0;

	if (temp->left != NULL)
		sumL = replace(temp->left);
	if (temp->right != NULL)
		sumR = replace(temp->right);

	el = temp->el;
	temp->el = sumR + sumL;

	return el + temp->el;
}

pos createList(int el) {
	pos temp = (pos)malloc(sizeof(list));

	if (temp == NULL)
		return NULL;

	temp->next = NULL;
	temp->el = el;

	return temp;
}

int push(pos list1, int el) {
	pos temp = createList(el);

	temp->next = list1->next;
	list1->next = temp;

	return 0;
}

pos inorder(poz tree1, pos list1) {
	if (tree1 == NULL)
		return NULL;

	inorder(tree1->left, list1);
	push(list1, tree1->el);
	inorder(tree1->right, list1);

	return tree1;
}

int writeFile(poz tree1, pos list1) {
	FILE* fp;

	fp = fopen("test.txt", "a");

	inorder(tree1, list1);

	pos temp = list1->next;

	while (temp != NULL) {
		fprintf(fp, "%d ", temp->el);
		temp = temp->next;
	}

	fprintf(fp, "\n\n");

	fclose(fp);

	return 0;
}