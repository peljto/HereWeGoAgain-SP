//binarno stablo pretrazivanja
//unosenje novog elementa
//ispis elementa - inorder, preorder, postorder, level order
//brisanje
//pronalazenje

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

struct _tree;
typedef struct _tree* poz;
typedef struct _tree {
	int el;
	poz left;
	poz right;
}tree;

poz createEmptyTree(poz);
poz addElementsInTree(int, poz);
poz findElementInTree(int, poz);
poz findMin(poz);
poz deleteElementInTree(int, poz);
poz inorder(poz);
poz postorder(poz);
poz preorder(poz);
int freeTree(poz);

int main()
{
	poz tree = NULL;
	poz x = NULL;
	int a, el;

	do {

		printf("\n\n1.add new element in tree\n");
		printf("2.inorder\n");
		printf("3.preorder\n");
		printf("4.postorder\n");
		printf("5.find element in tree\n");
		printf("6.delete element in tree\n");
		printf("0.end program");

		printf("\n\nyour choice: \n");
		scanf("%d", &a);

		switch (a) {
		case 1:
			printf("\nadd new element: \n");
			scanf("%d", &el);
			tree = addElementsInTree(el, tree);
			if (tree == NULL)
				printf("error!\n");
			break;
		case 2:
			x = inorder(tree);
			break;
		case 3:
			x = preorder(tree);
			break;
		case 4:
			x = postorder(tree);
			break;
		case 5:
			printf("\nfind element in tree\n");
			scanf("%d", &el);
			x = findElementInTree(el, tree);
			if (x == NULL)
				printf("element does not exist\n\n");
			else
				printf("element %d is found\n\n", x->el);
			break;
		case 6:
			printf("\ndelete this element: \n\n");
			scanf("%d ", &el);
			el = deleteElementInTree(el, tree);
			if (tree == NULL)
				printf("ERROR\n");
			break;
		case 0:
			printf("\ngbye!\n");
			break;
		default:
			printf("\nlol, try again!\n");

		}

	} while (a != 0);

	freeTree(tree);

	return 0;
}

poz createEmptyTree(poz t) {
	if (t != NULL) {
		createEmptyTree(t->left);
		createEmptyTree(t->right);
		free(t);
	}
	else
		return NULL;
}

poz addElementsInTree(int el, poz t) {
	if (t == NULL) {
		t = (poz)malloc(sizeof(tree));
		t->el = el;
		t->right = NULL;
		t->left = NULL;
	}
	else if (el < t->el)
		t->left = addElementsInTree(el, t->left);
	else if (el > t->el)
		t->right = addElementsInTree(el, t->right);
	else {
		printf("\nElement already exists!");
		free(t);
	}
	return t;
}

poz findElementInTree(int el, poz t) {
	if (t == NULL)
		return NULL;
	
	if (el < t->el)
		return findElementInTree(el, t->left);
	else if (el > t->el)
		return findElementInTree(el, t->right);
	else
		return t;
}

poz findMin(poz t) {
	if (t == NULL)
		return NULL;

	if (t->left == NULL)
		return t;
	else
		return findMin(t->left);
}

poz deleteElementInTree(int el, poz t) {
	if (t == NULL) {
		printf("\nElement does not exist!");
		return t;
	}
	else if (el < t->el) {
		t->left = deleteElementInTree(el, t->left);
		printf("AAAAAAAAAAAAAAAA");
	}
	else if (el > t->el)
		t->right = deleteElementInTree(el, t->right);
	else if (t->left != NULL && t->right != NULL) {
		poz temp = findMin(t->right);
		t->el = temp->el;

		t->right = deleteElementInTree(t->el, t->right);
	}
	else {
		poz temp = t;

		if (t->left == NULL)
			t = t->right;
		else
			t = t->left;

		free(temp);
	}

	return t;
}

poz inorder(poz t) {
	if (t == NULL)
		return 0;

	inorder(t->left);
	printf("%d ", t->el);
	inorder(t->right);

	return 0;
}

poz postorder(poz t) {
	if (t == NULL)
		return 0;

	postorder(t->left);
	postorder(t->right);
	printf("%d ", t->el);

	return 0;
}

poz preorder(poz t) {
	if (t == NULL)
		return 0;

	printf("%d ", t->el);
	preorder(t->left);
	preorder(t->right);

	return 0;
}

int freeTree(poz t) {
	if (t == NULL)
		return -1;

	freeTree(t->left);
	freeTree(t->right);
	free(t);

	return 0;
}