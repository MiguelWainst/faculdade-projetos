void limpar_pilha(No** topo) {
    if (*topo == NULL) {
        printf("Pilha vazia, não tem nada pra limpar.\n");
        return;
    }

    int cont = 0;
    No* atual = *topo;

    while (atual != NULL) {
        No* prox = atual->proximo;   // salvo o próximo antes de apagar
        free(atual);                 // libero o nó atual
        atual = prox;                // vou pro próximo
        cont++;
    }

    *topo = NULL;   // a pilha agora está vazia

    printf("Pilha totalmente limpa!\n");
    printf("Foram liberados %d nós\n", cont);
    printf("Memória liberada: %d bytes\n", cont * sizeof(No));
}
