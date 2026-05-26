#include <string.h>

typedef struct {
    int id;
    char nome[100];
    float preco;
    int quantidade;
} Produto;

void reset_estoque(Produto *p) {
    if (p == NULL) return;

    p->id = 0;
    strcpy(p->nome, "");
    p->preco = 0.0f;
    p->quantidade = 0;
}
