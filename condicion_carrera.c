#include <stdio.h>
#include <pthread.h> // Para hilos
#include <unistd.h>

// Variable compartida que causará la condición de carrera
int shared_value = 0; 

// Función que los hilos ejecutarán
void* increment_value(void* arg) {
    // Cada hilo incrementa la variable 100,000 veces
    for (int i = 0; i < 100000; i++) {
        // SECCIÓN CRÍTICA (No protegida)
        shared_value++; 
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    printf("Iniciando hilos... (Valor esperado = 200000)\n");

    // Crear dos hilos
    pthread_create(&thread1, NULL, increment_value, NULL);
    pthread_create(&thread2, NULL, increment_value, NULL);

    // Esperar a que los hilos terminen
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Imprimir el valor final
    // El resultado será inconsistente y menor a 200000
    printf("Valor final de shared_value: %d\n", shared_value);

    return 0;
}