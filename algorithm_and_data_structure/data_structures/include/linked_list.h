#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef void (*LinkedListCallback)(int data);

// Cada nó tem apenas 1 ponteiro (antecessor)
// Navegação é unidirecional (head → nó1 → nó2 → ... → NULL)
typedef struct Node
{
    int data;
    struct Node *antecessor;
} Node;

// Estrutura da lista com ponteiros head e tail para operacoes O(1)
// head e tail são ponteiros de controle, não fazem parte dos nós
typedef struct LinkedList
{
    Node *head; // ponteiro para o primeiro elemento
    Node *tail; // ponteiro para o ultimo elemento (otimiza append)
} LinkedList;

// Protótipos das operações básicas
void list_init(LinkedList *list);
Node *list_create_node(int valor);

void list_appini(LinkedList *list, int valor);
void list_append(LinkedList *list, int valor);
void list_pop(LinkedList *list, int chave);

void list_get(LinkedList *list, int chave);
void list_display(LinkedList *list);

// Protótipos das operações com callback
void list_apply(LinkedList *list, LinkedListCallback callback);
int list_find(LinkedList *list, int valor);
void list_destroy(LinkedList *list);

#endif