#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No *esq;
    struct No *dir;
} No;

No* inserir(No* raiz, int valor) {
    if (raiz == NULL) {
        No* novo = (No*)malloc(sizeof(No));
        novo->valor = valor;
        novo->esq = NULL;
        novo->dir = NULL;
        return novo;
    }
    if (valor < raiz->valor) raiz->esq = inserir(raiz->esq, valor);
    else raiz->dir = inserir(raiz->dir, valor);
    return raiz;
}

int menorValor(No *raiz) {
    No *atual = raiz;
    while (atual->esq != NULL) {
        atual = atual->esq;
    }
    return atual->valor;
}

int maiorValor(No *raiz) {
    No *atual = raiz;
    while (atual->dir != NULL) {
        atual = atual->dir;
    }
    return atual->valor;
}

void liberar(No* raiz) {
    if (raiz != NULL) {
        liberar(raiz->esq);
        liberar(raiz->dir);
        free(raiz);
    }
}

int main() {
    No* raiz = NULL;
    int valores[10] = {50, 25, 75, 12, 35, 65, 85, 5, 40, 90};
    for(int i = 0; i < 10; i++) raiz = inserir(raiz, valores[i]);

    printf("Menor valor da arvore: %d\n", menorValor(raiz));
    printf("Maior valor da arvore: %d\n", maiorValor(raiz));

    liberar(raiz);
    return 0;
}
