#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 1000

typedef enum Token {
//codificar em ascii
	Mais = '1',
	Menos = '2',
	Indeterminado = '3',
	Multiplicacao = '4',
	Divisao = '5',
	Polinomio = '6',
	Numero = '7',
} Token;

int contador (char *caracteres, int pos, int indicador){
	int numero = 0;
	int i = pos;
	if (indicador == 1){
		while (1 > 0){
		if (caracteres[i] == '*'){
			numero++;
			i++;
		}
		else
			break;
		}
	}
	if (indicador == 2){
		while (1 > 0){
			if (caracteres[i] == '1' || caracteres[i] == '2' || caracteres[i] 			== '3' || caracteres[i] == '4' || caracteres[i] == '5' || 					caracteres[i] == '6' || caracteres[i] == '7' || caracteres[i] == 			'8' || caracteres[i] == '0' || caracteres[i] == '9' ||caracteres[i] == '.'){
			numero++;
			i++;
		}
		else
			break;
		}
	}
	return numero;
}

void tokenizar(char *caracteres, int lenth, int *vetorTokens) {
  	
	int i = 0;
	int numero_mult;
	int numeroDeP;
	int numero;
	int inteiro;
	char ch;
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
				numero_mult = contador(caracteres, i, 1);
				if (numero_mult % 2 == 0){
					numeroDeP = numero_mult / 2;
					for (int l = 0; l < numeroDeP; l++)
						vetorTokens[i+l] = Polinomio;
				}
				else{
					if (numero_mult == 1)
						vetorTokens[i] = Multiplicacao;			
					else{
						numeroDeP = (numero_mult - 1)/2;
					int posicMult = numeroDeP+1;
					for (int l = 0; l < numeroDeP; l++)
						vetorTokens[i+l] = Polinomio;
					
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
				
				inteiro = contador(caracteres, i, 2);
				if (inteiro == 0){
					vetorTokens[i] = Indeterminado;
					inteiro = 1;
				}
				else{
					printf("\n-->%d", inteiro);
					ch = caracteres[i];
					numero = ch - '0';
					printf("O caractere '%c' em inteiro é: %d\n", ch, numero);
					vetorTokens[i] = Numero;
				}
							
				i = i + inteiro;
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
			if (vetorTokens[k] == '1')
				printf("Mais\n");
			else if (vetorTokens[k] == '2')
				printf("Menos\n");
			else if (vetorTokens[k] == '3'){
				printf("Indeterminado --> ");
				printf("%c\n",content[k]);
			}
			else if (vetorTokens[k] == '4')
				printf("Multiplicação\n");
			else if (vetorTokens[k] == '5')
				printf("Divisao\n");
			else if (vetorTokens[k] == '6')
				printf("Polinomio\n");
			else if (vetorTokens[k] == '7')
				printf("Numero\n");
			// else if (vetorTokens[k] == 9999)
			// 	printf("");
		
		}
	
  	return 0;
}