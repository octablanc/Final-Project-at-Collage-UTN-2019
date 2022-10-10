#ifndef REPRODUCTOR_H_INCLUDED
#define REPRODUCTOR_H_INCLUDED

/// Estructura que guarda la ruta de la cancion
typedef struct{
    char song[100];
}Cancion;

/// Reproduce una cancion, con 4 vuelve a la cancion anterior, con 5 pausa o continua y 6 cambia cancion siguiente
char reproductor(char a[], int opcion);

/// Agrega la ruta de la cancion al archivo que contiene las rutas de las canciones
void agregarCanciones(char a[]);

/// Busca la ruta de una cancion, pasando por parametro la posicion de la cancion
Cancion buscarCancion(char a[], int cancion);

/// Solo reproduce la cancion
void reproducir(Cancion a);

/// Solo pausa la cancion
void pausar(Cancion a);

/// Cierra la cancion
void cerrar(Cancion a);

/// Reproduce y pausa la cancion
char reproducirYpausar(char a[], int opcion);

#endif // REPRODUCTOR_H_INCLUDED
