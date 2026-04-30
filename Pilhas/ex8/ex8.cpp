#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no {
    char c;
    struct no *prox;
} No;

// push
void push(No **topo, char c) {
    No *novo = malloc(sizeof(No));

    if (novo == NULL) {
        printf("erro malloc\n");
        return;
    }

    novo->c = c;
    novo->prox = *topo;
    *topo = novo;
}

// pop
char pop(No **topo) {
    if (*topo == NULL) return '\0';

    No *temp = *topo;
    char c = temp->c;

    *topo = temp->prox;
    free(temp);

    return c;
}

// verifica se combina
int combina(char a, char b) {
    if (a == '(' && b == ')') return 1;
    if (a == '[' && b == ']') return 1;
    if (a == '{' && b == '}') return 1;
    return 0;
}

int main() {
    char exp[200];
    No *pilha = NULL;

    printf("digite a expressao: ");
    fgets(exp, 200, stdin);

    for (int i = 0; exp[i] != '\0'; i++) {

        char c = exp[i];

        // se abrir, empilha
        if (c == '(' || c == '[' || c == '{') {
            push(&pilha, c);
        }

        // se fechar
        if (c == ')' || c == ']' || c == '}') {

            if (pilha == NULL) {
                printf("invalida\n");
                return 0;
            }

            char topo = pop(&pilha);

            if (!combina(topo, c)) {
                printf("invalida\n");
                return 0;
            }
        }
    }

    // se sobrou coisa, invalida
    if (pilha != NULL) {
        printf("invalida\n");
    } else {
        printf("valida\n");
    }

    return 0;
}

