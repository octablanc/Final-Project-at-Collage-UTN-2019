#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "gotoxy.h"
#include "menu.h"

/// Borde de la ventana
void marcoMenu(){
    int x, y;
    color(9);

    /// Cuadrado Lineas
    for(y=1; y<144; y++){
        gotoxy(y, 0); printf("%c", 205);
    }
    for(x=0; x<34; x++){
        gotoxy(144, x); printf("%c", 186);
    }
    for(x=1; x<34; x++){
        gotoxy(1, x); printf("%c", 186);
    }
    for(y=1; y<144; y++){
        gotoxy(y, 34); printf("%c", 205);
    }
    /// Esquinas
    gotoxy(1, 0); printf("%c", 201);
    gotoxy(144, 0); printf("%c", 187);
    gotoxy(1, 34); printf("%c", 200);
    gotoxy(144, 34); printf("%c", 188);
    color(15);
}

/// Texto de MusicLib en grande
void textoMusicLib(){
    hidecursor(0);
    srand(time(NULL));

    color(rand()%15 +1);
    gotoxy(34, 5); puts(" /$$      /$$                     /$$           /$$       /$$ /$$");
    gotoxy(34, 6); puts("| $$$    /$$$                    |__/          | $$      |__/| $$");
    gotoxy(34, 7); puts("| $$$$  /$$$$ /$$   /$$  /$$$$$$$ /$$  /$$$$$$$| $$       /$$| $$$$$$$");
    gotoxy(34, 8); puts("| $$ $$/$$ $$| $$  | $$ /$$_____/| $$ /$$_____/| $$      | $$| $$__  $$");
    gotoxy(34, 9); puts("| $$  $$$| $$| $$  | $$|  $$$$$$ | $$| $$      | $$      | $$| $$  \\ $$");
    gotoxy(34, 10); puts("| $$\\  $ | $$| $$  | $$ \\____  $$| $$| $$      | $$      | $$| $$  | $$");
    gotoxy(34, 11); puts("| $$ \\/  | $$|  $$$$$$/ /$$$$$$$/| $$|  $$$$$$$| $$$$$$$$| $$| $$$$$$$/");
    gotoxy(34, 12); puts("|__/     |__/ \\______/ |_______/ |__/ \\_______/|________/|__/|_______/");
    color(15);
}

/// Menu Iniciar Admin, Usuario o Registrarse
int menu1(){
    int opcion;

    gotoxy(60, 20); puts("Iniciar como Admin");
    gotoxy(60, 21); puts("Iniciar como Usuario");
    gotoxy(60, 22); puts("Registrarse");
    gotoxy(60, 23); puts("Salir");
    marcoMenu();
    textoMusicLib();
    opcion = moverCursor(20, 58, 20, 23, 1);

    return opcion;
}

/// Menu Ingresar Id y Contraseña (Admin y Usuario)
void menu2(){
    color(9);
    gotoxy(60, 20); puts("Nombre de usuario");
    gotoxy(60, 23); printf("Contrase%ca", 164);
    color(15);
    marcoMenu();
    textoMusicLib();
}

/// Menu Registrarse
void menu3(){
    marcoMenu();
    textoMusicLib();

    gotoxy(60, 15); printf("INGRESE");
    color(9);
    gotoxy(60, 17); printf("Nombre de usuario ");
    gotoxy(60, 20); printf("Contrase%ca ", 164);
    gotoxy(60, 23); printf("Fecha de nacimiento (dd/mm/aaaa)");
    gotoxy(60, 26); printf("Genero ");
    gotoxy(60, 29); printf("Pais ");
    color(15);
}

