#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N;
    int *vetor;
    long soma = 0;
    double media;

    printf("Digite o tamanho do vetor: ");
    scanf("%d", &N);

    if (N <= 0) {
        printf("Tamanho invalido.\n");
        return 1;
    }

    vetor = (int *) malloc(N * sizeof(int));
    if (vetor == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    for (int i = 0; i < N; i++) {
        printf("Digite o elemento %d: ", i + 1);
        scanf("%d", &vetor[i]);
        soma += vetor[i];
    }

    media = (double)soma / N;

    printf("Media aritmetica = %.2f\n", media);

    free(vetor);
    return 0;
}
