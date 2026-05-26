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

void selectionSort(struct Chamado v[], int n) {
    int i, j, min;
    struct Chamado temp;
    comparacoes = 0; trocas = 0; // Reseta globais

    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            comparacoes++;
            if (v[j].codigo < v[min].codigo) {
                min = j;
            }
        }
        if (min != i) {
            temp = v[i];
            v[i] = v[min];
            v[min] = temp;
            trocas++;
        }
    }
}

void insertionSort(struct Chamado v[], int n) {
    int i, j;
    struct Chamado pivo;
    comparacoes = 0; trocas = 0;

    for (i = 1; i < n; i++) {
        pivo = v[i];
        j = i - 1;
        
        // Compara e move os elementos
        while (j >= 0 && v[j].codigo > pivo.codigo) {
            comparacoes++;
            v[j + 1] = v[j];
            j--;
            trocas++;
        }
        v[j + 1] = pivo;
        // A ultima comparacao que falha no while tambem conta
        if (j >= 0) comparacoes++; 
    }
}

void imprimir(struct Chamado v[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("ID: %d - Cliente: %s - Prioridade: %d\n", v[i].codigo, v[i].cliente, v[i].prioridade);
    }
}

// Cenário 1: Dados Aleatórios
void gerarAleatorio(struct Chamado v[]) {
    int i; // Declarando o i aqui fora para não dar erro
    struct Chamado dados[10] = {
        {105, "Prof Matheus", 3}, {102, "Maria", 5}, {108, "Ana", 1}, {101, "Beto", 2},
        {104, "Miguel", 4}, {107, "Duda", 3}, {103, "Erika", 5}, {110, "Lia", 2},
        {106, "Andrey", 1}, {109, "Emilly", 4}
    };
    for (i = 0; i < 10; i++) {
        v[i] = dados[i];
    }
}

// Cenário 2: Já Ordenado
void gerarOrdenado(struct Chamado v[]) {
    int i; // Declarando o i aqui fora
    for (i = 0; i < 10; i++) {
        v[i].codigo = 101 + i;
        strcpy(v[i].cliente, "Cliente");
        v[i].prioridade = 1;
    }
}

// Cenário 3: Ordem Inversa
void gerarInverso(struct Chamado v[]) {
    int i; // Declarando o i aqui fora
    for (i = 0; i < 10; i++) {
        v[i].codigo = 110 - i;
        strcpy(v[i].cliente, "Cliente");
        v[i].prioridade = 1;
    }
}

int main() {
    struct Chamado lista[10];
    int n = 10;

    // Aleatório
    printf("Teste 1: Aleatório\n");

    gerarAleatorio(lista);
    bubbleSort(lista, n);
    printf("Bubble Sort    -> Comp: %d | Trocas: %d\n", comparacoes, trocas);

    gerarAleatorio(lista);
    selectionSort(lista, n);
    printf("Selection Sort -> Comp: %d | Trocas: %d\n", comparacoes, trocas);

    gerarAleatorio(lista);
    insertionSort(lista, n);
    printf("Insertion Sort -> Comp: %d | Trocas: %d\n\n", comparacoes, trocas);


    // já prdenado
    printf("Teste 2: já ordenado\n");

    gerarOrdenado(lista);
    bubbleSort(lista, n);
    printf("Bubble Sort    -> Comp: %d | Trocas: %d\n", comparacoes, trocas);

    gerarOrdenado(lista);
    selectionSort(lista, n);
    printf("Selection Sort -> Comp: %d | Trocas: %d\n", comparacoes, trocas);

    gerarOrdenado(lista);
    insertionSort(lista, n);
    printf("Insertion Sort -> Comp: %d | Trocas: %d\n\n", comparacoes, trocas);


    // cenario inverso
    printf("Ordem Inversa\n");

    gerarInverso(lista);
    bubbleSort(lista, n);
    printf("Bubble Sort    -> Comp: %d | Trocas: %d\n", comparacoes, trocas);

    gerarInverso(lista);
    selectionSort(lista, n);
    printf("Selection Sort -> Comp: %d | Trocas: %d\n", comparacoes, trocas);

    gerarInverso(lista);
    insertionSort(lista, n);
    printf("Insertion Sort -> Comp: %d | Trocas: %d\n", comparacoes, trocas);

    return 0;
}
