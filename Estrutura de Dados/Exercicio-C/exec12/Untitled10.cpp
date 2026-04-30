#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int M, N;
    int **matriz;
    int i, j;

    printf("Digite o numero de linhas (M): ");
    scanf("%d", &M);

    printf("Difgite o numero de colunas (N): ");
    scanf("%d", &N);

    if (M <= 0 || N <= 0) {
        printf("Dimensoes invalidas.\n");
        return 1;
    }

    matriz = (int **) malloc(M * sizeof(int *));
    if (matriz == NULL) {
        printf("Erro ao alocar memoria para as linhas.\n");
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

    printf("Digite os elenentos da matriz:\n");
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            printf("matriz[%d][%d] = ", i, j);
            scanf("%d", &matriz[i][j]);
        }
    }

    printf("Matriz digitada:\n");
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }

    for (i = 0; i < M; i++) {
        free(matriz[i]);
    }
    free(matriz);

    return 0;
}
