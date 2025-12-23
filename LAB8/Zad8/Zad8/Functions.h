#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef struct Tree* TPosition;

typedef struct Tree {
	int value;
	TPosition left;
	TPosition right;
}Tree;

TPosition memoryAlloc();

TPosition treeAlloc(int value);

TPosition elementInput(TPosition Q, int value);

TPosition eraseElement(TPosition Q, int value);

TPosition minReturn(TPosition Q, TPosition temp);

TPosition findElement(TPosition Q, int value);

int inOrder(TPosition Q);

int preOrder(TPosition Q);

int postOrder(TPosition Q);

int trLevelOrder(TPosition Q, int level);

int levelOrder(TPosition Q);

int measureTree(TPosition Q);

int freeElements(TPosition Q);

#endif 
