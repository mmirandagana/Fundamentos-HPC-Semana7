#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>  // Para memoria compartida
#include <sys/ipc.h>  // Para claves de IPC
#include <unistd.h>   // Para fork
#include <sys/wait.h> // Para esperar a los procesos

int main() {
    // 1. Crear una clave única para la memoria compartida
    key_t key = ftok("shmfile", 65);

    // 2. Crear un segmento de memoria compartida (tamaño de un entero)
    int shmid = shmget(key, sizeof(int), 0666 | IPC_CREAT);

    // 3. Adjuntar el segmento de memoria al espacio de direcciones del proceso
    int *shared_value = (int *) shmat(shmid, NULL, 0);

    // 4. Inicializar el valor en la memoria compartida
    *shared_value = 0;
    printf("Proceso padre: Valor inicial en memoria = %d\n", *shared_value);

    // 5. Crear un proceso hijo
    if (fork() == 0) {
        // --- Proceso Hijo ---
        printf("Proceso hijo: Leyendo valor inicial = %d\n", *shared_value);
        *shared_value += 5; // Modificar el valor
        printf("Proceso hijo: Valor modificado = %d\n", *shared_value);
        
        // Desadjuntar el segmento de memoria
        shmdt(shared_value);  
        exit(0);
    } else {
        // --- Proceso Padre ---
        // Esperar a que el proceso hijo termine
        wait(NULL);  
        
        // Leer el valor modificado por el hijo
        printf("Proceso padre: Valor final leído de memoria = %d\n", *shared_value);

        // 6. Desadjuntar y eliminar el segmento de memoria
        shmdt(shared_value);
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}