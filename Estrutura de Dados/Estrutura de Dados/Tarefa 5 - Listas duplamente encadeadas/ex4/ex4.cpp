novo->next = atual->next;
novo->previous = atual;

atual->next->previous = novo;
atual->next = novo;
