#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024 // Tamaño del buffer para la lectura y escritura

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Uso: %s test1.txt test2.txt\n", argv[0]);
    exit(1);
  }

  char *archivo_origen = argv[1];
  char *archivo_destino = argv[2];

  // Abrir el archivo de origen en modo lectura
  int fd_origen = open(archivo_origen, O_RDONLY);
  if (fd_origen == -1) {
    perror("Error al abrir el archivo de origen");
    exit(1);
  }

  // Abrir el archivo de destino en modo escritura (crear si no existe, truncar si existe)
  int fd_destino = open(archivo_destino, O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (fd_destino == -1) {
    perror("Error al abrir el archivo de destino");
    close(fd_origen); // Cerrar el archivo de origen antes de salir
    exit(1);
  }

  // Copiar el contenido del archivo de origen al archivo de destino
  char buffer[BUFFER_SIZE];
  ssize_t bytes_leidos;
  while ((bytes_leidos = read(fd_origen, buffer, BUFFER_SIZE)) > 0) {
    if (write(fd_destino, buffer, bytes_leidos) != bytes_leidos) {
      perror("Error al escribir en el archivo de destino");
      close(fd_origen);
      close(fd_destino);
      exit(1);
    }
  }

  if (bytes_leidos == -1) {
    perror("Error al leer del archivo de origen");
    close(fd_origen);
    close(fd_destino);
    exit(1);
  }

  // Cerrar los archivos
  close(fd_origen);
  close(fd_destino);

  printf("Archivo copiado exitosamente.\n");
  return 0;
}