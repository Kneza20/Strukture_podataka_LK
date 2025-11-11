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
#include <string.h>

typedef struct postfix* Position;

typedef struct postfix {
	int number;
	Position Next;
}post;

Position memoryAlloc();

int push(Position P, int num);

int pop(Position P, int num);

int calculate(int first, int second, char operand);

int main() {

	return EXIT_SUCCESS;
}

Position memoryAlloc() {
	Position Q = NULL;
	Q = (Position)malloc(sizeof(post));
	if (Q == NULL) {
		printf("Error allocating memory");
		return ERROR_ALLOCATION;
	}
}

int push(Position P, int num) {
	Position newElement = NULL;
	newElement = memoryAlloc();

	newElement->number = num;       //spremanje novog elementa na stog
	newElement->Next = P;

	return newElement;
}

int pop(Position P, int num) {
	if (P == NULL) {
		printf("Stack is empty!");
		return ERROR_EMPTY_STACK;
	}

	Position temp = P; //trenutni vrh stoga spremamo u varijablu temp
	P = P->Next;       //pomicanje na sljedeći element stoga
	free(temp);		   //brisanje prethodnog vrha stoga
	return P;
}

int calculate(int first, int second, char operand) {
	switch (operand) {
	case '+': return first + second;
	case '-': return first - second;
	case '*': return first * second;
	case '/':
		if (second = 0) {
			printf("Can not divide by zero!\n");
			return ERROR_DIVIDING;
		}
		else {
			return first / second;
		}

	default:
		printf("Unknown operand!\n");
		return ERROR_OPERAND;
	}


}