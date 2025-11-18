# Repositorio de Código: Fundamentos de Computación (Semana 7)

Este repositorio contiene los códigos fuente en C desarrollados para el Entregable de la Semana 7, demostrando conceptos clave de Sistemas Operativos y Computación de Alto Desempeño.

## Contenido del Repositorio

1.  **gestion_procesos.c**: Demostración de `fork()`, `wait()` y `getpid()`.
2.  **memoria_compartida.c**: Demostración de `shmget` y `shmat` para IPC.
3.  **condicion_carrera.c**: Demostración de *Race Conditions* en hilos.
4.  **solucion_mutex.c**: Solución a *Race Conditions* usando *Locks* (`pthread_mutex_t`).
5.  **deadlock.c**: Simulación de un *Deadlock* (bloqueo mutuo) por espera circular.
6.  **productor_consumidor.c**: Implementación del patrón Productor-Consumidor con semáforos y mutex.
7.  **segmentacion.c**: Simulación de segmentación de memoria y protección.

---

## Instrucciones de Compilación y Ejecución

Los programas deben compilarse en un entorno UNIX (Linux, macOS, WSL) con `gcc`.

### 1. Gestión de Procesos
**Compilar:**
`gcc gestion_procesos.c -o gestion_procesos`
**Ejecutar:**
`./gestion_procesos`

### 2. Memoria Compartida
*(Nota: El archivo `shmfile` se incluye en el repositorio, ya que es requerido por la función `ftok` en `memoria_compartida.c` para generar la clave del segmento de memoria).*

**Compilar:**
`gcc memoria_compartida.c -o memoria_compartida`
**Ejecutar:**
`./memoria_compartida`

### 3. Condición de Carrera
**Compilar (requiere biblioteca pthread):**
`gcc condicion_carrera.c -o condicion_carrera -lpthread`
**Ejecutar:**
`./condicion_carrera`

### 4. Solución con Mutex (Lock)
**Compilar (requiere biblioteca pthread):**
`gcc solucion_mutex.c -o solucion_mutex -lpthread`
**Ejecutar:**
`./solucion_mutex`

### 5. Deadlock
**Compilar (requiere biblioteca pthread):**
`gcc deadlock.c -o deadlock -lpthread`
**Ejecutar (se congelará):**
`./deadlock`
*(Presionar Ctrl+C para terminar)*

### 6. Productor-Consumidor
**Compilar (requiere biblioteca pthread):**
`gcc productor_consumidor.c -o productor_consumidor -lpthread`
**Ejecutar:**
`./productor_consumidor`

### 7. Segmentación de Memoria
**Compilar:**
`gcc segmentacion.c -o segmentacion`
**Ejecutar:**
`./segmentacion`
