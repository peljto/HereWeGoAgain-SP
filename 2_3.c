#define _CRT_SECURE_NO_WARNINGS
#define M 100

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct _osoba;
typedef struct _osoba* poz;

typedef struct _osoba {
	char ime[M];
	char prezime[M];
	int godina;
	poz next;
}osoba;

int unosPocetak(poz);
int ispis(poz);
int unosKraj(poz);
poz trazi(poz, char*);
int brisi(poz, char*);
poz traziPrethodnog(poz, char*);
int unosIza(poz);
int unosIspred(poz);
int addSort(poz, poz);
int readFile(poz, char);
int writeFile(poz, char);


int main()
{
	return 0;
}

poz stvoriOsobu() {
	poz temp = (poz)malloc(sizeof(osoba));

	if (temp == NULL)
		return -1;
	else {
		temp->next = NULL;
		return temp;
	}
}

int unosPocetak(poz temp) {
	
	poz q = NULL;
	q = (poz)malloc(sizeof(osoba));

	if (q == NULL)
		return -1;

	printf("Unesite ime osobe:\t");
	scanf(" %s", q->ime);

	printf("\nUnesite prezime osobe:\t");
	scanf(" %s", q->prezime);

	printf("\nUnesite godinu rodenja osobe:\t");
	scanf("%d", &q->godina);

	q->next = temp->next;
	temp->next = q;

	return 0;
}

int ispis(poz head) {
	poz temp = head->next; //netribamo ispisat head

	while (temp != NULL) {
		printf("%s %s %d", temp->ime, temp->prezime, temp->godina);

		temp = temp->next;
	}
	return 0;
}

int unosKraj(poz temp) {
	while (temp->next != NULL) { //temp next jer saljemo head
		temp = temp->next;
	}
	unosPocetak(temp);

	return 0;
}

poz trazi(poz temp) {
	char prezime[M];

	printf("Unesite prezime osobe koju zelite pronaci:\t");
	scanf(" %s", prezime);

	while (temp->next != NULL && strcmp(temp->prezime, prezime))
		temp = temp->next;

	if (temp == NULL)
		return temp;

	return temp;
}

int brisi(poz head, char* prezime) { //nisam sigurna jel se trazi da se brise samo po prezimenu ili po bilokojem faktoru
	poz temp = head->next;
	poz prev = head; //prev - temp, setaju po listi

	while (temp != NULL) {
		if (strcmp(temp->prezime, prezime) == 0) {
			prev->next = temp->next;
			free(temp);
			temp = prev->next;
		}
		prev = temp;
		temp = temp->next;
	}
	return 0;
}

poz traziPrethodnog(poz temp, char* prezime) {
	poz prev = temp;
	temp = temp->next;

	while (temp->next != NULL && strcmp(temp->prezime, prezime)) {
		prev = temp;
		temp = temp->next;
	}

	if (temp->next == NULL) {
		printf("Trazena osoba ne postoji!\n");
		return NULL;
	}

	return prev;
}

int unosIza(poz temp) {
	temp = trazi(temp);

	if (temp == NULL)
		return -1;

	unosPocetak(temp);

	return 0;
}
int unosIspred(poz temp) {
	temp = traziPrethodnog(temp);

	if (temp == NULL)
		return -1;

	unosPocetak(temp);

	return 0;
}
int addSort(poz head, poz current) {
	if (head->next == NULL) {
		current->next = head->next;
		head->next = current;
		return 0;
	}

	poz temp = head->next;
	poz prev = head;

	while (temp != NULL) {
		if (strcmp(temp->prezime, current->prezime) < 0) {
			prev = temp;
			temp = temp->next;
		}
		else {
			current->next = prev->next;
			prev->next = current;
			return 0;
		}
	}
	current->next = prev->next;
	prev->next = current;

	return 0;
}

int readFile(poz temp, char filename) {
	FILE* fp;

	fp = fopen(filename, "r");

	if (fp == NULL)
		return -1;

	char* string = (char*)malloc(M * sizeof(char));
	poz temp = NULL;
	while (!feof(fp)) {
		fgets(string, M, fp);
		temp = stvoriOsobu();
	}

	fclose(fp);

	return 0;
}
int writeFile(poz temp, char filename) {
	FILE* fp;

	fp = fopen(filename, "w");

	if (fp == NULL)
		return -1;

	while (temp->next != NULL) {
		fprintf(fp, " %s %s %d\n", temp->ime, temp->prezime, temp->godina);
		temp = temp->next;
	}

	fclose(fp);

	return 0;
}

