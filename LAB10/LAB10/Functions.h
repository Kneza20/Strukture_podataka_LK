#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#define MAX_LINE 1024

typedef struct StateList* StateLPosition;
typedef struct TownTree* TownTPosition;
typedef struct TownList* TownLPosition;

typedef struct StateList {
	char stateName[MAX_LINE];
	TownTPosition Town;
	StateLPosition Next;
}StateList;

typedef struct StateTree* StateTPosition;

typedef struct StateTree {
	char stateName[MAX_LINE];
	TownTPosition Town;
	StateTPosition left;
	StateTPosition right;
}StateTree;

typedef struct TownTree {
	char townName[MAX_LINE];
	int townPopulation;
	TownTPosition left;
	TownTPosition right;
}TownTree;

typedef struct TownList {
	char townName[MAX_LINE];
	int townPopulation;
	TownLPosition Next;
}TownList;

TownTPosition memoryAllocTT();

StateTPosition memoryAllocST();

StateLPosition memoryAllocSL();

TownTPosition createTownT(char* name, int townPopulation);

TownTPosition addTownT(char* name, int population, TownTPosition root);

StateLPosition addStateL(char* name, StateLPosition Q, char* stateFile);

StateTPosition addStateT(char* stateName, char* stateFile, StateTPosition root);

StateTPosition createStateT(char* stateName, char* stateFile);

TownTPosition readTowns(char* stateFile);

int printLStates(StateLPosition Q);

int printTTowns(TownTPosition root);

int printTStates(StateTPosition root);

StateLPosition findState(StateLPosition Q, char* stateName);

int findTowns(TownTPosition root, int minPopulation);

#endif