#include "estrutura.h"
#include <stdlib.h>
#include <stdio.h>


Lista* criarLista() {

    Lista *l = (Lista*) malloc(sizeof(Lista));

    if(l == NULL) {
        printf("Erro ao criar lista!\n");
        return NULL;
    }

    l->head = NULL;
    l->tail = NULL;
    l->size = 0;

    return l;
}


int inserir_emergencia(Lista *l, Requisicao r) {

    No *novo = (No*) malloc(sizeof(No));

    if(novo == NULL) {
        printf("Sem memoria!\n");
        return 0;
    }

    novo->req = r;

    novo->previous = NULL;
    novo->next = l->head;

    if(l->head == NULL) {

        l->head = novo;
        l->tail = novo;

    }
    else {

        l->head->previous = novo;
        l->head = novo;

    }

    l->size++;

    return 1;
}


int inserir_triagem(Lista *l, Requisicao r) {

    No *novo = (No*) malloc(sizeof(No));

    if(novo == NULL) {
        printf("Sem memoria!\n");
        return 0;
    }

    novo->req = r;

    novo->next = NULL;
    novo->previous = l->tail;

    if(l->tail == NULL) {

        l->head = novo;
        l->tail = novo;

    }
    else {

        l->tail->next = novo;
        l->tail = novo;

    }

    l->size++;

    return 1;
}


int atender_paciente(Lista *l, Requisicao *r) {

    if(l->head == NULL)
        return 0;

    No *aux = l->head;

    *r = aux->req;

    l->head = aux->next;

    if(l->head == NULL)
        l->tail = NULL;
    else
        l->head->previous = NULL;

    free(aux);

    l->size--;

    return 1;
}


int remover_paciente_id(Lista *l, int id) {

    No *atual = l->head;

    while(atual != NULL) {

        if(atual->req.codigo == id) {

            if(atual->previous != NULL)
                atual->previous->next = atual->next;
            else
                l->head = atual->next;

            if(atual->next != NULL)
                atual->next->previous = atual->previous;
            else
                l->tail = atual->previous;

            free(atual);

            l->size--;

            return 1;
        }

        atual = atual->next;
    }

    return 0;
}


void imprimir_auditoria(Lista *l) {

    No *atual;

    printf("\n--- INICIO -> FIM ---\n");

    atual = l->head;

    while(atual != NULL) {

        imprimirRequisicao(atual->req);

        atual = atual->next;
    }

    printf("\n--- FIM -> INICIO ---\n");

    atual = l->tail;

    while(atual != NULL) {

        imprimirRequisicao(atual->req);

        atual = atual->previous;
    }
}


int tamanho(Lista *l) {

    return l->size;
}


void liberarLista(Lista *l) {

    No *atual = l->head;

    while(atual != NULL) {

        No *temp = atual;

        atual = atual->next;

        free(temp);
    }

    free(l);
}
