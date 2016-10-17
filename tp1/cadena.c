#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

char** split(const char* str, char sep){
  char* aux = NULL;
  char** res = NULL;
  int cont = 1;
  int contres = 1;
  for(int i = 0; i<=strlen(str); i++){
    if(str[i]!=sep){
      aux = realloc(aux, sizeof(char)*cont);
      aux[cont-1] = str[i];
      cont++;
    }
    if(str[i]==sep||str[i]=='\0'){
      aux = realloc(aux, sizeof(char)*cont);
      aux[cont-1] = '\0';
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
  int contres = 1;
  char *res = NULL;
  while(strv[cont]!=NULL){
    if(strv[cont][contres-1]!='\0'){
      res = realloc(res,sizeof(char)*contres);
      res[contres-1] = strv[cont][contres-1];
      contres++;
    }
    else{
      res = realloc(res,sizeof(char)*contres);
      res[contres-1] = sep;
      contres = 1;
      cont++;
    }
    contres++;
  }
  return res;
}


