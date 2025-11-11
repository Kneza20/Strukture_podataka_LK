/*5. Napisati program koji iz datoteke čita postfiks izraz i zatim 
korištenjem stoga računa rezultat. 
Stog je potrebno realizirati preko vezane liste.*/
#define _CRT_SECURE_NO_WARNINGS
#define MAX_LINE 1024
#define ERROR_ALLOCATING_MEMORY (-1)

#include <stdio.h>
#include <stdlib.h>

typedef struct postfix* Position;

typedef struct postfix {
	double number;
	Position Next;
}post;

int Push(Position P, double num);

int Pop(Position first, Position second);

int isFull(Position P);

int main() {
	Position head=NULL;
	head = memoryAlloc();

	return 0;
}

Position memoryAlloc() {
	Position P = malloc(sizeof(Position));
	if (P == NULL) {
		pritntf("Error allocating memory!\n");
		return ERROR_ALLOCATING_MEMORY;
	}
}

int Push(Position P, double num) {
	Position Q = P;                 //spremanje adrese heada u pomocnu varijablu q
	Position newEl = NULL;          
	newEl = memoryAlloc();
	newEl->number = num;
	newEl->Next = NULL;

	newEl->Next = Q->Next;
	Q->Next = newEl;
}

int Pop(Position first, Position second) {
	Position Q = memoryAlloc();
	first = Q->Next;
	second = first->Next;
}


//učitati datoteku
//pohranit podatke
//zatvoriti datoteku

//broj -> push
//operator -> pop
//trash

//POP
//q->Next = second->Next
//first->Next = NULL, second->Next = NULL
//free(first)
//free(second)
//Push(&head, rezultat)