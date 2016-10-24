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
  if(*actual==NULL){
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

nodo_abb_t* _abb_buscar_mayor(nodo_abb_t **actual, nodo_abb_t **padre){
  if((*actual)->der){
    *padre = *actual;
    return _abb_buscar_mayor(&(*actual)->der, padre);
  }
  return *actual;
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

void* abb_obtener(abb_t *arbol, const char *clave){
  nodo_abb_t *padre = NULL;
  nodo_abb_t *aux = _abb_buscar(arbol, &(arbol->raiz), clave, &padre);
  if(!aux) return NULL;
  return aux->dato;
}

bool abb_pertenece(abb_t *arbol, const char *clave){
  nodo_abb_t *padre = NULL;
  if(_abb_buscar(arbol, &(arbol->raiz), clave, &padre))return true;
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
