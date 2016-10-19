#include"abb.h"

typedef struct nodo_abb nodo_abb_t;

typedef struct abb abb_t;

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


abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
  abb_t *abb = calloc(1, sizeof(abb_t));
  if(abb==NULL){
    return NULL;
  }
  abb->cmp = cmp;
  abb->destruir_dato = destruir_dato;
  return abb;
}

bool _abb_guardar(abb_t *abb, nodo_abb_t *actual, nodo_abb_t *nuevo){
  if(actual==NULL){
    actual = nuevo;
    return true;
  }
  int compare = abb->cmp(actual->clave,nuevo->clave);
  if(compare==0){
    actual->dato = nuevo->dato;
    free(nuevo->clave);
    free(nuevo);
    return true;
  }
  else if(compare<0){
    return _abb_guardar(abb, actual->der, nuevo);
  }
  else{
    return _abb_guardar(abb, actual->izq, nuevo);
  }
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
  strcopy(nodo_abb->clave, clave);
  nodo_abb->dato = dato;
  arbol->cantidad++;
  return _abb_guardar(arbol, arbol->raiz, nodo_abb);
}

void* abb_borrar(abb_t *arbol, const char *clave){

}
