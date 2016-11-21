#include "heap-utils.h"

void** top_k(size_t k, void** datos, size_t tam_datos, cmp_func_t cmp){
  void **res = calloc(k, sizeof(void*));
  size_t dif = tam_datos - k;
  heap_t *heap = heap_crear_arr(datos, tam_datos, cmp);
  for(size_t i = tam_datos -1 - k; i<tam_datos; i--){
    heap_desencolar(heap);
    printf("Borro %zu\n", i);
  }
  if(dif<=tam_datos) dif = k;
  else dif = tam_datos;
  for(size_t i = dif; i>0; i--){
    res[i-1] = heap_desencolar(heap);
    printf("Guardo %zu\n", i);
  }
  heap_destruir(heap, NULL);
  return res;
}
