#ifndef REQUISICAO_H
#define REQUISICAO_H

typedef struct {
    char nome[41];
    int codigo;
    char procedimento[11];
} Requisicao;

// Funções
void criarRequisicao(Requisicao *r, char nome[], int cod, char proc[]);
void imprimirRequisicao(Requisicao r);

#endif
