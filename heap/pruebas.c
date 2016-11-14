#include "testing.h"
#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>  /* bool */
#include <stddef.h>	  /* size_t */
#include <string.h>

int comp_ent(const void *a, const void *b){
  if(*(int*)a<*(int*)b){
    return -1;
  }
  if(*(int*)a>*(int*)b){
    return 1;
  }
  return 0;
}

void prueba_sort(int largo){
  int *valores[largo];
  bool ok = true;
  for(int i = 0; i<largo; i++){
    valores[i] = malloc(sizeof(int));
    *valores[i] = largo-i-1;
  }
  heap_sort((void**)valores, 10, comp_ent);
  for(int i = largo-1; i>=0; i--){
    ok = (*valores[i] == i);
    if(!ok) break;
    free(valores[i]);
  }
}

void prueba_heap_mil(int largo){
  heap_t *heap = heap_crear(comp_ent);
  int *valores[largo];
  bool ok = true;
  print_test("Prueba heap el heap esta vacio", heap_esta_vacio(heap));
  for(int i = 0; i<largo; i++){
    valores[i] = malloc(sizeof(int));
    *valores[i] = rand();
    ok = heap_encolar(heap, valores[i]);
    if(!ok) break;
  }
  print_test("Prueba heap enconlar muchos", ok);
  heap_sort((void**)valores, largo, comp_ent);
  print_test("Prueba heap el heap esta vacio", !heap_esta_vacio(heap));
  print_test("Prueba heap la cantidad es correcta", heap_cantidad(heap) == largo);
  for(int i = largo-1; i>=0; i--){
    ok = (*valores[i] == *(int*)heap_ver_max(heap));
    ok = (*valores[i] == *(int*)heap_desencolar(heap));
    if(!ok) break;
    free(valores[i]);
  }
  print_test("Prueba heap desencolar muchos", ok);
  print_test("Prueba heap el heap esta vacio", heap_esta_vacio(heap));
  heap_destruir(heap, NULL);
}

void prueba_heap_vacio(){
  heap_t *heap = heap_crear(comp_ent);
  print_test("Prueba heap el heap esta vacio", heap_esta_vacio(heap));
  print_test("Prueba heap la cantidad es 0", heap_cantidad(heap) == 0);
  heap_destruir(heap,NULL);
}

void prueba_heap_4(){
  heap_t *heap = heap_crear(comp_ent);
  int arreglo[] = {4,6,7,20};
  print_test("Prueba heap el heap esta vacio", heap_esta_vacio(heap));
  print_test("Prueba heap encolar el primero", heap_encolar(heap, arreglo));
  print_test("Prueba heap no esta vacio", !heap_esta_vacio(heap));
  print_test("Prueba heap la cantidad es 1", heap_cantidad(heap) == 1);
  print_test("Prueba heap encolar el tercero", heap_encolar(heap, arreglo+2));
  print_test("Prueba heap la cantidad es 2", heap_cantidad(heap) == 2);
  print_test("Prueba heap encolar el segundo", heap_encolar(heap, arreglo+1));
  print_test("Prueba heap la cantidad es 3", heap_cantidad(heap) == 3);
  print_test("Prueba heap encolar el cuarto", heap_encolar(heap, arreglo+3));
  print_test("Prueba heap la cantidad es 4", heap_cantidad(heap) == 4);
  print_test("Prueba ver maximo", heap_ver_max(heap) == arreglo+3);
  print_test("Prueba desencolar", heap_desencolar(heap) == arreglo+3);
  print_test("Prueba heap la cantidad es 4", heap_cantidad(heap) == 3);
  print_test("Prueba ver maximo", heap_ver_max(heap) == arreglo+2);
  heap_destruir(heap,NULL);
}

void prueba_heap_10(){
  heap_t *heap = heap_crear(comp_ent);
  bool ok = true;
  int largo = 10;
  int *punteros[largo];
  for(int i=0; i<largo;i++){
    punteros[i] = calloc(1, sizeof(int));
    ok = heap_encolar(heap, punteros[i]);
    *punteros[i] = i;
    if(ok) break;
  }
  print_test("Prueba heap encolar 10 punteros", ok);
  heap_destruir(heap, free);
}

void pruebas_heap_alumno(){
  prueba_heap_vacio();
  prueba_heap_4();
  prueba_heap_10();
  prueba_heap_mil(1000);
  prueba_sort(10);
}
