#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H

typedef void (*DoubleLinkedListCallback)(int data);

typedef struct Node{
    int data;
    struct Node* predecessor;
    struct Node* sucessor;
} Node;

// Estrutura da lista duplamente ligada com ponteiros head e tail para operacoes O(1)
typedef struct DoubleLinkedList
{
    Node *head; // ponteiro para o primeiro elemento
    Node *tail; // ponteiro para o ultimo elemento (otimiza append e insert_end)
} DoubleLinkedList;

// Protótipos das operações básicas
void dlist_init(DoubleLinkedList *list);
Node *dlist_create_node(int valor);

void dlist_appini(DoubleLinkedList *list, int valor);
void dlist_append(DoubleLinkedList *list, int valor);
void dlist_pop(DoubleLinkedList *list, int chave);

void dlist_get(DoubleLinkedList *list, int chave);
void dlist_display(DoubleLinkedList *list);

// Protótipos das operações com callback
void dlist_apply(DoubleLinkedList *list, DoubleLinkedListCallback callback);
int dlist_find(DoubleLinkedList *list, int valor);
void dlist_destroy(DoubleLinkedList *list);

#endif