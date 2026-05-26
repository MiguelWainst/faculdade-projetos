int buscar_paciente_reverso(DList *list, int id_procurado) {
    Node *atual = list->tail;

    while (atual != NULL) {
        if (atual->id == id_procurado) {
            return 1;
        }
        atual = atual->previous;
    }

    return 0;
}
