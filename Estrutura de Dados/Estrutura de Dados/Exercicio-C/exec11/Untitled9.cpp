#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *vetor;
    int i;

    vetor = (int *) malloc(2 * sizeof(int));
    if (vetor == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    printf("Digite 2 numeros:\n");
    for (i = 0; i < 2; i++) {
        scanf("%d", &vetor[i]);
    }

    vetor = (int *) realloc(vetor, 4 * sizeof(int));
    if (vetor == NULL) {
        printf("Erro ao realocar memoria.\n");
        return 1;
    }

    printf("Digite mais 2 numeros:\n");
    for (i = 2; i < 4; i++) {
        scanf("%d", &vetor[i]);
    }

    printf("Valores armazenados:\n");
    for (i = 0; i < 4; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");

    free(vetor);
    return 0;
}
