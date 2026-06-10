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

int buscaSequencial(int vetor[], int tamanho, int valor, int *comparacoes) {
    for (int i = 0; i < tamanho; i++) {
        (*comparacoes)++;
        if (vetor[i] == valor) return 1;
    }
    return 0;
}

int buscarNaArvore(No* raiz, int valor, int *comparacoes) {
    if (raiz == NULL) {
        (*comparacoes)++;
        return 0;
    }
    (*comparacoes)++;
    if (raiz->valor == valor) return 1;
    if (valor < raiz->valor) return buscarNaArvore(raiz->esq, valor, comparacoes);
    return buscarNaArvore(raiz->dir, valor, comparacoes);
}

void liberar(No* raiz) {
    if (raiz != NULL) {
        liberar(raiz->esq);
        liberar(raiz->dir);
        free(raiz);
    }
}

int main() {
    int tamanho = 20;
    int vetor[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45, 55, 65, 75, 85, 90, 95, 5, 15, 100};
    
    No* raiz = NULL;
    for (int i = 0; i < tamanho; i++) {
        raiz = inserir(raiz, vetor[i]);
    }

    int valorBuscado = 75;
    int compSeq = 0, compArv = 0;

    printf("Valor buscado: %d\n", valorBuscado);

    printf("\nBusca sequencial:\n");
    if (buscaSequencial(vetor, tamanho, valorBuscado, &compSeq)) printf("Encontrado.\n");
    else printf("Nao encontrado.\n");
    printf("Comparacoes: %d\n", compSeq);

    printf("\nBusca na arvore:\n");
    if (buscarNaArvore(raiz, valorBuscado, &compArv)) printf("Encontrado.\n");
    else printf("Nao encontrado.\n");
    printf("Comparacoes: %d\n", compArv);

    liberar(raiz);
    return 0;
}
