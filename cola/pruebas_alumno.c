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
   printf("///////////////////Prueba cola///////////////////////////\n");
   printf("/////////////////////////////////////////////////////////\n");
   cola_t *cola0 = cola_crear();
   print_test("Se creo la cola1", cola0!=NULL);
   print_test("La cola1 esta vacia", cola_esta_vacia(cola0));
   cola_destruir(cola0, NULL);
   printf("/////////////////////////////////////////////////////////\n");
   printf("////////////////////////FIN//////////////////////////////\n");
   printf("/////////////////////////////////////////////////////////\n");
   printf("\n");
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
   printf("\n");
   printf("/////////////////////////////////////////////////////////\n");
   printf("///////////////////Prueba 300 numeros////////////////////\n");
   printf("/////////////////////////////////////////////////////////\n");
   int num[300];
   cola_t *cola300 = cola_crear();
   print_test("Se creo la cola3", cola3!=NULL);
   print_test("La cola3 esta vacia", cola_esta_vacia(cola300));
   for(int i = 0; i<300; i++){
     num[i]=i;
     print_test("Encolo un numero", cola_encolar(cola300, &num[i]));
   }
   print_test("La cola3 no esta vacia", !cola_esta_vacia(cola300));
   for(int i = 300; i<300; i++){
     print_test("Veo el numero", *(int*)cola_ver_primero(cola300)==num[i]);
     print_test("Desencolo el numero", *(int*)cola_desencolar(cola300)==num[i]);
   }
   print_test("La cola3 esta vacia", cola_esta_vacia(cola300));
   cola_destruir(cola300, NULL);
   printf("/////////////////////////////////////////////////////////\n");
   printf("////////////////////////FIN//////////////////////////////\n");
   printf("/////////////////////////////////////////////////////////\n");
   printf("\n");
   printf("/////////////////////////////////////////////////////////\n");
   printf("///////////////////Prueba 1000 heaps/////////////////////\n");
   printf("/////////////////////////////////////////////////////////\n");
   int* heap1[1000];
   cola_t *cola1000 = cola_crear();
   print_test("Se creo la cola1000", cola1000!=NULL);
   print_test("La cola1000 esta vacia", cola_esta_vacia(cola1000));
   for(int i = 0; i<1000; i++){
     heap1[i]=malloc(sizeof(int));
     *heap1[i]=i;
     print_test("Encolo un numero", cola_encolar(cola1000, heap1[i]));
   }
   print_test("La cola1000 no esta vacia", !cola_esta_vacia(cola1000));
   for(int i = 0; i<500; i++){
     print_test("Veo el numero", *(int*)cola_ver_primero(cola1000)==i);
     print_test("Desencolo el numero", *(int*)cola_desencolar(cola1000)==i);
     free(heap1[i]);
   }
   print_test("La cola1000 no esta vacia", !cola_esta_vacia(cola1000));
   cola_destruir(cola1000, free);
   printf("/////////////////////////////////////////////////////////\n");
   printf("////////////////////////FIN//////////////////////////////\n");
   printf("/////////////////////////////////////////////////////////\n");
 }
