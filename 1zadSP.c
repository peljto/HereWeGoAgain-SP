//cita redove u datoteci tj broj studenata u datoteci - readFile
//alocirat prostor
//strukt(ime, prezime, bodovi) - ucitat iz datoteke
//ispisat ime prezime apsolutni i relativni broj bodova

#define CRT_SECURE_NO_WARNINGS
#define MAX 64
#define MAX_RED 100

#include<stdio.h>
#include<stdlib.h>

typedef struct _student {
	char ime[MAX];
	char prezime[MAX];
	double bodovi;
}student;

int brojRedova(char);

int main()
{
	float aps;
	int br = 0, i = 0, max = 0;

	char filename[MAX] = "studenti.txt";

	student s;
	FILE* fp;

	student* niz = NULL;

	br = brojRedova(filename);

	niz = (student*)malloc(br * sizeof(student));

	fp = fopen(filename, "r");

	while (!(feof(fp))) {
		fscanf(fp, " %s %s %d", s.ime, s.prezime, &s.bodovi);
		niz[i] = s;

		if (s.bodovi >= max)
			max = s.bodovi;
		
		i++;
	}

	for (i = 0; i < br; i++) {
		aps = (float)niz[i].bodovi / max * 100;

		printf("\t %s %s %d - %.2f\n", niz[i].ime, niz[i].prezime, niz[i].bodovi, aps);
	}

	fclose(fp);

	return 0;
}

int brojRedova(char filename[MAX]) {
	int br = 0;
	char red[MAX_RED];
	
	FILE* fp;
	fp = fopen(filename, "r");

	while (fgets(red, 100, fp))
		br++;

	fclose(fp);
	return br;
}
