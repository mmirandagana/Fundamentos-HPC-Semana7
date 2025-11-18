#include <stdio.h>
#include <pthread.h>

int shared_value = 0;       // Variable compartida
pthread_mutex_t lock;       // Mutex (Lock) para proteger la variable

// Función que los hilos ejecutarán
void* increment_value(void* arg) {
    for (int i = 0; i < 100000; i++) {
        
        // 1. Bloquear el mutex (Adquirir el Lock)
        pthread_mutex_lock(&lock);

        // --- SECCIÓN CRÍTICA ---
        shared_value++;
        // --- FIN SECCIÓN CRÍTICA ---

        // 2. Desbloquear el mutex (Liberar el Lock)
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Inicializar el mutex antes de usarlo
    pthread_mutex_init(&lock, NULL);

    printf("Iniciando hilos con Mutex... (Valor esperado = 200000)\n");

    // Crear los hilos
    pthread_create(&thread1, NULL, increment_value, NULL);
    pthread_create(&thread2, NULL, increment_value, NULL);

    // Esperar a que los hilos terminen
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Imprimir el valor final
    // El resultado siempre será 200000
    printf("Valor final de shared_value: %d\n", shared_value);

    // Destruir el mutex después de usarlo
    pthread_mutex_destroy(&lock);

    return 0;
}