#include <stdio.h>
#include <stdlib.h>

#include "include/queue.h"

// Exemplo usando queue para simular fila de atendimento
typedef struct
{
    int customer_id;
    int arrival_time;
} Customer;

int main()
{
    printf("=== Queue: Simulador de Fila de Atendimento ===\n\n");

    Queue queue;
    queue_init(&queue);

    int customers[] = {101, 102, 103, 104, 105};
    int service_time = 0;

    printf("--- CHEGADA DE CLIENTES ---\n");
    for (int i = 0; i < 5; i++)
    {
        queue_enqueue(&queue, customers[i]);
        printf("Cliente %d chegou na fila\n", customers[i]);
    }

    printf("\n--- ATENDIMENTO (ordem FIFO) ---\n");
    while (!queue_is_empty(&queue))
    {
        int customer_id = queue_dequeue(&queue);
        service_time++;
        printf("Time=%d: Atendendo cliente %d\n", service_time, customer_id);
    }

    printf("\n--- TESTE: Procurar cliente ---\n");
    queue_enqueue(&queue, 201);
    queue_enqueue(&queue, 202);
    queue_enqueue(&queue, 203);

    printf("Fila: ");
    queue_display(&queue);

    printf("Cliente 202 existe? %s\n", queue_find(&queue, 202) ? "SIM" : "NÃO");
    printf("Cliente 999 existe? %s\n", queue_find(&queue, 999) ? "SIM" : "NÃO");

    queue_destroy(&queue);

    printf("\nPrograma finalizado.\n");
    return 0;
}
