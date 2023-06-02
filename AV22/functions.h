#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define ARRAY_SIZE 1000
#define NUM_CHILDREN 5
#define NUM_POSITIONS 200

int array[ARRAY_SIZE];

void ArrayGenerator(){
    for (int i = 0; i < 1000; i++) {
        array[i] = rand() % 1000 + 1;

        for (int j = 0; j < i; j++) {
            if (array[i] == array[j]) {
                i--;
                break;
            }
        }
    }
}



int search(int numero, int inicio, int fim) {
    for (int i = inicio; i <= fim; i++) {
        if (array[i] == numero) {
            return i;
        }
    }
    return 0;
}

