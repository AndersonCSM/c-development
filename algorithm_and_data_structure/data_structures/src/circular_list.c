#include <stdio.h>
#include <stdlib.h>

#include "../include/circular_list.h"

// Inicializa uma lista circular vazia
// Define head e tail como NULL (lista sem elementos)
void clist_init(CircularList *list)
{
    list->head = NULL;
    list->tail = NULL;
}

// Cria um novo nó para a lista circular
// Aloca memória e inicializa os campos
// Retorna ponteiro para o novo nó ou NULL se falhar na alocação
Node *clist_create_node(int valor)
{
    Node *new_node = malloc(sizeof(Node));
    if (!new_node)
        return NULL;

    new_node->data = valor;
    new_node->next = NULL;

    return new_node;
}

// Insere um elemento no inicio (head) da lista circular
// Atualiza head e mantem a circularidade (tail aponta para head)
// Complexidade: O(1) - operação em tempo constante
void clist_appini(CircularList *list, int valor)
{
    Node *new_node = clist_create_node(valor);
    if (!new_node)
        return;

    if (list->head == NULL) // lista vazia
    {
        new_node->next = new_node; // aponta para si mesmo (circular)
        list->head = new_node;
        list->tail = new_node;
    }
    else
    {
        new_node->next = list->head; // novo nó aponta para antigo head
        list->tail->next = new_node; // tail continua apontando para o novo head (circularidade)
        list->head = new_node;       // head agora é o novo nó
    }
}

// Insere um elemento no final (tail) da lista circular
// Usa o ponteiro tail para acesso direto ao ultimo nó
// Complexidade: O(1) - operação em tempo constante (OTIMIZADO!)
void clist_append(CircularList *list, int valor)
{
    Node *new_node = clist_create_node(valor);
    if (!new_node)
        return;

    if (list->head == NULL) // lista vazia
    {
        new_node->next = new_node; // aponta para si mesmo (circular)
        list->head = new_node;
        list->tail = new_node;
    }
    else
    {
        new_node->next = list->head; // novo nó aponta para head (circularidade)
        list->tail->next = new_node; // antigo tail aponta para novo nó
        list->tail = new_node;       // tail agora é o novo nó
    }
}

// Remove um nó especifico da lista circular usando uma chave
// Atualiza os apontadores para manter a circularidade
// Atualiza head/tail se necessário. Caso não encontre, lista permanece inalterada
void clist_pop(CircularList *list, int chave)
{
    if (list->head == NULL)
        return;

    Node *atual = list->head;
    Node *anterior = NULL;

    // Busca o nó com a chave
    do
    {
        if (atual->data == chave)
            break;
        anterior = atual;
        atual = atual->next;
    } while (atual != list->head);

    // Não encontrou
    if (atual->data != chave)
        return;

    // Caso 1: Único nó na lista
    if (atual->next == atual)
    {
        free(atual);
        list->head = NULL;
        list->tail = NULL;
        return;
    }

    // Caso 2: Remover o head
    if (atual == list->head)
    {
        list->tail->next = list->head->next; // tail aponta para o novo head
        list->head = list->head->next;       // head avança
        free(atual);
    }
    // Caso 3: Remover o tail
    else if (atual == list->tail)
    {
        anterior->next = list->head; // anterior aponta para head (circularidade)
        list->tail = anterior;       // tail recua
        free(atual);
    }
    // Caso 4: Remover nó no meio
    else
    {
        anterior->next = atual->next; // costura
        free(atual);
    }
}

// Procura um elemento na lista circular e exibe mensagem
// Retorna mensagem indicando se o elemento foi encontrado ou nao
// Nota: função de busca simples com comparação de valor inteiro
void clist_get(CircularList *list, int chave)
{
    if (list->head == NULL)
    {
        printf("Lista vazia.\n");
        return;
    }

    Node *temp_node = list->head;
    do
    {
        if (temp_node->data == chave)
        {
            printf("Valor %d esta presente na lista.\n", chave);
            return;
        }
        temp_node = temp_node->next;
    } while (temp_node != list->head);

    printf("Valor %d nao esta presente na lista.\n", chave);
}

// Exibe todos os elementos da lista circular
// Itera do head ao tail mantendo a estrutura circular
// Formato: Lista circular: elemento1 elemento2 elemento3 ...
void clist_display(CircularList *list)
{
    if (list->head == NULL)
    {
        printf("Lista vazia.\n");
        return;
    }

    Node *temp_node = list->head;
    printf("Lista circular: ");
    do
    {
        printf("%d ", temp_node->data);
        temp_node = temp_node->next;
    } while (temp_node != list->head);
    printf("\n");
}

// Aplica uma funcao callback a cada elemento da lista circular
// Util para processar, filtrar ou transformar os dados
// Nota: nao remove elementos da lista
void clist_apply(CircularList *list, CircularListCallback callback)
{
    if (list == NULL || list->head == NULL || callback == NULL)
    {
        printf("Erro: lista ou callback nula!\n");
        return;
    }

    Node *temp_node = list->head;

    // itera por cada elemento (circularmente) e aplica o callback
    do
    {
        callback(temp_node->data);
        temp_node = temp_node->next;
    } while (temp_node != list->head);
}

// Procura um elemento na lista retornando um valor booleano
// Retorna 1 se encontrado, 0 se nao encontrado
// Nota: diferente de clist_get, nao exibe mensagem
int clist_find(CircularList *list, int valor)
{
    if (list == NULL || list->head == NULL)
        return 0;

    Node *temp_node = list->head;

    // procura por cada elemento (circularmente) ate encontrar
    do
    {
        if (temp_node->data == valor)
            return 1; // encontrado
        temp_node = temp_node->next;
    } while (temp_node != list->head);

    return 0; // nao encontrado
}

// Libera toda a memoria alocada pela lista circular
// Remove todos os elementos e os desaloca
// Deve ser chamada ao final do programa
void clist_destroy(CircularList *list)
{
    if (list == NULL || list->head == NULL)
        return;

    Node *atual = list->head;
    Node *proximo;

    // quebra a circularidade para facilitar a liberação
    list->tail->next = NULL;

    // remove e libera cada no da lista
    while (atual != NULL)
    {
        proximo = atual->next;
        free(atual);
        atual = proximo;
    }

    // garante que head e tail sejam NULL após destruir
    list->head = NULL;
    list->tail = NULL;
}
