#ifndef STACK_H
#define STACK_H

typedef void (*StackCallback)(int data);

typedef struct Node
{
    int data;
    struct Node *antecessor;
} Node;

typedef struct Stack
{
    Node *top;
} Stack;

// Protótipos
void stack_init(Stack *stack);
int stack_is_empty(Stack *stack);

void stack_push(Stack *stack, int value);
int stack_pop(Stack *stack);
int stack_top(Stack *stack);

void stack_display(Stack *stack);

void stack_apply(Stack *stack, StackCallback callback);
int stack_find(Stack *stack, int value);
void stack_destroy(Stack *stack);

#endif