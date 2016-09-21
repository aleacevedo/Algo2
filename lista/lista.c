#include"lista.h"
#include <stdlib.h>
#include <stdio.h>


/* Definicion struct nodo_t */
typedef struct nodo nodo_t;

struct nodo {
  void *dato;
  nodo_t *prox;
};

/* Definicion struct lista */
struct lista{
  nodo_t *prim;
  nodo_t *ult;
  size_t largo;
};


/* Definicion struct iterador externo */
struct lista_iter{
  nodo_t *actual;
  lista_t *lista;
};


/* *****************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/

lista_t* lista_crear(){
  lista_t *lista = malloc(sizeof(lista_t));
  lista->prim = NULL;
  lista->ult = lista->prim;
  lista->largo = 0;
  return lista;
}

bool lista_esta_vacia(const lista_t *lista){
  if(lista_largo(lista)==0){
    return true;
  }
  return false;
}

bool lista_insertar_primero(lista_t *lista, void *dato){
  nodo_t *nodo_nuevo;
  nodo_nuevo = malloc(sizeof(nodo_t));
  if(nodo_nuevo==NULL){
    return false;
  }
  if(lista_esta_vacia(lista)){
    lista->prim = nodo_nuevo;
    lista->ult = lista->prim;
    lista->largo++;
    return true;
  }
  nodo_nuevo->prox = lista->prim;
  lista->prim = nodo_nuevo;
  lista->largo++;
  return true;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato){
  nodo_t *nodo_nuevo;
  nodo_nuevo = malloc(sizeof(nodo_t));
  if(nodo_nuevo==NULL){
    return false;
  }
  if(lista_esta_vacia(lista)){
    lista->prim = nodo_nuevo;
    lista->ult = lista->prim;
    lista->largo++;
    return true;
  }
  lista->ult->prox = nodo_nuevo;
  lista->ult = nodo_nuevo;
  return true;
}

void* lista_borrar_primero(lista_t *lista){
  nodo_t *nodo_aux;
  void *dato_aux = NULL;
  if(!lista_esta_vacia(lista)){
    nodo_aux = lista->prim;
    lista->prim = lista->prim->prox;
    dato_aux = nodo_aux->dato;
    free(nodo_aux);
  }
  if(lista_esta_vacia(lista)){
    lista->prim = NULL;
    lista->ult = NULL;
  }
  return dato_aux;
}

void* lista_ver_primero(const lista_t *lista){
  if(!lista_esta_vacia(lista)){
    return lista->prim->dato;
  }
  return NULL;
}

void* lista_ver_ultimo(const lista_t *lista){
  if(!lista_esta_vacia(lista)){
    return lista->ult->dato;
  }
  return NULL;
}

size_t lista_largo(const lista_t *lista){
  return lista->largo;
}

void lista_destruir(lista_t *lista, void destruir_dato()){
  nodo_t *nodo_aux;
  while(!lista_esta_vacia(lista)){
    if(destruir_dato!=NULL){
      destruir_dato(lista->prim->dato);
    }
    nodo_aux = lista->prim;
    lista->prim = lista->prim->prox;
    free(nodo_aux);
    lista->largo--;
  }
  free(lista);
}

/* *****************************************************************
 *                    PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/

lista_iter_t* lista_iter_crear(lista_t *lista){
  lista_iter_t *iter = malloc(sizeof(lista_iter_t));
  if(iter==NULL){
    return NULL;
  }
  iter->actual = lista->prim;
  iter->lista = lista;
  return iter;
}

bool lista_iter_avanzar(lista_iter_t *iter){
  if(lista_iter_al_final(iter)){
    return false;
  }
  iter->actual = iter->actual->prox;
  return true;
}

void* lista_iter_ver_actual(const lista_iter_t *iter){
  if(lista_iter_al_final(iter)){
    return NULL;
  }
  return iter->actual->dato;
}

bool lista_iter_al_final(const lista_iter_t *iter){
  if(iter->actual==NULL){
    return true;
  }
  return false;
}

void lista_iter_destruir(lista_iter_t *iter){
  free(iter);
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato){
  nodo_t *nodo_nuevo = malloc(sizeof(nodo_t));
  lista_iter_t *iter_aux = lista_iter_crear(iter->lista);
  nodo_nuevo->dato = dato;
  if(nodo_nuevo==NULL || iter_aux==NULL){
    return false;
  }
  if(iter->lista->prim==iter->actual){
    iter->lista->prim = nodo_nuevo;
    nodo_nuevo->prox = iter->actual;
    iter->lista->largo++;
    return true;
  }
  while(iter->actual!=iter_aux->actual->prox){
    lista_iter_avanzar(iter_aux);
  }
  nodo_nuevo->prox = iter->actual;
  iter_aux->actual->prox = nodo_nuevo;
  iter->lista->largo++;
  lista_iter_destruir(iter_aux);
  return true;
}

void *lista_iter_borrar(lista_iter_t *iter){
  lista_iter_t *iter_aux = lista_iter_crear(iter->lista);
  void *dato_aux;
  if(lista_iter_al_final(iter)){
    return NULL;
  }
  if(iter->lista->prim==iter->actual){
    iter->lista->prim = iter->actual->prox;
    dato_aux = iter->actual->dato;
    free(iter->actual);
    iter->lista->largo--;
    iter->actual = iter->lista->prim;
    return dato_aux;
  }
  while(iter->actual!=iter_aux->actual->prox){
    lista_iter_avanzar(iter_aux);
  }
  iter_aux->actual->prox = iter->actual->prox;
  dato_aux = iter->actual->dato;
  free(iter->actual);
  iter->actual = iter_aux->actual->prox;
  iter->lista->largo--;
  lista_iter_destruir(iter_aux);
  if(lista_esta_vacia(iter->lista)){
    iter->lista->prim = NULL;
    iter->lista->ult = NULL;
  }
  return dato_aux;
}

void lista_iterar(lista_t *lista, bool (*visitar)(void *dato, void *extra), void *extra){
  bool aux = true;
  void *lista_aux[lista_largo(lista)];
  if(visitar==NULL){
    return;
  }
  int i = 0;
  while(aux && !lista_esta_vacia(lista)){
    lista_aux[i] = lista_borrar_primero(lista);
    aux = visitar(lista_aux[i],extra);
    i++;
  }
  for(int o = i-1; i>=0; o--){
    lista_insertar_primero(lista, lista_aux[o]);
  }
}
