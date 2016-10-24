#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

char* caracter_copy(char* cadena, int nwlen, char caracter){
  /* Redimenciona la cadena pasada por parametro al nuevo tamaño tambien pasado
  por parametro y agrega un caracter al final*/
  cadena = realloc(cadena, sizeof(char)*nwlen);
  if(!cadena) return NULL;
  cadena[nwlen-1] = caracter;
  return cadena;
}

void free_strv(char* strv[]){
  /* Libera un array compuesto por cadenas*/
  int i = 0;
  while(strv[i]!=NULL){
    free(strv[i]);
    i++;
  }
  free(strv);
}

char** split(const char* str, char sep){
  /* Separa una cadena por el caracter que pasa el usuario por parametro
  y devuelve un array con estas nuevas cadenas*/
  char* aux = NULL;
  char** res = NULL;
  int cont = 1;
  int contres = 1;
  if(sep=='\0') return NULL;
  for(int i = 0; i<=strlen(str); i++){
    if(str[i]!=sep){
      aux = caracter_copy(aux, cont, str[i]);
      if(!aux) return NULL;
      cont++;
    }
    if(str[i]==sep||str[i]=='\0'){
      aux = caracter_copy(aux, cont, '\0');
      if(!aux) return NULL;
      cont = 1;
      res = realloc(res, sizeof(char*)*contres);
      if(!res) return NULL;
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
  /* Concatena un array en una sola cadena separando cada componente con el
  separador pasado por parametro*/
  int cont = 0;
  size_t largo = 0;
  char *res = calloc(1,sizeof(char));
  if(!res) return NULL;
  *res = '\0';
  if(!strv || !strv[0]){
    return res;
  }
  while(strv[cont]!=NULL){
    largo = (strlen(strv[cont])+(strlen(res)+2));
    res = realloc(res, sizeof(char)*largo);
    strcat(res, strv[cont]);
    res[largo-2] = sep;
    res[largo-1] = '\0';
    cont++;

  }
  res[largo-2] = '\0';
  return res;
}
