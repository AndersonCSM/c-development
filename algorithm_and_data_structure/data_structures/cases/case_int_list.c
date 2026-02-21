#include <stdio.h>
#include <stdlib.h>

#include "include/generic_list.h"

// Callback para comparar inteiros
int compare_int(void *a, void *b)
{
    int x = *(int *)a;
    int y = *(int *)b;
    return x - y;
}

// Callback para imprimir inteiros
bool print_int(int index, void *data)
{
    int value = *(int *)data;
    printf("Índice [%d]: %d\n", index, value);
    return true;
}

// Callback para processar inteiros pares
bool process_even(int index, void *data)
{
    int value = *(int *)data;
    if (value % 2 == 0)
    {
        printf("Número par encontrado: %d\n", value);
    }
    return true;
}

int main()
{
    printf("=== Int List: Processamento de Lista de Inteiros ===\n\n");

    List *list = list_create(sizeof(int), NULL, compare_int);

    printf("--- ADICIONANDO INTEIROS ---\n");
    int values[] = {10, 25, 8, 42, 15, 33, 7, 100};
    int count = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < count; i++)
    {
        int *data = malloc(sizeof(int));
        *data = values[i];
        list_add(list, data);
        free(data);
        printf("Adicionado: %d\n", values[i]);
    }

    printf("\n--- LISTANDO TODOS OS INTEIROS ---\n");
    list_foreach(list, print_int);

    printf("\n--- PROCESSANDO INTEIROS PARES ---\n");
    list_foreach(list, process_even);

    printf("\n--- PROCURANDO INTEIROS ---\n");
    int search_value = 42;
    if (list_contains(list, &search_value))
    {
        printf("✓ Inteiro %d encontrado!\n", search_value);
    }
    else
    {
        printf("✗ Inteiro %d NÃO encontrado.\n", search_value);
    }

    search_value = 999;
    if (list_contains(list, &search_value))
    {
        printf("✓ Inteiro %d encontrado!\n", search_value);
    }
    else
    {
        printf("✗ Inteiro %d NÃO encontrado.\n", search_value);
    }

    printf("\n--- REMOVENDO INTEIRO ---\n");
    int remove_value = 25;
    list_remove(list, &remove_value);
    printf("Inteiro %d removido.\n", remove_value);

    printf("\nInteiros após remoção:\n");
    list_foreach(list, print_int);

    list_destroy(list);

    printf("\nPrograma finalizado.\n");
    return 0;
}
