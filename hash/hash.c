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

nodo_hash_t *encontrar_nodo(const hash_t *hash, nodo_hash_t *nodo_hash, const char* clave, Fnv32_t hash_clave){
  Fnv32_t primer_hash = hash_clave;
  int i =0;
  while(nodo_hash->clave==NULL){
    i++;
    nodo_hash = avanzar_nodo(hash, nodo_hash, clave, &hash_clave);
    if(hash_clave==primer_hash){
      return NULL;
    }
  }
  while(strcmp(nodo_hash->clave,clave)!=0){
    nodo_hash = avanzar_nodo(hash, nodo_hash, clave, &hash_clave);
    if(hash_clave==primer_hash){
      return NULL;
    }
    while(nodo_hash->clave==NULL){
      nodo_hash = avanzar_nodo(hash, nodo_hash, clave, &hash_clave);
      if(hash_clave==primer_hash){
        return NULL;
      }
    }
  }
  return nodo_hash;
}

hash_t *hash_crear_tam_mod(hash_destruir_dato_t destruir_dato, size_t tam){
  hash_t *hash = calloc(sizeof(hash_t),1);
  if(hash==NULL){
    return NULL;
  }
  hash->destruir_dato = destruir_dato;
  hash->indice = calloc(sizeof(nodo_hash_t),tam);
  if(hash->indice==NULL){
    return NULL;
  }
  hash->largo = tam;
  return hash;
}

bool hash_redimencionar(hash_t *hash, size_t tam_nuevo){
  nodo_hash_t *aux = hash->indice;
  hash->indice = calloc(sizeof(nodo_hash_t), tam_nuevo);
  //hash_iter_t *iter = hash_iter_crear(hash);
  if(hash->indice==NULL){
    hash->indice = aux;
    return false;
  }
  hash->largo=tam_nuevo;
  for(int i = 0; i<hash->largo; i++){
    aux=aux+i;
    if(aux->estado==ocupado){
      hash_guardar(hash,aux->clave,aux->dato);
    }
    if(aux->estado!=vacio){
      free(aux->clave);
    }
  }
  free(aux);
  return true;
}

size_t calcular_carga(hash_t *hash){
  size_t resultado = ((hash->borrados + hash->cant_elementos)/(hash->largo))*100;
  return resultado;
}

hash_t *hash_crear(hash_destruir_dato_t destruir_dato){
  return hash_crear_tam_mod(destruir_dato, TAM_INICIAL);
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
      return true;
    }
    if(hash_clave<hash->largo-1){
      nodo_hash++;
      hash_clave++;
    }
    else{
      nodo_hash = hash->indice;
      hash_clave = 0;
    }
  }
  if(nodo_hash->estado==vacio){
    nodo_hash->clave = calloc(sizeof(char),strlen(clave)+1);
    if(nodo_hash->clave==NULL){
      return false;
    }
  }
  for(int i = 0; i<strlen(clave); i++){
    nodo_hash->clave[i] = clave[i];

  }
  nodo_hash->dato = dato;
  hash->cant_elementos+=1;
  nodo_hash->estado = ocupado;
  if(calcular_carga(hash)>70){
    hash_redimencionar(hash, hash->cant_elementos*100);
  }
  return true;
}

void *hash_borrar(hash_t *hash, const char *clave){
  Fnv32_t hash_clave = fnv_32_str(clave, FNV1_32_INIT);
  hash_clave = hash_clave % (int)hash->largo;
  nodo_hash_t *nodo_hash = &(hash->indice[hash_clave]);
  void *dato;
  nodo_hash = encontrar_nodo(hash, nodo_hash, clave, hash_clave);
  if(nodo_hash==NULL){
    return NULL;
  }
  if(nodo_hash->estado==borrado){
    return NULL;
  }
  nodo_hash->estado = borrado;
  hash->cant_elementos-=1;
  hash->borrados++;
  dato = nodo_hash->dato;
  if(calcular_carga(hash)<10){
    hash_redimencionar(hash, (hash->largo/2));
  }
  return dato;
}

void *hash_obtener(const hash_t *hash, const char *clave){
  Fnv32_t hash_clave = fnv_32_str(clave, FNV1_32_INIT);
  hash_clave = hash_clave % (int)hash->largo;
  nodo_hash_t *nodo_hash = &(hash->indice[hash_clave]);
  nodo_hash = encontrar_nodo(hash, nodo_hash, clave, hash_clave);
  if(nodo_hash==NULL || nodo_hash->estado==borrado){
    return NULL;
  }
  return nodo_hash->dato;
}

bool hash_pertenece(const hash_t *hash, const char *clave){
  Fnv32_t hash_clave = fnv_32_str(clave, FNV1_32_INIT);
  hash_clave = hash_clave % (int)hash->largo;
  nodo_hash_t *nodo_hash = &(hash->indice[hash_clave]);
  nodo_hash = encontrar_nodo(hash, nodo_hash, clave, hash_clave);
  if(nodo_hash==NULL || nodo_hash->estado==borrado){
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
    if(nodo_hash->estado != vacio){
      free(nodo_hash->clave);
      if(nodo_hash->estado == ocupado && hash->destruir_dato!=NULL){
        hash->destruir_dato(nodo_hash->dato);
      }
    }
    nodo_hash++;
  }
  free(hash->indice);
  free(hash);
}

hash_iter_t *hash_iter_crear(const hash_t *hash){
  hash_iter_t *hash_iter = calloc(sizeof(hash_iter_t),1);
  if (hash_iter==NULL){
    return NULL;
  }
  hash_iter->hash = hash;
  hash_iter->actual = hash->indice;
  hash_iter->pos = 1;
  if(hash_iter->actual == NULL){
    while(hash_iter->actual->estado!=ocupado){
    hash_iter->actual++;
    }
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
