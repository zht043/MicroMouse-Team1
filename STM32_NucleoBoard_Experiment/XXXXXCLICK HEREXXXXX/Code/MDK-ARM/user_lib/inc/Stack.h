#ifndef __STACK_H
#define __STACK_H
#include <stdio.h>
#include <stdlib.h>
typedef enum {false, true} bool;
typedef struct Stack{
	struct StackNode* root;
}Stack;
typedef struct StackNode
{
    int data;
    struct StackNode* next;
}StackNode;
Stack * newStack(void);
StackNode * newNode(int data);
int isEmpty(Stack* stack);
void push(Stack* stack, int data);
int pop(Stack* stack);
int peek(Stack* stack);

#endif
