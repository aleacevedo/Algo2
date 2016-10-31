#include"abb.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "pila.h"

typedef struct nodo_abb nodo_abb_t;

typedef struct abb abb_t;

typedef struct abb_iter abb_iter_t;

struct nodo_abb{
  char *clave;
  void *dato;
  nodo_abb_t *izq;
  nodo_abb_t *der;
};

struct abb{
  nodo_abb_t *raiz;
  abb_comparar_clave_t cmp;
  abb_destruir_dato_t destruir_dato;
  size_t cantidad;
};

struct abb_iter{
  const abb_t* arbol;
  pila_t* pila;
};


void _abb_destruir(abb_t *arbol, nodo_abb_t *actual){
  if(!actual) return;
  _abb_destruir(arbol, actual->der);
  _abb_destruir(arbol, actual->izq);
  free(actual->clave);
  if(arbol->destruir_dato) arbol->destruir_dato(actual->dato);
  free(actual);
  return;
}
bool _abb_guardar(abb_t *abb, nodo_abb_t **actual, nodo_abb_t *nuevo){
  if(*actual==NULL){
    *actual = nuevo;
    return true;
  }
  int compare = abb->cmp((*actual)->clave,nuevo->clave);
  if(compare==0){
    (*actual)->dato = nuevo->dato;
    free(nuevo->clave);
    free(nuevo);
    return true;
  }
  else if(compare<0){
    return _abb_guardar(abb, &((*actual)->der), nuevo);
  }
  else{
    return _abb_guardar(abb, &((*actual)->izq), nuevo);
  }
}

nodo_abb_t* _abb_buscar(abb_t *abb, nodo_abb_t **actual, const char* clave, nodo_abb_t **padre){
  if(*actual==NULL || !clave){
    return NULL;
  }
  int compare = abb->cmp((*actual)->clave,clave);
  if(compare==0){
    return *actual;
  }
  else if(compare<0){
    *padre = *actual;
    return _abb_buscar(abb, &((*actual)->der), clave, padre);
  }
  else{
    *padre = *actual;
    return _abb_buscar(abb, &((*actual)->izq), clave, padre);
  }
}

nodo_abb_t* _abb_perte_obte(const abb_t *abb, nodo_abb_t **actual, const char* clave, nodo_abb_t **padre){
  if(*actual==NULL || !clave){
    return NULL;
  }
  int compare = abb->cmp((*actual)->clave,clave);
  if(compare==0){
    return *actual;
  }
  else if(compare<0){
    *padre = *actual;
    return _abb_perte_obte(abb, &((*actual)->der), clave, padre);
  }
  else{
    *padre = *actual;
    return _abb_perte_obte(abb, &((*actual)->izq), clave, padre);
  }
}

nodo_abb_t* _abb_buscar_mayor(nodo_abb_t **actual, nodo_abb_t **padre){
  if((*actual)->der){
    *padre = *actual;
    return _abb_buscar_mayor(&(*actual)->der, padre);
  }
  return *actual;
}

void _abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra,nodo_abb_t** nodo){
  if(!(*nodo)) return;
  _abb_in_order(arbol, visitar, &extra, &((*nodo)->izq));
  visitar((*nodo)->clave, (*nodo)->dato, extra);
  _abb_in_order(arbol, visitar, &extra, &((*nodo)->der));
  return;
}

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
  abb_t *abb = calloc(1, sizeof(abb_t));
  if(abb==NULL){
    return NULL;
  }
  abb->raiz = NULL;
  abb->cmp = cmp;
  abb->destruir_dato = destruir_dato;
  return abb;
}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato){
  nodo_abb_t *nodo_abb = calloc(1, sizeof(nodo_abb_t));
  if(nodo_abb==NULL){
    return false;
  }
  nodo_abb->clave = calloc(strlen(clave)+1,sizeof(char));
  if(nodo_abb->clave==NULL){
    return false;
  }
  strcpy(nodo_abb->clave, clave);
  nodo_abb->dato = dato;
  arbol->cantidad++;
  _abb_guardar(arbol, &arbol->raiz, nodo_abb);
  return true;
}

