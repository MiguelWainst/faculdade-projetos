#include <stdio.h>
#include <stdlib.h>

struct Aluno {
    char nome[50];
    float nota;
};

int main(void) {
    struct Aluno *alunos;

    alunos = (struct Aluno *) malloc(3 * sizeof(struct Aluno));
    if (alunos == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    printf("Array dinamico de 3 alunos alocado com sucesso.\n");

    free(alunos);
    return 0;
}
