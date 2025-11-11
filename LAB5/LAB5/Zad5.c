/*5. Napisati program koji iz datoteke cita postfiks izraz i zatim koristenjem stoga racuna rezultat.
Stog je potrebno realizirati preko vezane liste.*/
#define _CRT_SECURE_NO_WARNINGS
#define MAX_LINE 1024
#define ERROR_ALLOCATION (-1)
#define ERROR_EMPTY_STACK (-2)
#define ERROR_DIVIDING (-3)
#define ERROR_OPERAND (-4)

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct postfix* Position;

typedef struct postfix {
	int number;
	Position Next;
}post;

Position memoryAlloc();

Position push(Position P, int num);

int pop(Position P);

int calculate(Position P);

int main() {
	Position P = NULL;
	P = memoryAlloc();
	int result = 0;
	result = calculate(P);
	printf("Result of postfix equation is: %d", result);

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

Position push(Position P, int num) {
	Position newElement = NULL;
	newElement = memoryAlloc();

	newElement->number = num;       //spremanje novog elementa na stog
	newElement->Next = P;

	return newElement;
}

int pop(Position P) {
	if (P == NULL) {
		printf("Stack is empty!");
		return ERROR_EMPTY_STACK;
	}

	int num = (P)->number;
	Position temp = P;
	P = P->Next;
	free(temp);
	return num;
}

int calculate(Position P) {
	int i = 0;
	FILE* fp = NULL;
	fp = fopen("dat.txt", "r");

	char buffer[MAX_LINE];

	while (fscanf(fp,"%s",buffer)==1) {
		if (isdigit(buffer[0]) || (buffer[0] == '-' && isdigit(buffer[0]))) {    //uvjet za provjeravanje da li je element broj i to da li je poz ili neg
			int number;
			number = buffer[i];
			P = push(P, number);
		}
		else {
			int result = 0;
			int first = pop(P);
			int second = pop(P);

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
		i++;
	}
	fclose(fp);

	int finalResult = pop(P);

	return finalResult;
}