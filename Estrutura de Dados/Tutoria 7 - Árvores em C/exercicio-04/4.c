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

No* encontrarMinimo(No* raiz) {
    No* atual = raiz;
    while (atual && atual->esq != NULL) atual = atual->esq;
    return atual;
}

No* remover(No *raiz, int valor) {
    if (raiz == NULL) return raiz;

    if (valor < raiz->valor) {
        raiz->esq = remover(raiz->esq, valor);
    } else if (valor > raiz->valor) {
        raiz->dir = remover(raiz->dir, valor);
    } else {
        // Caso 1 e 2: No com um filho ou folha
        if (raiz->esq == NULL) {
            No *temp = raiz->dir;
            free(raiz);
            return temp;
        } else if (raiz->dir == NULL) {
            No *temp = raiz->esq;
            free(raiz);
            return temp;
        }
        // Caso 3: No com dois filhos
        No* temp = encontrarMinimo(raiz->dir);
        raiz->valor = temp->valor;
        raiz->dir = remover(raiz->dir, temp->valor);
    }
    return raiz;
}

void imprimirEmOrdem(No* raiz) {
    if (raiz != NULL) {
        imprimirEmOrdem(raiz->esq);
        printf("%d ", raiz->valor);
        imprimirEmOrdem(raiz->dir);
    }
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
    int valores[] = {50, 30, 70, 20, 40, 60, 80};
    for(int i = 0; i < 7; i++) raiz = inserir(raiz, valores[i]);

    printf("Arvore inicial: ");
    imprimirEmOrdem(raiz); printf("\n");

    printf("\nRemovendo 20 (no folha)...\n");
    raiz = remover(raiz, 20);
    imprimirEmOrdem(raiz); printf("\n");

    printf("\nRemovendo 30 (no com filho)...\n");
    raiz = remover(raiz, 30);
    imprimirEmOrdem(raiz); printf("\n");

    printf("\nRemovendo 50 (raiz com dois filhos)...\n");
    raiz = remover(raiz, 50);
    imprimirEmOrdem(raiz); printf("\n");

    liberar(raiz);
    return 0;
}
