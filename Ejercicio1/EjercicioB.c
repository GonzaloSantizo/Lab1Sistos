

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int f = fork(); // Crear un nuevo proceso

    if (f == -1) { // Verificar si hubo un error al crear el proceso hijo
        printf("Error al crear el proceso hijo\n");
        exit(1);
    } else if (f == 0) { // Código del proceso hijo
        printf("Soy el proceso hijo (PID: %d)\n", getpid()); // Imprimir el ID del proceso hijo
        execl("ejer1c", "ejer1c", (char*)NULL); // Ejecutar otro programa llamado "ejer1c"
        printf("No se pudo ejecutar el programa\n"); // Esta línea solo se ejecuta si execl() falla
        exit(1); // Salir del proceso hijo
    } else { // Código del proceso padre
        printf("Soy el proceso del padre (PID: %d)\n", getpid()); // Imprimir el ID del proceso padre
        wait(NULL); // Esperar a que el proceso hijo termine
        printf("Proceso hijo terminado\n"); // Impresión después de que el proceso hijo termina
    }

    return 0; // Salir del programa principal
}