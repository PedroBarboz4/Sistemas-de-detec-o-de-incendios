#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "header.h"

Celula floresta[30][30]; // Matriz representando a floresta

void inicializar_floresta() {
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 30; j++) {
            floresta[i][j].estado = '-'; // Inicia todas as células como livres
            pthread_mutex_init(&floresta[i][j].mutex, NULL); // Inicializa o mutex de cada célula
        }
    }
}

int main() {
    pthread_t sensores[30][30];
    pthread_t thread_geradora, central_controle;

    inicializar_floresta();

    // Criação das threads sensores
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 30; j++) {
            int* pos = malloc(2 * sizeof(int));
            pos[0] = i;
            pos[1] = j;
            pthread_create(&sensores[i][j], NULL, sensor_func, (void*)pos);
        }
    }

    pthread_create(&thread_geradora, NULL, gerador_func, NULL);

    pthread_create(&central_controle, NULL, central_func, NULL);

    pthread_join(thread_geradora, NULL);
    pthread_join(central_controle, NULL);

    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 30; j++) {
            pthread_join(sensores[i][j], NULL);
        }
    }

    return 0;
}
