#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <mmsystem.h>
#include "gotoxy.h"

#include "manejoDeCanciones.h"
#include "manejoDeUsuarios.h"

/// Datos, marco y textos de cancion
void marcoCancion(){
    color(9);
    for(int y=66; y<95; y++){
        gotoxy(y, 4); printf("%c", 205);
        gotoxy(y, 30); printf("%c", 205);
    }
    gotoxy(65, 4); printf("%c", 201);
    gotoxy(95, 4); printf("%c", 187);

    for(int x=5; x<30; x++){
        gotoxy(65, x); printf("%c", 186);
        gotoxy(95, x); printf("%c", 186);
    }
    gotoxy(65, 30); printf("%c", 200);
    gotoxy(95, 30); printf("%c", 188);

    gotoxy(70, 6);  printf("ID Cancion");
    gotoxy(70, 9); printf("Titulo");
    gotoxy(70, 12); printf("Artista");
    gotoxy(70, 15); printf("Duracion");
    gotoxy(70, 18); printf("Album");
    gotoxy(70, 21); printf("A%co", 164);
    gotoxy(70, 24); printf("Genero");
    gotoxy(70, 27); printf("Eliminado");
    color(15);
}

/// Para usuario
void marcoCancionUsuario(){
    color(9);
    for(int y=66; y<95; y++){
        gotoxy(y, 10); printf("%c", 205);
        gotoxy(y, 30); printf("%c", 205);
    }
    for(int x=10; x<30; x++){
        gotoxy(65, x); printf("%c", 186);
        gotoxy(95, x); printf("%c", 186);
    }
    gotoxy(65, 10); printf("%c", 201);
    gotoxy(95, 10); printf("%c", 187);
    gotoxy(65, 30); printf("%c", 200);
    gotoxy(95, 30); printf("%c", 188);

    gotoxy(70, 12); printf("Titulo");
    gotoxy(70, 15); printf("Artista");
    gotoxy(70, 18); printf("Duracion");
    gotoxy(70, 21); printf("Album");
    gotoxy(70, 24); printf("A%co", 164);
    gotoxy(70, 27); printf("Genero");

    color(15);
}
/// Cargar estrucura de cancion
stCancion cargarStCancion(){
    stCancion song;

    marcoCancion();

    hidecursor(1);

    fflush(stdin);
    gotoxy(70, 7); scanf("%i", &song.idCancion);
    fflush(stdin);
    gotoxy(70, 10); gets(song.titulo);
    fflush(stdin);
    gotoxy(70, 13); gets(song.artista);
    fflush(stdin);
    gotoxy(70, 16); gets(song.duracion);
    fflush(stdin);
    gotoxy(70, 19); gets(song.album);
    fflush(stdin);
    gotoxy(70, 22); scanf("%i",&song.anio);
    fflush(stdin);
    gotoxy(70, 25); gets(song.genero);
    fflush(stdin);
    gotoxy(70, 28); scanf("%i", &song.eliminado);

    return song;
}

/// Cargar una cancion en un archivo de canciones
void cargarArchivoCancion(char a[]){
    FILE *archivo = fopen(a, "ab");
    stCancion song;

    song = cargarStCancion();

    if(archivo != NULL){
        fwrite(&song, sizeof(stCancion), 1, archivo);

        if(fclose(archivo) != 0){
            system("cls");
            printf("\n Error al cerrar el archivo\n");
            getch();
            exit(1);
        }
    }
    else{
        system("cls");
        printf("\n Error al abrir el archivo\n");
        getch();
        exit(1);
    }
}

/// BUSCAR CANCION POR ID, DEVUELVE EL GENERO (1 = ROCK, 2 = ROCK ALT, 3 = REGGAE, 4 = HIPHOP, 5 = POP)
int buscarCancionID (char a[], int id) {
    FILE *archivo = fopen(a, "rb");
    stCancion song;
    int pos = id-1, gen = 0;

    if(archivo != NULL) {
        fseek(archivo, pos * sizeof(stCancion), SEEK_SET);
        fread(&song, sizeof(stCancion), 1, archivo);
        if (song.eliminado != 1) {
            if (strcmpi(song.genero, "rock")==0) {
                gen = 1;
            } else if (strcmpi(song.genero, "rock alternativo")==0) {
                gen = 2;
            } else if (strcmpi(song.genero, "reggae")==0) {
                gen = 3;
            } else if (strcmpi(song.genero, "hip hop")==0) {
                gen = 4;
            } else if (strcmpi(song.genero, "pop")==0) {
                gen = 5;
            }
        }
        if(fclose(archivo) != 0){
            system("cls");
            printf("\n Error al cerrar el archivo\n");
            getch();
            exit(1);
        }
    } else {
        system("cls");
        printf("\n Error al abrir el archivo\n");
        getch();
        exit(1);
    }
    return gen;
}

