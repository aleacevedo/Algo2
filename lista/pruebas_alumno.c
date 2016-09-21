#include "lista.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/* Definicion de funciones*/
void ejemplo_iteradores();
bool prueba_lista_vacia(void);
bool prueba_lista_un_elemento(void);
bool prueba_lista_mil_heaps(void);
bool prueba_lista_iter_recorrer(void);
bool prueba_lista_iter_insertar_borrar(void);

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

void pruebas_lista_alumno(){
  print_test("Prueba lista vacia", prueba_lista_vacia());
  print_test("Prueba con un elemento", prueba_lista_un_elemento());
  print_test("Prueba con mil heaps", prueba_lista_mil_heaps());
  print_test("Prueba recorrer lista con iter", prueba_lista_iter_recorrer());
  print_test("Prueba insertar y borrar lista con iter", prueba_lista_iter_insertar_borrar());
  ejemplo_iteradores();
}

bool prueba_lista_vacia(){
  /* Crea una lista vacia constata que lo este y la destruye*/
  int fallas = 0;
  lista_t *lista = lista_crear();
  fallas += !(lista_esta_vacia(lista));
  lista_destruir(lista, NULL);
  if(fallas==0){
    return true;
  }
  return false;
}

bool prueba_lista_un_elemento(){
  int dato = 0;
  int fallas = 0;
  lista_t *lista = lista_crear();
  fallas += !(lista_esta_vacia(lista));
  fallas += !(lista_insertar_primero(lista, &dato));
  fallas += !(*(int*)lista_ver_primero(lista)==*(int*)lista_ver_ultimo(lista));
  fallas += !(*(int*)lista_borrar_primero(lista)==dato);
  fallas += !(lista_esta_vacia(lista));
  fallas += !(lista_insertar_ultimo(lista, &dato));
  fallas += !(*(int*)lista_ver_primero(lista)==*(int*)lista_ver_ultimo(lista));
  fallas += !(*(int*)lista_borrar_primero(lista)==dato);
  fallas += !(lista_esta_vacia(lista));
  lista_destruir(lista, NULL);
  if(fallas==0){
    return true;
  }
  return false;
}

bool prueba_lista_mil_heaps(){
  int *dato[1000];
  int fallas = 0;
  lista_t *lista = lista_crear();
  for(int i = 0; i<200; i++){
    dato[i] = malloc(sizeof(int));
    *dato[i] = i;
    fallas += !(lista_insertar_primero(lista, dato[i]));
  }
  for(int i = 200; i<1000; i++){
    dato[i] = malloc(sizeof(int));
    *dato[i] = i;
    fallas += !(lista_insertar_ultimo(lista, dato[i]));
  }
  for(int i = 199; i>=0; i--){
    fallas += !(*(int*)lista_borrar_primero(lista)==i);
  }
  for(int i = 200; i<500; i++){
    fallas += !(*(int*)lista_borrar_primero(lista)==i);
  }
  for(int i = 0; i<500; i++){
    free(dato[i]);
  }
  fallas += lista_esta_vacia(lista);
  lista_destruir(lista, free);
  if(fallas==0){
    return true;
  }
  return false;
}

bool prueba_lista_iter_recorrer(void){
  int fallas = 0;
  int dato[500];
  lista_t *lista = lista_crear();
  lista_iter_t *iter;
  for(int i = 0; i<500; i++){
    dato[i]=i;
    fallas += !lista_insertar_ultimo(lista, dato+i);
  }
  iter = lista_iter_crear(lista);
  for(int i = 0; i<500; i++){
    fallas += !(*(int*)lista_iter_ver_actual(iter)==i);
    lista_iter_avanzar(iter);
  }
  fallas += !(lista_iter_al_final(iter));
  lista_iter_destruir(iter);
  lista_destruir(lista, NULL);
  if(fallas==0){
    return true;
  }
  return false;
}

bool prueba_lista_iter_insertar_borrar(){
  int fallas = 0;
  char dato[501];
  lista_t *lista = lista_crear();
  lista_iter_t *iter = lista_iter_crear(lista);
  dato[0]='a';
  for(int i = 0; i<500; i++){
    fallas += !lista_iter_insertar(iter, dato+i);
    dato[i+1] = dato[i]++;
  }
  for(int i = 499; i>=0; i--){
    fallas += !(*(char*)lista_iter_borrar(iter)==dato[i]);
  }
  fallas += !lista_iter_al_final(iter);
  fallas += !lista_esta_vacia(lista);
  lista_iter_destruir(iter);
  lista_destruir(lista,NULL);
  if(fallas==0){
    return true;
  }
  return false;
}
