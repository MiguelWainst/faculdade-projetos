#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ponto.h"

struct ponto {
    float x;
    float y;
};

Ponto *criar(float x, float y) {
    Ponto *p;

    p = (Ponto *) malloc(sizeof(Ponto));

    if (p == NULL) {
        return NULL;
    }

    p->x = x;
    p->y = y;

    return p;
}

float distancia(Ponto *p1, Ponto *p2) {
    float dx;
    float dy;
    float d;

    dx = p1->x - p2->x;
    dy = p1->y - p2->y;

    d = sqrt(dx * dx + dy * dy);

    return d;
}

void destruir(Ponto *p) {
    free(p);
}

