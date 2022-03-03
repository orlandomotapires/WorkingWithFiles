#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "arquivo.h"

int main(){
//   int i, n, x=0;
  setlocale(LC_ALL, "portuguese");
  int opcao;
  char nomearq[50];
  FILE *arq;
  opcao = menu();
  fflush(stdin);
  printf("Digite o nome do arquivo: ");
  gets(nomearq); //scanf("%[^\n]s", nomearq);
  switchOption(opcao, nomearq, arq);
  // mostraArquivoTela(arq, nomearq);
  return 1;
}
