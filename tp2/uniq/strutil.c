#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strutil.h"

char** split(const char* str, char sep){
  int k=0;
  int contador=1;
  if (sep=='\0'){
    return NULL;
  }
  int i=0;
  if(str[0]=='\0'){
    char** arreglo=calloc(sizeof(char*),2);
    char *mini_str =calloc(sizeof(char),1);
    mini_str[0]='\0';
    arreglo[0]=mini_str;
    arreglo[1]=NULL;
    return arreglo;
  }
  while(str[i]!='\0'){
    if (str[i]==sep) contador++;
    i++;
  }
  i=0;
  char* copia=calloc(sizeof(char),strlen(str)+1);
  char** vec=calloc(sizeof(char*),contador+1);
  strncpy(copia, str,strlen(str));
   int ult=0;
   while(copia[i]!='\0'){
       if(copia[i]==sep){
         copia[i]='\0';
         size_t tam_string=(i-ult);
         char* mini_str=calloc(sizeof(char),tam_string+1);
         strcpy(mini_str,&copia[ult]);
         vec[k]=mini_str;
         ult=(i+1);
         k++;
       }
       if(copia[i+1]=='\0'){
         size_t tam_string=(i-ult+1);
         char* mini_str=calloc(sizeof(char),tam_string+1);
         strncpy(mini_str,&copia[ult],tam_string);
         vec[k]=mini_str;
         vec[k+1]=NULL;
       }

     i++;
   }
  free(copia);
  return vec;
}

char* join(char** strv, char sep){
  int i=0;
  char* cadena=calloc(sizeof(char),1);
  char* barra_cero = calloc(sizeof(char),2);
  barra_cero[0]=sep;
  barra_cero[1]='\0';
  while (strv[i]!= NULL){
    size_t tam_elemento=strlen(strv[i]);
    size_t tam_cadena=strlen(cadena);
    cadena = realloc(cadena,tam_elemento+tam_cadena+2);
    strcat(cadena,strv[i]);
    if(strv[i+1]!=NULL){
      strncat(cadena,barra_cero,2);
      }
    i++;
  }
  free(barra_cero);
  return (char*)cadena;
}

void free_strv(char* strv[]){
  int i = 0;
  while(strv[i]){
    free(strv[i]);
    i++;
  }
  free(strv);
}
