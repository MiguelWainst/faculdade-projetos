#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *ptr, *inicio;
    int i;

    ptr = (int *) malloc(5 * sizeof(int));
    if (ptr == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    inicio = ptr;

    for (i = 0; i < 5; i++) {
        printf("Digite o %d numero: ", i + 1);
        scanf("%d", ptr);
        ptr++;
    }

    ptr = inicio;

    printf("Valores do vetor:\n");
    for (i = 0; i < 5; i++) {
        printf("%d\n", *ptr);
        ptr++;
    }

    free(inicio);
    return 0;
}
