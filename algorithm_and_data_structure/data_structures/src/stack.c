#include <stdio.h>
#include <stdlib.h>

#include "../include/stack.h"

// Inicializa uma pilha vazia
// Define top como NULL (pilha sem elementos)
void stack_init(Stack *stack)
{
    stack->top = NULL;
}

// Verifica se a pilha esta vazia
// Retorna 1 (true) se estiver vazia, 0 (false) caso contrario
int stack_is_empty(Stack *stack)
{
    return stack->top == NULL;
}

// Adiciona um elemento no topo da pilha (LIFO - Last In, First Out)
// Aloca memoria para um novo no e o insere no topo
void stack_push(Stack *stack, int value)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (!new_node)
        return;

    new_node->data = value;
    new_node->antecessor = stack->top; // novo no aponta para o topo anterior
    stack->top = new_node;             // atualiza o topo para o novo no
}

// Remove e retorna o elemento do topo da pilha
// Retorna -1 se a pilha estiver vazia
int stack_pop(Stack *stack)
{
    if (stack->top == NULL)
        return -1;

    Node *temp_node = stack->top;       // guarda o no do topo
    int popped_value = temp_node->data; // valor a ser removido
    stack->top = temp_node->antecessor; // atualiza topo para o proximo

    free(temp_node);     // libera memoria do no removido
    return popped_value; // retorna o valor removido
}

// Retorna o elemento do topo sem remover
// Retorna -1 se a pilha estiver vazia
int stack_top(Stack *stack)
{
    if (stack->top == NULL)
        return -1;

    return stack->top->data;
}

// Exibe todos os elementos da pilha do primeiro ao último
void stack_display(Stack *stack)
{
    if (stack->top == NULL)
    {
        printf("Pilha vazia.\n");
        return;
    }

    Node *temp_node = stack->top;
    printf("Pilha: ");

    while (temp_node) // enquanto temp_node não for nulo
    {
        printf("%d ", temp_node->data);
        temp_node = temp_node->antecessor;
    }
    printf("\n");
}

// Aplica uma funcao callback a cada elemento da pilha
// Util para processar, filtrar ou transformar os dados
// Nota: nao remove elementos da pilha
void stack_apply(Stack *stack, StackCallback callback)
{
    if (stack == NULL || callback == NULL)
    {
        printf("Erro: pilha ou callback nulo!\n");
        return;
    }

    if (stack->top == NULL)
    {
        printf("Pilha vazia. Nada a processar.\n");
        return;
    }

    Node *temp_node = stack->top;

    // itera por cada elemento (do topo para a base) e aplica o callback
    while (temp_node)
    {
        callback(temp_node->data);
        temp_node = temp_node->antecessor;
    }
}

// Procura um elemento na pilha
// Retorna 1 se encontrado, 0 se nao encontrado
// Nota: nao remove elemento, apenas verifica existencia
int stack_find(Stack *stack, int value)
{
    if (stack == NULL)
    {
        printf("Erro: pilha nula!\n");
        return 0;
    }

    if (stack->top == NULL)
    {
        printf("Pilha vazia. Elemento nao encontrado.\n");
        return 0;
    }

    Node *temp_node = stack->top;

    // procura por cada elemento ate encontrar ou chegar a base
    while (temp_node)
    {
        if (temp_node->data == value)
            return 1; // encontrado

        temp_node = temp_node->antecessor;
    }

    return 0; // nao encontrado
}

// Libera toda a memoria alocada pela pilha
// Remove todos os elementos e os desaloca
// Deve ser chamada ao final do programa
void stack_destroy(Stack *stack)
{
    if (stack == NULL)
        return;

    Node *temp_node;

    // remove e libera cada no da pilha
    while (stack->top != NULL)
    {
        temp_node = stack->top;
        stack->top = stack->top->antecessor;
        free(temp_node);
    }
}