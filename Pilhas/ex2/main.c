#include <stdio.h>
#include "pilha.h"

int main() {
    
    printf("Navegador Web - Historico de URLs\n\n");
    
    Pilha *historico = criarPilha();
    
    // Simulando navegação do usuário
    push(historico, "https://www.google.com");
    push(historico, "https://www.youtube.com");
    push(historico, "https://github.com");
    push(historico, "https://chatgpt.com");
    
    printf("URLs visitadas:\n");
    printf("4 paginas foram abertas.\n\n");
    
    char urlAtual[100];
    
    // Usando peek para ver a página atual sem sair dela
    printf("Pagina atual (sem sair dela):\n");
    if(peek(historico, urlAtual)) {
        printf("Voce esta em: %s\n\n", urlAtual);
    }
    
    // Desfazendo (voltando) uma página
    printf("Voltando para pagina anterior...\n");
    pop(historico, urlAtual);
    printf("Voltou para: %s\n\n", urlAtual);
    
    // Verificando novamente a página atual
    printf("Pagina atual agora:\n");
    if(peek(historico, urlAtual)) {
        printf("Voce esta em: %s\n", urlAtual);
    }
    
    // Tentando peek com pilha vazia
    printf("\nEsvaziando o historico...\n");
    while(!estaVazia(historico)) {
        pop(historico, urlAtual);
    }
    
    printf("\nTentando ver pagina atual com historico vazio:\n");
    peek(historico, urlAtual);
    
    liberar(historico);
    
    printf("\nFim do programa.\n");
    
    return 0;
}
