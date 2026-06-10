#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo {
    int valor;
    struct Nodo *proximo;
} Nodo;

typedef struct {
    Nodo *inicio;
    Nodo *fim;
    int tamanho;
} Fila;

void inicializar (Fila *f) {
    f->inicio = NULL;
    f->fim = NULL;
    f->tamanho = 0;
}

int enfileirar (Fila *f, int valor) {
    Nodo *novo = (Nodo *) malloc(sizeof(Nodo)); // Reserva espaço
    
    if (novo == NULL) {
        return -1;
    }

    novo->valor = valor;
    novo->proximo = NULL;

    if (f->fim == NULL) {
        f->inicio = novo;
        f->fim = novo;
    }
    else {
        f->fim->proximo = novo;
        f->fim = novo;
    }

}

int desenfileirar (Fila *f) {
    Nodo *antigo_inicio;

    if (f->inicio == NULL) {
        return 0;
    }

    antigo_inicio = f->inicio;
    f->inicio = antigo_inicio->proximo;

    if(f->inicio == NULL) {
        f->fim = NULL;
    }

    free(antigo_inicio);
    f->tamanho--;
}

void imprimir(Fila *f) {
	Nodo *atual = f->inicio;
	
	printf("Fila:\n");
	
	while(atual != NULL) {
		printf("%d ", atual->valor);
		atual = atual->proximo;
	}
	
	printf("\n");
}

void destruir (Fila *f) {
	while (desenfileirar(f));
}

int main() {
    
    Fila fila;
    
    inicializar(&fila);
    
    enfileirar(&fila, 10);
	enfileirar(&fila, 20);
	enfileirar(&fila, 30);
	enfileirar(&fila, 40);
	
	imprimir(&fila);
	
	desenfileirar(&fila);
	
	imprimir(&fila);
	    
    return 0;
}
