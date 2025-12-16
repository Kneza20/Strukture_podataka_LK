#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef struct Directory* DPosition;

typedef struct Directory {
    char directoryName[MAX_LINE];
    DPosition child;
    DPosition sibling;
    DPosition parent;
} Dir;

DPosition memoryAlloc();

DPosition createDir(char* directoryName, DPosition parent);

int mkdir(DPosition current);

DPosition cdDir(DPosition current);

DPosition cdBack(DPosition current);

int ls(DPosition current);

#endif