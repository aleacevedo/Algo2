#include "cola.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

 void pruebas_cola_alumno(){

   printf("/////////////////////////////////////////////////////////\n");
   printf("///////////////////Prueba un elemento////////////////////\n");
   printf("/////////////////////////////////////////////////////////\n");
   int n=5;
   cola_t *cola1 = cola_crear();
   print_test("Se creo la cola1", cola1!=NULL);
   print_test("La cola1 esta vacia", cola_esta_vacia(cola1));
   print_test("Encolo un numero", cola_encolar(cola1, &n));
   print_test("La cola1 no esta vacia", !cola_esta_vacia(cola1));
   print_test("Veo el numero", *(int*)cola_ver_primero(cola1)==n);
   print_test("Desencolo el numero", *(int*)cola_desencolar(cola1)==n);
   print_test("La cola1 esta vacia", cola_esta_vacia(cola1));
   cola_destruir(cola1, NULL);
   printf("/////////////////////////////////////////////////////////\n");
   printf("////////////////////////FIN//////////////////////////////\n");
   printf("/////////////////////////////////////////////////////////\n");
   printf("\n");
   printf("/////////////////////////////////////////////////////////\n");
   printf("///////////////////Prueba un puntero/////////////////////\n");
   printf("/////////////////////////////////////////////////////////\n");
   int *pun = &n;
   cola_t *cola2 = cola_crear();
   print_test("Se creo la cola2", cola2!=NULL);
   print_test("La cola2 esta vacia", cola_esta_vacia(cola2));
   print_test("Encolo un numero", cola_encolar(cola2, pun));
   print_test("La cola2 no esta vacia", !cola_esta_vacia(cola2));
   print_test("Veo el numero", cola_ver_primero(cola2)==pun);
   print_test("Desencolo el numero", cola_desencolar(cola2)==pun);
   print_test("La cola2 esta vacia", cola_esta_vacia(cola2));
   cola_destruir(cola2, NULL);
   printf("/////////////////////////////////////////////////////////\n");
   printf("////////////////////////FIN//////////////////////////////\n");
   printf("/////////////////////////////////////////////////////////\n");
   printf("\n");
   printf("/////////////////////////////////////////////////////////\n");
   printf("///////////////////Prueba un heap/////////////////////\n");
   printf("/////////////////////////////////////////////////////////\n");
   int *heap = malloc(sizeof(int));
   *heap = n;
   cola_t *cola3 = cola_crear();
   print_test("Se creo la cola3", cola3!=NULL);
   print_test("La cola3 esta vacia", cola_esta_vacia(cola3));
   print_test("Encolo un numero", cola_encolar(cola3, heap));
   print_test("La cola3 no esta vacia", !cola_esta_vacia(cola3));
   print_test("Veo el numero", cola_ver_primero(cola3)==heap);
   //print_test("Desencolo el numero", cola_desencolar(cola3)==heap);
   //print_test("La cola3 esta vacia", cola_esta_vacia(cola3));
   cola_destruir(cola3, free);
   printf("/////////////////////////////////////////////////////////\n");
   printf("////////////////////////FIN//////////////////////////////\n");
   printf("/////////////////////////////////////////////////////////\n");
 }
