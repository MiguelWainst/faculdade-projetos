#include <stdio.h>
#include <stdlib.h>

int main() {
    float *p;

    p = (float *) malloc(sizeof(float));

    if (p == NULL) {
        printf("erro de alocacao");
        return 1;
    }

    scanf("%f", p);

    printf("%.2f\n", *p);

    free(p);

    return 0;
}
