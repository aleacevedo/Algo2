#ifndef LISTA_H
#define LISTA_H

#include<stdbool.h>

/* *****************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

typedef struct lista lista_t;
typedef struct lista_iter lista_iter_t;

/* *****************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/

// Crea una cola
// Post: devuelve una nueva cola vacia
lista_t* lista_crear(void);

// Devuelve true or false dependiendo si la lista tiene un elementos
// Pre: la lista fue creada
bool lista_esta_vacia(const lista_t *lista);

// Agrega un nuevo elemento a la lista, devuelve false en caso de error
// Pre: la lista fue creada
// Post: Se agrego un nuevo elemento a lista, dato es el nuevo primero
bool lista_insertar_primero(lista_t *lista, void *dato);

// Agrega un nuevo elemento a la lista, devuelve false en caso de error
// Pre: la lista fue creada
// Post: Se agrego un nuevo elemento a lista, dato es el nuevo ultimo
bool lista_insertar_ultimo(lista_t *lista, void *dato);

// Saca el primer elemento de la lista y lo devuelve, si la lista esta vacia
// devuelve NULL
// Pre: la lista fue creada
// Post: si la lista no esta vacia devuelve el primer elemento y la lista tiene
// un elemento menos
void* lista_borrar_primero(lista_t *lista);

// Obtiene el primer elemento de la lista y lo devuelve, si la lista esta vacia
// devuelve NULL
// Pre: la lista fue creada
// Post: si la lista no esta vacia devuelve el primer elemento
void* lista_ver_primero(const lista_t *lista);

// Obtiene el ultimo elemento de la lista y lo devuelve, si la lista esta vacia
// devuelve NULL
// Pre: la lista fue creada
// Post: si la lista no esta vacia devuelve el ultimo elemento
void* lista_ver_ultimo(const lista_t* lista);

// Obtiene el largo de la lista y lo devuleve
// Pre: la lista fue creada
// Post: devuelve el largo de la lista
size_t lista_largo(const lista_t *lista);

// Destruye la lista
// Pre: la lista fue creada
// Post: la lista fue destruida y sus datos son destruidos con la funcion
// pasada por parametro, si es NULL no hace nada
void lista_destruir(lista_t *lista, void destruir_dato(void *));

/* *****************************************************************
 *                    PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/

// Crea un iterador
// Post: devuelve un iterador que recorre la lista pasada por parametro
lista_iter_t *lista_iter_crear(lista_t *lista);

// Avanza el iterador un paso, devuelve false si es el ultimo
// Pre: el iterador fue creado
// Post: el iterador esta un paso mas adelante,
bool lista_iter_avanzar(lista_iter_t *iter);

// Devuleve el dato de donde se encuentra el iterador
// Pre: el iterador fue creado
// Post: el dato devuelto es donde se encuentra el iterador
void *lista_iter_ver_actual(const lista_iter_t *iter);

// Devuelve true or false dependiendo si el iterador esta al final
// Pre: el iterador fue creado
bool lista_iter_al_final(const lista_iter_t *iter);

// Destruye el iterador
// Pre: el iterador fue creado
// Post: el iterador fue destruido
void lista_iter_destruir(lista_iter_t *iter);

// Inserta un elemento entre donde se encuentra el iterador y el paso anterior
// Pre: el iterador fue creado
// Post: hay un nuevo dato entre el paso actual y elanterior
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

// Saca el elemento actual de donde se encuentra el iterador y lo devuelve
// Pre: el iterador fue creado
// Post: el elemento es devuleto y la lista tiene un elemento menos
void *lista_iter_borrar(lista_iter_t *iter);

/* *****************************************************************
 *                    PRIMITIVAS DEL ITERADOR INTERNO
 * *****************************************************************/

// Itera la lista pasada por parametro con la funcion pasada por parametro
// Pre: la lista fue creada al igual que la funcion
void lista_iterar(lista_t *lista, bool (*visitar)(void *dato, void *extra), void *extra);

/* *****************************************************************
 *                    FUNCION DE PRUEBA
 * *****************************************************************/

void pruebas_lista_alumno(void);

#endif //COLA_H
