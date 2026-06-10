#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ESTRUTURA DA ÁRVORE
typedef struct No {
    int valor;
    struct No *esq;
    struct No *dir;
} No;

No* criarNo(int valor) {
    No* novo = (No*)malloc(sizeof(No));
    if (novo != NULL) {
        novo->valor = valor;
        novo->esq = NULL;
        novo->dir = NULL;
    }
    return novo;
}

No* inserirNaArvore(No* raiz, int valor) {
    if (raiz == NULL) return criarNo(valor);
    if (valor < raiz->valor) raiz->esq = inserirNaArvore(raiz->esq, valor);
    else raiz->dir = inserirNaArvore(raiz->dir, valor);
    return raiz;
}

int buscarNaArvore(No* raiz, int valor, int *comparacoes) {
    if (raiz == NULL) {
        (*comparacoes)++;
        return 0;
    }
    (*comparacoes)++;
    if (raiz->valor == valor) return 1;
    if (valor < raiz->valor) return buscarNaArvore(raiz->esq, valor, comparacoes);
    else return buscarNaArvore(raiz->dir, valor, comparacoes);
}

int calcularAltura(No* raiz) {
    if (raiz == NULL) return -1;
    int altEsq = calcularAltura(raiz->esq);
    int altDir = calcularAltura(raiz->dir);
    return (altEsq > altDir ? altEsq : altDir) + 1;
}

void liberarArvore(No* raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esq);
        liberarArvore(raiz->dir);
        free(raiz);
    }
}

// ALGORITMOS DE BUSCA EM VETOR
int buscaSequencial(int vetor[], int tamanho, int valor, int *comparacoes) {
    for (int i = 0; i < tamanho; i++) {
        (*comparacoes)++;
        if (vetor[i] == valor) return i;
    }
    return -1;
}

int buscaBinaria(int vetor[], int tamanho, int valor, int *comparacoes) {
    int inicio = 0, fim = tamanho - 1;
    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        (*comparacoes)++;
        if (vetor[meio] == valor) return meio;
        if (vetor[meio] < valor) inicio = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

int compararInteiros(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void embaralhar(int vetor[], int tamanho) {
    for (int i = tamanho - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = vetor[i];
        vetor[i] = vetor[j];
        vetor[j] = temp;
    }
}

// EXECUTOR DOS EXPERIMENTOS
void executarExperimento(int tamanho, int ordenado) {
    printf("\n=========================================\n");
    printf("EXPERIMENTO: N = %d | TIPO: %s\n", tamanho, ordenado ? "ORDENADO" : "EMBARALHADO");
    printf("=========================================\n");
    
    int *vetor = (int*)malloc(tamanho * sizeof(int));
    if (!vetor) return;

    for (int i = 0; i < tamanho; i++) {
        vetor[i] = i * 2; 
    }

    if (!ordenado) {
        embaralhar(vetor, tamanho);
    }

    No *raiz = NULL;
    for (int i = 0; i < tamanho; i++) {
        raiz = inserirNaArvore(raiz, vetor[i]);
    }

    int altura = calcularAltura(raiz);
    printf("Altura da Arvore: %d\n", altura);

    if (!ordenado) {
        qsort(vetor, tamanho, sizeof(int), compararInteiros);
    }

    int alvos[4] = { 2, vetor[tamanho/2], vetor[tamanho-1], -5 };
    const char *nomes[4] = { "Inicio", "Meio", "Fim", "Inexistente" };

    for (int k = 0; k < 4; k++) {
        int alvo = alvos[k];
        int compSeq = 0, compBin = 0, compArv = 0;
        clock_t inc, fim;
        double tSeq, tBin, tArv;

        printf("\nBusca por %d (%s):\n", alvo, nomes[k]);

        inc = clock();
        buscaSequencial(vetor, tamanho, alvo, &compSeq);
        fim = clock();
        tSeq = (double)(fim - inc) / CLOCKS_PER_SEC;

        inc = clock();
        buscaBinaria(vetor, tamanho, alvo, &compBin);
        fim = clock();
        tBin = (double)(fim - inc) / CLOCKS_PER_SEC;

        inc = clock();
        buscarNaArvore(raiz, alvo, &compArv);
        fim = clock();
        tArv = (double)(fim - inc) / CLOCKS_PER_SEC;

        printf("  Busca Sequencial -> Comparacoes: %d | Tempo: %f s\n", compSeq, tSeq);
        printf("  Busca Binaria    -> Comparacoes: %d | Tempo: %f s\n", compBin, tBin);
        printf("  Busca na Arvore  -> Comparacoes: %d | Tempo: %f s\n", compArv, tArv);
    }

    liberarArvore(raiz);
    free(vetor);
}

int main() {
    srand(42); 

    executarExperimento(100, 1); // 100 Ordenado
    executarExperimento(100, 0); // 100 Embaralhado
    executarExperimento(1000, 1); // 1.000 Ordenado
    executarExperimento(1000, 0); // 1.000 Embaralhado

    return 0;
}