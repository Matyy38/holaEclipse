#include <stdio.h>
#include <string.h>

/*
 * Imprime espejado el texto recibido por linea de comandos.
 * Ejemplo: ./prog habemus papa  ->  apap sumebah
 */
int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Uso: %s <texto>\n", argv[0]);
        return 1;
    }

    /* Recorro los argumentos del ultimo al primero */
    for (int i = argc - 1; i >= 1; i--) {
        /* Y cada argumento lo recorro del ultimo caracter al primero */
        for (int j = (int)strlen(argv[i]) - 1; j >= 0; j--) {
            putchar(argv[i][j]);
        }
        if (i > 1) {
            putchar(' ');   /* espacio entre palabras */
        }
    }
    putchar('\n');

    return 0;
}
