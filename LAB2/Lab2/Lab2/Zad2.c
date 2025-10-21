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
#define ERROR_PRINT_OUT (-3)
#define ERROR_PERSON_NOT_FOUND (-4)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Person* newPerson;  //new listmember structure

typedef struct Person {
	char name[MAX_LINE];
	char surname[MAX_LINE];
	int yearOfBirth;
	newPerson Next;
}person;

newPerson memoryAlloc();

int addFirst(char name[MAX_LINE], char surname[MAX_LINE], int yearOfBirth, newPerson P);

int addLast(char name[MAX_LINE], char surname[MAX_LINE], int yearOfBirth, newPerson P);

int printOut(newPerson P);

int searchBySurname(char surname[MAX_LINE], newPerson P);

int eraseElement(char name[MAX_LINE], char surname[MAX_LINE], newPerson P);

int main() {
	newPerson head = NULL;
	head = memoryAlloc();    //head memory allocation

	addFirst("Luka", "Knezevic", 2005, head);
	addFirst("Ana", "Beslic", 2007, head);
	addLast("Ivan", "Radojkovic", 1992, head);
	addLast("Pasko", "Bilandzic", 1989, head);
	printOut(head->Next);
	searchBySurname("Knezevic", head->Next);
	eraseElement("Luka", "Knezevic", head);
	printOut(head->Next);

	free(head);
	return EXIT_SUCCESS;
}

newPerson memoryAlloc() {
	newPerson P = (newPerson)malloc(sizeof(person));
	if (P == NULL) {
		printf("Error allocating memory!!\n");
		return ERROR_MEMORY_ALLOCATION;
	}
	else {
		P->Next = NULL;   //setting next list member to NULL
		return P;
	}
}

int addFirst(char name[MAX_LINE], char surname[MAX_LINE], int yearOfBirth, newPerson P) {
	newPerson Q = NULL;               //new list member Q
	Q = memoryAlloc();
	Q->Next = P->Next;               //new member Q is set to what P points next
	P->Next = Q;					 //P now points to Q
	strcpy(Q->name, name);           //copying string from inserted value to new list member Q
	strcpy(Q->surname, surname);
	Q->yearOfBirth = yearOfBirth;
	return EXIT_SUCCESS;
}

int addLast(char name[MAX_LINE], char surname[MAX_LINE], int yearOfBirth, newPerson P) {
	newPerson Q = NULL;
	Q = memoryAlloc(Q);
	while (P->Next != NULL) {           //
		P = P->Next;                    //ensuring that we are at the end of list
	}
	Q->Next = P->Next;
	P->Next = Q;
	strcpy(Q->name, name);
	strcpy(Q->surname, surname);
	Q->yearOfBirth = yearOfBirth;
	return EXIT_SUCCESS;
}

int printOut(newPerson P) {
	if (P == NULL) {
		printf("Nothing to print out!\n");
		return ERROR_PRINT_OUT;
	}
	while (P != NULL) {
		printf("%s %s %d\n", P->name, P->surname, P->yearOfBirth);
		P = P->Next;
	}
	return EXIT_SUCCESS;
}

int searchBySurname(char surname[MAX_LINE], newPerson P) {
	while (P != NULL) {
		P = P->Next;
		if (strcmp(P->surname, surname) == 0) {    // strcmp checks if two strings are equal
			printf("Found person with surname %s: %s %s\n", surname, P->name, P->surname);
			return EXIT_SUCCESS;
		}
		else if (strcmp(P->surname, surname) != 0 && P->Next == NULL) {  //strcmp checks inequality of two strings and the next argument looks for end of the list
			printf("Person not found!\n");
			return ERROR_PERSON_NOT_FOUND;
		}
	}
}

int eraseElement(char name[MAX_LINE], char surname[MAX_LINE], newPerson P) {
	newPerson Q = NULL;
	printf("Erasing person %s %s...\n", name, surname);
	while (P->Next != NULL) {
		Q = P;
		P = P->Next;
		if (strcmp(P->name, name) == 0 && strcmp(P->surname, surname) == 0) {
			Q->Next = P->Next;
			P->Next = NULL;
			return EXIT_SUCCESS;
		}
	}
	if (P->Next == NULL) {
		printf("Person not found!\n");
		return ERROR_PERSON_NOT_FOUND;
	}
	return EXIT_SUCCESS;
}