#include "pilha.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Pilha* criarPilha() {
    Pilha *p = (Pilha*) malloc(sizeof(Pilha));
    if(p == NULL) {
        printf("Erro ao criar a pilha!\n");
        return NULL;
    }
    
    p->topo = NULL;
    return p;
}

int push(Pilha *p, char texto[]) {
    No *novo = (No*) malloc(sizeof(No));
    if(novo == NULL) {
        printf("Erro: nao foi possivel alocar memoria!\n");
        return 0;
    }
    
    strcpy(novo->texto, texto);
    novo->prox = p->topo;
    p->topo = novo;
    
    return 1;
}

int pop(Pilha *p, char texto[]) {
    if(estaVazia(p)) {
        printf("Erro: Nao ha acoes para desfazer\n");
        return 0;
    }
    
    No *aux = p->topo;
    strcpy(texto, aux->texto);
    
    p->topo = p->topo->prox;
    
    free(aux);
    return 1;
}

int estaVazia(Pilha *p) {
    if(p == NULL || p->topo == NULL) {
        return 1;
    }
    return 0;
}

void liberar(Pilha *p) {
    char lixo[100];
    while(!estaVazia(p)) {
        pop(p, lixo);
    }
    free(p);
}
