#include <stdio.h>
#include <string.h>

typedef struct {
    int codigo;
    char nome[50];
    char telefone[15];
} Cliente;

void ordenarPorCodigo(Cliente v[], int n) {
    int i, j, min;
    Cliente temp;

    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            if (v[j].codigo < v[min].codigo) {
                min = j;
            }
        }
        if (min != i) {
            temp = v[i];
            v[i] = v[min];
            v[min] = temp;
        }
    }
}

int main() {
    Cliente clientes[10] = {
        {88, "Ricardo", "11-9888"},
        {12, "Fernanda", "21-9122"},
        {45, "Alvaro", "31-9455"},
        {2,  "Beatriz", "11-9022"},
        {30, "Caio", "41-9300"},
        {5,  "Daniela", "51-9055"},
        {67, "Eduardo", "61-9677"},
        {19, "Gisele", "71-9199"},
        {99, "Hugo", "81-9999"},
        {23, "Iara", "91-9233"}
    };

    printf("--- Vetor Original Desordenado-\n");
    for(int i = 0; i < 10; i++) {
        printf("Cod: %02d | Nome: %-10s | Tel: %s\n", clientes[i].codigo, clientes[i].nome, clientes[i].telefone);
    }

    ordenarPorCodigo(clientes, 10);

    printf("\n-Vetor Ordenado Crescente por Codigo-\n");
    for(int i = 0; i < 10; i++) {
        printf("Cod: %02d | Nome: %-10s | Tel: %s\n", clientes[i].codigo, clientes[i].nome, clientes[i].telefone);
    }

    return 0;
}
