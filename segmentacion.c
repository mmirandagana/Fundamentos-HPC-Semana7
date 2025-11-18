#include <stdio.h>
#include <stdlib.h>

// 1. Estructura para representar un segmento de memoria
typedef struct {
    char *nombre;  // Nombre del segmento
    int base;      // Dirección base del segmento
    int tamano;    // Tamaño del segmento (límite)
} Segmento;

// 2. Función para inicializar los segmentos
void inicializarSegmentos(Segmento *segCodigo, Segmento *segDatos, Segmento *segPila) {
    // Segmento de código: Base 0x0000, Tamaño 1024 bytes
    segCodigo->nombre = "Código";
    segCodigo->base = 0x0000; 
    segCodigo->tamano = 1024;

    // Segmento de datos: Inicia después del código, Tamaño 512 bytes
    segDatos->nombre = "Datos";
    segDatos->base = segCodigo->base + segCodigo->tamano; // Base = 0x0400
    segDatos->tamano = 512;

    // Segmento de pila: Inicia después de los datos, Tamaño 256 bytes
    segPila->nombre = "Pila";
    segPila->base = segDatos->base + segDatos->tamano; // Base = 0x0600
    segPila->tamano = 256;
}

// 3. Función para simular el acceso (Cálculo de Dirección + Protección)
void accederSegmento(Segmento segmento, int desplazamiento) {
    
    // 3a. Protección de Memoria: Verificar si el acceso está dentro de los límites
    if (desplazamiento < 0 || desplazamiento >= segmento.tamano) {
        printf("[ERROR] Acceso denegado al segmento '%s'.\n", segmento.nombre);
        printf("        Motivo: Desplazamiento (%d) fuera de los límites (0 - %d).\n", 
               desplazamiento, segmento.tamano - 1);
    } else {
        // 3b. Cálculo de Dirección Física
        int direccionFisica = segmento.base + desplazamiento;
        printf("[OK] Accediendo al segmento '%s'.\n", segmento.nombre);
        printf("     Dirección Lógica (Desplazamiento): %d\n", desplazamiento);
        printf("     Dirección Física (Base + Desplazamiento): 0x%04X\n", direccionFisica);
    }
    printf("----------------------------------------\n");
}

int main() {
    Segmento segCodigo, segDatos, segPila;
    
    // Inicializar la "tabla de segmentos"
    inicializarSegmentos(&segCodigo, &segDatos, &segPila);
    
    printf("Simulación de Segmentación de Memoria:\n");
    printf("Segmento Código -> Base: 0x%04X, Límite: %d\n", segCodigo.base, segCodigo.tamano);
    printf("Segmento Datos  -> Base: 0x%04X, Límite: %d\n", segDatos.base, segDatos.tamano);
    printf("Segmento Pila   -> Base: 0x%04X, Límite: %d\n", segPila.base, segPila.tamano);
    printf("----------------------------------------\n");

    // 4. Simulación de accesos
    
    // Acceso válido al segmento de código
    accederSegmento(segCodigo, 100);

    // Acceso válido al segmento de datos
    accederSegmento(segDatos, 300);

    // Acceso INVÁLIDO (fuera de los límites) al segmento de datos
    accederSegmento(segDatos, 600); // 600 es mayor que el tamaño 512
    
    // Acceso válido al segmento de pila
    accederSegmento(segPila, 50);

    return 0;
}