#include "lista.h"

// Ex 1: Criar Nodo
Nodo* criar_nodo(int valor) {
    Nodo *novo = (Nodo*) malloc(sizeof(Nodo));
    if (novo) {
        novo->valor = valor;
        novo->anterior = NULL;
        novo->proximo = NULL;
    }
    return novo;
}

void destruir_nodo(Nodo *nodo) {
    free(nodo);
}

// Ex 2: Criar Lista
Lista* criar_lista() {
    Lista *lista = (Lista*) malloc(sizeof(Lista));
    if (lista) {
        lista->inicio = NULL;
        lista->fim = NULL;
        lista->tamanho = 0;
    }
    return lista;
}

int esta_vazia(Lista *lista) {
    return (lista->tamanho == 0);
}

// Ex 3: Insercaoo no Inicio
int inserir_inicio(Lista *lista, int valor) {
    Nodo *novo = criar_nodo(valor);
    if (!novo) return 0;

    if (esta_vazia(lista)) {
        lista->inicio = novo;
        lista->fim = novo;
    } else {
        novo->proximo = lista->inicio;
        lista->inicio->anterior = novo;
        lista->inicio = novo;
    }
    lista->tamanho++;
    return 1;
}

// Ex 4: Insercaoo no Fim
int inserir_fim(Lista *lista, int valor) {
    Nodo *novo = criar_nodo(valor);
    if (!novo) return 0;

    if (esta_vazia(lista)) {
        lista->inicio = novo;
        lista->fim = novo;
    } else {
        novo->anterior = lista->fim;
        lista->fim->proximo = novo;
        lista->fim = novo;
    }
    lista->tamanho++;
    return 1;
}

// Ex 5: Impressao Bidirecional
void imprimir_inicio_fim(Lista *lista) {
    Nodo *atual = lista->inicio;
    printf("Inicio para fim: ");
    while (atual) {
        printf("%d ", atual->valor);
        atual = atual->proximo;
    }
    printf("\n");
}

void imprimir_fim_inicio(Lista *lista) {
    Nodo *atual = lista->fim;
    printf("Fim para inicio: ");
    while (atual) {
        printf("%d ", atual->valor);
        atual = atual->anterior;
    }
    printf("\n");
}

void destruir_lista(Lista *lista) {
    Nodo *atual = lista->inicio;
    while (atual) {
        Nodo *temp = atual->proximo;
        free(atual);
        atual = temp;
    }
    free(lista);
}

// Exercício 8: Busca por valor
Nodo* buscar(Lista *lista, int valor) {
    Nodo *atual = lista->inicio;
    while (atual != NULL) {
        if (atual->valor == valor) return atual;
        atual = atual->proximo;
    }
    return NULL;
}

// Exercccio 9: Insercaoo em posicao especifica
int inserir_posicao(Lista *lista, int valor, int posicao) {
    if (posicao < 0 || posicao > lista->tamanho) return 0;
    if (posicao == 0) return inserir_inicio(lista, valor);
    if (posicao == lista->tamanho) return inserir_fim(lista, valor);

    Nodo *novo = criar_nodo(valor);
    if (!novo) return 0;

    Nodo *atual = lista->inicio;
    for (int i = 0; i < posicao; i++) {
        atual = atual->proximo;
    }

    novo->anterior = atual->anterior;
    novo->proximo = atual;
    atual->anterior->proximo = novo;
    atual->anterior = novo;

    lista->tamanho++;
    return 1;
}

// Exercício 10: Remocao por valor especifico
int remover_valor(Lista *lista, int valor) {
    Nodo *alvo = buscar(lista, valor);
    if (!alvo) return 0;

    if (alvo == lista->inicio) {
        int v; return remover_inicio(lista, &v);
    }
    if (alvo == lista->fim) {
        int v; return remover_fim(lista, &v);
    }

    alvo->anterior->proximo = alvo->proximo;
    alvo->proximo->anterior = alvo->anterior;

    free(alvo);
    lista->tamanho--;
    return 1;
}
