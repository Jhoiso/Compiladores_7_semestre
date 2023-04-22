#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAX_SIZE 1000

typedef enum Token {
    Mais,
    Inteiro,
    Decimal,
    Indeterminado,
	Menos,
	Multiplicacao,
	Divisao,
	Potencia,
    Espaco,
} Token;

struct Tokens {
    enum Token token;
    char texto[MAX_SIZE];
    double numero;
};

int contador(char *caracteres, int pos) {
    int numero = 0;
    while (isdigit(caracteres[pos]) || caracteres[pos] == '.') {
        numero++;
        pos++;
    }
    return numero;
}

double numeroRet(char *caracteres, int i, int inteiro, struct Tokens *vetorTokens, int j) {
    char numero[inteiro];
    for (int k = 0; k < inteiro; k++) {
        if (caracteres[i + k] == '.') {
            vetorTokens[j].token = Decimal;
        }
        // numero[k] = caracteres[i + k];
    }
    // return atof(numero);
    return strtod(&caracteres[i], NULL);
	
}

int tokenizar(char *caracteres, int lenth, struct Tokens *vetorTokens) {
    int i = 0, j = 0;
	int inteiro;
    while (i < lenth) {
        switch (caracteres[i]) {
            case ' ':
                i++;
                break;
            case '+':
                vetorTokens[j].token = Mais;
                j++;
                i++;
                break;
			case '-':
				vetorTokens[j].token = Menos;
				j++;
				i++;
				break;
			case '*':
				if (caracteres[i+1] == '*'){
					vetorTokens[j].token = Potencia;
					i += 2;
				}
				else{
					vetorTokens[j].token = Multiplicacao;
					i++;
				}
				j++;
				break;
			case '/':
				vetorTokens[j].token = Divisao;
				j++;
				i++;
				break;
			
            default:
                inteiro = contador(caracteres, i);
                if (inteiro == 0) {
                    vetorTokens[j].token = Indeterminado;
                    vetorTokens[j].texto[0] = caracteres[i];
                    vetorTokens[j].texto[1] = '\0';
                    j++;
                    inteiro = 1;
                } else {
                    vetorTokens[j].token = Inteiro;
                    vetorTokens[j].numero = numeroRet(caracteres, i, inteiro, vetorTokens, j);
                    j++;
                }
                i += inteiro;
        }
    }
    return j;
}

double operacao(double soma, Token operacao){
	double result = soma;
	

	
	return result;
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
        for (i = 0; content[i] != '\0'; i++) {
            index++;
        }
    }
    fclose(fp);

    struct Tokens vetorTokens[index];
    double soma = 0;
    int cont = tokenizar(content, index, vetorTokens);
	int contOperacao = 0;

    if (cont == 0) {
        printf("<EXPRESSÃO> ::= ε");
    } else {
        for (int k = 0; k < cont; k++) {
            if (vetorTokens[k].token == Mais) {
				if (contOperacao == 0)
					 soma += vetorTokens[k - 1].numero + vetorTokens[k + 1].numero;
				else
					soma += vetorTokens[k + 1].numero;
               contOperacao++;
				printf("SOMA\n");
            } 
			if (vetorTokens[k].token == Menos){
				if (contOperacao == 0)
					soma += vetorTokens[k - 1].numero - vetorTokens[k + 1].numero; 
				else
					soma -= vetorTokens[k + 1].numero;
				contOperacao++;
				printf("SUBTRAÇÃO\n");
			}
			if (vetorTokens[k].token == Potencia){
				if (contOperacao == 0){
					soma += pow(vetorTokens[k - 1].numero, vetorTokens[k + 1].numero);
					// printf("Valor atual1 --> %f\n", soma);
				}
				else{
					soma += pow(soma, vetorTokens[k+1].numero);
					// printf("Valor atual --> %f\n", soma);
				}
				contOperacao++;
				
				printf("POTENCIA\n");
			}
			if (vetorTokens[k].token == Multiplicacao){
				if (contOperacao == 0){
					soma += vetorTokens[k - 1].numero * vetorTokens[k + 1].numero;
					// printf("Valor atual --> %f\n", soma);
				}
				else{
					soma = soma * vetorTokens[k+1].numero;
					// printf("Valor atual --> %f\n", soma);
				}
				contOperacao++;
				printf("MULTIPLICAÇÃO\n");
			}
			if (vetorTokens[k].token == Divisao){
				if (contOperacao == 0){
					soma += (vetorTokens[k - 1].numero / vetorTokens[k + 1].numero);
					// printf("Valor atual --> %f\n", soma);
				}
				else{
					soma = soma / vetorTokens[k+1].numero;
					// printf("Valor atual --> %f\n", soma);
				}
				contOperacao++;
				printf("DIVISÃO\n");
			}
			
			else if (vetorTokens[k].token == Inteiro) {
                printf("Inteiro --> %.2f\n", vetorTokens[k].numero);
            } else if (vetorTokens[k].token == Indeterminado) {
                printf("Indeterminado --> %s\n", vetorTokens[k].texto);
            } else if (vetorTokens[k].token == Decimal) {
                printf("Decimal --> %.2f\n", vetorTokens[k].numero);
            }
        }
    	printf("Soma --> %.2f", soma);
		
    }

    return 0;
}
