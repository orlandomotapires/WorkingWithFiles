#ifndef arquivo
#define arquivo
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct{
  char name[256];
  int idade;
}tp_pessoa;

int ler_formatado_e_mostra_em_tela(FILE *arq, char nomearq[]){
  float nota1, nota2, nota3;
  arq = fopen(nomearq, "r");
  if(!arq) return 0; 
  while(fscanf(arq, "%f %f %f", &nota1, &nota2, &nota3)!= EOF)
    printf("Nota 1: %.1f Nota2: %.1f Nota3: %.1f\n", nota1, nota2, nota3);
  fclose(arq);
  return 1;
}

int ler_alterar_geral(FILE *arq, char nomearq[]){
  float notas[3][3];
  char registro[200];
  int i = 0;
  arq = fopen(nomearq, "r+");
  if(!arq) return 0;
  while(fscanf(arq, "%f %f %f", &notas[i][0], &notas[i][1], &notas[i][2]) != EOF){
    printf("\nAluno %d\n", i+1);
    printf("Nota 1 - Atual: %.1f Nova: ", notas[i][0]);
    scanf("%f", &notas[i][0]);
    printf("Nota 2 - Atual: %.1f Nova: ", notas[i][1]);
    scanf("%f", &notas[i][1]);
    printf("Nota 3 - Atual: %.1f Nova: ", notas[i][2]);
    scanf("%f", &notas[i][2]);
    i++;
  }
  rewind(arq);
  for(int i=0; i < 3; i++){
    sprintf(registro, "%.1f %.1f %.1f\n", notas[i][0], notas[i][1], notas[i][2]);
    fputs(registro, arq);
  }
  fclose(arq);
  return 1;
}

int gravar(FILE *arq, char nomearq[]){
  char mensagem[50];
  arq = fopen(nomearq,"w");
  if(!arq) return 0;
  printf("Digite a mensagem que deseja gravar no arquivo:\n");
  gets(mensagem);
  fprintf(arq, strcat(mensagem,"\n"));
  return 1;
}

int gravarDuasMensagens(FILE *arq, char nomearq[]){
  char mensagem[50];
  arq = fopen(nomearq,"w");
  if(!arq) return 0;
  printf("Digite mensagem 1 para gravar no arquivo:\n");
  fflush(stdin);
  gets(mensagem);
  fprintf(arq, strcat(mensagem,"\n"));
  printf("Digite mensagem 2 para gravar no arquivo:\n");
  fflush(stdin);
  gets(mensagem);
  fprintf(arq, strcat(mensagem,"\n"));
  return 1;
}

int alterar_no_final(FILE *arq, char nomearq[]){
  char mensagem[50];
  arq = fopen(nomearq,"a");
  if(!arq) return 0;
  printf("Digite a mensagem para gravar no arquivo: ");
  gets(mensagem);
  fprintf(arq, "\n%s", mensagem);
  fclose(arq);
  return 1;
} 

int mostraArquivoTela(FILE *arq, char nomearq[]){
  char mensagem[50];
  arq = fopen(nomearq,"r");
  if (!arq) return 0;
  printf("\n=-=-=-=-=-=-=-=-=-=-=Arquivo=-=-=-=-=-=-=-=-=-=-= \n");
  while(!feof(arq)){
    fgets(mensagem, 50, arq);
    printf("%s", mensagem);
  }
  return 1;
}

int reajustarArquivoComMais1Ponto(FILE *arq, char nomearq[]){
  int tam = 50;
  char mensagem[tam];
  arq = fopen(nomearq,"r+");
  FILE *arq2 = fopen("teste2.txt", "a+");
  if (!arq) return 0;
  while(!feof(arq)){
    fgets(mensagem, tam, arq);
    for(int i=0; i < tam; i++){
      if(isdigit(mensagem[i])){ 
          if(mensagem[i] == '9'){
            mensagem[i] = '1';
            mensagem[i+1] = '0';
          } else if(mensagem[i] != '0' && mensagem[i-1] != '1'){
             if(mensagem[i] != '1' && mensagem[i+1] != '0')     
             mensagem[i] += 1;
          } if(mensagem[i] == '1' && mensagem[i+1] != '0') mensagem[i] += 1;
      }
    }
    fprintf(arq2, mensagem);
  }
  fclose(arq);
  fclose(arq2);
  remove("teste.txt");
  rename("teste2.txt", "teste.txt");
  return 1;
}

