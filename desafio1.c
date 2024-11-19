#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// O uso de ponteiros foi uma forma que eu vi de acessar mais rápido os valores da var armario.
// E também usei para passar o valor da função por referência e não por parametro
bool armarioCheios(unsigned char* armario) {
    return *armario == 0xFF;
}

bool armarioOcupado(unsigned char* armario, unsigned char index) {
    return (*armario >> index) & 0x01; // Ex: 1110 0101 >> 3 & 0x01 = 0001 1100 & 0x01 = 0, livre!!
}  

unsigned char escolherArmario(unsigned char* armario) {
    unsigned char index;
    do {
        index = rand() % 8;
    } while(armarioOcupado(armario, index)); // while loopa verificando se a posição index está ocupada
    return index;
}

void ocuparArmario(unsigned char* armario, unsigned char index) {
    if (armarioOcupado(armario, index)) {
        printf("O armario selecionado já está ocupado!\n");
    }
    else {
        unsigned char index = escolherArmario(armario);
        *armario = *armario | (1 << index); //ocupa o armario com uma porta OR
        printf("O armário %hhu foi ocupado com sucesso!\n", index+1);
    }
}

void liberarArmario(unsigned char* armario, unsigned char index) {
    if (armarioOcupado(armario, index)) {
        *armario &= ~(1 << index);
        printf("O armário %hhu foi desocupado com sucesso!\n", index+1);
    }
}

int main(void) {

    unsigned char armario = 0x00;  
    int op;
    unsigned char index;

    do {
        printf("\nSelecione a operação desejada:\n");
        printf("1. Ocupar armário\n2. Liberar armário\n3. Sair\n");

        printf("Escolha uma opção: ");
        scanf("%d", &op);

        srand(time(NULL));

        switch (op) {
            case 1:
                ocuparArmario(&armario, index);
                break;
            case 2:
                printf("Digite o número do armário para liberar (1-8): ");
                scanf("%hhu", &index);
                if (index >= 1 && index <= 8) {
                    liberarArmario(&armario, index - 1);
                } else {
                    printf("Número de armário inválido!\n");
                }
                break;
            case 3:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }

    } while (op != 3);

    return 0;
}