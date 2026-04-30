#include <stdio.h>
#include <stdlib.h>

struct Produto {
    int id;
    float preco;
};

int main(void) {
    struct Produto *p;

    p = (struct Produto *) malloc(sizeof(struct Produto));
    if (p == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    p->id = 1;
    p->preco = 99.90f;

    printf("ID: %d\n", p->id);
    printf("Preco: %.2f\n", p->preco);

    free(p);
    return 0;
}
