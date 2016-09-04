#include "pila.h"
#include "testing.h"
#include <stdio.h>

/* ******************************************************************
 *                        PROGRAMA PRINCIPAL
 * *****************************************************************/

int main(void)
{
    /* Ejecuta todas las pruebas unitarias. */
    printf("~~~ PRUEBAS ALUMNO ~~~\n");
    prueba_pila_alumno();
    prueba_pila_un_elemento();
    prueba_pila_ocho_elementos();
    prueba_pila_mil_elementos();
    return failure_count() > 0;
}
