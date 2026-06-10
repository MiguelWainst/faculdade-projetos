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

int contarNos(No *raiz) {
    if (raiz == NULL) return 0;
    return 1 + contarNos(raiz->esq) + contarNos(raiz->dir);
}

int contarFolhas(No *raiz) {
    if (raiz == NULL) return 0;
    if (raiz->esq == NULL && raiz->dir == NULL) return 1;
    return contarFolhas(raiz->esq) + contarFolhas(raiz->dir);
}

int contarNosComDoisFilhos(No *raiz) {
    if (raiz == NULL) return 0;
    int atual = (raiz->esq != NULL && raiz->dir != NULL) ? 1 : 0;
    return atual + contarNosComDoisFilhos(raiz->esq) + contarNosComDoisFilhos(raiz->dir);
}

int altura(No *raiz) {
    if (raiz == NULL) return -1;
    int altEsq = altura(raiz->esq);
    int altDir = altura(raiz->dir);
    return (altEsq > altDir ? altEsq : altDir) + 1;
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
    int valores[] = {50, 30, 70, 20, 40, 80};
    for(int i = 0; i < 6; i++) raiz = inserir(raiz, valores[i]);

    printf("Total de nos: %d\n", contarNos(raiz));
    printf("Total de folhas: %d\n", contarFolhas(raiz));
    printf("Nos com dois filhos: %d\n", contarNosComDoisFilhos(raiz));
    printf("Altura: %d\n", altura(raiz));

    liberar(raiz);
    return 0;
}
