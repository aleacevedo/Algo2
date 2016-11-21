#ifndef ABB_H
#define ABB_H

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "pila.h"



/* Defino estructuras abb abb_nodo y abb_iter */
struct abb;
struct nodo_abb;
struct abb_iter;

typedef struct abb abb_t;
typedef struct nodo_abb nodo_abb_t;
typedef struct abb_iter abb_iter_t;
typedef struct abb_iter_post abb_iter_post_t;

/* Defino funciones de orden superiro */

typedef int (*abb_comparar_clave_t) (const char*, const char*);
typedef void (*abb_destruir_dato_t) (void*);


/* Defino primitivas */

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato);
bool abb_guardar(abb_t *arbol, const char *clave, void *dato);
void* abb_borrar(abb_t *arbol, const char *clave);
void* abb_obtener(const abb_t *arbol, const char *clave);
bool abb_pertenece(const abb_t *arbol, const char *clave);
size_t abb_cantidad(abb_t *arbol);
void abb_destruir(abb_t *arbol);

void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra);
void abb_post_order(abb_t* arbol, bool (*visitar)(const char*, void*, void*), void* extra);

abb_iter_t *abb_iter_in_crear(const abb_t *arbol);
bool abb_iter_in_avanzar(abb_iter_t *iter);
const char *abb_iter_in_ver_actual(const abb_iter_t *iter);
bool abb_iter_in_al_final(const abb_iter_t *iter);
void abb_iter_in_destruir(abb_iter_t* iter);

abb_iter_post_t*  abb_iter_post_crear(const abb_t* arbol);
bool  abb_iter_post_avanzar(abb_iter_post_t* iter);
const char*  abb_iter_post_ver_actual(const abb_iter_post_t* iter);
bool  abb_iter_post_al_final(const abb_iter_post_t* iter);
void  abb_iter_post_destruir(abb_iter_post_t* iter);

#endif //ABB_H
