#ifndef MANEJODECANCIONES_H_INCLUDED
#define MANEJODECANCIONES_H_INCLUDED
#include "manejoDeUsuarios.h"

typedef struct {
    int idCancion;
    char titulo[30];
    char artista[20];
    char duracion[5];
    char album[20];
    int anio;
    char genero[20];
    int eliminado;  // indica 1 o 0 si la canción fue eliminada
} stCancion;

/// Datos, marco y textos de cancion
void marcoCancion();

/// Para usuario
void marcoCancionUsuario();

/// Cargar estrucura de cancion
stCancion cargarStCancion();

/// Cargar una cancion en un archivo de canciones
void cargarArchivoCancion(char a[]);

/// Buscar cancion por nombre
int buscarCancionNombre(char a[], int opcion);

/// Marco para ingresar la cancion
void marcoBuscar();

/// Modificar usuario para los admins
void modificarCancion(char a[], int cancion, int opcion);

/// Mostrar cancion para los usuarios
void mostrarCancionUsuario(char a[], int pos);

/// Cargar playlist
void cargarPlayList(char a[], char b[], int pos);

/// Marco mostrar playlist
void marcoPlaylist();

/// Mostrar canciones de  la playlist
void mostrarCancionesPlayList(char songs[], int a[], int validos);

/// Mostrar playlist
int mostrarPlaylist(char a[], char b[], int pos);

/// Insertar ID
void insertarID(int a[], int validos, int dato);

/// BUSCAR CANCION POR ID, DEVUELVE EL GENERO (1 = ROCK, 2 = ROCK ALT, 3 = REGGAE, 4 = HIPHOP, 5 = POP)
int buscarCancionID (char a[], int id);

/// RECOMENDADOS
void mostrarRecomendados (char a[], char b[], int pos);

/// DEUELVE EL GENERO MAS ESCUCHADO DE LA PLAYLIST
int masEscuchado (int c[], int val);

/// Muestra las canciones de un genero determinado
void mostrar5CancionesPorGenero(char a[], int pos, Usuario us1);

/// Verifica que una cancion no se encuentre en la playlist
int verificarQueLaCancionNoSeRepita(Usuario us1, int id);

#endif // MANEJODECANCIONES_H_INCLUDED
