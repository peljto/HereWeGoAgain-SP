//2
//strukt osoba - ime prezime godina rod +
//dinamicki dodaje novi element na pocetak liste +
//ispis liste +
//dinamicki dodaje novi element na kraj liste +
//pronalazak po prezimenu +
//brise odredeni element - napravljeno bez dodatne funkcije, sa setanjem dva pokazivaca po listi +
//3
//dinamicki dodaje novi element iza odredenog
//dinamicki dodaje novi element ispred odredenog - dodatna funkcija koja ce nam naci prethodnog od trazenog i izmedu njih staviti novi element
//sortira listu po prezimenima - addSort
//upisuje listu u datoteku - addList
//cita listu iz datoteke - readList

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

poz stvoriOsobu(char*, char*, int);
int unosPocetak(poz, poz);
int ispis(poz);
int unosKraj(poz, poz);
poz trazi(poz, char*);
int brisi(poz, char*);
//int unosIza(poz);
//poz traziPrethodnog(poz);
//int unosIspred(poz);


int main()
{
	poz p = NULL;
	poz n = NULL;
	osoba head;
	head.next = NULL;
	int izbor = 0;
	char ime[M], prezime[M], prezimePronalazak[M];
	int god;

	while (1) {
		printf("\nIZBORNIK:"
			"\n\t1-Dodaj osobu na pocetak liste\n"
			"\t2-Ispis liste\n"
			"\t3-Dodaj osobu na kraj liste\n"
			"\t4-Pronalazak osobe po prezimenu\n"
			"\t5-Brisi osobu iz liste po prezimenu\n"
			"\t0-Izlaz iz programa\n");

		printf("\nVAS IZBOR - ");
		scanf("%d", &izbor);

		switch (izbor) {
		case 1:
			printf("Unesite ime osobe:\t");
			scanf(" %s", ime);

			printf("\nUnesite prezime osobe:\t");
			scanf(" %s", prezime);

			printf("\nUnesite godinu rodenja osobe:\t");
			scanf("%d", &god);

			printf("\n");

			p = stvoriOsobu(ime, prezime, god);
			unosPocetak(&head, p);
			ispis(&head);
			
			break;
		case 2:
			ispis(&head);

			break;
		case 3:
			printf("Unesite ime osobe:\t");
			scanf(" %s", ime);

			printf("\nUnesite prezime osobe:\t");
			scanf(" %s", prezime);

			printf("\nUnesite godinu rodenja osobe:\t");
			scanf("%d", &god);

			printf("\n");

			p = stvoriOsobu(ime, prezime, god);
			unosKraj(&head, p);
			ispis(&head);

			break;
		case 4:
			printf("Unesite prezime osobe koju zelite pronaci:\t");
			scanf(" %s", prezimePronalazak);

			p = trazi(&head, prezimePronalazak);

			printf("\n%s %s %d\n", p->ime, p->prezime, p->godina);

			break;
		case 5:
			printf("Unesite prezime osobe koju zelite izbrisati:\t");
			scanf(" %s", prezimePronalazak);

			brisi(&head, prezimePronalazak);
			ispis(&head);

			break;
		case 0:
			printf("Izlaz iz programa!\n");
			return -1;
			break;
		}

	}

	return 0;
}

poz stvoriOsobu(char* ime, char* prezime, int god) {
	poz temp = (poz)malloc(sizeof(osoba));

	strcpy(temp->ime, ime);
	strcpy(temp->prezime, prezime);
	temp->godina = god;
	
	temp->next = NULL;

	return temp;
}

int unosPocetak(poz head, poz temp) {
	temp->next = head->next;
	head->next = temp;

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

int unosKraj(poz temp, poz p) {
	while (temp->next != NULL) { //temp next jer saljemo head
		temp = temp->next;
	}
	unosPocetak(temp, p);

	return 0;
}

poz trazi(poz temp, char* prezime) {
	while (temp->next != NULL && strcmp(temp->prezime, prezime))
		temp = temp->next;
	
	/*if (temp == NULL)
		printf("\nNema trazene osobe u listi!");
	*/
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
