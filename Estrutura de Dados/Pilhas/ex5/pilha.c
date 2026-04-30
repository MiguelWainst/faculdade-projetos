#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no {
    char texto[100];
    struct no *prox;
} No;

typedef struct {
    No *topo;
} Pilha;

Pilha* criarPilha() {
    Pilha *p = (Pilha*) malloc(sizeof(Pilha));
    if(p == NULL) return NULL;
    p->topo = NULL;
    return p;
}

int push(Pilha *p, char texto[]) {
    No *novo = (No*) malloc(sizeof(No));
    if(novo == NULL) return 0;
    strcpy(novo->texto, texto);
    novo->prox = p->topo;
    p->topo = novo;
    return 1;
}

int pop(Pilha *p, char texto[]) {
    if(p == NULL || p->topo == NULL) {
        printf("Erro: Nao ha acoes para desfazer\n");
        return 0;
    }
    No *aux = p->topo;
    strcpy(texto, aux->texto);
    p->topo = p->topo->prox;
    free(aux);
    return 1;
}

int peek(Pilha *p, char texto[]) {
    if(p == NULL || p->topo == NULL) {
        printf("Erro: Pilha vazia!\n");
        return 0;
    }
    strcpy(texto, p->topo->texto);
    return 1;
}

int count(Pilha *p) {
    if(p == NULL || p->topo == NULL) return 0;
    int qtd = 0;
    No *atual = p->topo;
    while(atual != NULL) {
        qtd++;
        atual = atual->prox;
    }
    return qtd;
}

int compararPilhas(Pilha *p1, Pilha *p2) {
    if(p1 == NULL || p2 == NULL) return 0;
    if(count(p1) != count(p2)) return 0;

    Pilha *aux1 = criarPilha();
    Pilha *aux2 = criarPilha();
    
    char v1[100], v2[100];
    int iguais = 1;

    while(p1->topo != NULL && p2->topo != NULL) {
        pop(p1, v1);
        pop(p2, v2);
        push(aux1, v1);
        push(aux2, v2);
        if(strcmp(v1, v2) != 0) iguais = 0;
    }

    while(aux1->topo != NULL) {
        pop(aux1, v1);
        push(p1, v1);
    }
    while(aux2->topo != NULL) {
        pop(aux2, v2);
        push(p2, v2);
    }

    free(aux1);
    free(aux2);
    return iguais;
}

void liberarPilha(Pilha *p) {
    char lixo[100];
    while(p != NULL && p->topo != NULL) {
        pop(p, lixo);
    }
    free(p);
}

int main() {
    printf("=== Sincronizacao de Servidores ===\n\n");
    
    Pilha *servidorA = criarPilha();
    Pilha *servidorB = criarPilha();

    push(servidorA, "Login admin");
    push(servidorA, "Upload relatorio.pdf");
    push(servidorA, "Logout admin");

    push(servidorB, "Login admin");
    push(servidorB, "Upload relatorio.pdf");
    push(servidorB, "Logout admin");

    if(compararPilhas(servidorA, servidorB)) {
        printf("As pilhas sao IDENTICAS\n");
    } else {
        printf("As pilhas sao DIFERENTES\n");
    }

    push(servidorB, "Erro no sistema");

    if(compararPilhas(servidorA, servidorB)) {
        printf("As pilhas sao IDENTICAS\n");
    } else {
        printf("As pilhas sao DIFERENTES\n");
    }

    liberarPilha(servidorA);
    liberarPilha(servidorB);

    printf("\nFim.\n");
    return 0;
}
