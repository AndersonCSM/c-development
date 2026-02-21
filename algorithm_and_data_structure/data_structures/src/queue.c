#include <stdio.h>
#include <stdlib.h>

#include "../include/queue.h"

// Inicializa uma fila vazia
// Define front e tail como NULL (fila sem elementos)
void queue_init(Queue *queue)
{
    queue->front = queue->tail = NULL;
}

// Verifica se a fila está vazia
// Retorna 1 (true) se estiver vazia, 0 (false) caso contrário
int queue_is_empty(Queue *queue)
{
    return queue->front == NULL;
}

// Adiciona um elemento ao final da fila (FIFO - First In, First Out)
// Aloca memória para um novo nó e o insere no final
void queue_enqueue(Queue *queue, int value)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (!new_node)
        return;

    new_node->data = value;    // armazena o valor no nó
    new_node->sucessor = NULL; // novo nó não tem sucessor ainda

    if (queue->tail == NULL) // fila vazia
    {
        queue->front = queue->tail = new_node; // primeiro e último elemento é o novo nó
    }
    else
    {
        queue->tail->sucessor = new_node; // conecta o último nó ao novo
        queue->tail = new_node;           // atualiza o apontador de cauda
    }
}

// Remove e retorna o primeiro elemento da fila
// Retorna -1 se a fila estiver vazia
int queue_dequeue(Queue *queue)
{
    if (queue->front == NULL)
    {
        printf("Fila Vazia.\n");
        return -1;
    }

    Node *temp_node = queue->front;
    int dequeued_value = temp_node->data;

    queue->front = temp_node->sucessor; // move o apontador front para o próximo nó

    if (queue->front == NULL) // se fila ficar vazia
    {
        queue->tail = NULL; // tail também deve ser NULL
    }

    free(temp_node);       // libera memória do nó removido
    return dequeued_value; // retorna o valor removido
}

// Retorna o primeiro elemento sem remover da fila
// Retorna -1 se a fila estiver vazia
int queue_front(Queue *queue)
{
    if (queue->front == NULL)
    {
        printf("Fila Vazia.\n");
        return -1;
    }

    return queue->front->data;
}

// Exibe todos os elementos da fila do primeiro ao último
void queue_display(Queue *queue)
{
    if (queue->front == NULL)
    {
        printf("Fila Vazia.\n");
        return;
    }

    Node *temp_node = queue->front;
    printf("Fila: ");

    while (temp_node)
    {
        printf("%d ", temp_node->data);
        temp_node = temp_node->sucessor;
    }

    printf("\n");
}

// Aplica uma funcao callback a cada elemento da fila
// Util para processar, filtrar ou transformar os dados
// Nota: nao remove elementos da fila
void queue_apply(Queue *queue, QueueCallback callback)
{
    if (queue == NULL || callback == NULL)
    {
        printf("Erro: fila ou callback nulo!\n");
        return;
    }

    if (queue->front == NULL)
    {
        printf("Fila vazia. Nada a processar.\n");
        return;
    }

    Node *temp_node = queue->front;

    // itera por cada elemento e aplica o callback
    while (temp_node)
    {
        callback(temp_node->data);
        temp_node = temp_node->sucessor;
    }
}

// Procura um elemento na fila
// Retorna 1 se encontrado, 0 se não encontrado
// Nota: não remove elemento, apenas verifica existência
int queue_find(Queue *queue, int value)
{
    if (queue == NULL)
    {
        printf("Erro: fila nula!\n");
        return 0;
    }

    if (queue->front == NULL)
    {
        printf("Fila vazia. Elemento n\u00e3o encontrado.\n");
        return 0;
    }

    Node *temp_node = queue->front;

    // procura por cada elemento até encontrar ou chegar ao final
    while (temp_node)
    {
        if (temp_node->data == value)
            return 1; // encontrado
        temp_node = temp_node->sucessor;
    }

    return 0; // não encontrado
}

// Libera toda a memória alocada pela fila
// Remove todos os elementos e os desaloca
// Deve ser chamada ao final do programa
void queue_destroy(Queue *queue)
{
    if (queue == NULL)
        return;

    Node *temp_node;

    // remove e libera cada nó da fila
    while (queue->front != NULL)
    {
        temp_node = queue->front;
        queue->front = queue->front->sucessor;
        free(temp_node);
    }

    queue->tail = NULL; // garante que tail também é NULL
}