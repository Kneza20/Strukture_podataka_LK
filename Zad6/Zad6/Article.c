#define _CRT_SECURE_NO_WARNINGS
#define MAX_LINE 1024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Article.h"

APosition createArticle(char name[], int quantity, float price);

int sortArticles(APosition Q);

int freeArticles(APosition Q);

APosition createArticle(char name[], int quantity, float price) {
	APosition Q = NULL;
	Q = (APosition)malloc(sizeof(Article));

	strcpy(Q->name, name);
	Q->quantity = quantity;
	Q->price = price;
	Q->Next = NULL;
	return Q;
}

int sortArticles(APosition Q) {
	APosition temp = createArticle(Q->name, Q->quantity, Q->price);

	while (Q->Next != NULL && Q->Next->name > Q->name) {
		Q = Q->Next;
	}

	if (Q->Next != NULL && Q->Next->name < temp->name) {
		temp->Next = Q->Next;
		Q->Next = temp;
	}

	return EXIT_SUCCESS;
}

int freeArticles(APosition Q) {
	APosition temp = Q;
	while (Q != NULL) {
		temp = Q;
		Q = Q->Next;
		free(temp);
	}
	return EXIT_SUCCESS;
}