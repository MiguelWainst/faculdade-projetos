#include <stdio.h>
#include <stdlib.h>

int main() {
    void *p;

    p = malloc(1024L * 1024L * 1024L); // 1GB

    if (p == NULL) {
        printf("falha ao alocar memoria\n");
        return 1;
    }

    printf("memoria alocada com sucesso\n");

    free(p);

    return 0;
}
