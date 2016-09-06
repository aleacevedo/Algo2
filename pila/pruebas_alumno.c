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

void prueba_pila_un_elemento(){
  int num0=0;
  int *pun0=&num0;
  printf("INICIO PRUEBAS CON UN ELEMENTO\n");
  pila_t *pila1 = pila_crear();
  print_test("Crear pila1", pila1 != NULL);
  print_test("Apilar el primer", pila_apilar(pila1, pun0)==true);
  print_test("Ver tope del primero", pila_ver_tope(pila1)==pun0);
  print_test("Desapilar el primero", pila_desapilar(pila1)==pun0);
  print_test("Desapilar vacio", pila_desapilar(pila1)==NULL);
  pila_destruir(pila1);

}
void prueba_pila_ocho_elementos(){
  int num[8];
  int *punt[8];
  pila_t *pila = pila_crear();
  printf("INICIO PRUEBAS CON OCHO ELEMENTOS\n");
  for(int x = 0; x<8; x++){
    num[x] = x;
    punt[x] = &num[x];
    print_test("Apilar", pila_apilar(pila, punt[x])==true);
  }
  for(int x = 7; x>=0; x--){
    int *dev;
    dev = pila_ver_tope(pila);
    print_test("Ver tope", *dev ==x);
    print_test("Desapilar", pila_desapilar(pila)==punt[x]);
  }
  print_test("Desapilar vacio", pila_desapilar(pila)==NULL);
  pila_destruir(pila);
}

void prueba_pila_mil_elementos(){
  int num[1000];
  int *punt[1000];
  pila_t *pila = pila_crear();
  printf("INICIO PRUEBAS CON MIL ELEMENTOS\n");
  for(int x = 0; x<1000; x++){
    num[x] = x;
    punt[x] = &num[x];
    print_test("Apilar", pila_apilar(pila, punt[x])==true);
  }
  for(int x = 999; x>=0; x--){
    int *dev;
    dev = pila_ver_tope(pila);
    print_test("Ver tope", *dev ==x);
    print_test("Desapilar", pila_desapilar(pila)==punt[x]);
  }
  print_test("Desapilar vacio", pila_desapilar(pila)==NULL);
  pila_destruir(pila);
}

void prueba_pila_diezmil_elementos_intercalados(){
  int num[10000];
  int *punt[10000];
  pila_t *pila = pila_crear();
  printf("INICIO PRUEBAS CON MIL ELEMENTOS\n");
  for(int x = 0; x<5000; x++){
    num[x] = x;
    punt[x] = &num[x];
    print_test("Apilar", pila_apilar(pila, punt[x])==true);
  }
  for(int x = 4999; x>=2000; x--){
    int *dev;
    dev = pila_ver_tope(pila);
    print_test("Ver tope", *dev ==x);
    print_test("Desapilar", pila_desapilar(pila)==punt[x]);
  }
  for(int x = 2000; x<10000; x++){
    num[x] = x;
    punt[x] = &num[x];
    print_test("Apilar", pila_apilar(pila, punt[x])==true);
  }
  for(int x = 9999; x>=0; x--){
    int *dev;
    dev = pila_ver_tope(pila);
    print_test("Ver tope", *dev ==x);
    print_test("Desapilar", pila_desapilar(pila)==punt[x]);
  }
  print_test("Desapilar vacio", pila_desapilar(pila)==NULL);
  pila_destruir(pila);
}
