#include <stdio.h>

typedef struct node {
	char digit;
	struct node *next;
	struct node *prev;
} node;

typedef struct Integer {
	node *head;
	node *tail;
} Integer;

/*
 * 
 *initInteger should be called before calling other functions for any integer type
 *
 *
 */

void initInteger(Integer *a);
void addDigit(Integer *a, char c);
Integer createIntegerFromString(char *str);
Integer addIntegers(Integer a, Integer b);
Integer substractIntegers(Integer a, Integer b);
void printInteger(Integer a);
void destroyInteger(Integer *a);
