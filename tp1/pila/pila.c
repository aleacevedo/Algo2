#include "pila.h"
#include <stdlib.h>
#include <stdio.h>

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void **datos;
    size_t tam;
    size_t largo;
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

// ...

pila_t* pila_crear(){
  pila_t* pila = malloc(sizeof(pila_t));
  if (pila == NULL){
    return NULL;
  }
  pila->tam = 10;
  pila->largo = 0;
  pila->datos = malloc(pila->tam * sizeof(void*));
  if(pila->datos == NULL){
    free(pila);
    return NULL;
  }
  return pila;
}

bool pila_redimensionar(pila_t *pila, size_t tam){
  void* datos_nuevo = realloc(pila->datos, tam * sizeof(void*));
  if(datos_nuevo == NULL){
    return false;
  }
  pila->datos = datos_nuevo;
  pila->tam = tam;
  return true;
}

void pila_destruir(pila_t* pila){
  free(pila->datos);
  free(pila);
}

bool pila_esta_vacia(const pila_t* pila){
  if(pila->largo == 0){
    return true;
  }
  return false;
}

bool pila_apilar(pila_t *pila, void *valor){
  void **posi;
  if(pila->tam == pila->largo){
    if(!pila_redimensionar(pila, pila->tam*2)){
      return false;
    }
  }
  posi = pila->datos + pila->largo;
  *posi = valor;
  pila->largo++;
  return true;
}

void* pila_ver_tope(const pila_t *pila){
  void **posi;
  if(pila_esta_vacia(pila)){
    return NULL;
  }
  posi = pila->datos + pila->largo-1;
  return *posi;
}

void* pila_desapilar(pila_t *pila){
  void **posi;
  if(pila_esta_vacia(pila)){
    return NULL;
  }
  pila->largo--;
  if(pila->tam/2 > pila->largo){
    size_t nuevo_tam = pila->tam/2;
    pila_redimensionar(pila, nuevo_tam);
  }
  posi = pila->datos + pila->largo;
  return *posi;
}
