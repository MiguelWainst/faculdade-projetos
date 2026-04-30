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

//FUNÇÕES 

Pilha* criarPilha() {
    Pilha *p = (Pilha*) malloc(sizeof(Pilha));
    if(p == NULL) {
        printf("Erro ao criar pilha!\n");
        return NULL;
    }
    p->topo = NULL;
    return p;
}

int push(Pilha *p, char texto[]) {
    No *novo = (No*) malloc(sizeof(No));
    if(novo == NULL) {
        printf("Erro: sem memoria!\n");
        return 0;
    }
    
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

// Conta quantos itens tem na pilha sem estragar ela
int count(Pilha *p) {
    if(p == NULL || p->topo == NULL) {
        return 0;
    }
    
    int qtd = 0;
    No *atual = p->topo;
    
    while(atual != NULL) {
        qtd++;
        atual = atual->prox;
    }
    return qtd;
}

void liberarPilha(Pilha *p) {
    char lixo[100];
    while(p != NULL && p->topo != NULL) {
        pop(p, lixo);
    }
    free(p);
}

// MAIN 
int main() {
    
    printf("=== Sistema de Pilha - Undo + Navegador + Inventario ===\n\n");
    
    Pilha *p = criarPilha();
    
    // Parte 1
    printf("=== Teste 1: Desfazer (Undo) ===\n");
    push(p, "Digitei Ola mundo");
    push(p, "Apaguei a palavra mundo");
    push(p, "Digitei Bom dia");
    
    char acao[100];
    pop(p, acao);
    printf("Desfeito: %s\n", acao);
    pop(p, acao);
    printf("Desfeito: %s\n\n", acao);
    
    // Parte 2 
    printf("=== Teste 2: Peek (Pagina atual) ===\n");
    push(p, "https://google.com");
    push(p, "https://youtube.com");
    push(p, "https://github.com");
    
    peek(p, acao);
    printf("Pagina atual: %s\n\n", acao);
    
    // Parte 4
    printf("=== Teste 3: Count (Quantidade de caixas) ===\n");
    push(p, "Caixa de Eletronicos");
    push(p, "Caixa de Roupas");
    push(p, "Caixa de Alimentos");
    
    int total = count(p);
    printf("Total de caixas no armazem: %d\n\n", total);
    
    // Mostrando o topo novamente
    peek(p, acao);
    printf("Caixa no topo: %s\n", acao);
    
    liberarPilha(p);
    
    printf("\nPrograma finalizado.\n");
    
    return 0;
}
