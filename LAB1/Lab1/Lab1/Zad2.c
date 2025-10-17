/* Definirati strukturu osoba (ime, prezime, godina rodjenja) i napisati program koji: 
A. dinamicki dodaje novi element na pocetak liste, 
B. ispisuje listu, 
C. dinamicki dodaje novi element na kraj liste, 
D. pronalazi element u listi (po prezimenu), 
E. brise odredjeni element iz liste, U zadatku se ne smiju koristiti globalne varijable.*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define personBuffer (20)

typedef struct Person {
	char name[personBuffer];
	char surname[personBuffer];
	int yearOfBirth;
}person;

int main() {
	person* p=NULL;

	return 0;
}