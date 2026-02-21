#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../include/generic_list.h"
#include "include/lists/alunos_list.h"

// Callback para comparar dois alunos
// Compara pelo ID do estudante
int compare_student(void *a, void *b)
{
    Student *student_a = (Student *)a; // realiza o cast do dado generico para o tipo estudante
    Student *student_b = (Student *)b;

    return student_a->id - student_b->id; // compara o id dos alunos
}

// Callback para liberar memoria de um aluno
// Desaloca nome e estrutura
void free_student(void *data)
{
    Student *student_ptr = (Student *)data; // ponteiro generico

    if (student_ptr == NULL)
        return;

    if (student_ptr->name != NULL) // libera o nome do estudante
        free(student_ptr->name);

    free(student_ptr); // libera o ponteiro generico
}

// Cria um novo aluno com nome e ID
// Aloca memoria para nome usando strdup
Student *create_student(const char *name, int id)
{
    Student *new_student = (Student *)malloc(sizeof(Student)); // ponteiro generico
    if (new_student == NULL)
    {
        fprintf(stderr, "Erro ao alocar Student\n");
        return 1;
    }

    new_student->id = id;

    // strdup faz o malloc interno e a cópia.
    /*
    char *new_name = malloc(strlen(name) + 1);
    strcpy(new_name, name);
    */
    new_student->name = strdup(name);
    if (new_student->name == NULL)
    {
        free(new_student); // Limpeza em caso de falha de alocação do nome
        fprintf(stderr, "Erro ao alocar nome\n");
        return 1;
    }

    return new_student;
}
