#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>


/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

void pruebas_pila_alumno() {
    pila_t* ejemplo = NULL;

    print_test("Puntero inicializado a NULL", ejemplo == NULL);
}

void pruebas_pila_un_elemento(){
  int num0=0;
  int *pun0=&num0;

  printf("INICIO PRUEBAS CON ALGUNOS ELEMENTOS\n");
  pila_t *pila1 = pila_crear();
  print_test("Crear pila1", pila1 != NULL)

  print_test("Apilar el primer", pila_apilar(pila1, pun0)==true);
  print_test("Ver tope del primero", pila_ver_tope(pila1)==pun0);
  print_test("Desapilar el primero", pila_desapilar(pila1)==pun0);
  print_test("Desapilar vacio", pila_desapilar(pila1)==NULL);

}
