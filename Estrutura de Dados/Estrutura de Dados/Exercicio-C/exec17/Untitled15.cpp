#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[50];
    float nota;
} Aluno;

int main() {
    Aluno alunos[5];
    Aluno **aprovados;
    int i, cont = 0;

    for (i = 0; i < 5; i++) {
        printf("Digite o nome do aluno %d: ", i + 1);
        scanf("%s", alunos[i].nome);

        printf("Digite a nota do aluno %d: ", i + 1);
        scanf("%f", &alunos[i].nota);
    }

    aprovados = (Aluno **) malloc(5 * sizeof(Aluno *));

    for (i = 0; i < 5; i++) {
        if (alunos[i].nota > 7.0) {
            aprovados[cont] = &alunos[i];
            cont++;
        }
    }

    printf("\nAlunos aprovados:\n");
    for (i = 0; i < cont; i++) {
        printf("Nome: %s\n", aprovados[i]->nome);
        printf("Nota: %.2f\n", aprovados[i]->nota);
    }

    free(aprovados);

    return 0;
}

