#define TAM_INICIAL 10
#include "heap.h"
#include <stdbool.h>  /* bool */
#include <stddef.h>	  /* size_t */
#include <stdlib.h>
#include <stdio.h>

struct heap{
  void** dato;
  size_t cantidad;
  size_t tam;
  cmp_func_t cmp;
};

void _swap(void **datos, size_t a, size_t b){
  void *aux;
  aux = datos[a];
  datos[a] = datos[b];
  datos[b] = aux;
}

void _downheap(void **datos, size_t i, size_t cantidad, cmp_func_t cmp){
  if (i>=cantidad) return;
  size_t pos_h_izq = (2 * i) + 1;
  size_t pos_h_der = pos_h_izq + 1;
  size_t pos_mayor = i;
  if(pos_h_izq<cantidad&&(cmp(datos[i],datos[pos_h_izq])<0)){
    pos_mayor = pos_h_izq;
  }
  if(pos_h_der<cantidad&&(cmp(datos[pos_mayor],datos[pos_h_der])<0)){
    pos_mayor = pos_h_der;
  }
  if (pos_mayor != i){
    _swap(datos, i, pos_mayor);
    _downheap(datos,pos_mayor,cantidad,cmp);
  }
}

size_t _buscar_pos(heap_t *heap, void *dato){
	size_t i = 0;
	while(heap->cantidad>i){
		if(dato==heap->dato[i]) return i;
		i++;
	}
	return -1;
}
void _heapify(void *elementos[], size_t cant, cmp_func_t cmp){
  for(size_t i = cant/2 - 1; i !=-1; i--){
    _downheap(elementos, i, cant, cmp);
  }
}

bool _heap_redimensionar(heap_t *heap, size_t tam_nuevo){
  void *aux = realloc(heap->dato, sizeof(void*)*tam_nuevo);
  if(!aux) return false;
  heap->dato = aux;
  heap->tam = tam_nuevo;
  return true;
}


void _upheap(void **datos,size_t cant, cmp_func_t cmp){
    if (cant > 0){
        size_t padre = (cant-1) / 2;
        if (cmp(datos[padre],datos[cant])<0){
            _swap(datos,padre,cant);
            _upheap(datos,padre,cmp);
        }
    }
}

heap_t *heap_crear(cmp_func_t cmp){
  heap_t* heap = calloc(1,sizeof(heap_t));
  if(!heap) return NULL;
  heap->dato = calloc(TAM_INICIAL,sizeof(void*));
  if(!heap->dato){
    free(heap);
    return NULL;
  }
  heap->tam = TAM_INICIAL;
  heap->cantidad = 0;
  heap->cmp = cmp;
  return heap;
}

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp){
  heap_t* heap = calloc(1,sizeof(heap_t));
  if(!heap) return NULL;
  heap->dato = arreglo;
  heap->tam = n;
  heap->cantidad = n;
  heap->cmp = cmp;
  _heapify(heap->dato, n, cmp);
  return heap;
}

bool heap_esta_vacio(const heap_t *heap){
  return heap->cantidad==0;
}

size_t heap_cantidad(const heap_t *heap){
  return heap->cantidad;
}

void heap_destruir(heap_t *heap, void destruir_elemento(void *e)){
  for(size_t i=0; i<heap->cantidad; i++){
    if(destruir_elemento) destruir_elemento(heap->dato[i]);
  }
  free(heap->dato);
  free(heap);
}

bool heap_encolar(heap_t *heap, void *elem){
  if(heap->tam==heap->cantidad && !_heap_redimensionar(heap, heap->tam*2)) return false;
  heap->dato[(heap->cantidad)]=elem;
  _upheap(heap->dato, heap->cantidad, heap->cmp);
  heap->cantidad++;
  return true;
}

void* heap_ver_max(const heap_t *heap){
  if(heap_cantidad(heap)==0)return NULL;
  return heap->dato[0];
}

void* heap_desencolar(heap_t *heap){
  if(heap_esta_vacio(heap)) return NULL;
  if (heap->tam > TAM_INICIAL && heap->cantidad <= (heap->tam/4)){
    if (!_heap_redimensionar(heap,heap->tam/2))return NULL;
  }
  void *aux = heap->dato[0];
  heap->dato[0] = NULL;
  heap->cantidad--;
  _swap(heap->dato, 0, heap->cantidad);
  if(heap_cantidad(heap)>1)_downheap(heap->dato, 0, heap->cantidad, heap->cmp);
  return aux;
}

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp){
  _heapify(elementos,cant,cmp);
  for (size_t i = cant-1; i < cant; i--){
    _swap(elementos,0,i);
    _downheap(elementos,0,  i,cmp);
  }
}

void heap_actualizar_prioridad(heap_t *heap, void *dato){
	size_t pos = _buscar_pos(heap, dato);
	size_t pos_padre = (pos-1)/2;
	size_t pos_h_izq = (pos*2)+1;
	size_t pos_h_der = (pos*2)+2;
	if(pos_padre<heap->cantidad && heap->cmp(heap->dato[pos],heap->dato[pos_padre])>0){
		_upheap(heap->dato, pos, heap->cmp);
	}
	else if((heap->cantidad>pos_h_izq && heap->cmp(heap->dato[pos],heap->dato[pos_h_izq])<0)||(heap->cantidad>pos_h_der && heap->cmp(heap->dato[pos],heap->dato[pos_h_der])<0)){
		_downheap(heap->dato, pos, heap->cantidad, heap->cmp);
	}
}
