#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pila/pila.h"
#include "cola/cola.h"


typedef enum{
  ESPACIO,
  NUMERO,
  OPP
}tipo_t;

typedef struct linea{
  char *caracteres;
  ssize_t largo;
}linea_t;

tipo_t es_numero(char* caracter){
  if(*caracter==' '){
    return ESPACIO;
  }
  else if(atoi(caracter)!=0){
    return NUMERO;
  }
  else{
    if(*caracter=='0'){
      return NUMERO;
    }
    return OPP;
  }
}

int main(){
  while(true){
    char *guardado = NULL;
    pila_t *pila_num = pila_crear();
    cola_t *cola_opp = cola_crear();
    linea_t *linea = calloc(1,sizeof(linea_t));
    size_t cont = 0;
    size_t capacidad = 0;
    linea->caracteres = NULL;
    linea->largo = getline(&linea->caracteres, &capacidad, stdin);
    if(linea->largo==-1){
      pila_destruir(pila_num);
      cola_destruir(cola_opp, NULL);
      free(linea->caracteres);
      free(linea);
      break;
    }
    size_t i = 1;
    while(linea->caracteres[cont]!='\n'){
      if(es_numero(&linea->caracteres[cont])==ESPACIO){
        guardado = realloc(guardado, sizeof(char)*i);
        guardado[i-1] = '\0';
        if(es_numero(guardado)==NUMERO){
          int *num = calloc(1, sizeof(int));
          *num = atoi(guardado);
          free(guardado);
          pila_apilar(pila_num, num);
        }
        else{
          cola_encolar(cola_opp, guardado);
        }
        i = 1;
        guardado = NULL;
      }
      else if (es_numero(&linea->caracteres[cont])==NUMERO){
        guardado = realloc(guardado, sizeof(char)*i);
        guardado[i-1] = linea->caracteres[cont];
        i++;
      }
      else{
          guardado = calloc(1, sizeof(char));
          guardado[0] = linea->caracteres[cont];
          i++;
        }
      cont++;
    }
    if(es_numero(&linea->caracteres[cont-1])!=ESPACIO){
      guardado = realloc(guardado, sizeof(char)*i);
      guardado[i-1] = '\0';
      cola_encolar(cola_opp, guardado);
    }
    free(linea->caracteres);
    free(linea);
    while(!cola_esta_vacia(cola_opp)){
      char *opp = cola_desencolar(cola_opp);
      int *num1 = pila_desapilar(pila_num);
      int *num2 = pila_ver_tope(pila_num);
      if(*opp=='+'){
        *num2 = *num1 + *num2;
      }

      if(*opp=='-'){
        *num2 = *num1 - *num2;
      }
      if(*opp=='*'){
        *num2 = *num1 * *num2;
      }
      if(*opp=='/'){
        *num2 = *num1 / *num2;
      }
      free(num1);
      free(opp);
    }
    printf("%i\n",*(int*)pila_ver_tope(pila_num));
    free(pila_ver_tope(pila_num));
    pila_destruir(pila_num);
    cola_destruir(cola_opp, NULL);
    //break;
  }
}
