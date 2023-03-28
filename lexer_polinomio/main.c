#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 1000

typedef enum Token {
	Mais,
	Menos,
	Indeterminado,
	Multiplicacao,
	Divisao,
	Potencia,
} Token;

int contador_mult (char *caracteres, int pos){
	int numero = 0;
	int i = pos;
	while (1 > 0){
		if (caracteres[i] == '*'){
			numero++;
			i++;
		}
		else
			break;
	}
	return numero;
}

void tokenizar(char *caracteres, int lenth, int *vetorTokens) {
  	
	int i = 0;
	int numero_mult;
	int numeroDeP;
	while (i < lenth){
		switch (caracteres[i]) {
			case '+':
				vetorTokens[i] = Mais;
				i++;
				break;
			case '-':
				vetorTokens[i] = Menos;
				i++;
				break;
			case '/':
				vetorTokens[i] = Divisao;
				i++;
				break;
			case '*':
				numero_mult = contador_mult(caracteres, i);
				if (numero_mult % 2 == 0){
					numeroDeP = numero_mult / 2;
					for (int l = 0; l < numeroDeP; l++)
						vetorTokens[i+l] = Potencia;

					printf("%d", numero_mult);
				}
				else{
					if (numero_mult == 1)
						vetorTokens[i] = Multiplicacao;			
					else{
						numeroDeP = (numero_mult - 1)/2;
					int posicMult = numeroDeP+1;
					for (int l = 0; l < numeroDeP; l++)
						vetorTokens[i+l] = Potencia;
					
					vetorTokens[i+posicMult] = Multiplicacao;
					}
					
				}
				i = i + numero_mult;
				break;
			case ' ':
				vetorTokens[i] = 9999;
				i++;
				break;
			default:
					vetorTokens[i] = Indeterminado;
					i++;
			}
	}
}

int main(int argc, char **argv) {
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
  		int vetorTokens[i];
  		tokenizar(content, i, vetorTokens);
		for (int k = 0; k < i; k++){
			if (vetorTokens[k] == 0)
				printf("Mais\n");
			else if (vetorTokens[k] == 1)
				printf("Menos\n");
			else if (vetorTokens[k] == 2){
				printf("Indeterminado --> ");
				printf("%c\n",content[k]);
			}
			else if (vetorTokens[k] == 3)
				printf("Multiplicação\n");
			else if (vetorTokens[k] == 4)
				printf("Divisao\n");
			else if (vetorTokens[k] == 5)
				printf("Potencia\n");
			// else if (vetorTokens[k] == 9999)
			// 	printf("");
		
		}
	
  	return 0;
}