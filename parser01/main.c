#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_SIZE 1000

typedef enum Token {
//codificar em ascii
	Mais,
	Inteiro,
	Decimal,
	Indeterminado,
	ERRO,
} Token;

struct Tokens
{
    enum Token token;
    union
    {
        char texto;
        double numero;
    } value;
};

int contador (char *caracteres, int pos){
	int numero = 0;
	int i = pos;
	while (1 > 0){
		if (caracteres[i] == '1' || caracteres[i] == '2' || caracteres[i] 			== '3' || caracteres[i] == '4' || caracteres[i] == '5' || 					caracteres[i] == '6' || caracteres[i] == '7' || caracteres[i] == 			'8' || caracteres[i] == '0' || caracteres[i] == '9' ||caracteres[i] == '.'){
		numero++;
		i++;
	}
	else
		break;
	}
	return numero;
}

double numeroRet(char *caracteres, int i, int inteiro, double *vetorSoma, struct Tokens *vetorTokens){
	char numero[inteiro];
	for (int k = 0; k < inteiro; k++){
		if (caracteres[i+k] == '.'){
			// printf("--------------->%d", i);
			vetorTokens[i].token = Decimal;
		}
			
		numero[k] = caracteres[i+k];
	}
	char *endptr = '\0';
	double num = strtod(numero, &endptr);
	return num;
}


int tokenizar(char *caracteres, int lenth, struct Tokens *vetorTokens) {
  	
	int i = 0;
	int inteiro;
	int j;
	double retorno;
	double vetorSoma[512];
	int contadorNumero = 0;
	while (i < lenth){
		switch (caracteres[i]) {
			case '+':
				vetorTokens[i].token = Mais;
				j++;
				if (!isdigit(caracteres[i+1]) && caracteres[i+1]){
					i = lenth;
					vetorTokens[i].token = ERRO;
				}
				i++;
				break;
			default:
				
				inteiro = contador(caracteres, i);
				if (inteiro == 0){
					vetorTokens[i].token = Indeterminado;
					vetorTokens[i].value.texto = caracteres[i];
					j++;
					inteiro = 1;
				}
				else{
					vetorTokens[i].token = Inteiro;
					retorno = numeroRet(caracteres,i, inteiro, vetorSoma, vetorTokens);
					vetorTokens[i].value.numero = retorno;
					j++;
				}
							
				i = i + inteiro;
			}
	}
	return j;
}

int main(int argc, char **argv) {
	char content[MAX_SIZE];
	int index = 0;
	FILE *fp;
	int i = 0;

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
  		struct Tokens vetorTokens[i];
		double soma;
		int cont;
		if (i == 0){
			printf("<EXPRESSÃO> ::= ε");
		}
		else{
			cont = tokenizar(content, i, vetorTokens);
			for (int k = 0; k < i; k++){
				if (vetorTokens[k].token == Mais) {
					
					// printf("\nNumero anterior %f\n", vetorTokens[k-1].value.numero);
					// printf("\nNumero posteror %f\n", vetorTokens[k+1].value.numero);
					
					soma = vetorTokens[k+1].value.numero + vetorTokens[k-1].value.numero;
				}
				if (vetorTokens[k].token == Inteiro)
					printf("Inteiro> --> %.2f\n", vetorTokens[k].value.numero);
				
				if (vetorTokens[k].token == Indeterminado){
					printf("Indeterminado --> ");
					printf("%c\n",vetorTokens[k].value.texto);
				}
				
				if (vetorTokens[k].token == Decimal)
					printf("Decimal --> %.2f\n",  vetorTokens[k].value.numero);
			}
		}
  		printf("Soma --> %f", soma);
	
  	return 0;
}

//Código com erro na hora de reconhecer e somar os números decimais. tirar duvida heredia