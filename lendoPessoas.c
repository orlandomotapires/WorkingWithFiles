#include <stdlib.h>
#include <stdio.h>
#define NUM_PESSOA 3

typedef struct{
  char nome[50];
  int idade;
}tp_pessoa;

void grava_dados(FILE *arq);
void le_dados(FILE *arq);

int main(){
  char nomearq[50];
  FILE *arq = NULL;
  printf("Digite o nome do arquivo.\n");
  gets(nomearq);

  gets(nomearq);
  return 0;
}