#include "lista.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/* Definicion de funciones*/
bool prueba_lista_vacia(void);

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

void pruebas_lista_alumno(){
  print_test("Prueba lista vacia", prueba_lista_vacia());

}

bool prueba_lista_vacia(){
  int fallas = 0;
  lista_t *lista = lista_crear();
  fallas += !(lista_esta_vacia(lista));
  lista_destruir(lista, NULL);
  if(fallas==0){
    return true;
  }
  return false;
}
