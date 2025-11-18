#include <stdio.h>    // Para la función printf
#include <stdlib.h>   // Para la función exit
#include <unistd.h>   // Para fork() y getpid()
#include <sys/wait.h> // Para wait()

int main() {
    pid_t pid; // Variable para almacenar el PID

    // 1. Crear un proceso hijo
    pid = fork();

    // 2. Manejo de errores
    // Si fork() falla, devuelve un valor negativo
    if (pid < 0) {
        fprintf(stderr, "Error al crear el proceso hijo.\n");
        return 1;
    }

    // 3. Código del Proceso Hijo
    // fork() devuelve 0 al proceso hijo
    if (pid == 0) {
        printf("--- Proceso Hijo ---\n");
        printf("Soy el proceso hijo, mi PID es: %d\n", getpid());
        printf("Mi proceso padre es el PID: %d\n", getppid());
        sleep(2); // Simula una tarea
        printf("Proceso hijo (PID: %d) finaliza.\n", getpid());
        exit(0); // El hijo termina
    
    // 4. Código del Proceso Padre
    // fork() devuelve el PID del hijo al proceso padre
    } else {
        printf("--- Proceso Padre ---\n");
        printf("Soy el proceso padre, mi PID es: %d\n", getpid());
        printf("He creado un hijo con PID: %d\n", pid);
        
        // El padre espera a que el hijo termine
        printf("Proceso padre esperando que el hijo (PID: %d) termine...\n", pid);
        wait(NULL); 
        
        printf("Mi proceso hijo ha terminado.\n");
        printf("Proceso padre (PID: %d) finaliza.\n", getpid());
    }

    return 0;
}
