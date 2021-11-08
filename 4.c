#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

struct polinom;
typedef struct polinom* Polinom;
struct polinom {
	int koeficijent;
	int potencija;
	Polinom next;
};

int Unos(Polinom);
int Ispis(Polinom);
int Suma(Polinom, Polinom, Polinom);
int Umnozak(Polinom, Polinom, Polinom);

int main()
{
	struct polinom p1, p2, suma, produkt;
	p1.next = NULL;
	p2.next = NULL;
	suma.next = NULL;
	produkt.next = NULL;

	Unos(&p1);
	Unos(&p2);

	printf("\tPrvi polinom:\n ");
	Ispis(p1.next);
	printf("\tDrugi polinom:\n ");
	Ispis(p2.next);

	Suma(p1.next, p2.next, &suma);

	printf("\tSuma:\n ");
	Ispis(suma.next);

	Umnozak(p1.next, p2.next, &produkt);

	printf("\tProdukt: \n ");
	Ispis(produkt.next);

	return 0;
}

int Unos(Polinom P)
{
	char str[20];
	FILE* dat = NULL;
	Polinom q = NULL, prev = NULL, temp = NULL;

	printf("Upisi ime datoteke: ");
	scanf(" %s", str);
	if (strchr(str, '.') == NULL)
		strcat(str, ".txt");

	dat = fopen(str, "r");
	if (dat == NULL) return -1;

	while (!feof(dat))
	{
		q = (Polinom)malloc(sizeof(struct polinom));
		if (q == NULL) return -1;
		q->next = NULL;

		fscanf(dat, "%d %d", &q->koeficijent, &q->potencija);

		prev = P;
		temp = P->next;

		while (temp != NULL && temp->potencija > q->potencija)
		{
			prev = temp;
			temp = temp->next;
		}
		q->next = temp;
		prev->next = q;
	}
	fclose(dat);
	return 0;
}

int Ispis(Polinom P)
{
	while (P->next != NULL)	//ispis s plusom do predzadnjeg elementa (ukljucujuci njega)
	{
		printf("%d*x^%d + ", P->koeficijent, P->potencija);
		P = P->next;
	}
	printf("%d*x^%d", P->koeficijent, P->potencija);	//ispis posljednjeg elementa bez plusa
	printf("\n");
	return 0;
}

int Suma(Polinom P1, Polinom P2, Polinom S)
{
	Polinom q, temp;
	q = temp = NULL;

	while (P1 != NULL && P2 != NULL)
	{
		q = (Polinom)malloc(sizeof(struct polinom));
		if (q == NULL) return -1;
		q->next = NULL;

		if (q == NULL) return -1;

		if (P1->potencija > P2->potencija)
		{
			q->koeficijent = P1->koeficijent;
			q->potencija = P1->potencija;

			P1 = P1->next;
		}
		else if (P1->potencija < P2->potencija)
		{
			q->koeficijent = P2->koeficijent;
			q->potencija = P2->potencija;

			P2 = P2->next;
		}
		else
		{
			q->koeficijent = P1->koeficijent + P2->koeficijent;
			q->potencija = P1->potencija;

			P1 = P1->next;
			P2 = P2->next;
		}
		q->next = S->next;
		S->next = q;
		S = q;
	}

	if (P1 != NULL)
		temp = P1;
	else
		temp = P2;

	while (temp != NULL)
	{
		q = (Polinom)malloc(sizeof(struct polinom));
		if (q == NULL) return -1;
		q->next = NULL;

		if (q == NULL) return -1;

		q->koeficijent = temp->koeficijent;
		q->potencija = temp->potencija;

		S->next = q;
		S = q;

		temp = temp->next;
	}
	return 0;
}

int Umnozak(Polinom P1, Polinom P2, Polinom P)
{
	Polinom q = NULL, Pocetak1 = P1, Pocetak2 = P2, temp = P->next, prev = P;
	int ZbrPot;

	while (P1 != NULL)
	{
		P2 = Pocetak2;

		while (P2 != NULL)
		{
			prev = P;
			temp = P->next;

			ZbrPot = P1->potencija + P2->potencija;

			while (temp != NULL && temp->potencija > ZbrPot)
			{
				temp = temp->next;
				prev = prev->next;
			}

			if (temp != NULL && temp->potencija == ZbrPot)
			{
				temp->koeficijent += (P1->koeficijent * P2->koeficijent);
			}
			else
			{
				q = (Polinom)malloc(sizeof(struct polinom));
				if (q == NULL) return -1;
				q->next = NULL;

				if (q == NULL) return -1;

				q->koeficijent = P1->koeficijent * P2->koeficijent;
				q->potencija = ZbrPot;

				prev->next = q;
				q->next = temp;
			}
			P2 = P2->next;
		}
		P1 = P1->next;
	}
	return 0;
}