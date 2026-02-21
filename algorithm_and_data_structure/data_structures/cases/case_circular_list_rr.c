#include <stdio.h>
#include <stdlib.h>

#include "include/circular_list.h"

// Exemplo usando circular list para escalonamento round-robin
int main()
{
    printf("=== Circular List: Escalonamento Round-Robin ===\n\n");

    CircularList fila_processos;
    clist_init(&fila_processos);

    printf("--- ADICIONANDO PROCESSOS ---\n");
    printf("Processos: P1, P2, P3, P4, P5 (representados por IDs 1-5)\n\n");

    clist_append(&fila_processos, 1); // P1
    clist_append(&fila_processos, 2); // P2
    clist_append(&fila_processos, 3); // P3
    clist_append(&fila_processos, 4); // P4
    clist_append(&fila_processos, 5); // P5

    printf("Fila circular: ");
    clist_display(&fila_processos);

    printf("\n--- ESCALONAMENTO ROUND-ROBIN (Time Slice = 2) ---\n");
    printf("Executando processos em rotação (circular)...\n\n");

    int time_quantum = 2;
    int total_time = 0;

    // Simular 3 rodadas completas
    for (int rodada = 0; rodada < 3; rodada++)
    {
        printf("=== RODADA %d ===\n", rodada + 1);

        // Percorrer a lista circular
        printf("Execução: ");
        clist_apply(&fila_processos, (CircularListCallback)printf);
        printf("\n\n");
    }

    printf("--- REMOVENDO PROCESSADO ---\n");
    printf("P2 finalizado. Removendo...\n");
    clist_remove(&fila_processos, 2);
    printf("Fila atualizada: ");
    clist_display(&fila_processos);

    printf("\nP4 finalizado. Removendo...\n");
    clist_remove(&fila_processos, 4);
    printf("Fila atualizada: ");
    clist_display(&fila_processos);

    printf("\n--- PROCURANDO PROCESSOS ---\n");
    printf("P3 na fila? %s\n", clist_find(&fila_processos, 3) ? "SIM" : "NÃO");
    printf("P2 na fila? %s\n", clist_find(&fila_processos, 2) ? "SIM" : "NÃO");

    clist_destroy(&fila_processos);

    printf("\nPrograma finalizado.\n");
    return 0;
}
