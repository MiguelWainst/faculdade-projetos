Node* atual = buscar_no(list, id);

if (atual == NULL) return;

if (atual->previous != NULL)
    atual->previous->next = atual->next;

if (atual->next != NULL)
    atual->next->previous = atual->previous;

if (atual == list->tail)
    list->tail = atual->previous;

list->size--;

// inserir no início (head)
atual->previous = NULL;
atual->next = list->head;

if (list->head != NULL)
    list->head->previous = atual;

list->head = atual;

list->size++;

