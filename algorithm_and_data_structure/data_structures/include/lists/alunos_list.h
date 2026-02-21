#ifndef ALUNOSLIST_H
#define ALUNOSLIST_H

typedef struct student
{
    char *name;
    int id;
} Student;

// Protótipos com os novos nomes
int compare_student(void *a, void *b);
void free_student(void *data);
Student *create_student(const char *name, int id);

#endif