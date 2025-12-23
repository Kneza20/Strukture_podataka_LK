#ifndef HEADER_H
#define HEADER_H

typedef struct Tree* TPosition;

typedef struct Tree {
	int value;
	TPosition left;
	TPosition right;
}Tree;

TPosition memoryAlloc();

TPosition treeAlloc(TPosition Q);

TPosition insertElement(TPosition Q, int value);

int replace(TPosition Q);

int printInOrder(TPosition Q, FILE* fp);

int freeTree(TPosition Q);

#endif 