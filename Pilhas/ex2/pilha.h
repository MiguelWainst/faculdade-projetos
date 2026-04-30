#ifndef PILHA_H
#define PILHA_H

typedef struct no {
    char texto[100];
    struct no *prox;
} No;

typedef struct {
    No *topo;
} Pilha;

Pilha* criarPilha();
int push(Pilha *p, char texto[]);
int pop(Pilha *p, char texto[]);
int peek(Pilha *p, char texto[]);   // Nova função
int estaVazia(Pilha *p);
void liberar(Pilha *p);

#endif
