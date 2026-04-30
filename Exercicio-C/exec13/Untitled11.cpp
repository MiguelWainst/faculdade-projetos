#include <stdio.h>
#include <stdlib.h>

void liberarMatriz(int **matriz, int linhas) {
    int i;

    for (i = 0; i < linhas; i++) {
        free(matriz[i]);
    }

    free(matriz);
}

int main(void) {
    int M = 3, N = 4;
    int **matriz;
    int i, j;

    matriz = (int **) malloc(M * sizeof(int *));
    if (matriz == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    for (i = 0; i < M; i++) {
        matriz[i] = (int *) malloc(N * sizeof(int));
        if (matriz[i] == NULL) {
            printf("Erro ao alocar memoria para a linha %d.\n", i);

            for (j = 0; j < i; j++) {
                free(matriz[j]);
            }
            free(matriz);
            return 1;
        }
    }

    printf("Matriz alocada com sucesso.\n");

    liberarMatriz(matriz, M);

    printf("Matriz liberada com sucesso.\n");

    return 0;
}