/// Buscar cancion por nombre
int buscarCancionNombre(char a[], int opcion){
    int flag=0, pos=-1;
    FILE *archivo = fopen(a, "rb");
    stCancion song;
    char cancion[30];

    marcoBuscar();
    hidecursor(1);
    fflush(stdin);
    gotoxy(65,5); gets(cancion);

    if(archivo != NULL){
        while(fread(&song, sizeof(stCancion), 1, archivo) > 0 && !flag){
            if(opcion == 1){
                if(song.eliminado != 1){
                    if(strcmpi(cancion, song.titulo) == 0){
                        flag++;
                        pos = song.idCancion;
                    }
                }
            }
            else if(opcion == 0){
                if(strcmpi(cancion, song.titulo) == 0){
                    flag++;
                    pos = song.idCancion;
                }
            }
        }

        if(fclose(archivo) != 0){
            system("cls");
            printf("\n Error al cerrar el archivo\n");
            getch();
            exit(1);
        }
    }
    else{
        system("cls");
        printf("\n Error al abrir el archivo\n");
        getch();
        exit(1);
    }

    return pos;
}

/// Marco para ingresar la cancion
void marcoBuscar(){
    color(9);
    for(int x=4; x<6; x++){
        gotoxy(63, x); printf("%c", 179);
        gotoxy(113, x); printf("%c", 179);
    }
    for(int y=63; y<113; y++){
        gotoxy(y, 4); printf("%c", 196);
        gotoxy(y, 6); printf("%c", 196);
    }
    gotoxy(63, 4); printf("%c", 218);
    gotoxy(113, 4); printf("%c", 191);
    gotoxy(63, 6); printf("%c", 192);
    gotoxy(113, 6); printf("%c", 217);
    color(15);

    gotoxy(81, 2); printf("BUSCAR CANCION");
}

/// Mostrar cancion para los admins
void mostrarCancion(char a[], int pos){
    stCancion song;
    FILE *archivo = fopen(a, "rb");
    hidecursor(0);

    if(archivo != NULL){
        fseek(archivo, (pos-1) * sizeof(stCancion), SEEK_SET);

        if(fread(&song, sizeof(stCancion), 1, archivo) > 0){
            marcoCancion();
            gotoxy(70, 7);  printf("%i", song.idCancion);
            gotoxy(70, 10); printf("%s", song.titulo);
            gotoxy(70, 13); printf("%s", song.artista);
            gotoxy(70, 16); printf("%s", song.duracion);
            gotoxy(70, 19); printf("%s", song.album);
            gotoxy(70, 22); printf("%i", song.anio);
            gotoxy(70, 25); printf("%s", song.genero);
            gotoxy(70, 28); printf("%i", song.eliminado);
        }

        if(fclose(archivo) != 0){
            system("cls");
            printf("\n Error al cerrar el archivo\n");
            getch();
            exit(1);
        }
    }
    else{
        system("cls");
        printf("\n Error al abrir el archivo\n");
        getch();
        exit(1);
    }
}

/// Mostrar cancion para los usuarios
void mostrarCancionUsuario(char a[], int pos){
    stCancion song;
    FILE *archivo = fopen(a, "rb");
    hidecursor(0);

    if(archivo != NULL){
        fseek(archivo, (pos-1) * sizeof(stCancion), SEEK_SET);

        if(fread(&song, sizeof(stCancion), 1, archivo) > 0){
            marcoCancionUsuario();
            gotoxy(70, 13); printf("%s", song.titulo);
            gotoxy(70, 16); printf("%s", song.artista);
            gotoxy(70, 19); printf("%s", song.duracion);
            gotoxy(70, 22); printf("%s", song.album);
            gotoxy(70, 25); printf("%i", song.anio);
            gotoxy(70, 28); printf("%s", song.genero);
        }

        if(fclose(archivo) != 0){
            system("cls");
            printf("\n Error al cerrar el archivo\n");
            getch();
            exit(1);
        }
    }
    else{
        system("cls");
        printf("\n Error al abrir el archivo\n");
        getch();
        exit(1);
    }
}

