#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no {
    char c;
    struct no *prox;
} No;

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

char pop(No **topo) {
    if (*topo == NULL) return '\0';

    No *temp = *topo;
    char c = temp->c;

    *topo = temp->prox;
    free(temp);

    return c;
}

int main() {
    char str[200];
    No *pilha = NULL;

    printf("digite: ");
    fgets(str, 200, stdin);

    str[strcspn(str, "\n")] = '\0';

    for (int i = 0; str[i] != '\0'; i++) {

        if (str[i] != ' ') {
            push(&pilha, str[i]);
        } else {
            while (pilha != NULL) {
                printf("%c", pop(&pilha));
            }
            printf(" ");
        }
    }

    while (pilha != NULL) {
        printf("%c", pop(&pilha));
    }

    printf("\n");

    return 0;
}

