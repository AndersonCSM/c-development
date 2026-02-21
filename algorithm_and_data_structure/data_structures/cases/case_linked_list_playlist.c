#include <stdio.h>
#include <stdlib.h>

#include "include/linked_list.h"

// Exemplo usando linked list para gerenciar uma playlist
int main()
{
    printf("=== Linked List: Gerenciador de Playlist ===\n\n");

    LinkedList playlist;
    list_init(&playlist);

    printf("--- CONSTRUINDO PLAYLIST ---\n");
    printf("Adicionando músicas no final (append)...\n");
    list_append(&playlist, 1); // Música 1
    list_append(&playlist, 2); // Música 2
    list_append(&playlist, 3); // Música 3
    list_append(&playlist, 4); // Música 4

    printf("Adicionando música no inicio (prepend)...\n");
    list_appini(&playlist, 0); // Música 0 no início

    printf("Estado da playlist: ");
    list_display(&playlist);

    printf("\n--- BUSCANDO MÚSICAS ---\n");
    list_get(&playlist, 2);
    list_get(&playlist, 10);

    printf("\n--- REMOVENDO MÚSICAS ---\n");
    printf("Removendo música 0...\n");
    list_pop(&playlist, 0);
    printf("Playlist: ");
    list_display(&playlist);

    printf("\nRemovendo música 3 (do meio)...\n");
    list_pop(&playlist, 3);
    printf("Playlist: ");
    list_display(&playlist);

    printf("\nRemovendo música 4 (do final)...\n");
    list_pop(&playlist, 4);
    printf("Playlist: ");
    list_display(&playlist);

    printf("\n--- PROCESSANDO COM CALLBACK ---\n");
    printf("Duplicando IDs das músicas:\n");
    list_apply(&playlist, (LinkedListCallback)printf);

    list_destroy(&playlist);

    printf("\n\nPrograma finalizado.\n");
    return 0;
}
