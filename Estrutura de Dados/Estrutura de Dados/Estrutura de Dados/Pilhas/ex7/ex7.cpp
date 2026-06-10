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

int main() {
    int num;
    No *pilha = NULL;

    printf("digite um numero decimal: ");
    scanf("%d", &num);

    if (num == 0) {
        printf("binario: 0\n");
        return 0;
    }

    // empilha restos da divisao por 2
    while (num > 0) {
        push(&pilha, num % 2);
        num = num / 2;
    }

    printf("binario: ");

    // desempilha pra mostrar na ordem correta
    while (pilha != NULL) {
        printf("%d", pop(&pilha));
    }

    printf("\n");

    return 0;
}

