#include <stdio.h>
#include <stdlib.h>
#include "integer.h"

void initInteger(Integer *a) {
	a->head = a->tail = NULL;
}

void addDigit(Integer *a, char c) {
	if(c < '0' || c > '9')
		return;
	else if(a->head == NULL) {
		node *temp;
		temp = (node *)malloc(sizeof(node));
		if(c != '0')
			temp->digit = c;
		else 
			return;	
		temp->next = NULL;
		temp->prev = NULL;
		a->head = temp;
		a->tail = temp;
	}
	else {
		node *temp;
		temp = (node *)malloc(sizeof(node));
		temp->digit = c;
		temp->next = NULL;
		temp->prev = a->tail;
		a->tail->next = temp;
		a->tail = temp;
	}
}

Integer createIntegerFromString(char *str) {
	int i;
	Integer myinteger;
	initInteger(&myinteger);
	for(i = 0; str[i] == '0'; i++);
	for( ; str[i] >= '0' && str[i] <= '9'; i++)
		addDigit(&myinteger, str[i]);
	return myinteger;
}

Integer addIntegers(Integer a, Integer b) {
	Integer c;
	Integer *pa = &a, *pb = &b, *pc = &c;
	if(pa->head == NULL)
		return b;
	else if(pb->head == NULL)
		return a;
	else {		
		int i1, i2, carry, flag;
		initInteger(pc);
		node *int1, *int2, *int3;
		int1 = pa->tail;
		int2 = pb->tail;
		char storeInteger[2];
		carry = 0;
		while(int1 != NULL || int2 != NULL) {
			flag = 0;
			if(int1 == NULL)
				i1 = 0;
			else {
				storeInteger[0] = int1->digit;
				storeInteger[1] = '\0';	
				i1 = atoi(storeInteger);
				//printf("first in a : %d\n", i1);
			}	
			if(int2 == NULL)
				i2 = 0;
			else {	
				storeInteger[0] = int2->digit;
				storeInteger[1] = '\0';	
				i2 = atoi(storeInteger);
				//printf("first in b : %d\n", i2);
			}	
			i1 = i1 + i2 + carry;
			if(i1/10 != 0) {
				flag = 1;
				i1 -= 10;
			}
			sprintf(storeInteger, "%d", i1);
			//printf("%s\n", storeInteger);	
			if(pc->head == NULL) {
				pc->head = (node *)malloc(sizeof(node));
				pc->tail = pc->head;
				pc->head->next = pc->head->prev = NULL;
				pc->head->digit = storeInteger[0];
				int3 = pc->head;
			}	
			else {
				int3->prev = (node *)malloc(sizeof(node));
				int3->prev->next = int3;
				int3 = int3->prev;
				int3->digit = storeInteger[0];
				int3->prev = NULL;
				pc->head = int3;
			}
			if(int1 != NULL)
				int1 = int1->prev;	
			if(int2 != NULL)
				int2 = int2->prev;
			if(flag == 1)
				carry = 1;
			else 
				carry = 0;		
		}
		if(carry == 1) {
			pc->head->prev = (node *)malloc(sizeof(node));
			pc->head->prev->prev = NULL;
			pc->head->prev->next = pc->head;
			pc->head = pc->head->prev;
			pc->head->digit = '1';
		}
	}	
	return c;
}			

Integer substractIntegers(Integer a, Integer b) {
	Integer c, zerointeger;
	initInteger(&zerointeger);
	Integer *pa = &a, *pb = &b, *pc = &c;
	initInteger(pc);
	if(pa->head == NULL || pb->head == NULL)
		return a;
	else {
		int i1, i2, borrow, flag;
		initInteger(pc);
		node *int1, *int2, *int3;
		int1 = pa->tail;
		int2 = pb->tail;
		char storeInteger[2];
		borrow = 0;
		while(int1 != NULL || int2 != NULL) {
			flag = 0;
			if(int1 == NULL)
				i1 = 0;
			else {
				storeInteger[0] = int1->digit;
				storeInteger[1] = '\0';	
				i1 = atoi(storeInteger);
				//printf("first in a : %d\n", i1);
			}	
			if(int2 == NULL)
				i2 = 0;
			else {	
				storeInteger[0] = int2->digit;
				storeInteger[1] = '\0';	
				i2 = atoi(storeInteger);
				//printf("first in b : %d\n", i2);
			}	
			if(i1 >= (i2 + borrow))
				i1 = i1 - i2 - borrow;
			else {
				i1 = i1 - i2 - borrow + 10;
				flag = 1;
			}
			sprintf(storeInteger, "%d", i1);
			//printf("%s\n", storeInteger);	
			if(pc->head == NULL) {
				pc->head = (node *)malloc(sizeof(node));
				pc->tail = pc->head;
				pc->head->next = pc->head->prev = NULL;
				pc->head->digit = storeInteger[0];
				int3 = pc->head;
			}	
			else {
				int3->prev = (node *)malloc(sizeof(node));
				int3->prev->next = int3;
				int3 = int3->prev;
				int3->digit = storeInteger[0];
				int3->prev = NULL;
				pc->head = int3;
			}
			if(int1 != NULL)
				int1 = int1->prev;	
			if(int2 != NULL)
				int2 = int2->prev;
			if(flag == 1)
				borrow = 1;
			else 
				borrow = 0;		
		}
		int1 = pc->head;
		while(int1->digit == '0') {
			int2 = int1;
			int1 = int1->next;
			int1->prev = NULL;
			pc->head = int1;
			free(int2);
		}
		if(borrow == 1) {
			destroyInteger(pc);
			return zerointeger;
		}
	}		
	return c;
}

void printInteger(Integer a) {
	if(a.head == NULL)
		putchar('0');
	else {	
		node *current_node;
		Integer *pa = &a;
		current_node = pa->head;
		while(current_node != NULL) {
			putchar(current_node->digit);
			current_node = current_node->next;
		}
	}	
}		

void destroyInteger(Integer *a) {
	node *temp;
	while(a->tail != NULL) {
		temp = a->tail;
		a->tail = a->tail->prev;
		free(temp);		
	}
	a->head = NULL;
}

