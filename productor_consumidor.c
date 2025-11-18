#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5 // Tamaño de la cola de mensajes

// Estructura de la cola de mensajes
typedef struct {
    int buffer[BUFFER_SIZE];
    int in;  // Índice para insertar (Productor)
    int out; // Índice para consumir (Consumidor)
    sem_t full;    // Semáforo: cuenta los espacios llenos
    sem_t empty;   // Semáforo: cuenta los espacios vacíos
    pthread_mutex_t mutex; // Mutex: para acceso exclusivo al buffer
} MessageQueue;

MessageQueue queue; // Instancia global de la cola

// Función para inicializar la cola
void initQueue(MessageQueue *q) {
    q->in = 0;
    q->out = 0;
    sem_init(&q->full, 0, 0);          // Inicialmente no hay mensajes (0)
    sem_init(&q->empty, 0, BUFFER_SIZE); // Inicialmente hay N espacios vacíos
    pthread_mutex_init(&q->mutex, NULL);
}

// Función del Hilo Productor
void* producer(void *arg) {
    for (int i = 0; i < 10; i++) {
        int message = i; // Mensaje a producir
        
        // 1. Esperar si la cola está llena (espera por un espacio vacío)
        sem_wait(&queue.empty);
        
        // 2. Adquirir mutex para entrar a la sección crítica
        pthread_mutex_lock(&queue.mutex);

        // 3. Añadir mensaje al buffer
        queue.buffer[queue.in] = message;
        printf("Productor ha creado el mensaje %d (en índice %d)\n", message, queue.in);
        queue.in = (queue.in + 1) % BUFFER_SIZE;

        // 4. Liberar mutex
        pthread_mutex_unlock(&queue.mutex);
        
        // 5. Señalizar que hay un nuevo mensaje disponible
        sem_post(&queue.full);

        sleep(1); // Simular tiempo de producción
    }
    return NULL;
}

// Función del Hilo Consumidor
void* consumer(void *arg) {
    for (int i = 0; i < 10; i++) {
        
        // 1. Esperar si la cola está vacía (espera por un mensaje)
        sem_wait(&queue.full);
        
        // 2. Adquirir mutex para entrar a la sección crítica
        pthread_mutex_lock(&queue.mutex);

        // 3. Consumir mensaje del buffer
        int message = queue.buffer[queue.out];
        printf("Consumidor ha procesado el mensaje %d (de índice %d)\n", message, queue.out);
        queue.out = (queue.out + 1) % BUFFER_SIZE;

        // 4. Liberar mutex
        pthread_mutex_unlock(&queue.mutex);
        
        // 5. Señalizar que hay un nuevo espacio vacío
        sem_post(&queue.empty);

        sleep(1.5); // Simular tiempo de consumo
    }
    return NULL;
}

int main() {
    initQueue(&queue); // Inicializar la cola
    
    pthread_t producerThread, consumerThread;

    printf("Iniciando Productor y Consumidor...\n");

    // Crear los hilos
    pthread_create(&producerThread, NULL, producer, NULL);
    pthread_create(&consumerThread, NULL, consumer, NULL);

    // Esperar a que ambos hilos finalicen
    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);

    printf("Todos los mensajes han sido procesados.\n");

    // Destruir semáforos y mutex
    sem_destroy(&queue.full);
    sem_destroy(&queue.empty);
    pthread_mutex_destroy(&queue.mutex);

    return 0;
}