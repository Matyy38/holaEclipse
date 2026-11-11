#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Copia 'tam' bytes apuntados por 'dato' a un bloque nuevo en el heap.
 *
 * Devuelve: puntero al bloque nuevo (lo debe liberar quien llama con free),
 *           o NULL si 'dato' es NULL, si 'tam' es 0 o si malloc falla.
 */
void *copiar_a_heap(const void *dato, size_t tam)
{
    if (dato == NULL || tam == 0) {
        return NULL;
    }

    void *copia = malloc(tam);
    if (copia == NULL) {
        return NULL;
    }

    memcpy(copia, dato, tam);
    return copia;
}

/* ---- Ejemplo de uso ---- */

typedef struct {
    int legajo;
    double promedio;
    char nombre[32];
} alumno_t;

int main(void)
{
    /* 1) Un int */
    int x = 42;
    int *px = copiar_a_heap(&x, sizeof x);
    if (px == NULL) {
        fprintf(stderr, "Error: no se pudo copiar el int\n");
        return EXIT_FAILURE;
    }
    printf("int copiado: %d\n", *px);

    /* 2) Un struct */
    alumno_t a = { 12345, 8.75, "Matias" };
    alumno_t *pa = copiar_a_heap(&a, sizeof a);
    if (pa == NULL) {
        fprintf(stderr, "Error: no se pudo copiar el struct\n");
        free(px);
        return EXIT_FAILURE;
    }
    printf("struct copiado: %d %.2f %s\n", pa->legajo, pa->promedio, pa->nombre);

    /* 3) Un arreglo */
    double v[] = { 1.5, 2.5, 3.5 };
    size_t n = sizeof v / sizeof v[0];
    double *pv = copiar_a_heap(v, sizeof v);
    if (pv == NULL) {
        fprintf(stderr, "Error: no se pudo copiar el arreglo\n");
        free(pa);
        free(px);
        return EXIT_FAILURE;
    }
    printf("arreglo copiado:");
    for (size_t i = 0; i < n; i++) {
        printf(" %.1f", pv[i]);
    }
    putchar('\n');

    /* La copia es independiente del original */
    x = 0;
    printf("original modificado: x = %d, copia = %d\n", x, *px);

    free(pv);
    free(pa);
    free(px);
    pv = NULL;
    pa = NULL;
    px = NULL;

    return EXIT_SUCCESS;
}
