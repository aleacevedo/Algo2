#include "cola.h"
#include <stdlib.h>
#include <stdio.h>

/* Definicion del struct cola y nodo*/

struct cola {
  nodo_t *prim;
  nodo_t *ultim;
};

struct nodo {
  void *dato;
  nodo_t *prox;
};


/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

cola_t* cola_crear(){
  /*Crea una cola vacia, en caso de que no sea posible devuelve NULL*/
  cola_t *cola = malloc(sizeof(cola_t));
  cola->prim = NULL;
  cola->ultim = NULL;
  return cola;
}

void cola_destruir(cola_t *cola, void destruir_dato(void*)){
  /* Destruye la totalidad de la cola junto con sus datos en caso de que se pase
    una funciona para que asi sea realizado */
  nodo_t *aux;
  while(cola->prim!=NULL){
    if(destruir_dato){
      destruir_dato(cola->prim->dato);
    }
    aux = cola->prim;
    cola->prim = cola->prim->prox;
    free(aux);
  }
  free(cola);
}

bool cola_esta_vacia(const cola_t *cola){
/* Devuelve true si la cola esta vacia, false en caso que no lo este*/
  if(cola->prim==NULL){
    return true;
  }
  return false;
}

bool cola_encolar(cola_t *cola, void *valor){
/* Encola el valor pasado por parametro, en caso de que no sea posible devuelve
  false*/
  nodo_t *nodo = malloc(sizeof(nodo_t));
  if(nodo==NULL){
    return false;
  }
  nodo->dato = valor;
  nodo->prox = NULL;
  if(cola_esta_vacia(cola)){
    cola->prim = nodo;
    cola->ultim = nodo;
    return true;
  }
  cola->ultim->prox = nodo;
  cola->ultim = nodo;
  return true;
}

void* cola_ver_primero(const cola_t *cola){
/* Devuelve el primero de la lista, si esta vacia Devuelve null*/
  void *aux;
  if(cola_esta_vacia(cola)){
    return NULL;
  }
  aux=cola->prim->dato;
  return aux;
}

void* cola_desencolar(cola_t *cola){
/* Desencola el primero de la lista, si esta vacia devuelve null*/
  nodo_t *aux;
  void *valor;
  if(cola_esta_vacia(cola)){
    return NULL;
  }
  aux = cola->prim;
  valor = cola->prim->dato;
  cola->prim = cola->prim->prox;
  free(aux);
  return valor;
}
