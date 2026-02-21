#include <stdio.h>
#include <stdlib.h>

#include "../include/dlinked_list.h"

// Inicializa uma lista duplamente ligada vazia
// Define head e tail como NULL (lista sem elementos)
void dlist_init(DoubleLinkedList *list)
{
    list->head = NULL;
    list->tail = NULL;
}

// Cria um novo nó para lista duplamente ligada
// Aloca memória e inicializa campos sucessor e predecessor
// Retorna ponteiro para o novo nó ou NULL se falhar na alocação
Node *dlist_create_node(int valor)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (!new_node)
        return NULL;

    new_node->data = valor;
    new_node->sucessor = NULL;
    new_node->predecessor = NULL;

    return new_node;
}

// Insere um elemento no inicio (head) da lista duplamente ligada
// Atualiza apontadores sucessor e predecessor adequadamente
// Complexidade: O(1) - operação em tempo constante
void dlist_appini(DoubleLinkedList *list, int valor)
{
    Node *new_node = dlist_create_node(valor);
    if (!new_node)
        return;

    if (list->head == NULL) // lista vazia
    {
        list->head = new_node;
        list->tail = new_node;
    }
    else
    {
        new_node->sucessor = list->head;    // novo nó aponta para o antigo head (próximo)
        list->head->predecessor = new_node; // antigo head aponta de volta para novo nó (anterior)
        list->head = new_node;              // head agora é o novo nó
    }
}

// Insere um elemento no final da lista duplamente ligada
// Usa o ponteiro tail para acesso direto ao ultimo nó
// Complexidade: O(1) - operação em tempo constante (OTIMIZADO!)
void dlist_append(DoubleLinkedList *list, int valor)
{
    Node *new_node = dlist_create_node(valor);
    if (!new_node)
        return;

    if (list->head == NULL) // lista vazia
    {
        list->head = new_node;
        list->tail = new_node;
    }
    else
    {
        list->tail->sucessor = new_node;    // tail aponta para o novo nó (próximo)
        new_node->predecessor = list->tail; // novo nó aponta de volta para tail (anterior)
        list->tail = new_node;              // atualiza tail para o novo nó
    }
}

// Remove um nó especifico da lista usando uma chave
// Atualiza os apontadores sucessor e predecessor para manter conectividade
// Atualiza head/tail se necessário. Caso não encontre a chave, lista permanece inalterada
void dlist_pop(DoubleLinkedList *list, int chave)
{
    if (list->head == NULL)
        return;

    Node *atual = list->head;

    // Busca o nó com a chave
    while (atual && atual->data != chave)
    {
        atual = atual->sucessor;
    }

    if (!atual) // não encontrou
        return;

    // Atualiza predecessor (se existir)
    if (atual->predecessor)
    {
        atual->predecessor->sucessor = atual->sucessor;
    }
    else // É o head
    {
        list->head = atual->sucessor;
    }

    // Atualiza sucessor (se existir)
    if (atual->sucessor)
    {
        atual->sucessor->predecessor = atual->predecessor;
    }
    else // É o tail
    {
        list->tail = atual->predecessor;
    }

    free(atual);
}

// Procura um elemento na lista duplamente ligada usando uma chave
// Retorna mensagem indicando se o elemento foi encontrado ou nao
// Nota: função de busca simples com comparação de valor inteiro
void dlist_get(DoubleLinkedList *list, int chave)
{
    if (list->head == NULL)
    {
        printf("Lista vazia.\n");
        return;
    }

    Node *temp_node = list->head;
    while (temp_node && temp_node->data != chave)
    {
        temp_node = temp_node->sucessor;
    }

    if (!temp_node)
    {
        printf("Valor %d nao esta presente na lista.\n", chave);
    }
    else
    {
        printf("Valor %d esta presente na lista.\n", chave);
    }
}

// Exibe todos os elementos da lista duplamente ligada
// Itera do inicio (head) ate o final (tail)
// Formato: Lista: elemento1 elemento2 elemento3 ...
void dlist_display(DoubleLinkedList *list)
{
    if (list->head == NULL)
    {
        printf("Lista vazia.\n");
        return;
    }

    Node *atual = list->head;
    printf("Lista dupla: ");
    while (atual)
    {
        printf("%d ", atual->data);
        atual = atual->sucessor;
    }
    printf("\n");
}

// Aplica uma funcao callback a cada elemento da lista
// Util para processar, filtrar ou transformar os dados
// Nota: nao remove elementos da lista
void dlist_apply(DoubleLinkedList *list, DoubleLinkedListCallback callback)
{
    if (list == NULL || list->head == NULL || callback == NULL)
    {
        printf("Erro: lista ou callback nula!\n");
        return;
    }

    Node *temp_node = list->head;

    // itera por cada elemento e aplica o callback
    while (temp_node)
    {
        callback(temp_node->data);
        temp_node = temp_node->sucessor;
    }
}

// Procura um elemento na lista retornando um valor booleano
// Retorna 1 se encontrado, 0 se nao encontrado
// Nota: diferente de dlist_get, nao exibe mensagem
int dlist_find(DoubleLinkedList *list, int valor)
{
    if (list == NULL || list->head == NULL)
        return 0;

    Node *temp_node = list->head;

    // procura por cada elemento ate encontrar ou chegar ao final
    while (temp_node)
    {
        if (temp_node->data == valor)
            return 1; // encontrado
        temp_node = temp_node->sucessor;
    }

    return 0; // nao encontrado
}

// Libera toda a memoria alocada pela lista
// Remove todos os elementos e os desaloca
// Deve ser chamada ao final do programa
void dlist_destroy(DoubleLinkedList *list)
{
    if (list == NULL)
        return;

    Node *temp_node;

    // remove e libera cada no da lista
    while (list->head != NULL)
    {
        temp_node = list->head;
        list->head = list->head->sucessor;
        free(temp_node);
    }

    // garante que tail também seja NULL após destruir
    list->tail = NULL;
}
