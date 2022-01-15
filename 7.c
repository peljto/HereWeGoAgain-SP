#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

struct Direktorij;
typedef struct Direktorij* pozicija;
typedef struct Direktorij {
	char* dirname;
	pozicija sibling;
	pozicija child;
}DIR;

struct Stog;
typedef struct Stog* poz;
typedef struct Stog {
	pozicija dir;
	poz next;
}ST;

int izbor(char*);
pozicija Dodavanje_Direktorija(pozicija, char*);
int ispis_poddirektorija(pozicija);
pozicija Poddirektorij(pozicija, char*, poz);
int Stavljanje_na_stog(pozicija, poz);
pozicija Naddirektorij(pozicija, poz);

int main()
{
	DIR root;
	root.sibling = NULL;
	root.child = NULL;
	char* komandna_linija = NULL;
	char* buff = NULL;
	int pos = 0;
	pozicija last = NULL;
	ST stog;
	stog.dir = NULL;
	stog.next = NULL;
	poz NewNode = NULL;


	root.dirname = (char*)malloc(4 * sizeof(char));
	if (root.dirname == NULL)
		printf("Greska!!!\n");

	strcpy(root.dirname, "Root");

	last = &root;

	komandna_linija = (char*)malloc(30 * sizeof(char));
	if (komandna_linija == NULL)
		printf("Greska!!!\n");

	memset(komandna_linija, 0, 30);

	buff = (char*)malloc(30 * sizeof(char));
	if (buff == NULL)
		printf("Greska!!!\n");

	memset(buff, 0, 30);

	NewNode = (poz)malloc(sizeof(ST));
	if (NewNode == NULL)
		printf("Greska!!!\n");

	NewNode->next = NULL;
	NewNode->dir = NULL;

	NewNode->dir = last;
	NewNode->next = stog.next;
	stog.next = NewNode;

	while (strcmp(buff, "exit"))
	{
		memset(komandna_linija, 0, 30);
		gets(komandna_linija);
		sscanf(komandna_linija, "%s%n", buff, &pos);

		switch (izbor(buff))
		{
		case 1://md
			memset(buff, 0, 30);
			sscanf(komandna_linija + pos, "%s", buff);
			last = Dodavanje_Direktorija(last, buff);
			break;
		case 2://cd..
			last = Naddirektorij(last, &stog);
			break;
		case 3://cd dir
			memset(buff, 0, 30);
			sscanf(komandna_linija + pos, "%s", buff);
			last = Poddirektorij(last->child, buff, &stog);
			break;
		case 4://dir
			if (ispis_poddirektorija(last) != 0)
				printf("Greska!!!\n");
			break;
		case 5://exit
			break;
		default:
			printf("%s is not recognized as an internal or external command, operable program or batch file.", buff);
			break;
		}
	}

	free(komandna_linija);
	free(buff);

	return 0;
}
pozicija Naddirektorij(pozicija last, poz stog)
{
	poz tmp = NULL;
	pozicija temp = NULL;

	tmp = stog->next;
	stog->next = tmp->next;

	temp = stog->next->dir;
	free(tmp);

	return temp;
}
pozicija Poddirektorij(pozicija lastchild, char* buff, poz stog)
{
	pozicija trenutni = NULL;

	trenutni = lastchild;

	while (strcmp(trenutni->dirname, buff) && trenutni != NULL)
		trenutni = trenutni->sibling;


	if (Stavljanje_na_stog(trenutni, stog) != 0)
		printf("Greska!!!\n");

	return trenutni;
}
int Stavljanje_na_stog(pozicija trenutni, poz stog)
{
	poz NewNode = NULL;

	NewNode = (poz)malloc(sizeof(ST));
	if (NewNode == NULL)
		printf("Greska!!!\n");

	NewNode->next = NULL;
	NewNode->dir = NULL;


	NewNode->dir = trenutni;
	NewNode->next = stog->next;
	stog->next = NewNode;

	return 0;
}
int ispis_poddirektorija(pozicija last)
{
	pozicija trenutni = NULL;

	trenutni = last->child;

	printf("\nDirectory of %s\n\n", last->dirname);

	while (trenutni != NULL)
	{
		printf("<DIR>\t%s\n", trenutni->dirname);
		trenutni = trenutni->sibling;
	}

	return 0;
}
pozicija Dodavanje_Direktorija(pozicija last, char* dirname)
{
	pozicija Novi_cvor = NULL;
	pozicija prethodni = NULL;

	Novi_cvor = (pozicija)malloc(sizeof(DIR));
	if (Novi_cvor == NULL)
		printf("Greska!!!\n");

	Novi_cvor->dirname = (char*)malloc(30 * sizeof(char));
	if (Novi_cvor->dirname == NULL)
		printf("Greska!!!\n");

	strcpy(Novi_cvor->dirname, dirname);
	Novi_cvor->child = NULL;
	Novi_cvor->sibling = NULL;

	if (last->child == NULL)
	{
		Novi_cvor->child = last->child;
		last->child = Novi_cvor;

		return last;
	}

	prethodni = last->child;

	while (prethodni->sibling != NULL && (strcmp(prethodni->sibling->dirname, Novi_cvor->dirname) < 0))
		prethodni = prethodni->sibling;

	if (prethodni != NULL && (strcmp(prethodni->dirname, Novi_cvor->dirname) < 0))
	{
		Novi_cvor->sibling = prethodni->sibling;
		prethodni->sibling = Novi_cvor;

		return last;
	}
	else
	{
		Novi_cvor->sibling = last->child;
		last->child = Novi_cvor;

		return last;
	}

}
int izbor(char* komanda)
{
	if (!strcmp(komanda, "md"))
		return 1;
	else if (!strcmp(komanda, "cd.."))
		return 2;
	else if (!strcmp(komanda, "cd"))
		return 3;
	else if (!strcmp(komanda, "dir"))
		return 4;
	else if (!strcmp(komanda, "exit"))
		return 5;
}