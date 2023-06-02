#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>

#define ARRAY_SIZE 1000
#define THREADS 5
#define NUM_POSITIONS 200

int array[ARRAY_SIZE];

typedef struct {
    int numero; 
    int inicio;
} SearchParametro;

void *searchWrapper(void *arg) {
    SearchParametro *parametro = (SearchParametro *)arg;
    int posicao;
    int retorno0 = 0;

    int numero = parametro->numero;
    int inicio = parametro->inicio;
    int fim = inicio + NUM_POSITIONS - 1;

    for (int i = inicio; i <= fim; i++) {

        if (array[i] == numero) {
            posicao = i;
            retorno0 = 1;
            return (void *)(intptr_t)posicao;
        }
    }
       
    return (void *)(intptr_t)retorno0;
}



