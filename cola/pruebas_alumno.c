#include "cola.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/* Definicion de funciones*/
bool prueba_cola_vacia(void);
bool prueba_cola_un_numero(void);
bool prueba_cola_un_puntero(void);
bool prueba_cola_un_heap(void);
bool prueba_cola_100_numeros(void);
bool prueba_cola_500_punteros_intercalados(void);
bool prueba_cola_1000_heaps(void);

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

 void pruebas_cola_alumno(){
  print_test("Prueba cola vacia",prueba_cola_vacia());
  print_test("Prueba con un numero",prueba_cola_un_numero());
  print_test("Prueba con un puntero",prueba_cola_un_puntero());
  print_test("Prueba con un heap",prueba_cola_un_heap());
  print_test("Prueba con 100 numero",prueba_cola_100_numeros());
  print_test("Prueba con 500 punteros intercalados",prueba_cola_500_punteros_intercalados());
  print_test("Prueba con 1000 heaps",prueba_cola_1000_heaps());
 }

bool prueba_cola_vacia(){
  cola_t *cola = cola_crear();
  int fallo = 0;
  if(cola==NULL){
    return false;
  }
  fallo += (!cola_esta_vacia(cola));
  cola_destruir(cola, NULL);
  if(fallo==0){
    return true;
  }
  return false;
}

bool prueba_cola_un_numero(){
  int n=5;
  int fallo = 0;
  cola_t *cola = cola_crear();
  if(cola==NULL){
    return false;
  }
  fallo += !(cola_esta_vacia(cola));
  fallo += !(cola_encolar(cola,&n));
  fallo += (cola_esta_vacia(cola));
  fallo += !(*(int*)cola_ver_primero(cola)==n);
  fallo += !(*(int*)cola_desencolar(cola)==n);
  fallo += !(cola_esta_vacia(cola));
  cola_destruir(cola, NULL);
  if (fallo==0){
    return true;
  }
  return false;
}

bool prueba_cola_un_puntero(){
  int n = 5;
  int fallo = 0;
  int *pun = &n;
  cola_t *cola = cola_crear();
  if(cola == NULL){
    return false;
  }
  fallo += !(cola_esta_vacia(cola));
  fallo += !(cola_encolar(cola, pun));
  fallo += (cola_esta_vacia(cola));
  fallo += !(cola_ver_primero(cola)==pun);
  fallo += !(cola_desencolar(cola)==pun);
  fallo += !(cola_esta_vacia(cola));
  cola_destruir(cola, NULL);
  if (fallo==0){
    return true;
  }
  return false;
}

bool prueba_cola_un_heap(){
  int *heap = malloc(sizeof(int));
  int n = 5;
  int fallo = 0;
  *heap = n;
  cola_t *cola = cola_crear();
  if(cola==NULL){
    return false;
  }
  fallo += !(cola_esta_vacia(cola));
  fallo += !(cola_encolar(cola, heap));
  fallo += (cola_esta_vacia(cola));
  fallo += !(cola_ver_primero(cola)==heap);
  cola_destruir(cola, free);
  if (fallo==0){
    return true;
  }
  return false;
}

bool prueba_cola_100_numeros(){
  int fallo = 0;
  int num[100];
  cola_t *cola = cola_crear();
  if(cola==NULL){
    return false;
  }
  fallo += !(cola_esta_vacia(cola));
  for(int i = 0; i<100; i++){
    num[i]=i;
    fallo += !(cola_encolar(cola, &num[i]));
  }
  fallo += (cola_esta_vacia(cola));
  cola_destruir(cola, NULL);
  if (fallo==0){
    return true;
  }
  return false;
}

bool prueba_cola_500_punteros_intercalados(){
  int fallo = 0;
  int num[500];
  int *pun[500];
  cola_t *cola = cola_crear();
  if(cola==NULL){
    return false;
  }
  fallo += !(cola_esta_vacia(cola));
  for(int i = 0; i<300; i++){
    num[i]=i;
    pun[i]=&num[i];
    fallo += !(cola_encolar(cola, pun[i]));
  }
  for(int i = 0; i<100; i++){
    fallo += !(cola_ver_primero(cola)==pun[i]);
    fallo += !(cola_desencolar(cola)==pun[i]);
  }
  fallo += (cola_esta_vacia(cola));
  for(int i = 0; i<100; i++){
    num[i]=i;
    pun[i]=&num[i];
    fallo += !(cola_encolar(cola, pun[i]));
  }
  for(int i = 300; i<500; i++){
    num[i]=i;
    pun[i]=&num[i];
    fallo += !(cola_encolar(cola, pun[i]));
  }
  for(int i = 100; i<300; i++){
    fallo += !(cola_ver_primero(cola)==pun[i]);
    fallo += !(cola_desencolar(cola)==pun[i]);
  }
  for(int i = 0; i<100; i++){
    fallo += !(cola_ver_primero(cola)==pun[i]);
    fallo += !(cola_desencolar(cola)==pun[i]);
  }
  for(int i = 300; i<500; i++){
    fallo += !(cola_ver_primero(cola)==pun[i]);
    fallo += !(cola_desencolar(cola)==pun[i]);
  }
  fallo += !(cola_esta_vacia(cola));
  cola_destruir(cola, NULL);
  if (fallo==0){
    return true;
  }
  printf("DEBUG: %i\n", fallo);
  return false;
}

bool prueba_cola_1000_heaps(){
  int* heap[1000];
  int fallo = 0;
  cola_t *cola = cola_crear();
  if(cola==NULL){
    return false;
  }
  fallo += !(cola_esta_vacia(cola));
  for(int i = 0; i<1000; i++){
    heap[i]=malloc(sizeof(int));
    *heap[i]=i;
    fallo += !(cola_encolar(cola, heap[i]));
  }
  fallo += (cola_esta_vacia(cola));
  for(int i = 0; i<500; i++){
    fallo += !(*(int*)cola_ver_primero(cola)==i);
    fallo += !(*(int*)cola_desencolar(cola)==i);
    free(heap[i]);
  }
  fallo += (cola_esta_vacia(cola));
  cola_destruir(cola, free);
  if (fallo==0){
    return true;
  }
  return false;
}
