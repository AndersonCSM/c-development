#include <stdio.h>
#include <stdlib.h>

#include "../include/linked_list.h"

// Inicializa uma lista vazia
// Define head e tail como NULL (lista sem elementos)
void list_init(LinkedList *list)
{
    list->head = NULL;
    list->tail = NULL;
}

// Cria um novo nó para lista simples
// Aloca memória e inicializa os campos (data e antecessor)
// Retorna ponteiro para o novo nó ou NULL se falhar na alocação
Node *list_create_node(int valor)
{
    Node *new_node = malloc(sizeof(Node));
    if (!new_node)
        return NULL;

    new_node->data = valor;
    new_node->antecessor = NULL;

    return new_node;
}

// Insere um elemento no inicio (head) da lista simples
// O novo nó passa a ser a cabeça e aponta para o antigo nó da cabeça
// Complexidade: O(1) - operação em tempo constante
void list_appini(LinkedList *list, int valor)
{
    Node *new_node = list_create_node(valor);
    if (!new_node)
        return;

    new_node->antecessor = list->head; // o novo nó aponta para a antiga cabeça
    list->head = new_node;             // o ponteiro head agora é o novo nó

    // se a lista estava vazia, tail também deve apontar para o novo nó
    if (list->tail == NULL)
    {
        list->tail = new_node;
    }
}

// Insere um elemento no final da lista simples
// Usa o ponteiro tail para acesso direto ao ultimo nó
// Complexidade: O(1) - operação em tempo constante (OTIMIZADO!)
void list_append(LinkedList *list, int valor)
{
    Node *new_node = list_create_node(valor);
    if (!new_node)
        return;

    if (list->head == NULL) // lista vazia
    {
        list->head = new_node; // o novo nó é tanto head quanto tail
        list->tail = new_node;
    }
    else
    {
        list->tail->antecessor = new_node; // tail aponta para o novo nó
        list->tail = new_node;             // atualiza tail para o novo nó
    }
}

// Remove um nó especifico da lista usando uma chave
// Realiza a costura entre os nós para manter a lista conectada após remocao
// Atualiza tail se o nó removido for o último
// Caso nao encontre a chave, a lista permanece inalterada
void list_pop(LinkedList *list, int chave)
{
    if (list->head == NULL)
        return;

    Node *temp_node = list->head; // nó atual
    Node *anterior = NULL;        // nó anterior

    // Caso especial: remover o head
    if (temp_node->data == chave)
    {
        list->head = temp_node->antecessor; // head será atualizado para o antecessor

        // se a lista ficar vazia, tail também deve ser NULL
        if (list->head == NULL)
        {
            list->tail = NULL;
        }

        free(temp_node); // libera a antiga cabeça
        return;
    }

    // Busca o nó com a chave na lista
    do
    {
        anterior = temp_node;              // salva o nó anterior
        temp_node = temp_node->antecessor; // avança para o proximo nó

        if (!temp_node) // chegou ao final sem encontrar
            return;

        if (temp_node->data == chave) // encontrou o nó a remover
        {
            anterior->antecessor = temp_node->antecessor; // costura: pula o nó a ser removido

            // se o nó removido era o tail, atualiza tail para o anterior
            if (temp_node == list->tail)
            {
                list->tail = anterior;
            }

            free(temp_node); // libera memoria do nó removido
            return;
        }

    } while (temp_node != NULL);
}

// Procura um elemento na lista simples usando uma chave
// Retorna mensagem indicando se o elemento foi encontrado ou nao
// Nota: funcao de busca simples com comparacao de valor inteiro
void list_get(LinkedList *list, int chave)
{
    if (list->head == NULL)
    {
        printf("Lista vazia.\n");
        return;
    }

    Node *temp_node = list->head; // inicia da cabeça
    while (temp_node && temp_node->data != chave)
    {
        temp_node = temp_node->antecessor; // avanca para o proximo nó
    }

    if (temp_node == NULL) // elemento nao encontrado
    {
        printf("Valor %d nao esta presente na lista.\n", chave);
    }
    else
    {
        printf("Valor %d esta presente na lista.\n", chave);
    }
}

// Exibe todos os elementos da lista simples
// Itera da cabeça ate o final (onde antecessor == NULL)
// Formato: Lista: elemento1 elemento2 elemento3 ...
void list_display(LinkedList *list)
{
    if (list->head == NULL)
    {
        printf("Lista vazia.\n");
        return;
    }

    Node *temp_node = list->head;
    printf("Lista: ");
    while (temp_node)
    {
        printf("%d ", temp_node->data);
        temp_node = temp_node->antecessor;
    }
    printf("\n");
}

// Aplica uma funcao callback a cada elemento da lista
// Util para processar, filtrar ou transformar os dados
// Nota: nao remove elementos da lista
void list_apply(LinkedList *list, LinkedListCallback callback)
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
        temp_node = temp_node->antecessor;
    }
}

// Procura um elemento na lista retornando um valor booleano
// Retorna 1 se encontrado, 0 se nao encontrado
// Nota: diferente de list_get, nao exibe mensagem
int list_find(LinkedList *list, int valor)
{
    if (list == NULL || list->head == NULL)
        return 0;

    Node *temp_node = list->head;

    // procura por cada elemento ate encontrar ou chegar ao final
    while (temp_node)
    {
        if (temp_node->data == valor)
            return 1; // encontrado
        temp_node = temp_node->antecessor;
    }

    return 0; // nao encontrado
}

// Libera toda a memoria alocada pela lista
// Remove todos os elementos e os desaloca
// Deve ser chamada ao final do programa
void list_destroy(LinkedList *list)
{
    if (list == NULL)
        return;

    Node *temp_node;

    // remove e libera cada no da lista
    while (list->head != NULL)
    {
        temp_node = list->head;
        list->head = list->head->antecessor;
        free(temp_node);
    }

    // garante que tail também seja NULL após destruir
    list->tail = NULL;
}
