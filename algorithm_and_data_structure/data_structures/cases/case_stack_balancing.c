#include <stdio.h>
#include <stdlib.h>

#include "include/stack.h"

// Exemplo usando stack para verificar se parênteses são balanceados
int main()
{
    printf("=== Stack: Verificador de Parênteses Balanceados ===\n\n");

    Stack stack;
    stack_init(&stack);

    const char *expressions[] = {
        "(())",
        "([{}])",
        "([){}]",
        "{[(])}",
        "((()))"};

    int num_expressions = sizeof(expressions) / sizeof(expressions[0]);

    for (int i = 0; i < num_expressions; i++)
    {
        const char *expr = expressions[i];
        int is_balanced = 1;

        for (int j = 0; expr[j] != '\0'; j++)
        {
            char c = expr[j];

            if (c == '(' || c == '[' || c == '{')
            {
                stack_push(&stack, c);
            }
            else if (c == ')' || c == ']' || c == '}')
            {
                if (stack_is_empty(&stack))
                {
                    is_balanced = 0;
                    break;
                }

                int top = stack_pop(&stack);

                if ((c == ')' && top != '(') ||
                    (c == ']' && top != '[') ||
                    (c == '}' && top != '{'))
                {
                    is_balanced = 0;
                    break;
                }
            }
        }

        if (!stack_is_empty(&stack))
            is_balanced = 0;

        printf("Expressão: %s\n", expr);
        printf("Resultado: %s\n\n", is_balanced ? "BALANCEADA ✓" : "DESBALANCEADA ✗");
    }

    stack_destroy(&stack);

    printf("Programa finalizado.\n");
    return 0;
}
