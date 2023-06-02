#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include "functions.h"

int main() {
    int numero;

    printf("Digite o número que deseja pesquisar: ");
    scanf("%d", &numero);

    srand(time(NULL));
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = rand() % 1000 + 1;

        for (int j = 0; j < i; j++) {
            if (array[i] == array[j]) {
                i--;
                break;
            }
        }
    }

    pthread_t threads[THREADS];
    int resultados[THREADS];

    SearchParametro parametro[THREADS];

    for (int i = 0; i < THREADS; i++) {
        resultados[i] = -1; // Inicializa o resultado como -1 (número não encontrado)

        parametro[i].numero = numero;
        parametro[i].inicio = i * NUM_POSITIONS;

        printf("| Inicio: %d |\n", parametro[i].inicio);
 
        if (pthread_create(&threads[i], NULL, searchWrapper, (void *)&parametro[i]) != 0) {
            printf("Erro ao criar a thread.\n");
            return 1;
        }
    }

    for (int i = 0; i < THREADS; i++) {
        pthread_join(threads[i], (void **)&resultados[i]);

        if (resultados[i] == 0) {
            printf("Processo: %d | Número %d não encontrado. Return %d \n", i + 1, numero, resultados[i]);
        }

        if (resultados[i] != 0) {
            printf("Processo: %d | Número %d encontrado na posição %d \n", i + 1, numero, resultados[i]);
        }
        
    }

    return 0;
}
