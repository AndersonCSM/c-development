#include <stdio.h>
#include <stdlib.h>

#include "include/lists/alunos_list.h"
#include "include/generic_list.h"

int main()
{
    printf("=== Alunos List: Gerenciador de Estudantes ===\n\n");

    List *student_list = list_create(sizeof(Student), free_student, compare_student);

    printf("--- CADASTRANDO ALUNOS ---\n");

    Student *student1 = create_student("Alice Silva", 101);
    Student *student2 = create_student("Bob Santos", 102);
    Student *student3 = create_student("Carol Oliveira", 103);
    Student *student4 = create_student("David Costa", 104);

    list_add(student_list, student1);
    printf("Aluno cadastrado: %s (ID: %d)\n", student1->name, student1->id);

    list_add(student_list, student2);
    printf("Aluno cadastrado: %s (ID: %d)\n", student2->name, student2->id);

    list_add(student_list, student3);
    printf("Aluno cadastrado: %s (ID: %d)\n", student3->name, student3->id);

    list_add(student_list, student4);
    printf("Aluno cadastrado: %s (ID: %d)\n", student4->name, student4->id);

    printf("\n--- BUSCANDO ALUNOS ---\n");
    Student search_student = {NULL, 103};
    if (list_contains(student_list, &search_student))
    {
        printf("✓ Aluno com ID 103 encontrado!\n");
    }
    else
    {
        printf("✗ Aluno com ID 103 NÃO encontrado.\n");
    }

    search_student.id = 999;
    if (list_contains(student_list, &search_student))
    {
        printf("✓ Aluno com ID 999 encontrado!\n");
    }
    else
    {
        printf("✗ Aluno com ID 999 NÃO encontrado.\n");
    }

    printf("\n--- REMOVENDO ALUNO ---\n");
    Student remove_student = {NULL, 102};
    list_remove(student_list, &remove_student);
    printf("Aluno com ID 102 removido.\n");

    list_destroy(student_list);

    printf("\nPrograma finalizado.\n");
    return 0;
}
