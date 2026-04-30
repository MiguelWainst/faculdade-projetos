#include <stdio.h>

void dobrar(int *valor) {
    *valor = (*valor) * 2;
}

int main(void) {
    int num;

    printf("Dgite um numero inteiro: ");
    scanf("%d", &num);

    dobrar(&num);

    printf("Valor dobrado: %d\n", num);

    return 0;
}
