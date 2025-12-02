/*Napisati program za zbrajanje i množenje polinoma. 
Koeficijenti i eksponenti se čitaju iz datoteke. 
Napomena: Eksponenti u datoteci nisu nužno sortirani.*/
#define _CRT_SECURE_NO_WARNINGS
#define MAX_LINE 1024
#define ERROR_FILE (-1)
#define ERROR_PRINTING (-2)
#define ERROR_MEMORY_ALLOC (-3)
#define ERROR_READING_POLYNOME (-4)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct polynome* Position;

typedef struct polynome {
	int coefficient;
	int power;
	Position Next;
}polynome;

Position memoryAlloc();

Position addToList(int coefficient, int power);

int readFile(Position FirstP, Position SecondP);

int sortedInput(Position Q, int coef, int pow);

int Addition(Position FirstP, Position SecondP, Position AddResult);

int Multiplication(Position FirstP, Position SecondP, Position MultResult);

int printPoly(Position Q);

int freePoly(Position Q);

int main() {
	polynome FirstP, SecondP, result;
	FirstP.Next = NULL;
	SecondP.Next = NULL;
	result.Next = NULL;

	readFile(&FirstP, &SecondP);

	printf("Polynomes:\n");
	printPoly(FirstP.Next);
	printPoly(SecondP.Next);
	printf("\n");

	printf("Addition of 2 polynomes: ");
	Addition(FirstP.Next, SecondP.Next, &result);
	printPoly(result.Next);

	freePoly(&result);

	printf("\nMultiplication of 2 polynomes: ");
	Multiplication(FirstP.Next, SecondP.Next, &result);
	printPoly(result.Next);

	freePoly(&FirstP);
	freePoly(&SecondP);
	freePoly(&result);

	return 0;
}

Position memoryAlloc() {
	Position Q = (Position)malloc(sizeof(polynome));
	if (Q == NULL) {
		printf("Error allocating memory!");
		return NULL;
	}
	return Q;
}

Position addToList(int coefficient, int power) {			//funkcija za dodavanje elemenata iz dokumenta u listu
	Position Q = NULL;
	Q = memoryAlloc();
	Q->coefficient = coefficient;
	Q->power = power;
	Q->Next = NULL;
	return Q;
}

int readFile(Position FirstP, Position SecondP) {
	FILE* fp = NULL;
	char* buffer;
	int coefficient, power, byteSize, count, row = 0;    //byteSize predstavlja broj pročitanih elemenata iz elementa polinoma
	fp = fopen("polynomes.txt", "r");
	if (fp == NULL) {
		printf("Error reading file.\n");
		return ERROR_FILE;
	}

	buffer = (char*)malloc(sizeof(char) * MAX_LINE);
	if (buffer == NULL) {
		printf("Error allocating memory!\n");
		return ERROR_MEMORY_ALLOC;
	}

	while (!feof(fp)) {
		row++;
		fgets(buffer, MAX_LINE, fp);
		while (strlen(buffer) > 0) {			//petlja gleda u kojem smo retku
			count = sscanf(buffer, "%d %d %n", &coefficient, &power, &byteSize);  //broji se broj elemenata te se sprema u byteSize
			if (count != 2) {     //ako je broj elemenata jednog elementa polinoma različit od 2 tada element nije dobro očitan
				printf("Error reading polynome.\n");
				return ERROR_READING_POLYNOME;
			}
			if (row == 1) {
				sortedInput(FirstP, coefficient, power);
			}
			else {
				sortedInput(SecondP, coefficient, power);
			}

			buffer = buffer + byteSize;
		}
	}

	return EXIT_SUCCESS;
}

int sortedInput(Position Q, int coefficient, int power) {
	Position temp = addToList(coefficient, power);  

	while (Q->Next != NULL && Q->Next->power > temp->power) {   //gleda se je li iduća potencija veća od prethodne
		Q = Q->Next;  //ako je zamijenjuju se ta 2 elementa polinoma
	}

	if (Q->Next == NULL) {
		temp->Next = Q->Next;  
		Q->Next = temp;
	}

	else if (Q->Next != NULL && Q->Next->power < temp->power) {
		temp->Next = Q->Next;
		Q->Next = temp;
	}

	else if (Q->Next != NULL && Q->Next->power == temp->power) {    //elementi s istom potencijom se zbrajaju
		Q->Next->coefficient += temp->coefficient;
	}

	return EXIT_SUCCESS;
}

int Addition(Position FirstP, Position SecondP, Position AddResult) {
	while (FirstP != NULL && SecondP != NULL) {
		if (FirstP->power == SecondP->power) {
			sortedInput(AddResult, FirstP->coefficient + SecondP->coefficient, FirstP->power);
			FirstP = FirstP->Next;
			SecondP = SecondP->Next;
		}
		else if (FirstP->power > SecondP->power) {
			sortedInput(AddResult, FirstP->coefficient, FirstP->power);
			FirstP = FirstP->Next;
		}
		else if (FirstP->power < SecondP->power) {
			sortedInput(AddResult, SecondP->coefficient, SecondP->power);
			SecondP = SecondP->Next;
		}
		if (SecondP == NULL) {
			while (FirstP != NULL) {
				sortedInput(AddResult, FirstP->coefficient, FirstP->power);
				FirstP = FirstP->Next;
			}
		}
		else if (FirstP == NULL) {
			while (SecondP != NULL) {
				sortedInput(AddResult, SecondP->coefficient, SecondP->power);
				SecondP = SecondP->Next;
			}
		}
	}
	return EXIT_SUCCESS;
}

int Multiplication(Position FirstP, Position SecondP, Position MultiResult) {
	Position temp = SecondP;
	while (FirstP != NULL) {
		while (temp != NULL) {
			sortedInput(MultiResult, FirstP->coefficient * temp->coefficient, FirstP->power + temp->power);
			temp = temp->Next;
		}
		FirstP = FirstP->Next;
		temp = SecondP;
	}
	return EXIT_SUCCESS;
}

int printPoly(Position Q)
{
	while (Q != NULL) {
		printf("%dx^%d", Q->coefficient, Q->power);
		if (Q->Next != NULL) {
			printf("+");
		}
		Q = Q->Next;
	}
	printf("\n");
	return EXIT_SUCCESS;
}

int freePoly(Position Q) {
	Position temp = Q->Next;
	Position deleteEl = NULL;
	while (temp != NULL) {
		deleteEl = temp;
		temp = temp->Next;
		free(deleteEl);
	}
	Q->Next = NULL;

	return EXIT_SUCCESS;
}