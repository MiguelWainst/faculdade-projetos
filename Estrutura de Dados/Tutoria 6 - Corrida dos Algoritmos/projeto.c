#include <stdio.h>
#include <string.h>

// Definindo a estrutura
struct Chamado {
    int codigo;
    char cliente[50];
    int prioridade;
};

// Variaveis globais para contar
int comparacoes = 0;
int trocas = 0;

// Funcao Bubble Sort
void bubbleSort(struct Chamado v[], int n) {
    int i, j;
    struct Chamado temp;
    
    comparacoes = 0; // zera antes de começar
    trocas = 0;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            comparacoes++; 
            if (v[j].codigo > v[j + 1].codigo) {
                // Troca os dados
                temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
                trocas++;
            }
        }
    }
}

void imprimir(struct Chamado v[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("ID: %d - Cliente: %s - Prioridade: %d\n", v[i].codigo, v[i].cliente, v[i].prioridade);
    }
}

int main() {
    int n = 10;
    
    // Criando o vetor com os dados desordenados
    struct Chamado lista[10] = {
        {105, "Prof Matheus", 3}, {102, "Maria", 5}, {108, "Ana", 1}, {101, "Beto", 2},
        {104, "Miguel", 4}, {107, "Duda", 3}, {103, "Erika", 5}, {110, "Lia", 2},
        {106, "Andrey", 1}, {109, "Emilly", 4}
    };

    printf("-Chamados antes de ordenar-\n");
    imprimir(lista, n);

    bubbleSort(lista, n);

    printf("\n-Chamados depois de ordenar-\n");
    imprimir(lista, n);

    printf("\nRESULTADOS:\n");
    printf("Comparacoes: %d\n", comparacoes);
    printf("Trocas: %d\n", trocas);

    return 0;
}
