#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Usuario {
    char *nome;
};

int main(void) {
    struct Usuario *usuario;
    char buffer[100];

    usuario = (struct Usuario *) malloc(sizeof(struct Usuario));
    if (usuario == NULL) {
        printf("Erro ao alocar memoria para o usuario.\n");
        return 1;
    }

    printf("Digite o nome: ");
    fgets(buffer, sizeof(buffer), stdin);

    buffer[strcspn(buffer, "\n")] = '\0';

    usuario->nome = (char *) malloc((strlen(buffer) + 1) * sizeof(char));
    if (usuario->nome == NULL) {
        printf("Erro ao alocar memoria para o nome.\n");
        free(usuario);
        return 1;
    }

    strcpy(usuario->nome, buffer);

    printf("Nome armazenado: %s\n", usuario->nome);

    free(usuario->nome);
    free(usuario);

    return 0;
}
