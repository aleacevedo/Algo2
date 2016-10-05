#include "hash.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "fnv.h"

#define TAM_INICIAL (100)

typedef enum state{
  vacio,
  ocupado,
  borrado,
}state_t;

typedef struct nodo_hash{
  void *dato;
  state_t estado;
  char *clave;
} nodo_hash_t;

struct hash{
  hash_destruir_dato_t destruir_dato;
  nodo_hash_t *indice;
  size_t largo;
  size_t cant_elementos;
  size_t n_mersenne;
};

struct hash_iter{
  const hash_t *hash;
  nodo_hash_t *actual;
  size_t pos;
};

nodo_hash_t *avanzar_nodo(const hash_t *hash, nodo_hash_t *nodo_hash, const char* clave, Fnv32_t *hash_clave){
  if(*hash_clave < hash->largo-1){
    nodo_hash++;
    (*hash_clave)++;
  }
  else{
    nodo_hash = hash->indice;
    (*hash_clave) = 0;
  }
  return nodo_hash;
}

nodo_hash_t *encontrar_nodo(const hash_t *hash, const char* clave){
  Fnv32_t hash_clave = fnv_32_str(clave, FNV1_32_INIT);
  hash_clave = hash_clave % (int)hash->largo;
  nodo_hash_t *nodo_hash = &(hash->indice[hash_clave]);
  while(nodo_hash->estado!=vacio){
    if(nodo_hash->estado==ocupado){
      if(strcmp(nodo_hash->clave,clave)==0){
        return nodo_hash;
      }
    }
    nodo_hash = avanzar_nodo(hash, nodo_hash, clave, &hash_clave);
  }
  if(nodo_hash->estado==vacio){
    return nodo_hash;
  }
  return nodo_hash;
}

hash_t *hash_crear_tam_mod(hash_destruir_dato_t destruir_dato, size_t tam){
  hash_t *hash = calloc(1,sizeof(hash_t));
  if(hash==NULL){
    return NULL;
  }
  hash->destruir_dato = destruir_dato;
  hash->indice = calloc(tam, sizeof(nodo_hash_t));
  if(hash->indice==NULL){
    return NULL;
  }
  hash->largo = tam;
  return hash;
}

bool hash_redimensionar(hash_t *hash, size_t tam_nuevo){
  nodo_hash_t *aux = hash->indice;
  size_t tam_aux = hash->largo;
  hash->indice = calloc(tam_nuevo, sizeof(nodo_hash_t));
  //hash_iter_t *iter = hash_iter_crear(hash);
  if(hash->indice==NULL || aux == NULL){
    hash->indice = aux;
    return false;
  }
  hash->cant_elementos = 0;
  hash->largo=tam_nuevo;
  for(int i = 0; i<tam_aux; i++){
    if(aux[i].estado==ocupado){
      hash_guardar(hash,aux[i].clave,aux[i].dato);
      free(aux[i].clave);
    }
  }
  free(aux);
  return true;
}

size_t calcular_carga(hash_t *hash){
  size_t resultado = ((hash->cant_elementos)/(hash->largo))*100;
  return resultado;
}

hash_t *hash_crear(hash_destruir_dato_t destruir_dato){
  return hash_crear_tam_mod(destruir_dato, TAM_INICIAL);
}

bool hash_guardar(hash_t *hash, const char* clave, void* dato){
  nodo_hash_t *nodo_hash = encontrar_nodo(hash, clave);
  if(nodo_hash->estado==ocupado){
    if(hash->destruir_dato!=NULL){
        hash->destruir_dato(nodo_hash->dato);
      }
    nodo_hash->dato=dato;
    return true;
  }
  nodo_hash->clave = calloc(strlen(clave)+1,sizeof(char));
  if(nodo_hash->clave==NULL){
    return false;
  }
  for(int i = 0; i<strlen(clave); i++){
    nodo_hash->clave[i] = clave[i];
  }
  nodo_hash->dato = dato;
  hash->cant_elementos+=1;
  nodo_hash->estado = ocupado;
  if(calcular_carga(hash)>80){
    printf("DEBUG Redim UP\n");
    hash_redimensionar(hash, hash->largo*5);
  }
  return true;
}

void *hash_borrar(hash_t *hash, const char *clave){
  void *dato;
  nodo_hash_t *nodo_hash = encontrar_nodo(hash, clave);
  if(nodo_hash->estado!=ocupado){
    return NULL;
  }
  nodo_hash->estado = borrado;
  free(nodo_hash->clave);
  hash->cant_elementos-=1;
  dato = nodo_hash->dato;
  if(calcular_carga(hash)<5){
    printf("DEBUG Redim DW\n");
    if(hash->cant_elementos==0){
      hash_redimensionar(hash, TAM_INICIAL);
    }
    else{
      hash_redimensionar(hash, (size_t)((double)hash->cant_elementos/0.3));
    }
  }
  return dato;
}

void *hash_obtener(const hash_t *hash, const char *clave){
  nodo_hash_t *nodo_hash = encontrar_nodo(hash, clave);
  if(nodo_hash->estado!=ocupado){
    return NULL;
  }
  return nodo_hash->dato;
}

bool hash_pertenece(const hash_t *hash, const char *clave){
  nodo_hash_t *nodo_hash = encontrar_nodo(hash, clave);
  if(nodo_hash->estado!=ocupado){
    return false;
  }
  return true;
}

size_t hash_cantidad(const hash_t *hash){
  size_t aux = hash->cant_elementos;
  return aux;
}

void hash_destruir(hash_t *hash){
  nodo_hash_t *nodo_hash = hash->indice;
  for(int i = 0; i<hash->largo; i++){
    if(nodo_hash->estado == ocupado){
      free(nodo_hash->clave);
      if(hash->destruir_dato!=NULL){
        hash->destruir_dato(nodo_hash->dato);
      }
    }
    nodo_hash++;
  }
  free(hash->indice);
  free(hash);
}

hash_iter_t *hash_iter_crear(const hash_t *hash){
  hash_iter_t *hash_iter = calloc(1,sizeof(hash_iter_t));
  if (hash_iter==NULL){
    return NULL;
  }
  hash_iter->hash = hash;
  hash_iter->actual = hash->indice;
  hash_iter->pos = 1;
  if(hash_iter->hash->cant_elementos==0){
    return hash_iter;
  }
  while(hash_iter->actual->estado!=ocupado){
    hash_iter->actual++;
  }
  return hash_iter;
}

bool hash_iter_avanzar(hash_iter_t *iter){
  if(hash_iter_al_final(iter)){
    return false;
  }
  if(iter->pos==iter->hash->cant_elementos){
    iter->pos++;
    iter->actual = NULL;
    return true;
  }
  iter->actual++;
  while(iter->actual->estado!=ocupado){
    iter->actual++;
  }
  iter->pos++;
  return true;
}

const char *hash_iter_ver_actual(const hash_iter_t *iter){
  if(hash_iter_al_final(iter)){
    return NULL;
  }
  return iter->actual->clave;
}

bool hash_iter_al_final(const hash_iter_t *iter){
  if(iter->pos>iter->hash->cant_elementos){
    return true;
  }
  return false;
}

void hash_iter_destruir(hash_iter_t* iter){
  free(iter);
}
