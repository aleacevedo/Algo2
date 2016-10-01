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
  nodo_t *anterior;
  lista_t *lista;
};


/* *****************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/

lista_t* lista_crear(){
  lista_t *lista = malloc(sizeof(lista_t));
  lista->prim = NULL;
  lista->ult = NULL;
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
  nodo_t *nodo_nuevo = malloc(sizeof(nodo_t));;
  if(nodo_nuevo==NULL){
    return false;
  }
  nodo_nuevo->dato = dato;
  nodo_nuevo->prox = NULL;
  if(lista_esta_vacia(lista)){
    lista->prim = nodo_nuevo;
    lista->ult = nodo_nuevo;
    lista->largo++;
    return true;
  }
  lista->largo++;
  nodo_nuevo->prox = lista->prim;
  lista->prim = nodo_nuevo;
  return true;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato){
  nodo_t *nodo_nuevo;
  nodo_nuevo = malloc(sizeof(nodo_t));
  if(nodo_nuevo==NULL){
    return false;
  }
  nodo_nuevo->prox = NULL;
  nodo_nuevo->dato = dato;
  if(lista_esta_vacia(lista)){
    lista->prim = nodo_nuevo;
    lista->ult = lista->prim;
    lista->largo++;
    return true;
  }
  lista->largo++;
  lista->ult->prox = nodo_nuevo;
  lista->ult = nodo_nuevo;
  return true;
}

void* lista_borrar_primero(lista_t *lista){
  nodo_t *nodo_aux = NULL;
  void *dato_aux = NULL;
  if(!lista_esta_vacia(lista)){
    nodo_aux = lista->prim;
    dato_aux = lista->prim->dato;
    lista->prim = lista->prim->prox;
    free(nodo_aux);
    lista->largo--;
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
  iter->anterior = NULL;
  iter->lista = lista;
  return iter;
}

bool lista_iter_avanzar(lista_iter_t *iter){
  if(lista_iter_al_final(iter)){
    return false;
  }
  iter->anterior = iter->actual;
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
  if(nodo_nuevo == NULL){
    return false;
  }
  nodo_nuevo->dato = dato;
  nodo_nuevo->prox = NULL;
  if(lista_esta_vacia(iter->lista)){
    iter->lista->prim = nodo_nuevo;
    iter->lista->ult = nodo_nuevo;
    iter->actual = iter->lista->prim;
    iter->lista->largo++;
    return true;
  }
  if(iter->actual==iter->lista->prim){
    iter->lista->prim = nodo_nuevo;
    iter->lista->prim->prox = iter->actual;
    iter->actual = iter->lista->prim;
    iter->lista->largo++;
    return true;
  }
  if(lista_iter_al_final(iter)){
    iter->anterior->prox = nodo_nuevo;
    iter->lista->ult = nodo_nuevo;
    iter->actual = iter->lista->ult;
    iter->lista->largo++;
    return true;
  }
  iter->anterior->prox = nodo_nuevo;
  nodo_nuevo->prox = iter->actual;
  iter->actual = nodo_nuevo;
  iter->lista->largo++;
  return true;
}

void *lista_iter_borrar(lista_iter_t *iter){
  void *dato_aux = NULL;
  nodo_t *nodo_aux = NULL;
  if(lista_iter_al_final(iter)){
    return NULL;
  }
  iter->lista->largo--;
  if(iter->actual==iter->lista->prim){
    nodo_aux = iter->lista->prim;
    dato_aux = nodo_aux->dato;
    iter->lista->prim = iter->lista->prim->prox;
    iter->actual = iter->lista->prim;
    free(nodo_aux);
    return dato_aux;
  }
  if(iter->actual==iter->lista->ult){
    nodo_aux = iter->lista->ult;
    dato_aux = nodo_aux->dato;
    iter->lista->ult = iter->anterior;
    iter->anterior->prox = NULL;
    iter->actual = NULL;
    free(nodo_aux);
    return dato_aux;
  }
  nodo_aux = iter->actual;
  dato_aux = nodo_aux->dato;
  iter->anterior->prox = iter->actual->prox;
  iter->actual = iter->actual->prox;
  free(nodo_aux);
  return dato_aux;
}

void lista_iterar(lista_t *lista, bool (*visitar)(void *dato, void *extra), void *extra){
  nodo_t *aux = lista->prim;
  while(aux!=NULL && visitar(aux->dato, extra)==true){
    aux=aux->prox;
  }
}