/// Menu una vez iniciada la sesion de Admin
void vistaAdmin(){
    int x, y;
    hidecursor(0);

    marcoMenu();
    color(9);
    for(y=2; y<30; y++){
        gotoxy(y, 4); printf("%c", 205);
    }
    gotoxy(1, 4); printf("%c", 204);

    for(x=1; x<4; x++){
            gotoxy(30, x); printf("%c", 186);
    }
    gotoxy(30, 0); printf("%c", 203);
    gotoxy(30, 4); printf("%c", 185);
    color(15);
    gotoxy(9, 2); printf("ADMINISTRADOR");

    color(9);
    for(x=5; x<34; x++){
            gotoxy(30, x); printf("%c", 186);
    }
    gotoxy(30, 34); printf("%c", 202);
    color(15);
    gotoxy(6, 7); printf("Ver usuarios");
    gotoxy(6, 9); printf("Alta de usuario");
    gotoxy(6, 11); printf("Baja de usuario");
    gotoxy(6, 13); printf("Modificar usuario");
    gotoxy(6, 15); printf("Cargar cancion");
    gotoxy(6, 17); printf("Buscar cancion");
    gotoxy(6, 19); printf("Modificar cancion");
    gotoxy(6, 21); printf("Agregar ruta Cancion");
    gotoxy(6, 23); printf("Cerrar sesion");
    gotoxy(6, 25); printf("Salir");
}

/// Menu una vez iniciada la sesion de Usuario
void vistaUsuarios(){
    int x, y;
    hidecursor(0);

    marcoMenu();
    color(9);
    for(y=2; y<30; y++){
        gotoxy(y, 4); printf("%c", 205);
    }
    gotoxy(1, 4); printf("%c", 204);

    for(x=1; x<4; x++){
            gotoxy(30, x); printf("%c", 186);
    }
    gotoxy(30, 0); printf("%c", 203);
    gotoxy(30, 4); printf("%c", 185);
    color(15);
    gotoxy(12, 2); printf("USUARIO");

    color(9);
    for(x=5; x<34; x++){
            gotoxy(30, x); printf("%c", 186);
    }
    gotoxy(30, 34); printf("%c", 202);
    color(15);
    gotoxy(6, 7); printf("Ver perfil");
    gotoxy(6, 9); printf("Playlist");
    gotoxy(6, 11); printf("Canciones");
    gotoxy(6, 13); printf("Recomendados");
    gotoxy(6, 15); printf("Configuracion", 164);
    gotoxy(6, 17); printf("Cerrar sesion");
    gotoxy(6, 19); printf("Salir");
}
/// Mover flechita para elegir opcion en algun menu
int moverCursor(int X, int Y, int arriba, int abajo, int saltos){
    int x=X, y=Y, opcion=1;
    char control;

    color(9);

    gotoxy(y, x); printf("%c", 62);
    do{
        control = getch();
        if(control !=13){
            if(control == 80 && x < abajo){
                x+=saltos;
                opcion++;
            }
            else if(control == 72 && x > arriba){
                x-=saltos;
                opcion--;
            }
            else if(control == 80 && x == abajo+1){
                x-=saltos;
                opcion--;
            }
            else if(control == 72 && x == arriba-1){
                x+=saltos;
                opcion++;
            }

            if(control == 80){
                gotoxy(y, x-saltos); printf(" ");
                gotoxy(y, x); printf("%c", 62);
            }
            else if(control == 72){
                gotoxy(y, x+saltos); printf(" ");
                gotoxy(y, x); printf("%c", 62);
            }

        }
    }while(control != 13);
    color(15);
    gotoxy(y, x); printf(" ");

    return opcion;
}

/// Mueve la flechita en la pantalla de usuarios
int moverCursorUsuarios(int users){
    int arriba = 6;
    int asd = 3*users;
    int abajo = arriba + asd;
    int opcion = moverCursor(6, 34, 6, abajo-3, 3);
    return opcion;
}

/// Mueve la flechita en la pantalla de modificacion
int moverCursorModificacion(int cant){
    int arriba = 9;
    int asd = 3*cant;
    int abajo = arriba + asd;
    int opcion = moverCursor(9, 68, 9, abajo-3, 3);
    return opcion;
}

/// Mueve la flechita en la pantalla de modificacion canciones
int moverCursorModificacionCacion(int cant){
    int arriba = 8;
    int asd = 3*cant;
    int abajo = arriba + asd;
    int opcion = moverCursor(7, 68, 7, abajo-6, 3);
    return opcion;
}

/// Mueve la flechita en la pantalla de modificacion de configuracion
int moverCursorConfiguracion(int cant){
    int arriba = 12;
    int asd = 3*cant;
    int abajo = arriba + asd;
    int opcion = moverCursor(12, 68, 12, abajo-3, 3);
    return opcion;
}






