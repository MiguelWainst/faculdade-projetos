#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int chave;
    struct No *esq, *dir;
} No;

No* criarNo(int valor) {
    No* novo = (No*)malloc(sizeof(No));
    novo->chave = valor;
    novo->esq = novo->dir = NULL;
    return novo;
}

No* inserir(No* raiz, int valor) {
    if (raiz == NULL) return criarNo(valor);
    if (valor < raiz->chave) raiz->esq = inserir(raiz->esq, valor);
    else if (valor > raiz->chave) raiz->dir = inserir(raiz->dir, valor);
    return raiz;
}

No* buscar(No* raiz, int valor) {
    if (raiz == NULL || raiz->chave == valor) return raiz;
    if (valor < raiz->chave) return buscar(raiz->esq, valor);
    return buscar(raiz->dir, valor);
}

No* minimo(No* raiz) {
    No* atual = raiz;
    while (atual && atual->esq != NULL) atual = atual->esq;
    return atual;
}

No* removerNo(No* raiz, int valor) {
    if (raiz == NULL) return raiz;
    if (valor < raiz->chave) raiz->esq = removerNo(raiz->esq, valor);
    else if (valor > raiz->chave) raiz->dir = removerNo(raiz->dir, valor);
    else {
        if (raiz->esq == NULL) {
            No* temp = raiz->dir;
            free(raiz);
            return temp;
        } else if (raiz->dir == NULL) {
            No* temp = raiz->esq;
            free(raiz);
            return temp;
        }
        No* temp = minimo(raiz->dir);
        raiz->chave = temp->chave;
        raiz->dir = removerNo(raiz->dir, temp->chave);
    }
    return raiz;
}

void liberarArvore(No* raiz) {
    if (raiz == NULL) return;
    liberarArvore(raiz->esq);
    liberarArvore(raiz->dir);
    free(raiz);
}

void imprimir(No* raiz) {
    if (raiz != NULL) {
        imprimir(raiz->esq);
        printf("%d ", raiz->chave);
        imprimir(raiz->dir);
    }
}

int main() {
    No* raiz = NULL;
    int opcao, valor;

    do {
        printf("\n--- MENU ARVORE ---\n");
        printf("1. Inserir\n2. Buscar\n3. Remover No\n4. Imprimir\n0. Sair e Deletar Arvore\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                printf("Valor: ");
                scanf("%d", &valor);
                raiz = inserir(raiz, valor);
                break;
            case 2:
                printf("Buscar: ");
                scanf("%d", &valor);
                if(buscar(raiz, valor)) printf("Encontrado!\n");
                else printf("Nao encontrado.\n");
                break;
            case 3:
                printf("Remover: ");
                scanf("%d", &valor);
                raiz = removerNo(raiz, valor);
                break;
            case 4:
                printf("Arvore: ");
                imprimir(raiz);
                printf("\n");
                break;
            case 0:
                liberarArvore(raiz);
                raiz = NULL;
                printf("Memoria limpa. Tchau!\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}
