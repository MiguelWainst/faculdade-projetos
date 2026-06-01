#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Aluno {
    int matricula;
    char nome[50];
    float nota;
} Aluno;

typedef struct No {
    Aluno aluno;
    struct No *esq;
    struct No *dir;
} No;

No* inserir(No* raiz, Aluno aluno) {
    if (raiz == NULL) {
        No* novo = (No*)malloc(sizeof(No));
        novo->aluno = aluno;
        novo->esq = NULL;
        novo->dir = NULL;
        return novo;
    }
    if (aluno.matricula < raiz->aluno.matricula)
        raiz->esq = inserir(raiz->esq, aluno);
    else
        raiz->dir = inserir(raiz->dir, aluno);
    return raiz;
}

No* buscar(No* raiz, int matricula) {
    if (raiz == NULL || raiz->aluno.matricula == matricula)
        return raiz;
    if (matricula < raiz->aluno.matricula)
        return buscar(raiz->esq, matricula);
    return buscar(raiz->dir, matricula);
}

void imprimirEmOrdem(No* raiz) {
    if (raiz != NULL) {
        imprimirEmOrdem(raiz->esq);
        printf("%d - %s - Nota: %.1f\n", raiz->aluno.matricula, raiz->aluno.nome, raiz->aluno.nota);
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
    Aluno a1 = {102, "Ana", 9.0};
    Aluno a2 = {55, "Bruno", 8.5};
    Aluno a3 = {180, "Carla", 7.5};

    printf("Inserindo aluno 102 - Ana\n");
    raiz = inserir(raiz, a1);
    printf("Inserindo aluno 55 - Bruno\n");
    raiz = inserir(raiz, a2);
    printf("Inserindo aluno 180 - Carla\n");
    raiz = inserir(raiz, a3);

    printf("\nAlunos em ordem:\n");
    imprimirEmOrdem(raiz);

    int matBusca = 102;
    printf("\nBuscar matricula %d:\n", matBusca);
    No* resultado = buscar(raiz, matBusca);
    if (resultado != NULL)
        printf("Aluno encontrado: %s\n", resultado->aluno.nome);
    else
        printf("Matricula %d nao encontrada.\n", matBusca);

    liberar(raiz);
    return 0;
}
