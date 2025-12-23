#define _CRT_SECURE_NO_WARNINGS
#define MAX_LINE 1024
#define ERROR_ERASE (-1)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Functions.h"

TPosition memoryAlloc() {
	TPosition Q = (TPosition)malloc(sizeof(Tree));
	if (Q == NULL) {
		printf("Error allocating memory!");
		return NULL;
	}
	return Q;
}

TPosition treeAlloc(int value) {    //alociranje stabla te postavljanje root elementa na integer vrijednost value
	TPosition Q = NULL;
	Q = memoryAlloc();
	if (Q == NULL) {
		printf("Tree not allocated!\n");
		return NULL;
	}

	Q->value = value;
	Q->left = NULL;
	Q->right =NULL;

	return Q;
}

TPosition elementInput(TPosition Q, int value) {
	if (Q == NULL) {
		return treeAlloc(value);
	}
	if (value > Q->value) {
		Q->right = elementInput(Q->right, value);
	}
	else if (value < Q->value) {
		Q->left = elementInput(Q->left, value);
	}
	
	return Q;
}

TPosition eraseElement(TPosition Q, int value) {  
	TPosition temp = NULL;
	if (Q == NULL) {
		return Q;
	}

	
	if (value > Q->value) {
		Q->right = eraseElement(Q->right, value);
	}
	else if (value < Q->value){
		Q->left = eraseElement(Q->left, value);
	}
	else {
		if (Q->right == NULL) {
			temp = Q->left;
			free(Q);
			return temp;
		} else if (Q->left == NULL) {
			temp = Q->right;
			free(Q);
			return temp;
		}

		Q = minReturn(Q, temp);
	}
		
	return Q;
}

TPosition minReturn(TPosition Q, TPosition temp) {
	temp = Q->right;
	while (temp->left != NULL) {
		temp = temp->left;
	}
	Q->value = temp->value;
	Q->right = eraseElement(Q->right, temp->value);

	return Q;
}

TPosition findElement(TPosition Q, int value) {
	if (Q == NULL || Q->value == value) {		//ako je element null ili je njegova vrijednost jednaka trazenoj vraca se ta vrijednost
		return Q;	
	}
	else if (value < Q->value) {				//za elemente vece ili manje od trazene prosljedjujemo vrijednost koja odgovara odreðenom podstablu tog èvora rekurzivno nazad u fju
		return findElement(Q->left, value); 
	}
	else {
		return findElement(Q->right, value);
	}
}

int inOrder(TPosition Q) {
	if (Q != NULL) {
		inOrder(Q->left);
		printf("%d", Q->value);
		inOrder(Q->right);
	}

	return EXIT_SUCCESS;
}

int preOrder(TPosition Q) {
	if (Q != NULL) {
		printf("%d", Q->value);
		preOrder(Q->left);
		preOrder(Q->right);
	}

	return EXIT_SUCCESS;
}

int postOrder(TPosition Q) {
	if (Q != NULL) {
		postOrder(Q->left);
		postOrder(Q->right);
		printf("%d", Q->value);
	}

	return EXIT_SUCCESS;
}

int trLevelOrder(TPosition Q, int level) {
	if (Q == NULL) {	//nema stabla nema ispisa
		return;
	}

	if (level == 1) {
		printf("%d ", Q->value);
	}

	else if (level > 1) {
		trLevelOrder(Q->left, level - 1);
		trLevelOrder(Q->right, level - 1);
	}

	return EXIT_SUCCESS;
}

int measureTree(TPosition Q) {
	if (Q == NULL) return 0;
	int left = measureTree(Q->left);
	int right = measureTree(Q->right);
	if (left > right) {
		return left+1;
	}
	else {
		return right+1;
	}
}

int levelOrder(TPosition Q) {
	int h = measureTree(Q);
	for (int i = 1; i <= h; i++) {
		trLevelOrder(Q, i);
	}
}

int freeElements(TPosition Q) {
	if (Q != NULL) {
		freeElements(Q->left);
		freeElements(Q->right);
		free(Q);
	}

	return EXIT_SUCCESS;
}


//fja measureTree mjeri velicinu stabla
//fja level postavlja ispis na svaki level stabla zasebno
//fja levelOrder ispisuje vrijednost na svakom levelu zasebno te ako nismo na odredjenom levelu
//s else if petljom se pomice na iduci level stabla