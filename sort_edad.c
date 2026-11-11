#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/* Indices del arreglo de fecha */
enum { DIA = 0, MES = 1, ANIO = 2 };

/* a) Persona: nombre y fecha de nacimiento [dia, mes, anio] */
typedef struct {
    char nombre[20];
    int16_t nacimiento[3];   /* entero signado de exactamente 2 bytes */
} persona_t;

/*
 * Comparador para qsort: del mas joven al mas mayor.
 * Mas joven = nacio DESPUES, asi que va primero la fecha mas grande.
 */
static int cmp_edad(const void *a, const void *b)
{
    const persona_t *pa = a;
    const persona_t *pb = b;

    /* 1) Comparo el anio */
    if (pa->nacimiento[ANIO] > pb->nacimiento[ANIO]) return -1;  /* a es mas joven */
    if (pa->nacimiento[ANIO] < pb->nacimiento[ANIO]) return  1;  /* a es mas mayor */

    /* 2) Mismo anio: comparo el mes */
    if (pa->nacimiento[MES] > pb->nacimiento[MES]) return -1;
    if (pa->nacimiento[MES] < pb->nacimiento[MES]) return  1;

    /* 3) Mismo mes: comparo el dia */
    if (pa->nacimiento[DIA] > pb->nacimiento[DIA]) return -1;
    if (pa->nacimiento[DIA] < pb->nacimiento[DIA]) return  1;

    /* Misma fecha: misma edad */
    return 0;
}

/* b) Ordena 'len' personas del mas joven al mas mayor */
void sort_edad(persona_t personas[], size_t len)
{
    if (personas == NULL || len < 2) {
        return;
    }
    qsort(personas, len, sizeof personas[0], cmp_edad);
}

/* ---- Ejemplo de uso ---- */
int main(void)
{
    persona_t gente[] = {
        { "Ana",    { 15,  3, 1990 } },
        { "Bruno",  {  2, 11, 2001 } },
        { "Carla",  { 30,  3, 1990 } },
        { "Diego",  {  1,  1, 1975 } },
        { "Elena",  { 15,  7, 2001 } },
    };
    size_t len = sizeof gente / sizeof gente[0];

    sort_edad(gente, len);

    for (size_t i = 0; i < len; i++) {
        printf("%-6s %02d/%02d/%04d\n", gente[i].nombre,
               gente[i].nacimiento[DIA],
               gente[i].nacimiento[MES],
               gente[i].nacimiento[ANIO]);
    }
    return EXIT_SUCCESS;
}
