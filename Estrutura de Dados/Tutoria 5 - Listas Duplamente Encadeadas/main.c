#include "lista.h"

int main() {
    Lista *L = criar_lista();

    inserir_fim(L, 10);
    inserir_fim(L, 20);
    inserir_fim(L, 40);
    
    // Testando Exercccio 9 (Inserir 30 na posicao 2)
    inserir_posicao(L, 30, 2); 

    printf("Lista completa (Ex 1-9):\n");
    imprimir_inicio_fim(L); // Deve mostrar: 10 20 30 40

    // Testando Exercicio 10 (Remover o 20)
    remover_valor(L, 20);
    printf("\nApos remover o 20 (Ex 10):\n");
    imprimir_inicio_fim(L); // Deve mostrar: 10 30 40

    destruir_lista(L);
    return 0;
}