// C program for linked list implementation of stack
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "Stack.h"
// A structure to represent a stack
Stack* newStack(){
	Stack* stack = (Stack*) malloc(sizeof(Stack));;
	stack->root = NULL;
	return stack;
}
StackNode* newNode(int data)
{
    StackNode* stackNode =
              (StackNode*) malloc(sizeof(StackNode));
    stackNode->data = data;
    stackNode->next = NULL;
    return stackNode;
}
int isEmpty(Stack* stack)
{
    return !stack->root;
}
void push(Stack* stack, int data)
{
    StackNode* stackNode = newNode(data);
    stackNode->next = stack->root;
    stack->root = stackNode;
}
int pop(Stack* stack)
{
    if (isEmpty(stack))
        return false;
    StackNode* temp = stack->root;
    stack->root = stack->root->next;
    int popped = temp->data;
    free(temp);
 
    return popped;
}
int peek(Stack * stack)
{
    if (isEmpty(stack))
        return false;
    return stack->root->data;
}
