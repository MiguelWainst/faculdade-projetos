#include "requisicao.h"
#include <string.h>
#include <stdio.h>

void criarRequisicao(Requisicao *r, char nome[], int cod, char proc[]) {

    strcpy(r->nome, nome);

    r->codigo = cod;

    strcpy(r->procedimento, proc);
}


void imprimirRequisicao(Requisicao r) {

    printf("Paciente: %s | Codigo: %d | Procedimento: %s\n",
           r.nome,
           r.codigo,
           r.procedimento);
}
