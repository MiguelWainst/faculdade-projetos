#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int valor;
    struct no *prox;
} No;

// push
void push(No **topo, int v) {
    No *novo = malloc(sizeof(No));

    if (novo == NULL) {
        printf("erro malloc\n");
        return;
    }

    novo->valor = v;
    novo->prox = *topo;
    *topo = novo;
}

// pop
int pop(No **topo) {
    if (*topo == NULL) return -1;

    No *temp = *topo;
    int v = temp->valor;

    *topo = temp->prox;
    free(temp);

    return v;
}

// imprimir (so pra testar)
void imprimir(No *topo) {
    while (topo != NULL) {
        printf("%d ", topo->valor);
        topo = topo->prox;
    }
    printf("\n");
}

// ordenar (menor fica no topo)
void ordenar(No **pilha) {
    No *aux = NULL;

    while (*pilha != NULL) {

        int temp = pop(pilha);

        // enquanto aux tem elemento maior, devolve pra original
        while (aux != NULL && aux->valor > temp) {
            push(pilha, pop(&aux));
        }

        push(&aux, temp);
    }

    // volta tudo pra pilha original
    while (aux != NULL) {
        push(pilha, pop(&aux));
    }
}

int main() {
    No *pilha = NULL;

    // exemplo
    push(&pilha, 3);
    push(&pilha, 1);
    push(&pilha, 4);
    push(&pilha, 2);

    printf("antes: ");
    imprimir(pilha);

    ordenar(&pilha);

    printf("depois: ");
    imprimir(pilha);

    return 0;
}

