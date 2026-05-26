#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no {
    int id;
    int urgencia;
    char tecnico[50];
    struct no *prox;
} No;

// push
void push(No **topo, int id, int urg, char *tec) {
    No *novo = malloc(sizeof(No));

    if (novo == NULL) {
        printf("erro malloc\n");
        return;
    }

    novo->id = id;
    novo->urgencia = urg;
    strcpy(novo->tecnico, tec);

    novo->prox = *topo;
    *topo = novo;
}

// pop
No* pop(No **topo) {
    if (*topo == NULL) return NULL;

    No *temp = *topo;
    *topo = temp->prox;
    return temp;
}

// função filtro
void filtrar(No **pilha, No **prioridade) {
    No *aux = NULL;

    // separa tudo
    while (*pilha != NULL) {
        No *temp = pop(pilha);

        if (temp->urgencia == 5) {
            temp->prox = *prioridade;
            *prioridade = temp;
        } else {
            temp->prox = aux;
            aux = temp;
        }
    }

    // restaura ordem da pilha original
    while (aux != NULL) {
        No *temp = aux;
        aux = aux->prox;

        temp->prox = *pilha;
        *pilha = temp;
    }
}

// imprimir
void imprimir(No *topo) {
    while (topo != NULL) {
        printf("[id:%d urg:%d tec:%s]\n", topo->id, topo->urgencia, topo->tecnico);
        topo = topo->prox;
    }
}

int main() {
    No *pilha = NULL;
    No *prioridade = NULL;

    // exemplo
    push(&pilha, 1, 3, "ana");
    push(&pilha, 2, 5, "joao");
    push(&pilha, 3, 2, "maria");
    push(&pilha, 4, 5, "carlos");

    printf("pilha original:\n");
    imprimir(pilha);

    filtrar(&pilha, &prioridade);

    printf("\npilha apos filtro:\n");
    imprimir(pilha);

    printf("\nprioridade maxima:\n");
    imprimir(prioridade);

    return 0;
}