int reajustandoNotaPelaLinCol(FILE *arq, char nomearq[]){
  int tam = 100, lin, col, currentLine=1, currentCol=1;
  char mensagem[tam];
  arq = fopen(nomearq,"r+");
  FILE *arq2 = fopen("teste2.txt", "w");
  if (!arq) return 0;
  //mostraArquivoTela(arq, nomearq);
  printf("\nInsert line and column ");
  scanf(" %d %d", &lin, &col);
  while(!feof(arq)){
    fgets(mensagem, tam, arq);
    if(currentLine == (lin+2)){      
      for(int i=0; i < tam; i++){
        if(isdigit(mensagem[i])){
          if(currentCol == col){
            if(mensagem[i] == '0' && mensagem[i-1] == '1'){
              for(int j=i+1; j < tam; j++) 
                if(isdigit(mensagem[j])){
                  i = j;
                  break;
                }
            }
            char num[2];          
            printf("You choosed the grade %c%c\n", mensagem[i], mensagem[i+1]);
            printf("To wich grade you want to change ?\n");
            scanf(" %s", num);
            if(num[0] == '1' && num[1] == '0'){            
              mensagem[i] = '1';
              mensagem[i+1] = '0';
            } else if(mensagem[i] != '1' && mensagem[i+1] != '0'){
              mensagem[i] = num[0];
            }          
            if(mensagem[i] == '1' && mensagem[i+1] == '0'){         
              mensagem[i] = num[0];
              mensagem[i+1] = ' ';
            }
          }
          currentCol++;
        }
      }
    } 
    fprintf(arq2, mensagem);
    currentLine++;
  }
  
  fclose(arq);
  fclose(arq2);
  remove("teste.txt");
  rename("teste2.txt", "teste.txt");
  return 1;
}

int  menu(){
  int opcao;
  printf("\nDigite a opcao desejada: \n");
  printf("0 - Pular esta parte\n");
  printf("1 - Abrir um arquivo para gravacao\n");
  printf("2 - Abrir um arquivo para atualizar no final \n");
  printf("3 - Abrir um arquivo para ler formatado\n");
  printf("4 - Abrir um arquivo para gravar struct pessoa\n");
  printf("5 - Abrir um arquivo para leitura e gravação geral\n");
  printf("19 - Abrir um arquivo para reajustar 1 nota\n");
  printf("21 - Reajustar arquivo com mais 1 ponto\n");
  printf("25 - Abrir um arquivo para gravacao de duas mensagens\n");
  printf("50 - Mostrar o arquivo na tela\n");
  scanf("%d", &opcao);
  return opcao;
}

tp_pessoa *lendoUmaStructDePessoas(int *qntPessoas){
  tp_pessoa pessoas[*qntPessoas];
  printf("Quantas pessoas serao lidas: \n");
  scanf(" %d", qntPessoas);
  for(int i=0; i < *qntPessoas; i++){
    printf("Insira o nome da pessoa numero %d: ", i+1);
    scanf(" %s", pessoas[i].name);
    printf("Insira a idade da pessoa numero %d: ", i+1);
    scanf(" %d", &pessoas[i].idade);
  }
  return pessoas;
}

int gravandoStructDePessoasEmDisco(FILE *arq, char nomearq[]){
  int qntPessoas;
  printf("amor");
  tp_pessoa *pessoas = lendoUmaStructDePessoas(&qntPessoas);
  int num=0;
  char idades[50];
  arq = fopen(nomearq, "wb");
  if (!arq) return 0;
  fprintf(arq, "Pessoas     Idades\n");
  while(num < qntPessoas){
    fprintf(arq, strcat(pessoas[num].name, "\t\t\t"));
    itoa(pessoas[num].idade, idades, 10);
    fprintf(arq, strcat(idades, "\n"));
    num++;
  }
}

void switchOption(int opcao, char nomearq[], FILE *arq){
  switch(opcao){
    case 1: gravar(arq, nomearq);
      break;
    case 2: alterar_no_final(arq, nomearq);
      break; 
    case 3: ler_formatado_e_mostra_em_tela(arq, nomearq);
      break;
    case 4: gravandoStructDePessoasEmDisco(arq, nomearq);
      break;
    case 5: ler_alterar_geral(arq, nomearq);
      break;
    case 19: reajustandoNotaPelaLinCol(arq, nomearq);       
      break;
    case 21: reajustarArquivoComMais1Ponto(arq, nomearq);
      break;
    case 25: gravarDuasMensagens(arq, nomearq);
      break;
    case 0: break;
  }
}

#endif