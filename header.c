#ifndef HEADER_H
#define HEADER_H

#include <pthread.h>

typedef struct {
    char estado; 
    pthread_mutex_t mutex; 
} Celula;

extern Celula floresta[30][30];

void* sensor_func(void* arg);
void* gerador_func(void* arg);
void* central_func(void* arg);
void propagar_mensagem(int x, int y);
void combater_fogo();
void imprimir_floresta();

#endif
