#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    float preco;
    char nome[50];
} Produto;

Produto* clonar(Produto *origem) {
    Produto *novo;

    novo = (Produto *) malloc(sizeof(Produto));

    novo->id = origem->id;
    novo->preco = origem->preco;
    strcpy(novo->nome, origem->nome);

    return novo;
}

int main() {
    Produto p1;
    Produto *p2;

    p1.id = 1;
    p1.preco = 25.5;
    strcpy(p1.nome, "Caderno");

    p2 = clonar(&p1);

    printf("Produto original:\n");
    printf("ID: %d\n", p1.id);
    printf("Preco: %.2f\n", p1.preco);
    printf("Nome: %s\n", p1.nome);

    printf("\nProduto clonado:\n");
    printf("ID: %d\n", p2->id);
    printf("Preco: %.2f\n", p2->preco);
    printf("Nome: %s\n", p2->nome);

    free(p2);

    return 0;
}

