/* Prethodnom zadatku dodati funkcije: 
A. dinamicki dodaje novi element iza odredjenog elementa, 
B. dinamicki dodaje novi element ispred odredjenog elementa, 
C. sortira listu po prezimenima osoba, 
D. upisuje listu u datoteku, 
E. cita listu iz datoteke.*/
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

newPerson searchBySurname(char surname[MAX_LINE], newPerson P);

int eraseElement(char name[MAX_LINE], char surname[MAX_LINE], newPerson P);

//part of zad3

int addAfter(char surn[MAX_LINE], char name[MAX_LINE], char surname[MAX_LINE], int yearOfBirth, newPerson P);

int addBefore(char surn[MAX_LINE], char name[MAX_LINE], char surname[MAX_LINE], int yearOfBirth, newPerson P);

int sortListBySurname(newPerson P);

int writeInList(newPerson P);

int readFromList(newPerson P);

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

	//part of zad3
	addAfter("Beslic", "Ante", "Brcic", 2005, head);
	addBefore("Bilandzic", "Kreso", "Stojic", 1990, head);
	writeInList(head->Next);
	readFromList(head);
	printf("Sorted list: \n");
	sortListBySurname(head);
	writeInList(head->Next);
	printOut(head->Next);
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
	newPerson Q = NULL;              //new list member Q
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
	Q = memoryAlloc();
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

newPerson searchBySurname(char surname[MAX_LINE], newPerson P) {
	while (P != NULL && strcmp(P->surname, surname) != 0) {
		P = P->Next;
	}
	if (P == NULL) {
		printf("Person not found!\n");
	}
	return P;
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

			free(P);
			return EXIT_SUCCESS;
		}
	}

	if (P->Next == NULL) {
		printf("Person not found!\n");
		return ERROR_PERSON_NOT_FOUND;
	}

	return EXIT_SUCCESS;
}

// zad 3

int addAfter(char surn[MAX_LINE], char name[MAX_LINE], char surname[MAX_LINE], int yearOfBirth, newPerson P) {
	newPerson previous = NULL;
	newPerson Q = NULL;

	previous = searchBySurname(surn, P);
	if (previous == NULL) {
		printf("Error finding person!\nb");
		return ERROR_PERSON_NOT_FOUND;
	}

	Q = memoryAlloc();

	Q->Next = previous->Next;
	previous->Next = Q;
	strcpy(Q->name, name);
	strcpy(Q->surname, surname);
	Q->yearOfBirth = yearOfBirth;

	return EXIT_SUCCESS;
}

int addBefore(char surn[MAX_LINE],char name[MAX_LINE], char surname[MAX_LINE], int yearOfBirth, newPerson P) {
	newPerson prev = NULL;
	newPerson Q = NULL;
	newPerson temp = P;
	prev = searchBySurname(surn, P);
	if (prev == NULL) {
		printf("Person not found!\n");
		return ERROR_PERSON_NOT_FOUND;
	}
	while (temp->Next != prev) {
		temp = temp->Next;
	}
	Q = memoryAlloc();
	Q->Next = prev;
	temp->Next = Q;
	strcpy(Q->name, name);
	strcpy(Q->surname, surname);
	Q->yearOfBirth = yearOfBirth;
	return EXIT_SUCCESS;
}

int sortListBySurname(newPerson P) {
	newPerson Q, prev, temp, end = NULL;

	while (P->Next != end) {
		prev = P;
		Q = P->Next;
		while (Q->Next != end) {
			if (strcmp(Q->surname, Q->Next->surname) > 0) {
				temp = Q->Next;
				prev->Next = temp;
				Q->Next = temp->Next;
				temp->Next = Q;
				prev = temp;
			}
			else {
				prev = Q;
				Q = Q->Next;
			}
		}
		end = Q;
	}

	return EXIT_SUCCESS;
}

int writeInList(newPerson P) {
	FILE *fp=NULL;
	fp = fopen("list.txt", "w");
	if (fp == NULL) {
		printf("File didn't open!\n");
		return ERROR_FILE_NOT_OPENED;
	}
	while (P != NULL) {
		fprintf(fp, "%s %s %d", P->name, P->surname, P->yearOfBirth);
		if (P->Next != NULL) {
			fprintf(fp, "\n");
		}
		P = P->Next;
	}

	fclose(fp);
	printf("Data has been inserted!\n");
	return EXIT_SUCCESS;
}

int readFromList(newPerson P) {
	FILE* fp;
	char name[MAX_LINE], surname[MAX_LINE];
	int yearOfBirth = 0;
	fp = fopen("list.txt", "r");
	if (fp == NULL) {
		printf("File didn't open!\n");
		return ERROR_FILE_NOT_OPENED;
	}
	while (!feof(fp)) {
		(void)fscanf(fp, "%s %s %d", name, surname, &yearOfBirth);
		addLast(name, surname, yearOfBirth, P);
	}

	fclose(fp);
	return EXIT_SUCCESS;
}