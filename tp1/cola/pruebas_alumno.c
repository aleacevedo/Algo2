#include "cola.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/* Definicion de funciones*/
void prueba_cola_vacia(void);
void prueba_cola_un_numero(void);
void prueba_cola_un_puntero(void);
void prueba_cola_5_punteros_intercalados(void);
void prueba_cola_1000_heaps(void);

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

 void pruebas_cola_alumno(){
  prueba_cola_vacia();
  prueba_cola_un_numero();
  prueba_cola_un_puntero();
  prueba_cola_5_punteros_intercalados();
  prueba_cola_1000_heaps();
 }

void prueba_cola_vacia(){
  cola_t *cola = cola_crear();
  if(cola==NULL){
    return;
  }
  printf("<<<<<  INICIO PRUEBA VACIA >>>>>>\n");
  print_test("Prueba cola vacia",cola_esta_vacia(cola));
  cola_destruir(cola, NULL);
  printf("<<<<<<  FIN PRUEBA VACIA  >>>>>>>\n");

}

void prueba_cola_un_numero(){
  int n=5;
  cola_t *cola = cola_crear();
  if(cola==NULL){
    return;
  }
  printf("<<<<<  INICIO PRUEBA UN ENTERO >>>>>>\n");
  print_test("Prueba cola vacia",cola_esta_vacia(cola));
  print_test("Prueba encolo un numero",cola_encolar(cola,&n));
  print_test("Prueba cola vacia", !cola_esta_vacia(cola));
  print_test("Prueba ver primero",*(int*)cola_ver_primero(cola)==n);
  print_test("Prueba desencolar primero",*(int*)cola_desencolar(cola)==n);
  print_test("Prueba cola vacia", cola_esta_vacia(cola));
  cola_destruir(cola, NULL);
  printf("<<<<<<  FIN PRUEBA UN ENTERO  >>>>>>>\n");
}

void prueba_cola_un_puntero(){
  int n = 5;
  int *pun = &n;
  cola_t *cola = cola_crear();
  if(cola == NULL){
    return ;
  }
  printf("<<<<<  INICIO PRUEBA UN PUNTERO >>>>>>\n");
  print_test("Prueba cola vacia",cola_esta_vacia(cola));
  print_test("Prueba encolo un puntero",cola_encolar(cola, pun));
  print_test("Prueba cola vacia",!cola_esta_vacia(cola));
  print_test("Prueba ver primero",cola_ver_primero(cola)==pun);
  print_test("Prueba desencolar primero",cola_desencolar(cola)==pun);
  print_test("Prueba cola vacia",cola_esta_vacia(cola));
  cola_destruir(cola, NULL);
  printf("<<<<<<  FIN PRUEBA UN PUNTERO  >>>>>>>\n");
}

void prueba_cola_5_punteros_intercalados(){
  int num[5];
  int *pun[5];
  cola_t *cola = cola_crear();
  if(cola==NULL){
    return;
  }
  printf("<<<<<  INICIO PRUEBA 5 VALORES INTERCALADOS >>>>>>\n");
  print_test("Prueba cola vacia",cola_esta_vacia(cola));
  num[0]=0;
  pun[0]=&num[0];
  print_test("Prueba encolo valor 1",cola_encolar(cola, pun[0]));
  num[1]=1;
  pun[1]=&num[1];
  print_test("Prueba encolo valor 2",cola_encolar(cola, pun[1]));
  num[2]=2;
  pun[2]=&num[2];
  print_test("Prueba encolo valor 3",cola_encolar(cola, pun[2]));
  print_test("Prueba ver primero es valor 1",cola_ver_primero(cola)==pun[0]);
  print_test("Prueba desencolar primero es valor1",cola_desencolar(cola)==pun[0]);
  print_test("Prueba cola no esta vacia", !cola_esta_vacia(cola));
  print_test("Prueba encolo valor 1",cola_encolar(cola, pun[0]));
  num[3]=3;
  pun[3]=&num[3];
  print_test("Prueba encolo valor 4",cola_encolar(cola, pun[3]));
  num[4]=4;
  pun[4]=&num[4];
  print_test("Prueba encolo valor 5",cola_encolar(cola, pun[4]));
  print_test("Prueba ver primero es valor 2",cola_ver_primero(cola)==pun[1]);
  print_test("Prueba desencolar primero es valor 2",cola_desencolar(cola)==pun[1]);
  print_test("Prueba ver primero es valor 3",cola_ver_primero(cola)==pun[2]);
  print_test("Prueba desencolar primero es valor3",cola_desencolar(cola)==pun[2]);
  print_test("Prueba ver primero es valor 1",cola_ver_primero(cola)==pun[0]);
  print_test("Prueba desencolar primero es valor1",cola_desencolar(cola)==pun[0]);
  print_test("Prueba ver primero es valor 4",cola_ver_primero(cola)==pun[3]);
  print_test("Prueba desencolar primero es valor 4",cola_desencolar(cola)==pun[3]);
  print_test("Prueba ver primero es valor 5",cola_ver_primero(cola)==pun[4]);
  print_test("Prueba desencolar primero es valor5",cola_desencolar(cola)==pun[4]);
  cola_destruir(cola, NULL);
  printf("<<<<<  FIN PRUEBA 5 VALORES INTERCALADOS >>>>>>\n");

}

void prueba_cola_1000_heaps(){
  printf("<<<<<  INICIO PRUEBA 1000 VALORES >>>>>>\n");
  int* heap[1000];
  bool ok;
  cola_t *cola = cola_crear();
  if(cola==NULL){
    return;
  }
  print_test("Prueba cola esta vacio",cola_esta_vacia(cola));
  for(int i = 0; i<1000; i++){
    heap[i]=malloc(sizeof(int));
    *heap[i]=i;
    ok = (cola_encolar(cola, heap[i]));
    if(!ok) break;
  }
  print_test("Prueba cola encolo varios elementos", ok);
  for(int i = 0; i<500; i++){
    ok =  (*(int*)cola_ver_primero(cola)==i);
    ok =  (*(int*)cola_desencolar(cola)==i);
    free(heap[i]);
    if(!ok) break;
  }
  print_test("Prueba cola desencolo varios elementos", ok);
  cola_destruir(cola, free);
  printf("<<<<<  FIN PRUEBA 1000 VALORES >>>>>>\n");
}
