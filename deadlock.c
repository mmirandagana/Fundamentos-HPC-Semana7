#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

// Dos recursos, cada uno protegido por un mutex
pthread_mutex_t resource1;
pthread_mutex_t resource2;

// Hilo 1: Adquiere resource1, luego resource2
void* thread1_function(void* arg) {
    printf("Hilo 1: Intentando adquirir el recurso 1...\n");
    pthread_mutex_lock(&resource1);
    printf("Hilo 1: Recurso 1 adquirido.\n");

    sleep(1); // Simular trabajo

    printf("Hilo 1: Intentando adquirir el recurso 2...\n");
    pthread_mutex_lock(&resource2); // SE BLOQUEA AQUÍ
    printf("Hilo 1: Recurso 2 adquirido.\n");

    pthread_mutex_unlock(&resource2);
    pthread_mutex_unlock(&resource1);
    printf("Hilo 1: Recursos liberados\n");
    return NULL;
}

// Hilo 2: Adquiere resource2, luego resource1 (Orden inverso)
void* thread2_function(void* arg) {
    printf("Hilo 2: Intentando adquirir el recurso 2...\n");
    pthread_mutex_lock(&resource2);
    printf("Hilo 2: Recurso 2 adquirido.\n");

    sleep(1); // Simular trabajo

    printf("Hilo 2: Intentando adquirir el recurso 1...\n");
    pthread_mutex_lock(&resource1); // SE BLOQUEA AQUÍ
    printf("Hilo 2: Recurso 1 adquirido.\n");

    pthread_mutex_unlock(&resource1);
    pthread_mutex_unlock(&resource2);
    printf("Hilo 2: Recursos liberados\n");
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Inicializar los mutexes
    pthread_mutex_init(&resource1, NULL);
    pthread_mutex_init(&resource2, NULL);

    printf("Iniciando hilos para simular deadlock...\n");
    
    // Crear los hilos
    pthread_create(&thread1, NULL, thread1_function, NULL);
    pthread_create(&thread2, NULL, thread2_function, NULL);

    // El programa se quedará "colgado" en pthread_join
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Programa finalizado (esto no debería imprimirse).\n");

    pthread_mutex_destroy(&resource1);
    pthread_mutex_destroy(&resource2);
    return 0;
}