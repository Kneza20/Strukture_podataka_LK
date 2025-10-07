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

typedef struct student {
	char ime[20];
	char prezime[20];
	int brojBodova;
}Student;

int brojStud(int i) {

}

int main() {
	Student s;
	FILE *fp;

	return 0;
}