/// Modificar cancion
void modificarCancion(char a[], int cancion, int opcion){
    stCancion song;
    FILE *archivo = fopen(a, "r+b");
    hidecursor(1);

    if(archivo != NULL){
        fseek(archivo, (cancion-1) * sizeof(stCancion), SEEK_SET);
        fread(&song, sizeof(stCancion), 1, archivo);

        if(opcion == 1){
            fflush(stdin);
            gotoxy(70, 7); printf("               ");
            gotoxy(70, 7); scanf("%i", &song.idCancion);
        }
        else if(opcion == 2){
            gotoxy(70, 10); printf("                      ");
            fflush(stdin);
            gotoxy(70, 10); gets(song.titulo);
        }
        else if(opcion == 3){
            gotoxy(70, 13); printf("                   ");
            fflush(stdin);
            gotoxy(70, 13); gets(song.artista);
        }
        else if(opcion == 4){
            gotoxy(70, 16); printf("            ");
            fflush(stdin);
            gotoxy(70, 16); gets(song.duracion);
        }
        else if(opcion == 5){
            gotoxy(70, 19); printf("                      ");
            fflush(stdin);
            gotoxy(70, 19); gets(song.album);
        }
        else if(opcion == 6){
            gotoxy(70, 22); printf("              ");
            fflush(stdin);
            gotoxy(70, 22); scanf("%i",&song.anio);
        }else if(opcion == 7){
            gotoxy(70, 25); printf("                  ");
            fflush(stdin);
            gotoxy(70, 25); gets(song.genero);
        }else if(opcion == 8){
            gotoxy(70, 28); printf(" ");
            fflush(stdin);
            gotoxy(70, 28); scanf("%i", &song.eliminado);
        }

        fseek(archivo, (cancion-1) * sizeof(stCancion), SEEK_SET);
        fwrite(&song, sizeof(stCancion), 1, archivo);

        if(fclose(archivo) != 0){
            system("cls");
            printf("\nError al cerrar el archivo");
            Sleep(5000);
            exit(1);
        }

    }
    else{
        system("cls");
        printf("\nError al abrir el archivo");
        Sleep(5000);
        exit(1);
    }
}

/// Cargar playlist
void cargarPlayList(char a[], char b[], int pos){
    FILE *archivo = fopen(a, "r+b");
    int aux;
    Usuario us1;

    hidecursor(0);
    if(archivo != NULL){
        fseek(archivo, (pos-1) * sizeof(Usuario), SEEK_SET);
        fread(&us1, sizeof(Usuario), 1, archivo);

        aux = buscarCancionNombre(b, 1);

        if(aux != -1){
            insertarID(us1.playlist, us1.cantidad, aux);
            mostrarCancionUsuario(b, aux);
            us1.cantidad++;

            fseek(archivo, (pos-1) * sizeof(Usuario), SEEK_SET);
            fwrite(&us1, sizeof(Usuario), 1, archivo);
        }
        else{
            mciSendString("play sounds\\error.mp3", NULL, 0, NULL);
            color(4);
            gotoxy(70, 8); printf("La cancion no se encuentra disponible");
            color(15);
        }
        if(fclose(archivo) != 0){
            system("cls");
            printf("\nError al cerrar el archivo");
            Sleep(5000);
            exit(1);
        }
    }
    else{
        system("cls");
        printf("\nError al abrir el archivo");
        Sleep(5000);
        exit(1);
    }
}

/// RECOMENDADOS
void mostrarRecomendados (char a[], char b[], int pos) {
    FILE *archivo = fopen(a, "rb");
    Usuario us1;
    int rock=0, rockAlt=0, reggae=0, hiphop=0, pop=0;
    int i=0, id;
    int gen;

    if (archivo != NULL) {
        fseek(archivo, (pos-1) * sizeof(Usuario), SEEK_SET);
        fread(&us1, sizeof(Usuario), 1, archivo);
        while (i < us1.cantidad) {
            id = us1.playlist[i];
            gen = buscarCancionID(b, id);
            if (gen == 1) {
                rock++;
            } else if (gen == 2) {
                rockAlt++;
            } else if (gen == 3) {
                reggae++;
            } else if (gen == 4) {
                hiphop++;
            } else if (gen == 5) {
                pop++;
            }
            i++;
        }
        int cantidades[]={rock, rockAlt, reggae, hiphop, pop};
        int mayor = masEscuchado(cantidades, 5);

        mostrar5CancionesPorGenero(b, mayor, us1);
        if(fclose(archivo) != 0){
            system("cls");
            printf("\nError al cerrar el archivo");
            Sleep(5000);
            exit(1);
        }
    } else {
        system("cls");
        printf("\nError al abrir el archivo");
        Sleep(5000);
        exit(1);
    }
}

/// DEUELVE EL GENERO MAS ESCUCHADO DE LA PLAYLIST
int masEscuchado (int c[], int val) {
    int i = 1;
    int posMayor = 0;
    int mayor = c[posMayor];

    while (i<val) {
        if (mayor<c[i]) {
            mayor=c[i];
            posMayor=i;
        }
        i++;
    }
    return posMayor;
}

