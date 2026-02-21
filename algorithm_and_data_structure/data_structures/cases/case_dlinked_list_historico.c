#include <stdio.h>
#include <stdlib.h>

#include "include/dlinked_list.h"

// Exemplo usando double linked list para navegação bidirecional
int main()
{
    printf("=== Double Linked List: Navegação Bidirecional ===\n\n");

    DoubleLinkedList historico;
    dlist_init(&historico);

    printf("--- ADICIONANDO PÁGINAS AO HISTÓRICO ---\n");
    printf("Visitando páginas: Home, Google, GitHub, Stack Overflow, MDN\n");
    printf("(Representadas por IDs: 1, 2, 3, 4, 5)\n\n");

    dlist_append(&historico, 1); // Home
    dlist_append(&historico, 2); // Google
    dlist_append(&historico, 3); // GitHub
    dlist_append(&historico, 4); // Stack Overflow
    dlist_append(&historico, 5); // MDN

    printf("Histórico: ");
    dlist_display(&historico);

    printf("\n--- NAVEGAÇÃO BIDIRECIONAL ---\n");
    printf("Procurando página 3...\n");
    dlist_get(&historico, 3);

    printf("Página 2 existe? %s\n", dlist_find(&historico, 2) ? "SIM" : "NÃO");
    printf("Página 10 existe? %s\n\n", dlist_find(&historico, 10) ? "SIM" : "NÃO");

    printf("--- REMOVENDO PÁGINAS ---\n");
    printf("Removendo página 3 do histórico...\n");
    dlist_pop(&historico, 3);
    printf("Histórico atualizado: ");
    dlist_display(&historico);

    printf("\nRemovendo primeira página (Home)...\n");
    dlist_pop(&historico, 1);
    printf("Histórico atualizado: ");
    dlist_display(&historico);

    printf("\nRemovendo última página (MDN)...\n");
    dlist_pop(&historico, 5);
    printf("Histórico atualizado: ");
    dlist_display(&historico);

    printf("\n--- PROCESSANDO COM CALLBACK ---\n");
    printf("Mostrando todas as páginas restantes:\n");
    dlist_apply(&historico, (DoubleLinkedListCallback)printf);
    printf("\n");

    dlist_destroy(&historico);

    printf("\nPrograma finalizado.\n");
    return 0;
}
