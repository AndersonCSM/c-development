#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "include/generic_list.h"

// Callback para imprimir inteiros genéricos
bool print_generic_int(int index, void *data)
{
    int value = *(int *)data;
    printf("Índice [%d]: %d\n", index, value);
    return true;
}

int main()
{
    printf("=== Generic List: Lista de Números Inteiros ===\n\n");

    List *list = list_create(sizeof(int), NULL, (cb_compare)compare_int);

    printf("--- ADICIONANDO NÚMEROS ---\n");
    int numbers[] = {42, 17, 89, 5, 23, 56, 11};
    int num_count = sizeof(numbers) / sizeof(numbers[0]);

    for (int i = 0; i < num_count; i++)
    {
        int *data = malloc(sizeof(int));
        *data = numbers[i];
        list_add(list, data);
        free(data);
        printf("Adicionado: %d\n", numbers[i]);
    }

    printf("\n--- LISTANDO TODOS OS NÚMEROS ---\n");
    list_foreach(list, print_generic_int);

    printf("\n--- PROCURANDO NÚMEROS ---\n");
    int search_values[] = {89, 30, 5};
    int search_count = sizeof(search_values) / sizeof(search_values[0]);

    for (int i = 0; i < search_count; i++)
    {
        int value = search_values[i];
        if (list_contains(list, &value))
        {
            printf("✓ Número %d encontrado!\n", value);
        }
        else
        {
            printf("✗ Número %d NÃO encontrado.\n", value);
        }
    }

    printf("\n--- REMOVENDO NÚMEROS ---\n");
    int remove_value = 89;
    list_remove(list, &remove_value);
    printf("Removido: %d\n", remove_value);

    printf("\nNúmeros após remoção:\n");
    list_foreach(list, print_generic_int);

    list_destroy(list);

    printf("\nPrograma finalizado.\n");
    return 0;
}

// Callback para comparar inteiros
int compare_int(void *a, void *b)
{
    int x = *(int *)a;
    int y = *(int *)b;
    return x - y;
}
