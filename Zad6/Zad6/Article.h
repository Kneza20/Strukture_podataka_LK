#ifndef ARTICLE_H
#define ARTICLE_H

typedef struct Article* APosition;

typedef struct Article {
    char name[256];
    int quantity;
    float price;
    APosition Next;
} Article;

#endif