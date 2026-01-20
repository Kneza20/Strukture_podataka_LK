#define _CRT_SECURE_NO_WARNINGS
#define MAX_LINE 1024
#define ERROR_FILE -1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Functions.h"

TownTPosition memoryAllocTT() {
	TownTPosition Q = (TownTPosition)malloc(sizeof(TownTree));
	if (Q == NULL) {
		printf("Error allocating TownTree memory!\n");
		return NULL;
	}
	return Q;
}

StateLPosition memoryAllocSL() {
	StateLPosition Q = (StateLPosition)malloc(sizeof(StateList));
	if (Q == NULL) {
		printf("Error allocating TownTree memory!\n");
		return NULL;
	}
	return Q;
}

StateTPosition memoryAllocST() {
	StateTPosition Q = (StateTPosition)malloc(sizeof(StateTree));
	if (Q == NULL) {
		printf("Error allocating state tree!\n");
		return NULL;
	}

	return Q;
}

TownTPosition createTownT(char* name, int townPopulation) {
	TownTPosition town = memoryAllocTT();

	strcpy(town->townName, name);
	town->townPopulation = townPopulation;
	town->left = NULL;
	town->right = NULL;
	return town;
}

TownTPosition addTownT(char* name, int population, TownTPosition root) {
	if (!root) {
		return createTownT(name, population);
	}

	if (population <= root->townPopulation) {
		root->left = addTownT(name, population, root->left);
	}
	else {
		root->right = addTownT(name, population, root->right);
	}

	return root;
}

StateLPosition addStateL(char* name, StateLPosition Q, char* stateFile) {
	StateLPosition state = memoryAllocSL();

	strcpy(state->stateName, name);
	state->Town = readTowns(stateFile);
	state->Next = NULL;

	FILE* fp = NULL;
	fp = fopen("drzave.txt", "r");

	if (!Q || strcmp(name, Q->stateName) < 0) {			//provjerava je li lista prazna i nalazi li se ime nove države ispred postojeæe
		state->Next = Q;
		return state;
	}

	StateLPosition temp = Q;
	while (temp->Next && strcmp(name, temp->Next->stateName) > 0) {
		temp = temp->Next;
	}

	fclose(fp);

	state->Next = temp->Next;
	temp->Next = state;

	return Q;
}

TownTPosition readTowns(char* stateFile) {
	FILE* fp = NULL;
	fp = fopen(stateFile, "r");

	if (fp == NULL) {
		printf("Error while opening file!");
		return NULL;
	}

	TownTPosition root = NULL;
	char townName[MAX_LINE];
	int population;
	while (fscanf(fp, " %[^,],%d", townName, &population)==2) {
		root = addTownT(townName, population, root);
	}

	fclose(fp);
	return root;
}

int printLStates(StateLPosition Q) {
	while (Q) {
		printf("%s:\n", Q->stateName);
		printTTowns(Q->Town);
		Q = Q->Next;
	}

	return 0;
}

int printTTowns(TownTPosition root) {
	if (root == NULL) {
		return 0;
	}
	printTTowns(root->left);
	printf(" %s,%d\n", root->townName, root->townPopulation);
	printTTowns(root->right);

	return 0;
}

int printTStates(StateTPosition root) {
	if (root == NULL) {
		return 0;
	}
	printTStates(root->left);
	printf("%s\n", root->stateName);
	printTStates(root->right);

	return 0;
}

StateTPosition createStateT(char* stateName, char* stateFile) {
	StateTPosition Q = memoryAllocST();

	strcpy(Q->stateName, stateName);
	Q->Town = readTowns(stateFile);
	Q->left = NULL;
	Q->right = NULL;

	return Q;
}

StateTPosition addStateT(char* stateName, char* stateFile, StateTPosition root) {
	if (root == NULL) {
		return createStateT(stateName, stateFile);
	}

	if (strcmp(stateName, root->stateName) < 0) {
		root->left = addStateT(stateName, stateFile, root->left);
	}
	else {
		root->right = addStateT(stateName, stateFile, root->right);
	}

	return root;
}

StateLPosition findState(StateLPosition Q, char* stateName) {
	while (Q && strcmp(Q->stateName, stateName) != 0) {
		Q = Q->Next;
	}

	return Q;
}

int findTowns(TownTPosition root, int minPopulation) {
	if (root == NULL) {
		return 0;
	}

	findTowns(root->left, minPopulation);
	if (root->townPopulation > minPopulation) {
		printf(" %s / %d\n", root->townName, root->townPopulation);
	}
	findTowns(root->right, minPopulation);
}

//11. zadatak

int key(char* stateName) {
	int sum = 0;
	for (int i = 0; i < 5 && stateName[i] != '\0'; i++) {
		sum += (int)stateName[i];
	}

	return sum%MAX_TABLE;
}

int tableInitialization(StateLPosition hash[]) {
	for (int i = 0; i < MAX_TABLE; i++) {
		hash[i] = NULL;
	}

	return 0;
}

int readStatesH(StateLPosition hash[], char* stateFile) {
	FILE* fp = NULL;
	char stateName[MAX_LINE], file[MAX_LINE];
	fp = fopen(stateFile, "r");
	if (fp == NULL) {
		printf("Error opening state files!");
		return NULL;
	}

	while (fscanf(fp, "%s %s", stateName, file) == 2) {
		int index = key(stateName);
		hash[index] = addStateL(stateName, hash[index], file);
	}
	fclose(fp);

	return 0;
}

int printHash(StateLPosition hash[]) {
	for (int i = 0; i < MAX_TABLE; i++) {
		printf("%d\n", i);
		StateLPosition temp = hash[i];

		while (temp) {
			printf("%s\n", temp->stateName);
			printTTowns(temp->Town);
			temp = temp->Next;
		}
	}

	return 0;
}

StateLPosition findStateH(StateLPosition hash[], char* stateName) {
	int index = key(stateName);
	StateLPosition temp = hash[index];

	while (temp && strcmp(temp->stateName, stateName) != 0) {
		temp = temp->Next;
	}

	return temp;
}