/// Marco mostrar playlist
void marcoPlaylist(){
    int x, y;
    color(9);
    for(y=33; y<141; y++){
        gotoxy(y, 4); printf("%c", 196);
        gotoxy(y, 33); printf("%c", 196);
    }
    for(x=4; x<33; x++){
        gotoxy(33, x); printf("%c", 179);
        gotoxy(141, x); printf("%c", 179);
    }
    gotoxy(33, 4); printf("%c", 218);
    gotoxy(141, 4); printf("%c", 191);
    gotoxy(33, 33); printf("%c", 192);
    gotoxy(141, 33); printf("%c", 217);
    color(15);
}

/// Mostrar canciones de  la playlist
void mostrarCancionesPlayList(char songs[], int a[], int validos){
    int x= 5, y = 35;
    FILE *archivo = fopen(songs, "rb");
    stCancion can;

    if(archivo != NULL){
        for(int i=0; i<validos; i++){
            fseek(archivo, (a[i]-1)*sizeof(stCancion), SEEK_SET);
            fread(&can, sizeof(stCancion), 1, archivo);
            gotoxy(y,x); printf("  %i %s - ", can.idCancion, can.artista);
            printf("%s", can.titulo);
            x++;
        }

       if(fclose(archivo) != 0){
            system("cls");
            printf("\nError al cerrar el archivo");
            Sleep(5000);
            exit(1);
        }
    }
    else{
        system("cls");
        printf("\nError al abrir el archivo");
        Sleep(5000);
        exit(1);
    }
}

/// Mostrar playlist
int mostrarPlaylist(char a[], char b[], int pos){
    FILE *archivo = fopen(a, "rb");
    Usuario us1;

    marcoPlaylist();
    if(archivo != NULL){
        fseek(archivo, (pos-1) * sizeof(Usuario), SEEK_SET);
        fread(&us1, sizeof(Usuario), 1, archivo);

        if(us1.cantidad > 0){
            mostrarCancionesPlayList(b, us1.playlist, us1.cantidad);
        }
        else{
            gotoxy(35, 5); printf("No tiene canciones registradas aun");
            us1.cantidad = -1;
        }

        if(fclose(archivo) != 0){
            system("cls");
            printf("\nError al cerrar el archivo");
            Sleep(5000);
            exit(1);
        }
    }
    else{
        system("cls");
        printf("\nError al abrir el archivo");
        Sleep(5000);
        exit(1);
    }

    return us1.cantidad;
}

/// Insertar ID
void insertarID(int a[], int validos, int dato){
    int i=validos;
    while(i>=0 && a[i]>dato){
        a[i+1]=a[i];
        i--;
    }

    a[i+1]=dato;
}

/// Muestra las canciones de un genero determinado
void mostrar5CancionesPorGenero(char a[], int pos, Usuario us1){
    char generos[5][20]={
            {'R', 'o', 'c', 'k', '\0'},
            {'R', 'o', 'c', 'k', ' ', 'A', 'l', 't', 'e', 'r', 'n', 'a', 't', 'i', 'v', 'o', '\0'},
            {'R', 'e', 'g', 'g', 'a', 'e', '\0'},
            {'H', 'i', 'p', '-', 'H', 'o', 'p', '\0'},
            {'P', 'o', 'p', '\0'}
            };

    FILE *archivo = fopen(a, "rb");
    int cant=0, arregloID[5];
    stCancion aux;

    if(archivo != NULL){
        while(fread(&aux, sizeof(stCancion), 1, archivo)>0 && cant<5){
            if(strcmpi(aux.genero, generos[pos]) == 0){
                if(verificarQueLaCancionNoSeRepita(us1, aux.idCancion) == 0){
                    insertarID(arregloID, cant, aux.idCancion);
                    cant++;
                }
            }
        }

        if(fclose(archivo) !=0){
            system("cls");
            printf("\nError al cerrar el archivo");
            Sleep(5000);
            exit(1);
        }
    }
    else{
        system("cls");
        printf("\nError al abrir el archivo");
        Sleep(5000);
        exit(1);
    }

    mostrarCancionesPlayList(a, arregloID, cant);
}

/// Verifica que una cancion no se encuentre en la playlist
int verificarQueLaCancionNoSeRepita(Usuario us1, int id){
    int flag=0, i=0;
    while(i<us1.cantidad && !flag){
        if(us1.playlist[i] == id)
            flag++;
        i++;
    }

    return flag;
}
