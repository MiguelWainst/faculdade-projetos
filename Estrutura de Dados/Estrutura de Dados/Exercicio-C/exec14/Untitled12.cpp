#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int n, i;
    char buffer[100];
    char **cidades;

    printf("Quantas cidades deseja informar? ");
    scanf("%d", &n);
    getchar();

    if (n <= 0) {
        printf("Quantidade invalida.\n");
        return 1;
    }

    cidades = (char **) malloc(n * sizeof(char *));
    if (cidades == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        printf("Digite o nome da cidade %d: ", i + 1);
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        cidades[i] = (char *) malloc((strlen(buffer) + 1) * sizeof(char));
        if (cidades[i] == NULL) {
            printf("Erro ao alocar memoria para a cidade.\n");

            for (int j = 0; j < i; j++) {
                free(cidades[j]);
            }
            free(cidades);
            return 1;
        }

        strcpy(cidades[i], buffer);
    }

    printf("\nCidades informadas:\n");
    for (i = 0; i < n; i++) {
        printf("%s\n", cidades[i]);
    }

    for (i = 0; i < n; i++) {
        free(cidades[i]);
    }
    free(cidades);

    return 0;
}

