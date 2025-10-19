/* Definirati strukturu osoba (ime, prezime, godina rodjenja) i napisati program koji: 
A. dinamicki dodaje novi element na pocetak liste, 
B. ispisuje listu, 
C. dinamicki dodaje novi element na kraj liste, 
D. pronalazi element u listi (po prezimenu), 
E. brise odredjeni element iz liste, U zadatku se ne smiju koristiti globalne varijable.*/
#define _CRT_SECURE_NO_WARNINGS
#define MAX_LINE (1024)
#define ERROR_FILE_NOT_OPENED (-1)
#define ERROR_MEMORY_ALLOCATION (-2)
#include <stdio.h>
#include <stdlib.h>

typedef struct Person* newPerson;

typedef struct Person {
	char name[MAX_LINE];
	char surname[MAX_LINE];
	int yearOfBirth;
	newPerson Next;
}person;

int memoryAlloc(newPerson P) {
	P = (newPerson)malloc(sizeof(person));
	if (P == NULL) {
		printf("Error allocating memory!!\n");
		return ERROR_MEMORY_ALLOCATION;
	}
	else {
		return P;
	}
}

int addFirst(char name[MAX_LINE], char surname[MAX_LINE], int yearOfBirth, newPerson P);

int addLast(char name[MAX_LINE], char surname[MAX_LINE], int yearOfBirth, newPerson P);

int printOut(newPerson P);

int searchBySurname(char surname[MAX_LINE], newPerson P);

int erase(char name[MAX_LINE], char surname[MAX_LINE], int yearOfBirth, newPerson P);

int main() {
	newPerson head = NULL;
	head = memoryAlloc(head);

	head->Next;
	addFirst("Luka", "Knezevic", 2005, head);
	addLast("Ana", "Beslic", 2007, head);

	return 0;
}

int addFirst(char name[MAX_LINE], char surname[MAX_LINE], int yearOfBirth, newPerson P) {
	newPerson Q = NULL;
	Q = memoryAlloc(Q);
	Q->Next = P->Next;
	P->Next = Q;
	strcpy(Q->name, name);
	strcpy(Q->surname, surname);
	Q->yearOfBirth = yearOfBirth;
	return EXIT_SUCCESS;
}

int addLast(char name[MAX_LINE], char surname[MAX_LINE], int yearOfBirth, newPerson P) {
	newPerson Q = NULL;
	Q = memoryAlloc(Q);
	while (P->Next != NULL) {
		P = P->Next;
	}
	Q->Next = P->Next;
	P->Next = Q;
	strcpy(Q->name, name);
	strcpy(Q->surname, surname);
	Q->yearOfBirth = yearOfBirth;
	return EXIT_SUCCESS;
}