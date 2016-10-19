#ifndef ABB_H
#define ABB_H

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>


/* Defino estructuras abb abb_nodo y abb_iter */
struct abb;
struct nodo_abb;
struct abb_iter;

typedef struct abb abb_t;
typedef struct nodo_abb nodo_abb_t;
typedef struct abb_iter abb_iter_t;

/* Defino funciones de orden superiro */

typedef int (*abb_comparar_clave_t) (const char*, const char*);
typedef void (*abb_destruir_dato_t) (void*);


/* Defino primitivas */

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato);
bool abb_guardar(abb_t *arbol, const char *clave, void *dato);
void* abb_borrar(abb_t *arbol, const char *clave);





#endif //ABB_H
