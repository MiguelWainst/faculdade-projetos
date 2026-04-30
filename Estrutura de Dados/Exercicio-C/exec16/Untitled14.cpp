#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    float preco;
} Produto;

Produto* buscar(Produto *v, int id) {
    int i;

    for (i = 0; i < 10; i++) {
        if (v[i].id == id) {
            return &v[i];
        }
    }

    return NULL;
}

int main() {
    Produto *produtos;
    Produto *achou;
    int i, idBusca;

    produtos = (Produto *) malloc(10 * sizeof(Produto));

    for (i = 0; i < 10; i++) {
        printf("Digite o id do produto %d: ", i + 1);
        scanf("%d", &produtos[i].id);

        printf("Digite o preco do produto %d: ", i + 1);
        scanf("%f", &produtos[i].preco);
    }

    printf("Qual id voce quer buscar? ");
    scanf("%d", &idBusca);

    achou = buscar(produtos, idBusca);

    if (achou != NULL) {
        printf("Produto encontrado!\n");
        printf("ID: %d\n", achou->id);
        printf("Preco: %.2f\n", achou->preco);
    } else {
        printf("Produto nao encontrado.\n");
    }

    free(produtos);

    return 0;
}

