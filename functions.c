#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "header.h"

void* sensor_func(void* arg) {
    int x = ((int*)arg)[0];
    int y = ((int*)arg)[1];
    free(arg);

    while (1) {
        pthread_mutex_lock(&floresta[x][y].mutex);
        if (floresta[x][y].estado == '@') {
            propagar_mensagem(x, y);
        }
        pthread_mutex_unlock(&floresta[x][y].mutex);
        usleep(500000); 
    }
    return NULL;
}

void* gerador_func(void* arg) {
    while (1) {
        int x = rand() % 30;
        int y = rand() % 30;

        pthread_mutex_lock(&floresta[x][y].mutex);
        if (floresta[x][y].estado == '-') {
            floresta[x][y].estado = '@'; 
        }
        pthread_mutex_unlock(&floresta[x][y].mutex);
        sleep(3); 
    }
    return NULL;
}

void* central_func(void* arg) {
    while (1) {
        combater_fogo(); 
        sleep(1); 
    }
    return NULL;
}

void propagar_mensagem(int x, int y) {
    printf("Propagando mensagem de incêndio na posição (%d, %d)\n", x, y);
}

void combater_fogo() {
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 30; j++) {
            pthread_mutex_lock(&floresta[i][j].mutex);
            if (floresta[i][j].estado == '@') {
                floresta[i][j].estado = '/'; 
            }
            pthread_mutex_unlock(&floresta[i][j].mutex);
        }
    }
}

void imprimir_floresta() {
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 30; j++) {
            printf("%c ", floresta[i][j].estado);
        }
        printf("\n");
    }
}
