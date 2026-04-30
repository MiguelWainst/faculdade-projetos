#include <stdio.h>
#include "pilha.h"

int main() {
    
    printf("=== Editor de Texto - Sistema de Desfazer ===\n\n");
    
    Pilha *minhaPilha = criarPilha();
    
    // Simulando ações do usuário
    push(minhaPilha, "Digitei: Ola mundo");
    push(minhaPilha, "Apaguei a palavra mundo");
    push(minhaPilha, "Digitei: Bom dia turma");
    push(minhaPilha, "Adicionei ponto de exclamacao!");
    
    printf("Algumas acoes foram feitas...\n\n");
    
    char acaoDesfeita[100];
    
    printf("Desfazendo as acoes:\n");
    
    while(!estaVazia(minhaPilha)) {
        pop(minhaPilha, acaoDesfeita);
        printf("Desfeito -> %s\n", acaoDesfeita);
    }
    
    // Testando quando a pilha está vazia
    printf("\nTentando desfazer mais uma vez:\n");
    pop(minhaPilha, acaoDesfeita);
    
    liberar(minhaPilha);
    
    printf("\nPrograma finalizado.\n");
    
    return 0;
}
