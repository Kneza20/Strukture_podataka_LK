/*Napisati program koji omogucava rad s binarnim stablom pretrazivanja. 
Treba omoguciti unošenje novog elementa u stablo, ispis elemenata 
(inorder, preorder, postorder i level order), brisanje i pronalazenje nekog elementa.*/
#define _CRT_SECURE_NO_WARNINGS
#define MAX_LINE 1024
#define ERROR_SEARCH (-1)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Functions.h"

int main() {
	TPosition root = NULL;
	int value=0;
	printf("Start your tree with one value: ");
	(void)scanf("%d", &value);

	root = treeAlloc(value);

	int operation;
	printf("Choose an option: 1. Insert element, 2. Search element, 3. Erase element, 0. Program exit\nChoose an option: ");
	(void)scanf("%d", &operation);
	do {
		switch (operation) {
			case 1:
				printf("Insert new element: ");
				(void)scanf("%d", &value);
				root = elementInput(root, value);
				printf("Output preorder: ");
				preOrder(root);
				printf("\n");
				printf("Output inorder: ");
				inOrder(root);
				printf("\n");
				printf("Output postorder: ");
				postOrder(root);
				printf("\n");
				printf("Output levelorder: ");
				levelOrder(root);
				printf("\n");
				return 0;

			case 2:
				printf("Search element: ");
				(void)scanf("%d", &value);
				if (findElement(root, value) == NULL) {
					printf("Element can't be found!\n");
					return ERROR_SEARCH;
				}
				printf("Element found!\n");
				break;

			case 3:
				printf("Erase element: ");
				(void)scanf("%d", &value);
				eraseElement(root, value);
				printf("Output preorder: ");
				preOrder(root);
				printf("\n");
				printf("Output inorder: ");
				inOrder(root);
				printf("\n");
				printf("Output postorder: ");
				postOrder(root);
				printf("\n");
				printf("Output levelorder: ");
				levelOrder(root);
				printf("\n");
				break;

			case 0:
				return 0;
		}
	}while (operation != 0);

	freeElements(root);

	return 0;
}