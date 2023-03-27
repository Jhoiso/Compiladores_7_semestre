#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 1000

typedef enum Token {
  Mais,
  Menos,
  Indeterminado,
} Token;

int *tokenizar(char *caracteres, int lenth) {
  int vetorTokens[lenth];
	int i = 0;
  // for (int i = 0; i < lenth; i++) {
	while (i < lenth){
		switch (caracteres[i]) {
            case '+':
                vetorTokens[i] = Mais;
			    ++;
                break;
            case '-':
                vetorTokens[i] = Menos;
			    i++;
                break;
            case ' ':
			    i++;
			    break;
            default:
                vetorTokens[i] = Indeterminado;
			    ++;
            }
	}
    //printf("\n%c ", caracteres[i]);
    
  return vetorTokens;
}

int main(int argc, char **argv) {
  char filename[100];
  char content[MAX_SIZE];
  int index = 0;
  FILE *fp;
  int i;

  fp = fopen(argv[1], "r");

  if (fp == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return 1;
  }

  while (fgets(content, MAX_SIZE, fp) != NULL) {
    for (i = 0; content[i] != '\0'; i++)
      index++;
  }
  fclose(fp);

  int *vetorTokens = tokenizar(content, i);;
	for (int k = 0; k < i; k++){
		if (vetorTokens[k] == 0)
			printf("Mais\n");
		else if (vetorTokens[k] == 1)
			printf("Menos\n");
			else if (vetorTokens[k] == 2){
				printf("Indeterminado --> ");
				printf("%c\n",content[k]);
			}
				else
					printf("");
	}
	
  return 0;
}