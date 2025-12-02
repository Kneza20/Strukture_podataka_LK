/*5. Napisati program koji iz datoteke cita postfiks izraz i zatim koristenjem stoga racuna rezultat.
Stog je potrebno realizirati preko vezane liste.*/
#define _CRT_SECURE_NO_WARNINGS
#define MAX_LINE 1024
#define ERROR_ALLOCATION (-1)
#define ERROR_EMPTY_STACK (-2)
#define ERROR_DIVIDING (-3)
#define ERROR_OPERAND (-4)
#define ERROR_FILE_OPENING (-5)

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct postfix* Position;

typedef struct postfix {
	double number;
	Position Next;
}post;

Position memoryAlloc();

Position push(Position P, double num);

Position pop(Position P, double* result);

double calculate(Position P);

int main() {
	Position P = NULL;
	P = memoryAlloc();
	printf("Result of postfix equation is: %.2lf\n", calculate(P));

	free(P);
	return EXIT_SUCCESS;
}

Position memoryAlloc() {
	Position Q = NULL;
	Q = (Position)malloc(sizeof(post));
	if (Q == NULL) {
		printf("Error allocating memory");
		return ERROR_ALLOCATION;
	}
	return Q;
}

Position push(Position P, double num) {
	Position newElement = NULL;
	newElement = memoryAlloc();

	newElement->number = num;       //spremanje novog elementa na stog
	newElement->Next = P;			//pomicanje na sljedeci element koji se dodaje na stog

	return newElement;
}

Position pop(Position P, double* result) {
	if (P == NULL) {
		printf("Stack is empty!");
		return ERROR_EMPTY_STACK;
	}

	*result = P->number;			//spremanje trenutnog vrha stoga na rezultat
	Position temp = P;				
	P = P->Next;					//prebacivanje na sljedeci element stoga
	temp->Next = NULL;				//potrebno je iduci element postaviti na NULL kako ne bi ostao visiti u memoriji
	free(temp);						//oslobadjanje prethodnog elementa sa vrha stoga
	return P;
}

double calculate(Position P) {
	int i = 0;
	FILE* fp = NULL;
	fp = fopen("dat.txt", "r");

	if (fp == NULL) {
		printf("Error opening file!\n");
		return ERROR_FILE_OPENING;
	}

	char buffer[MAX_LINE];

	while (fscanf(fp,"%s",buffer)==1) {
		if (isdigit(buffer[0]) || (buffer[0] == '-' && isdigit(buffer[0]))) {    //uvjet za provjeravanje da li je element broj i to da li je poz ili neg
			double number = atof(buffer);   //atof funkcija uzima brojcanu vrijednost iz stringa
			P = push(P, number);			//dodavanje broja na stog
		}
		else {
			double result = 0, first = 0, second = 0;
			P = pop(P, &first);				//izbacivanje prvog zadnjeg dodanog elementa
			P = pop(P, &second);			//izbacivanje elementa koji se nalazi prije first elementa

			switch (buffer[0]) {
			case '+': result = second + first; break;
			case '-': result = second - first; break;
			case '*': result = second * first; break;
			case '/':
				if (first = 0) {
					printf("Can not divide by zero!\n");
					return ERROR_DIVIDING;
				}
				else {
					result = second / first;
					break;
				}

			default:
				printf("Unknown operand!\n");
				return ERROR_OPERAND;
			}
			P = push(P, result);
		}
	}
	fclose(fp);

	double finalResult = 0;

	P = pop(P, &finalResult);  //funkcija u finalResult sprema finalni rezultat računanja izraza na stogu

	return finalResult;
}
