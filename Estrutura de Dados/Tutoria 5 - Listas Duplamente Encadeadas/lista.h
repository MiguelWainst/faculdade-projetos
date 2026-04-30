#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>

// Exercicio 1: Estrutura do Nodo Duplo
typedef struct Nodo {
    int valor;
    struct Nodo *anterior;
    struct Nodo *proximo;
} Nodo;

// Exercicio 2: Estrutura da Lista Duplamente Encadeada
typedef struct {
    Nodo *inicio;
    Nodo *fim;
    int tamanho;
} Lista;

// Funcoes do Nodo (Ex 1)
Nodo* criar_nodo(int valor);
void destruir_nodo(Nodo *nodo);

// Funcoes da Lista (Ex 2)
Lista* criar_lista();
int esta_vazia(Lista *lista);
void destruir_lista(Lista *lista);

// Funcoes de Insercaoo e Impressao (Ex 3, 4 e 5)
int inserir_inicio(Lista *lista, int valor);
int inserir_fim(Lista *lista, int valor);
void imprimir_inicio_fim(Lista *lista);
void imprimir_fim_inicio(Lista *lista);

Nodo* buscar(Lista *lista, int valor);
int inserir_posicao(Lista *lista, int valor, int posicao);
int remover_valor(Lista *lista, int valor);

#endif
