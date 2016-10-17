#include"cadena.h"

char** split(const char* str, char sep);

int main(){
  char *str = {"abc,def,ghi"};
  char **strsplit;
  int i = 0;
  printf("%s\n", str);
  strsplit = split(str, ',');
  while(strsplit[i]!=NULL){
    printf("%s\n", strsplit[i]);
    i++;
  }
  return 0;
}
