#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <Mmsystem.h>
#include "gotoxy.h"
#include "reproductor.h"
#include "manejoDeCanciones.h"

/// Reproduce una cancion, con 4 vuelve a la cancion anterior, con 5 pausa o continua y 6 cambia cancion siguiente
char reproductor(char a[], int opcion){
    char control;
    control = reproducirYpausar(a, opcion);
    return control;
}

/// Agrega la ruta de la cancion al archivo que contiene las rutas de las canciones
void agregarCanciones(char a[]){
    FILE *archivo = fopen(a, "ab");

    Cancion a1;
    marcoBuscar();
    gotoxy(81, 2); printf("                      ");
    gotoxy(75, 2); printf("AGREGAR RUTA DE LA CANCION");
    fflush(stdin);
    hidecursor(1);
    gotoxy(65, 5); gets(a1.song);
    hidecursor(0);
    if(archivo != NULL){
        fwrite(&a1, sizeof(Cancion), 1, archivo);

        if(fclose(archivo) != 0)
            printf("\nError al cerrar el archivo\n");
    }
    else
        printf("\nError al cerrar el archivo\n");
}

/// Busca la ruta de una cancion, pasando por parametro la posicion de la cancion
Cancion buscarCancion(char a[], int cancion){
    FILE *archivo = fopen(a, "rb");
    Cancion aux;
    if(archivo != NULL){
        fseek(archivo, (cancion-1) * sizeof(Cancion), SEEK_SET);

        fread(&aux, sizeof(Cancion), 1, archivo);

        if(fclose(archivo) != 0)
            printf("\nError al cerrar el archivo\n");
    }
    else
        printf("\nError al cerrar el archivo\n");

    return aux;
}

/// Solo reproduce la cancion
void reproducir(Cancion a){
    char play[100] = "play ";

    strcat(play, a.song);

    mciSendString(play, NULL, 0, NULL);
}

/// Solo pausa la cancion
void pausar(Cancion a){
    char pause[100] = "pause ";

    strcat(pause, a.song);
    mciSendString(pause, NULL, 0, NULL);
}


/// Cierra la cancion
void cerrar(Cancion a){
    char close[100] = "close ";

    strcat(close, a.song);
    mciSendString(close, NULL, 0, NULL);
}

/// Reproduce y pausa la cancion
char reproducirYpausar(char a[], int opcion){

    char control;
    Cancion song;

    do{
        song = buscarCancion(a, opcion);
        reproducir(song);

        fflush(stdin);
        control = getch();

        if(control == '5'){
            pausar(song);
            getch();
        }
    }while(control == '5');
    cerrar(song);

    return control;
}









