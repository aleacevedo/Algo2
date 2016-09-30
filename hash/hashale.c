#include "hash.h"

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
  size_t borrados;
  size_t n_mersenne;
};

struct hash_iter{
  const hash_t *hash;
  size_t pos;
};

hash_t *hash_crear(hash_destruir_dato_t destruir_dato){
  hash_t *hash = malloc(sizeof(hash_t));
  if(hash==NULL){
    return NULL;
  }
  hash->destruir_dato = destruir_dato;
  hash->indice = malloc(sizeof(nodo_hash_t)*TAM_INICIAL);
  if(hash->indice==NULL){
    return NULL;
  }
  hash->largo = TAM_INICIAL;
  hash->cant_elementos = 0;
  hash->borrados = 0;
  hash->n_mersenne = 0;
  for(int i=0; i<TAM_INICIAL; i++){
    hash->indice[i].dato=NULL;
    hash->indice[i].estado=0;
    hash->indice[i].clave=NULL;
  }
  return hash;
}

bool hash_guardar(hash_t *hash, const char* clave, void* dato){
  Fnv32_t hash_clave = fnv_32_str(clave, FNV1_32_INIT);
  hash_clave = hash_clave % (int)hash->largo;
  nodo_hash_t *nodo_hash = &(hash->indice[hash_clave]);
  int comp = 0;
  while(nodo_hash->estado == ocupado){
    comp=strcmp(nodo_hash->clave,clave);
    if(comp == 0){
      nodo_hash->dato = dato;
    }
    if(hash_clave<hash->largo){
      nodo_hash++;
      hash_clave++;
    }
    else{
      nodo_hash = hash->indice;
      hash_clave = 0;
    }
  }
  nodo_hash->clave = malloc(sizeof(char)*strlen(clave));
  if(nodo_hash->clave==NULL){
    return false;
  }
  for(int i = 0; i<strlen(clave); i++){
    nodo_hash->clave[i] = clave[i];
  }
  //nodo_hash->dato = malloc(sizeof(void*));
  nodo_hash->dato = dato;
  nodo_hash->estado = ocupado;
  hash->cant_elementos++;
  return true;
}

void *hash_borrar(hash_t *hash, const char *clave){
  Fnv32_t hash_clave = fnv_32_str(clave, FNV1_32_INIT);
  hash_clave = hash_clave % (int)hash->largo;
  Fnv32_t primer_hash= hash_clave;
  nodo_hash_t *nodo_hash = &(hash->indice[hash_clave]);

  while(nodo_hash->clave==NULL||strcmp(nodo_hash->clave,clave)){
//    printf("DEBUG: %i\n", hash_clave);
    if(hash_clave < hash->largo-1){
      nodo_hash++;
      hash_clave++;
    }
    else{
      nodo_hash = hash->indice;
      hash_clave = 0;
    }
    if(hash_clave == primer_hash){
      return NULL;
    }
  }
  if(nodo_hash->estado==borrado){
    return NULL;
  }
  nodo_hash->estado = borrado;
  hash->cant_elementos--;
  return nodo_hash->dato;
}
