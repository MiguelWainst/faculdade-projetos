#include <stdio.h>
#include "estrutura.h"
#include "requisicao.h"

int main() {

    printf("Sistema de Triagem Hospitalar\n\n");

    Lista *lista = criarLista();

    Requisicao p;

    criarRequisicao(&p, "Ana Silva", 101, "EXAME1");
    inserir_triagem(lista, p);

    criarRequisicao(&p, "Pedro Santos", 102, "CONSULTA");
    inserir_triagem(lista, p);

    criarRequisicao(&p, "Maria Oliveira", 103, "EXAME2");
    inserir_triagem(lista, p);

    criarRequisicao(&p, "Carlos Souza", 999, "URGENTE");
    inserir_emergencia(lista, p);

    printf("\nTamanho atual: %d\n", tamanho(lista));

    imprimir_auditoria(lista);

    printf("\nRemovendo paciente codigo 102...\n");

    remover_paciente_id(lista, 102);

    imprimir_auditoria(lista);

    printf("\nAtendendo pacientes...\n");

    Requisicao atendido;

    while(tamanho(lista) > 0) {

        atender_paciente(lista, &atendido);

        imprimirRequisicao(atendido);
    }

    liberarLista(lista);

    return 0;
}