void* abb_borrar(abb_t *arbol, const char *clave){
  nodo_abb_t *padre = NULL;
  nodo_abb_t *aux = _abb_buscar(arbol, &(arbol->raiz), clave, &padre);
  nodo_abb_t *mayor = NULL;
  nodo_abb_t *padre_mayor = NULL;
  void *dato;
  char *aux_clave;
  if(!aux) return NULL;
  dato = aux->dato;
  if(!aux->der && !aux->izq){
    arbol->cantidad--;
    if(!padre) arbol->raiz = NULL;
    else if(padre->izq==aux) padre->izq = NULL;
    else padre->der = NULL;
    free(aux->clave);
    free(aux);
    return dato;
  }
  else if(!aux->izq){
    arbol->cantidad--;
    dato = aux->dato;
    aux_clave = aux->clave;
    nodo_abb_t *der = aux->der;
    aux->clave = der->clave;
    aux->dato = der->dato;
    aux->der = der->der;
    aux->izq = der->izq;
    free(aux_clave);
    free(der);
    return dato;
  }
  else{
    dato = aux->dato;
    mayor = _abb_buscar_mayor(&(aux->izq), &(padre_mayor));
    aux_clave = malloc(sizeof(char)*strlen(mayor->clave)+1);
    strcpy(aux_clave, mayor->clave);
    aux->dato = abb_borrar(arbol, aux_clave);
    free(aux->clave);
    aux->clave = aux_clave;
    return dato;
  }
}

void* abb_obtener(const abb_t *arbol, const char *clave){
  nodo_abb_t *padre = NULL;
  nodo_abb_t *actual = arbol->raiz;
  nodo_abb_t *aux = _abb_perte_obte(arbol, &actual, clave, &padre);
  if(!aux) return NULL;
  return aux->dato;
}

bool abb_pertenece(const abb_t *arbol, const char *clave){
  nodo_abb_t *padre = NULL;
  nodo_abb_t *actual = arbol->raiz;
  if(_abb_perte_obte(arbol, &actual, clave, &padre))return true;
  return false;
}

size_t abb_cantidad(abb_t *arbol){
  return arbol->cantidad;
}

void abb_destruir(abb_t *arbol){
  _abb_destruir(arbol, arbol->raiz);
  free(arbol);
  return;
}

void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra){
  _abb_in_order(arbol, visitar, extra, &(arbol->raiz));
  return;
}

bool _iter_apilar(nodo_abb_t *actual, pila_t *pila){
  if(!actual)return true;
  return pila_apilar(pila, actual) && _iter_apilar(actual->izq, pila);
}

abb_iter_t *abb_iter_in_crear(const abb_t *arbol){
  abb_iter_t *iter = calloc(1, sizeof(abb_iter_t));
  if(!iter) return NULL;
  iter->arbol = arbol;
  iter->pila = pila_crear();
  if(!iter->pila) return NULL;
  if(!_iter_apilar(arbol->raiz, iter->pila)){
    pila_destruir(iter->pila);
    return NULL;
  }
  return iter;
}

bool abb_iter_in_al_final(const abb_iter_t *iter){
  return pila_esta_vacia(iter->pila);
}

bool abb_iter_in_avanzar(abb_iter_t *iter){
  nodo_abb_t *actual;
  if(abb_iter_in_al_final(iter)) return false;
  actual = pila_desapilar(iter->pila);
  return _iter_apilar(actual->der, iter->pila);
}

const char* abb_iter_in_ver_actual(const abb_iter_t *iter){
  nodo_abb_t *actual = pila_ver_tope(iter->pila);
  return actual->clave;
}

void abb_iter_in_destruir(abb_iter_t* iter){
  pila_destruir(iter->pila);
  free(iter);
}
