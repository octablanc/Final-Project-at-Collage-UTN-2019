#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <mmsystem.h>
#include "gotoxy.h"
#include "menu.h"
#include "manejoDeUsuarios.h"
#include "manejoDeCanciones.h"
#include "reproductor.h"

int main()
{
    int opcion, salir = 0, opcion2, cerrarSesion, pos;
    int control2;
    char control;
    char users[]={"C:\\Users\\Octa\\Documents\\tsp\\Pruebas\\TpFinal\\users\\users.dat"};
    char admins[]={"C:\\Users\\Octa\\Documents\\tsp\\Pruebas\\TpFinal\\users\\admins.dat"};
    char songs[]={"C:\\Users\\Octa\\Documents\\tsp\\Pruebas\\TpFinal\\canciones\\songs.dat"};
    char mp3[]={"C:\\Users\\Octa\\Documents\\tsp\\Pruebas\\TpFinal\\canciones\\mp3.dat"};

    char us[30];
    char pw[30];
    mciSendString("play sounds\\sound3.mp3", NULL, 0, NULL);

    do{
        cerrarSesion = 0;
        system("cls");
        opcion = menu1();
        if(opcion == 3){      /// Entra al menu para registrarse.
            system("cls");
            menu3();
            crearUsuario(users);
        }
        else if(opcion == 2){ /// Entra al menu de inicio de sesion de un Usuario.
            system("cls");
            menu2();
            if(iniciarSesion(users, us, pw) == 1){
                pos = encontrarUsuario(users, us, pw);
                mciSendString("play sounds\\sound2.mp3", NULL, 0, NULL);
                do{
                    int x=4;
                    system("cls");
                    vistaUsuarios();
                    opcion = moverCursor(7, 4, 7, 19, 2);
                    switch(opcion){
                    case 1:
                        mostrarUnUsuario(users, pos, 2);
                        getch();
                        break;

                    case 2:
                        gotoxy(83, 2); printf("PLAYLIST");
                        opcion = mostrarPlaylist(users, songs, pos);
                        if(opcion != -1){
                            opcion2 = moverCursor(5, 35, 5, opcion+4, 1);
                            x+=opcion2;
                            do{
                                opcion = posId(users, pos, opcion2);
                                color(10);
                                gotoxy(35, x); printf("%c", 62);
                                color(15);
                                control = reproductor(mp3, opcion);
                                fflush(stdin);

                                if(control == '6'){
                                    opcion2++;
                                    gotoxy(35, x); printf(" ");
                                    x++;
                                }
                                else if(control == '4'){
                                    gotoxy(35, x); printf(" ");
                                    x--;
                                    opcion2--;
                                }
                            }while(control == '6' || control == '4');
                        }
                        break;

                    case 3:
                        hidecursor(0);
                        cargarPlayList(users, songs, pos);
                        getch();

                        break;

                    case 4:
                        hidecursor(0);
                        gotoxy(81, 2); printf("RECOMENDADOS");
                        marcoPlaylist();
                        mostrarRecomendados(users, songs, pos);
                        getch();
                        hidecursor(1);
                        break;

                    case 5:
                        mostrarUnUsuario(users, pos, 2);
                        opcion = moverCursorConfiguracion(5);
                        configurarUsuario(users, pos, opcion);
                        break;

                    case 6:
                        cerrarSesion++;
                        break;

                    case 7:
                        system("cls");
                        exit(1);
                    }
                }while(cerrarSesion == 0);
            }
        }
        else if(opcion == 1){ /// Entra al menu de inicio de sesion de un Admin.
            system("cls");
            menu2();
            if(iniciarSesion(admins, us, pw) == 1){
                mciSendString("play sounds\\sound2.mp3", NULL, 0, NULL);
                do{
                    system("cls");
                    vistaAdmin();
                    opcion = moverCursor(7, 4, 7, 25, 2);
                    switch(opcion){
                    case 1:
                        mostrarUsuarios(users);
                        opcion = moverCursorUsuarios(cantUsers(users, 2));
                        mostrarUnUsuario(users, opcion, 1);
                        getch();
                        system("cls");
                        break;

                    case 2:
                        control = mostrarUsuariosAltaBaja(users, 1);
                        if(control > 0){
                            opcion = moverCursorUsuarios(cantUsers(users, 1));
                            system("cls");
                            bajarUsuario(users, opcion, 0);
                            system("cls");
                        }
                        else{
                            gotoxy(36, 5);
                            printf("No hay usuarios dados de baja");
                            getch();
                            system("cls");
                        }
                        break;

                    case 3:
                        control = mostrarUsuariosAltaBaja(users, 0);
                        if(control >= 0){
                            opcion = moverCursorUsuarios(cantUsers(users, 0));
                            bajarUsuario(users, opcion, 1);
                            system("cls");
                        }
                        else{
                            gotoxy(36, 5);
                            printf("No hay usuarios dados de alta");
                            getch();
                            system("cls");
                        }
                        break;

                    case 4:
                        mostrarUsuarios(users);
                        opcion = moverCursorUsuarios(cantUsers(users, 2));
                        mostrarUnUsuario(users, opcion, 1);
                        opcion2 = moverCursorModificacion(7);
                        modificarUsuario(users, opcion, opcion2);
                        system("cls");
                        break;

                    case 5:
                        cargarArchivoCancion(songs);
                        break;

                    case 6:
                        pos = buscarCancionNombre(songs, 0);
                        if(pos > 0){
                            system("cls");
                            vistaAdmin();
                            mostrarCancion(songs, pos);
                            getch();
                        }
                        else{
                            hidecursor(0);
                            color(4);
                            mciSendString("play sounds\\error.mp3", NULL, 0, NULL);
                            gotoxy(70, 7); printf("La cancion no existe");
                            getch();
                            color(15);
                        }
                        break;

                    case 7:
                        pos = buscarCancionNombre(songs, 0);
                        system("cls");
                        if(pos > 0){
                            vistaAdmin();
                            mostrarCancion(songs, pos);
                            opcion = moverCursorModificacionCacion(8);
                            modificarCancion(songs, pos, opcion);
                        }
                        else{
                            hidecursor(0);
                            color(4);
                            mciSendString("play sounds\\error.mp3", NULL, 0, NULL);
                            gotoxy(70, 7); printf("La cancion no existe");
                            getch();
                            color(15);
                        }
                        break;

                    case 8:
                        agregarCanciones(mp3);
                        break;

                    case 9:
                        cerrarSesion++;
                        break;

                    case 10:
                        system("cls");
                        exit(1);
                    }
                }while(cerrarSesion == 0);
            }
        }
        else
            salir++;
    }while(salir == 0);
    system("cls");

    return 0;
}
