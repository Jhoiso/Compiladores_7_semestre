#include <stdio.h>

#define MAX_VAL 256

int main(int argc, char** argv) {
  unsigned char buffer[MAX_VAL] = {0};
  int acumulador = 0;
  int contador_programa = 0;
  int flag_negativo = 0;
  int flag_zero = 0;

  if (argc < 2) {
    printf("\nUSO: ./nre <input_file.nre>\n");
    return 1;
  }

  FILE *arquivo_entrada = fopen(argv[1], "rb");
  if (!arquivo_entrada) {
    printf("\nErro!\n");
    return 1;
  }

  fread(buffer, sizeof(unsigned char), MAX_VAL, arquivo_entrada);
  fclose(arquivo_entrada);

  if (buffer[0] != 0x2A) {
    printf("\nNúmero não encontrado\n\n");
    return 1;
  }

  acumulador = buffer[1];
  contador_programa = buffer[2];

  if (acumulador == 0) {
    flag_zero = 1;
  } else {
    flag_zero = 0;
  }

  if (acumulador < 0) {
    flag_negativo = 1;
  } else {
    flag_negativo = 0;
  }

  while (contador_programa < MAX_VAL) {
    switch (buffer[contador_programa]) {
      case 0xF0: // HLT 
        printf("\nAcumulador: %d\n", acumulador);
        return 0;

      case 0x10: // STA 
        contador_programa++;
        buffer[buffer[contador_programa]] = acumulador;
        break;

      case 0x20: // LDA
        contador_programa++;
        acumulador = buffer[buffer[contador_programa]];
        if (acumulador == 0) {
          flag_zero = 1;
        } else {
          flag_zero = 0;
        }
        if (acumulador < 0) {
          flag_negativo = 1;
        } else {
          flag_negativo = 0;
        }
        break;

      case 0x30: // ADD
        contador_programa++;
        acumulador += buffer[buffer[contador_programa]];
        if (acumulador == 0) {
          flag_zero = 1;
        } else {
          flag_zero = 0;
        }
        if (acumulador < 0) {
          flag_negativo = 1;
        } else {
          flag_negativo = 0;
        }
        break;

      case 0x40: // OR
        contador_programa++;
        acumulador |= buffer[buffer[contador_programa]];
        if (acumulador == 0) {
          flag_zero = 1;
        } else {
          flag_zero = 0;
        }
        if (acumulador < 0) {
          flag_negativo = 1;
        } else {
          flag_negativo = 0;
        }
        break;

      case 0x50: // AND
        contador_programa++;
        acumulador &= buffer[buffer[contador_programa]];
        if (acumulador == 0) {
          flag_zero = 1;
        } else {
          flag_zero = 0;
        }
        if (acumulador < 0) {
          flag_negativo = 1;
        } else {
          flag_negativo = 0;
        }
        break;

      case 0x60: // NOT
        acumulador = -acumulador;
        if (acumulador == 0) {
          flag_zero = 1;
        } else {
          flag_zero = 0;
        }
        if (acumulador < 0) {
          flag_negativo = 1;
        } else {
          flag_negativo = 0;
        }
        break;

      case 0x80: // JMP
        contador_programa++;
        contador_programa = buffer[contador_programa] - 1;
        break;

      case 0x90: // JN
        if (flag_negativo) {
          contador_programa++;
          contador_programa = buffer[contador_programa] - 1;
        }
        break;

      case 0xA0: // JZ
        if (flag_zero) {
          contador_programa++;
          contador_programa = buffer[contador_programa] - 1;
        }
        break;

      default:
        break;
    }

    contador_programa++;
  }

  return 0;
}
