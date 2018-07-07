// C program for linked list implementation of stack
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "Stack.h"
// A structure to represent a stack
Stack* newStack(int capacity){
	Stack* stack = (Stack*)malloc(sizeof(Stack));
	if(capacity > MAX){
		return NULL;
	}
	stack->top = -1;
	stack->capacity = capacity;
	return stack;
}
int isEmpty(int store[], Stack* stack)
{
    return stack->top == -1;
}
void push(int store[], Stack* stack, int data)
{
		++stack->top;
		store[stack->top] = data;
}
int pop(int store[], Stack* stack)
{
    if(isEmpty(store, stack)){
			return false;
		}
		else{
			return store[stack->top--];
		}
}
int peek(int store[], Stack * stack)
{
    if (isEmpty(store, stack)){
        return false;
		}
    return store[stack->top];
}
