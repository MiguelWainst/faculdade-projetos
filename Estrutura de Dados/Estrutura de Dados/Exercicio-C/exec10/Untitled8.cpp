#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Endereco {
    char rua[100];
    int numero;
};

struct Pessoa {
    char nome[100];
    struct Endereco *endereco;
};

int main(void) {
    struct Pessoa *pessoa;

    pessoa = (struct Pessoa *) malloc(sizeof(struct Pessoa));
    if (pessoa == NULL) {
        printf("Erro ao alocar memoria para pessoa.\n");
        return 1;
    }

    pessoa->endereco = (struct Endereco *) malloc(sizeof(struct Endereco));
    if (pessoa->endereco == NULL) {
        printf("Erro ao alocar memoria para endereco.\n");
        free(pessoa);
        return 1;
    }

    strcpy(pessoa->nome, "Carlos");
    strcpy(pessoa->endereco->rua, "Rua das Flores");
    pessoa->endereco->numero = 123;

    printf("Nome: %s\n", pessoa->nome);
    printf("Rua: %s\n", pessoa->endereco->rua);
    printf("Numero: %d\n", pessoa->endereco->numero);

    free(pessoa->endereco);
    free(pessoa);

    return 0;
}
