#ifndef ESTRUTURA_H
#define ESTRUTURA_H

#include "requisicao.h"

typedef struct no {

    Requisicao req;

    struct no *next;
    struct no *previous;

} No;

typedef struct {

    No *head;
    No *tail;

    int size;

} Lista;


// Funções

Lista* criarLista();

int inserir_emergencia(Lista *l, Requisicao r);
int inserir_triagem(Lista *l, Requisicao r);

int atender_paciente(Lista *l, Requisicao *r);

int remover_paciente_id(Lista *l, int id);

void imprimir_auditoria(Lista *l);

int tamanho(Lista *l);

void liberarLista(Lista *l);

#endif
