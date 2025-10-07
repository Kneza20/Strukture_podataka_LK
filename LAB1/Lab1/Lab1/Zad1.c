/*Napisati program koji prvo pročita koliko redaka ima datoteka, tj. 
koliko ima studenata zapisanih u datoteci. Nakon toga potrebno je dinamički 
alocirati prostor za niz struktura studenata (ime, prezime, bodovi) i učitati 
iz datoteke sve zapise. Na ekran ispisati ime, prezime, apsolutni i relativni 
broj bodova. Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te 
broj bodova na kolokviju. relatvan_br_bodova = br_bodova/max_br_bodova*100*/
#define MAX_LINE (1024)
#define _CRT_SECURE_NO_WARNINGS
#define FILE_NOT_OPENED (-1)
#include <stdio.h>
#include <stdlib.h>

typedef struct student {
	char ime[20];
	char prezime[20];
	int brojBodova;
}Student;

int brojStud(int i) {     //fja za prebrojavanje studenata
	FILE* fp;
	char buffer[MAX_LINE];
	fp = fopen("doc.txt", "r");
	while (fgets(buffer,MAX_LINE, fp) != NULL) {
		i = i+1;
	}
	fp = fclose(fp);
	return i;
}

int main() {
	int i = 0;
	Student s;

	printf("U datoteci je zapisano %d studenata.\n", brojStud(i));

	return 0;
}