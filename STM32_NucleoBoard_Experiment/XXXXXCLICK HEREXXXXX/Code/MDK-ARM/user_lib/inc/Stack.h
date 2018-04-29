#ifndef __STACK_H
#define __STACK_H
#include <stdio.h>
#include <stdlib.h>

#define MAX 20000
typedef enum {false, true} bool;

typedef struct Stack{
	int capacity;
	int top;
}Stack;
Stack * newStack(int capacity);
int isEmpty(int store[], Stack* stack);
void push(int store[], Stack* stack, int data);
int pop(int store[], Stack* stack);
int peek(int store[], Stack* stack);

#endif
