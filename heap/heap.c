#define TAM_INICIAL 10
#include "heap.h"

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
  size_t pos_mayor = 0;
  if(pos_h_izq<cantidad&&(cmp(datos[i],datos[pos_h_izq])<0)){
    pos_mayor = pos_h_izq;
  }
  if(pos_h_der<cantidad&&(cmp(datos[pos_mayor],datos[pos_h_der])<0)){
    pos_mayor = pos_h_der;
  }
  if (pos_mayor>0){
    _swap(datos, i, pos_mayor);
    _downheap(datos,pos_mayor,cantidad,cmp);
  }
}

void _heapify(void *elementos[], size_t cant, cmp_func_t cmp){
  size_t i = cant/2;
  while(i > 0){
    _downheap(elementos,i,cant,cmp);
    i--;
    printf("%zu\n", i);
  }
  //_downheap(elementos,i,cant,cmp);
}

bool _heap_redimensionar(heap_t *heap, size_t tam_nuevo){
    void *aux = realloc(heap->dato, tam_nuevo);
    if(!aux) return false;
    heap->dato = aux;
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
  *heap->dato = calloc(TAM_INICIAL,sizeof(void*));
  if(!*heap->dato){
    free(heap);
    return NULL;
  }
  for(int i =0;i<n;i++){
    if(!heap_encolar(heap,cmp)); free(heap->dato); free(heap); return NULL;
  }
  return heap;
}

bool heap_esta_vacio(const heap_t *heap){
  return heap->cantidad==0;
}

size_t heap_cantidad(const heap_t *heap){
  return heap->cantidad;
}

void heap_destruir(heap_t *heap, void destruir_elemento(void *e)){
  int i=0;
  while(heap->dato[i]){
    if(destruir_elemento) destruir_elemento(heap->dato[i]);
    i++;
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
	printf("Arreglo");
	for(int i = 0; i<cant; i++){
		printf("|%i|", *(int*)elementos[i]);
	}
	printf("\n");
    _heapify(elementos,cant,cmp);
    printf("Arreglo");
	for(int i = 0; i<cant; i++){
		printf("|%i|", *(int*)elementos[i]);
	}
	printf("\n");
    size_t i=0;
    while(i < cant){
        _swap(elementos,0,cant-i-1);
        _downheap(elementos,0,cant-i-1,cmp);
         i++;
    }
    printf("Arreglo");
	for(int h = 0; h<cant; h++){
		printf("|%i|", *(int*)elementos[h]);
	}
	printf("\n");
}
