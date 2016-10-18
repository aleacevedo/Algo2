#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

char* caracter_copy(char* cadena, int nwlen, char caracter){
  cadena = realloc(cadena, sizeof(char)*nwlen);
  if(cadena == NULL) return NULL;
  cadena[nwlen-1] = caracter;
  return cadena;
}

char** split(const char* str, char sep){
  char* aux = NULL;
  char** res = NULL;
  int cont = 1;
  int contres = 1;
  for(int i = 0; i<=strlen(str); i++){
    if(str[i]!=sep){
      aux = caracter_copy(aux, cont, str[i]);
      if(aux == NULL) return NULL;
      cont++;
    }
    if(str[i]==sep||str[i]=='\0'){
      aux = caracter_copy(aux, cont, '\0');
      if(aux == NULL) return NULL;
      cont = 1;
      res = realloc(res, sizeof(char*)*contres);
      res[contres-1] = aux;
      aux = NULL;
      contres++;
    }
    res = realloc(res,sizeof(char*)*contres);
    res[contres-1] = NULL;
  }
  return res;
}

char *join(char** strv, char sep){
  int cont = 0;
  int i = 1;
  int contres = 1;
  char *res = NULL;
  while(strv[cont]!=NULL){
    if(strv[cont][contres-1]!='\0'){
      res = caracter_copy(res, i, strv[cont][contres-1]);
      if(res == NULL) return NULL;
      contres++;
    }
    else{
      res = caracter_copy(res, i, sep);
      if(res == NULL) return NULL;
      contres = 1;
      cont++;
    }
    i++;
  }
  res[i-2] = '\0';
  return res;
}
