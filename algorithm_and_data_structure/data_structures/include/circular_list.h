#ifndef CIRCULARLIST_H
#define CIRCULARLIST_H

typedef void (*CircularListCallback)(int data);

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

// Estrutura da lista circular com ponteiros head e tail para operacoes O(1)
typedef struct CircularList
{
    Node *head; // ponteiro para o primeiro elemento
    Node *tail; // ponteiro para o ultimo elemento (otimiza append e mantem circularidade)
} CircularList;

// Protótipos das operações básicas
void clist_init(CircularList *list);
Node *clist_create_node(int valor);

void clist_appini(CircularList *list, int valor);
void clist_append(CircularList *list, int valor);
void clist_remove(CircularList *list, int chave);

void clist_get(CircularList *list, int chave);
void clist_display(CircularList *list);

// Protótipos das operações com callback
void clist_apply(CircularList *list, CircularListCallback callback);
int clist_find(CircularList *list, int valor);
void clist_destroy(CircularList *list);

#endif