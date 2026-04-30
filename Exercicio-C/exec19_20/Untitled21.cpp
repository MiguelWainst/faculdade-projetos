#ifndef PONTO_H
#define PONTO_H

typedef struct ponto Ponto;

Ponto *criar(float x, float y);
float distancia(Ponto *p1, Ponto *p2);
void destruir(Ponto *p);

#endif

