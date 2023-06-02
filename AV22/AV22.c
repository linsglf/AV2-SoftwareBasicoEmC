#include <stdio.h>
#include <stdlib.h>
#include <time.h>   
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "functions.h"

int main() {
    int numero; 

    printf("Digite o numero que deseja pesquisar: ");
    scanf("%d", &numero);

    srand(time(NULL));
    ArrayGenerator();

    printf("Array: ");
    for (int i = 0; i < 1000; i++) {
        printf("POSICAO %d | NUMERO %d \n", i, array[i]);
    }

    for (int i = 0; i < NUM_CHILDREN; i++) {
        pid_t pid = fork();

        if (pid == 0) {
            
            int inicio = i * NUM_POSITIONS;
            int fim = inicio + NUM_POSITIONS - 1;
            int result = search(numero, inicio, fim);

            if (result != 0) {
                printf("Processo: %d | Número %d encontrado na posição %d. Return: %d. \n", i + 1, numero, result, i + 1);
                exit(i + 1);
            } else if (result == 0){
                printf("Processo: %d | Número %d não encontrado. Return: 0 \n", i + 1, numero);
                exit(0);
            }
        } else if (pid < 0) {
            printf("Erro ao criar o processo filho.\n");
            return 1;
        }
    }

    int processo[5];
    for (int i = 0; i < NUM_CHILDREN; i++) {
        int status;
        pid_t pid = wait(&status);   
        
        if (WIFEXITED(status) == 1) {
            if (WEXITSTATUS(status) != 0) {
                processo[i] = WEXITSTATUS(status);
            }else {
                processo[i] = 0;
            }
        }
    }

    for (int i = 0; i < NUM_CHILDREN; i++) {
        if (processo[i] > 0) {
            printf("Numero %d encontrado no processo: %d\n", numero, processo[i]);
        }
    }

    return 0;
}