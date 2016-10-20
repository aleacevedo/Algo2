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

bool soy_raiz(abb_t *abb,const char* clave_yo){
  return strcmp(abb->raiz->clave,clave_yo)==0;
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

nodo_abb_t* _abb_buscar(abb_t *abb, nodo_abb_t *actual, const char* clave, nodo_abb_t *padre){
  if(actual==NULL){
    return NULL;
  }
  if(!padre) padre=actual;
  int compare = abb->cmp(actual->clave,clave);
  if(compare==0){
    return actual;
  }
  else if(compare<0){
    padre = actual;
    return _abb_buscar(abb, actual->der, clave, padre);
  }
  else{
    padre = actual;
    return _abb_buscar(abb, actual->izq, clave, padre);
  }
}

nodo_abb_t* _abb_buscar_mayor(nodo_abb_t *actual, nodo_abb_t *padre){
  if(actual->der){
    padre = actual;
    return _abb_buscar_mayor(actual->der, padre);
  }
  return actual;
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
  printf("DEBUG Clave: %s\n",clave);
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
  printf("quiero borrar: %s\n", clave);
  printf("raiz: %s\n",arbol->raiz->clave );
  if (arbol->raiz->izq) printf("hijo izq: %s\n",arbol->raiz->izq->clave );
  else printf("hijo izq NULL\n");
  if(arbol->raiz->der) printf("hijo der:%s\n", arbol->raiz->der->clave);
  else printf("hijo der NULL\n");
  nodo_abb_t *padre = NULL;
  nodo_abb_t *padre_mayor = NULL;
  nodo_abb_t *aux = _abb_buscar(arbol, arbol->raiz, clave, padre);
  if (padre) printf("padre: %s\n", padre->clave);
  nodo_abb_t *mayor = NULL;
  void *dato;
  if(!aux){
    return NULL;
  }
  /* si quiero borrar la raiz tengo este algoritmo, sino es raiz ejecuto el else*/

  if(soy_raiz(arbol,clave)){
    if(!aux->izq && !aux->der){
      dato=aux->dato;
      free(aux->clave);
      free(aux);
      return dato;
    }
    if(aux->izq && !aux->der){
      dato=aux->dato;
      arbol->raiz=aux->izq;
      free(aux->clave);
      free(aux);
      return dato;
    }

    dato=aux->dato;
    padre_mayor=aux;
    if(aux->izq){        //si no tengo h.izq estaria queriendo buscar el hijo de un null y me daria error
      mayor= _abb_buscar_mayor(aux->izq,padre_mayor);
    }
    else{
      arbol->raiz=aux->der;
      free(aux->clave);
      free(aux);
      return dato;
    }
    if(arbol->raiz->izq != mayor){
      mayor->izq=aux->izq;
    }
    else{
      mayor->izq =NULL;
    }
    mayor->der=arbol->raiz->der;
    arbol->raiz=mayor;
    free(aux->clave);
    free(aux);
    return dato;
  }
/*Si llego aca es porque no quiero borrar la raiz*/
  if(!aux->der && !aux->izq){
      if(strcmp(padre->izq->clave,aux->clave)==0){
        padre->izq=NULL;
      }
      else{
        padre->der=NULL;
      }
      dato=aux->dato;
      free(aux->clave);
      free(aux);
      return dato;
    }
  if(!aux->der && aux->izq){
    if(strcmp(padre->izq->clave,aux->clave)==0){
      padre->izq=aux->izq;
    }
    else{
      padre->der=aux->izq;
    }
    dato=aux->dato;
    free(aux->clave);
    free(aux);
    return dato;
  }
  if(aux->der && !aux->izq){
    mayor=_abb_buscar_mayor(aux->der,padre_mayor);     //me muevo hacia los mayores entonces yo soy el padre del mayor(por ahora)
    if(strcmp(padre->izq->clave,aux->clave)){
      padre->izq=mayor->izq;
    }
    else{
      padre->der=mayor->izq;
    }
    if(!padre_mayor){
      padre_mayor=aux;        //si no tengo padre mayor, yo soy el padre de mi hijo mas grande
    }
    else{
      padre_mayor->der=mayor->izq;
    }
    mayor->izq=aux->izq;
    if(strcmp(mayor->clave,aux->der->clave)==0){//si el mayor que le sigue al que quiero borrar soy yo mismo, lo apunto a null
      mayor->der=NULL;
    }
    mayor->der=aux->der;
    dato=aux->dato;
    free(aux->clave);
    free(aux);
    return dato;

  }
/* Si llego aca no soy raiz y tengo 2 hijos*/
  padre_mayor=aux;
  mayor=_abb_buscar_mayor(aux->izq,padre_mayor);
  if(!padre_mayor){ //SI NO TENGO PADRE MAYOR ES PORQUE _abb_buscar_mayor NO SE MOVIO, SIGNIFICA QUE NO TENGO HIJOS DERECHOS
    padre_mayor=aux; // LA FUNCION NO ME CAMBIO A PADRE MAYOR, ACA IGUALO PERO SOLO ES PARA RECORDARLO.
    mayor->der=aux->der;
    /* Esto es para quien apuntaba a el que quiero boorar, yo a priori no se si soy hijo izq o der */
    if(strcmp(padre->der->clave,aux->clave)==0){
      padre->der=mayor; //apunto a mi nuevo nodo ya q el aux tiene que ser borrado y reemplazado por el mayor de los menores
    }
    else{
      padre->izq=mayor;
    }
  }
  /* Si existe padre mayor SIGNIFICA que el padre del mayor NO es el que quiero borrar.*/
  else{
    if(strcmp(padre->der->clave,aux->clave)==0){
      padre->der=mayor;
    }
    else{
      padre->izq=mayor;
    }
    padre_mayor->der=mayor->izq;
    mayor->izq=aux->izq;
    mayor->der=aux->der;
  }
  dato=aux->dato;
  free(aux->clave);
  free(aux);
  return dato;
  }

  /* ESTO ES LO VIEJO :) */

//   if(aux->der && aux->izq){
//     mayor = _abb_buscar_mayor(aux->der, padre);
//     if(padre_mayor){
//       padre_mayor->der = mayor->izq;
//     }
//     if(padre){
//       mayor->der = aux->der;
//       mayor->izq = aux->izq;
//       padre = mayor;
//     }
//     else{
//       mayor->der = arbol->raiz->der;
//       arbol->raiz = mayor;
//     }
//   }
//   else if(aux->der){
//     if(padre){
//       padre->
//     }
//   }
//   free(aux->clave);
//   free(aux);
//   return dato;
// }
