//iz datoteke cita postix
//preko stoga racuna
//stog preko vezane liste

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX (32)

typedef struct _node* poz;
typedef struct _node {
	int el;
	poz next;
}node;

int push(poz, poz);
int pop(poz);
poz createNode();
int readFile(char);
int racunaj(poz, char*);

int main()
{
	node stack;
	stack.next = NULL;
	char filename[MAX];
	char* postfix;

	printf("\nUnesite ime datoteke: ");
	scanf("%s", filename);

	postfix = readFile(filename);

	racunaj(&stack, postfix);

	printf("\nrezultat = %d\n", stack.next->el);

	return 0;
}

int push(poz stack, poz current) {
	current->next = stack->next;
	stack->next = current;

	return 0;
}

int pop(poz stack) {
	int broj = 0;
	broj = stack->next->el;

	poz temp;
	temp = stack->next;
	stack->next = stack->next->next;
	free(temp);

	return broj;
}

poz createNode() {
	poz temp = malloc(sizeof(node));
	
	if (temp == NULL)
		return NULL;
	
	temp->next = NULL;
	return temp;
}

int readFile(char filename[MAX]) {
	FILE* fp;
	strcat(filename, ".txt");

	fp = fopen(filename, "r");

	char* postfix = (char*)malloc(MAX * sizeof(char));

	//netriba while jer nam je zapis samo u jednom redu

	fgets(postfix, MAX, fp);

	fclose(fp);

	return postfix;
}

int racunaj(poz stack, char* row) {
	int n = 0, a = 0, b = 0;
	char c;
	poz temp;

	while (strlen(row) > 0) {
		sscanf(row, " %c %n", &c, &n);
		row += n; //pomicanje po stringu sa %n

		//printf("\n%s", row); samo za provjeru

		if (c - '+' == 0 || c - '-' == 0 || c - '*' == 0) { //ako naide na zadane operatore skini ih sa stoga napravi operaciju i rezultat vrati na stog
			a = pop(stack);
			b = pop(stack);

			printf("\n\ta = %d b = %d\n", a, b);

			if (c - '+' == 0) {
				a += b;
				printf("\n\t a + b = %d\n", a);
			}
			else if (c - '-' == 0) {
				a -= b;
				printf("\n\t a - b = %d\n", a);
			}
			else if (c - '*' == 0){
				a = a * b;
				printf("\n\t a * b = %d\n", a);
			}

			temp = createNode();
			temp->el = a;
			push(stack, temp);
		}
		else { //ako ne samo stvori node i pushaj na stog
			temp = createNode();
			temp->el = c - '0';
			push(stack, temp);
		}
	}

	return 0;
}