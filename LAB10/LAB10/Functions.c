#include "Define.h"
#include "Functions.h"

TownLPosition memoryAllocTT() {
	TownTPosition Q = (TownTPosition)malloc(sizeof(TownTree));
	if (Q == NULL) {
		printf("Error allocating TownTree memory!");
		return NULL;
	}
	return Q;
}

StateLPosition memoryAllocSL() {
	StateLPosition Q = (StateLPosition)malloc(sizeof(StateList));
	if (Q == NULL) {
		printf("Error allocating TownTree memory!");
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

	state->Next = temp->Next;
	temp->Next = state;

	return Q;
}

TownTPosition readTowns(char* stateFile) {
	FILE* fp = NULL;
	fp = fopen(stateFile, "r");

	if (fp == NULL) {
		printf("Error while opening file!");
		return ERROR_FILE;
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
		printf("%s\n", Q->stateName);
		printTTowns(Q->Town);
		Q = Q->Next;
	}

	return 0;
}

int printTTowns(TownTPosition root) {
	printTTowns(root->left);
	printf(" %[^,],%d", root->townName, root->townPopulation);
	printTTowns(root->right);
}

