#include <stdio.h>

int main() {
    int n, i, j;
    int matriz[10][10];

    printf("Digite o tamanho da matriz: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("Digite um valor para matriz[%d][%d]: ", i, j);
            scanf("%d", &matriz[i][j]);
        }
    }

    printf("\nValores da matriz:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }

    /*
    A complexidade e O(n2) porque tem dois for
    O primeiro for roda n vezes
    Dentro dele, o segundo for tambem roda n vezes
    Entao no total acontece n * n
    Por isso fica O(n2)
    */

    return 0;
}

