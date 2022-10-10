#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <mmsystem.h>
#include "gotoxy.h"
#include "manejoDeUsuarios.h"
#include "menu.h"

/// Crear usuario
void crearUsuario(char a[]){
    FILE *archivo = fopen(a, "ab");
    Usuario usuario1;

    if(archivo != NULL){

        usuario1 = cargarUsuario();

        fwrite(&usuario1, sizeof(Usuario), 1, archivo);

        if(fclose(archivo) != 0){
            system("cls");
            printf("\n Error al cerrar el archivo\n");
        }
    }
    else{
        system("cls");
        printf("\n Error al abrir el archivo de Admins\n");
    }
}

/// Cargar un usuario en una estructura Usuario
Usuario cargarUsuario(){
    int i=0;
    Usuario us1;
    hidecursor(1);

    us1.cantidad=0;
    us1.idUsuario = 0;

    fflush(stdin);
    gotoxy(60, 18); gets(us1.nombreUsuario);

    gotoxy(60, 21); while(us1.pass[i]!=13){
        us1.pass[i] = getch();

        if(us1.pass[i]>32 && i<20){
            putchar('*');
            i++;
        }
        else if(us1.pass[i]==8 && i>0){
                putchar(8);
                putchar(' ');
                putchar(8);
                i--;
        }
    }
    us1.pass[i] = '\0';


    fflush(stdin);
    gotoxy(60, 24); gets(us1.anioNacimiento);

    fflush(stdin);
    gotoxy(60, 27); scanf("%c", &us1.genero);

    fflush(stdin);
    gotoxy(60, 30); gets(us1.pais);

    us1.eliminado = 0;

    return us1;
}

/// Verifica si son correctos los datos ingresados (devuelve 1 si son los 2 correctos, 2 si el nombre de usuario es correcto pero la contraseña no y 0 los dos incorrectos).
int validarIngreso(char a[], char b[], char c[]){
    int flag = 0;
    FILE *archivo = fopen(a, "rb");
    Usuario us1;

    if(archivo != NULL){
        while(fread(&us1, sizeof(Usuario), 1, archivo) > 0 && !flag){
            if(strcmpi(us1.nombreUsuario, b) == 0){
                flag++;
                if(strcmpi(us1.pass, c) == 0){
                    flag++;
                    if(us1.eliminado == 1)
                        flag++;
                }
            }
        }

        if(fclose(archivo) != 0){
            system("cls");
            printf("\n Error al cerrar el archivo\n");
        }
    }
    else{
        system("cls");
        printf("\n Error al abrir el archivo\n");
    }

    return flag;
}

/// Ingresa usuario y contraseña
void ingresarCuenta(char b[], char c[]){
    int i=0;
    hidecursor(1);

    fflush(stdin);
    gotoxy(60, 21); scanf("%s", b);

    gotoxy(60, 24); while(c[i]!=13){
        c[i] = getch();

        if(c[i]>32 && i<20){
            putchar('*');
            i++;
        }
        else if(c[i]==8 && i>0){
                putchar(8);
                putchar(' ');
                putchar(8);
                i--;
        }
    }
    c[i] = '\0';
    hidecursor(0);
}
/// Permite iniciar sesion
int iniciarSesion(char a[], char b[], char c[]){
    int permiso=0, intentos=0;

    do{
        ingresarCuenta(b, c);
        int validar = validarIngreso(a, b, c);

        if(validar == 2){
            permiso++;
        }
        else if(validar == 1){
            hidecursor(0);
            mciSendString("play sounds\\error.mp3", NULL, 0, NULL);
            intentos++;
            if(intentos == 3){
                gotoxy(40, 27); printf("Intentaste mas de 3 veces, el programa se cerrara en 5 segundos");
                Sleep(5000);
                system("cls");
                exit(1);
            }
            gotoxy(60, 21); printf("                      ");
            gotoxy(60, 24); printf("                      ");
            color(4);
            gotoxy(40, 27); printf("Contrase%ca incorrecta. Presione una tecla para intentar de nuevo", 164);
            color(15);
            getch();
            hidecursor(1);
            gotoxy(40, 27); printf("                                                                ");
        }
        else if(validar == 3){
                hidecursor(0);
                gotoxy(60, 21); printf("                      ");
                gotoxy(60, 24); printf("                      ");
                mciSendString("play sounds\\error.mp3", NULL, 0, NULL);
                color(4);
                gotoxy(55, 27); printf("El usuario ha sido bloqueado");
                color(15);
                getch();
                gotoxy(55, 27); printf("                                  ");
                hidecursor(1);
        }
        else if(validar == 0){
            hidecursor(0);
            mciSendString("play sounds\\error.mp3", NULL, 0, NULL);
            intentos++;
            if(intentos == 3){
                gotoxy(40, 27); printf("Intentaste mas de 3 veces, el programa se cerrara en 5 segundos");
                Sleep(5000);
                system("cls");
                exit(1);
            }
            gotoxy(60, 21); printf("                      ");
            gotoxy(60, 24); printf("                      ");
            color(4);
            gotoxy(35, 27); printf("Usuario y Contrase%ca incorrectos. Presione una tecla para intentar de nuevo", 164);
            color(15);
            getch();
            hidecursor(1);
            gotoxy(35, 27); printf("                                                                           ");
        }
    }while(!permiso);
    hidecursor(0);

    return permiso;
}

/// Mostrar usuarios
void mostrarUsuarios(char a[]){
    FILE *archivo = fopen(a, "rb");
    Usuario us1;

    gotoxy(75, 2); printf("USUARIOS");

    if(archivo != NULL){
        int i = 5;
        while(fread(&us1, sizeof(Usuario), 1, archivo) > 0){
                if(us1.eliminado == 1)
                    color(4);
                else
                    color(10);

                gotoxy(36, i); printf(" %c", 201);

                for(int i=0; i<20; i++){
                    printf("%c", 205);
                }
                printf("%c", 187);
                i++;

                gotoxy(37, i); printf("%c", 186);
                gotoxy(58, i); printf("%c", 186);
                i++;

                gotoxy(36, i++); printf(" %c", 200);
                for(int i=0; i<20; i++){
                    printf("%c", 205);
                }
                printf("%c\n", 188);
                color(15);

                gotoxy(40, i-2); printf("%s", us1.nombreUsuario);

        }

        if(fclose(archivo) != 0)
            printf("\n Error al cerrar el archivo\n");
    }
    else
        printf("\n Error al abrir el archivo\n");
}

/// Muestra los usuarios que estan dados de alta o baja, 1(baja), 0(alta)
int mostrarUsuariosAltaBaja(char a[], int b){
    int cantBajados = 0;
    FILE *archivo = fopen(a, "rb");
    Usuario us1;

    gotoxy(75, 2); printf("USUARIOS");

    if(archivo != NULL){
        int i = 5;
        while(fread(&us1, sizeof(Usuario), 1, archivo) > 0){
            if(us1.eliminado == b){
                cantBajados++;
                if(b==1)
                    color(4);
                else
                    color(10);

                gotoxy(36, i);
                printf(" %c", 201);

                for(int i=0; i<20; i++){
                    printf("%c", 205);
                }
                printf("%c", 187);
                i++;

                gotoxy(37, i);
                printf("%c", 186);
                gotoxy(58, i);
                printf("%c", 186);
                i++;

                gotoxy(36, i++);
                printf(" %c", 200);
                for(int i=0; i<20; i++){
                    printf("%c", 205);
                }
                printf("%c\n", 188);
                color(15);

                gotoxy(40, i-2);
                printf("%s", us1.nombreUsuario);
            }
        }

        if(fclose(archivo) != 0)
            printf("\n Error al cerrar el archivo\n");
    }
    else
        printf("\n Error al abrir el archivo\n");

    return cantBajados;
}

/// Muestra un usuario
void mostrarUnUsuario(char a[], int opcion, int opcion2){
    FILE *archivo = fopen(a, "rb");
    Usuario us1;

    system("cls");
    if(opcion2 == 1)
        vistaAdmin();
    else
        vistaUsuarios();

    if(archivo != NULL){
        fseek(archivo, (opcion-1) * sizeof(Usuario), SEEK_SET);
        fread(&us1, sizeof(Usuario), 1, archivo);

        if(opcion2 == 1){
            if(us1.eliminado == 1)
                color(4);
            else
                color(10);
        }
        else
            color(9);

        for(int y=66; y<95; y++){
            gotoxy(y, 6); printf("%c", 205);
            gotoxy(y, 29); printf("%c", 205);
        }
        gotoxy(65, 6); printf("%c", 201);
        gotoxy(95, 6); printf("%c", 187);

        for(int x=7; x<29; x++){
            gotoxy(65, x); printf("%c", 186);
            gotoxy(95, x); printf("%c", 186);
        }
        gotoxy(65, 29); printf("%c", 200);
        gotoxy(95, 29); printf("%c", 188);

        if(opcion2 == 1){
            gotoxy(70, 8); printf("ID Usuario");
            gotoxy(70, 26); printf("Eliminado");
        }
        gotoxy(70, 11); printf("Nombre de usuario");
        gotoxy(70, 14); printf("Contrase%ca", 164);
        gotoxy(70, 17); printf("A%co de Nacimiento", 164);
        gotoxy(70, 20); printf("Genero");
        gotoxy(70, 23); printf("Pais");
        color(15);

        if(opcion2 == 1){
            gotoxy(70, 9); printf("%i", us1.idUsuario);
            gotoxy(70, 27); printf("%i", us1.eliminado);
        }
        gotoxy(70, 12); printf("%s", us1.nombreUsuario);
        gotoxy(70, 15); printf("%s", us1.pass);
        gotoxy(70, 18); printf("%s", us1.anioNacimiento);
        gotoxy(70, 21); printf("%c", us1.genero);
        gotoxy(70, 24); printf("%s", us1.pais);

        if(fclose(archivo) != 0){
            system("cls");
            printf("\n Error al cerrar el archivo\n");
            getch();
        }
    }
    else{
        system("cls");
        printf("\n Error al abrir el archivo\n");
    }
}

/// Cantidad de usuarios (si se pasa por parametro: 1 cuenta los que estan dados de baja, 0 de alta y 2 cuenta los 2
int cantUsers(char a[], int b){
    int cant=0;
    FILE *archivo = fopen(a, "rb");
    Usuario us1;

    if(archivo != NULL){
        if(b==2){
            while(fread(&us1, sizeof(Usuario), 1, archivo) > 0){
                    cant++;
            }
        }
        else{
            while(fread(&us1, sizeof(Usuario), 1, archivo) > 0){
                if(us1.eliminado == b)
                    cant++;
            }
        }
        if(fclose(archivo) != 0){
            system("cls");
            printf("\n Error al cerrar el archivo\n");
            Sleep(3000);
            exit(1);
        }
    }
    else{
        system("cls");
        printf("\n Error al abrir el archivo\n");
        Sleep(3000);
        exit(1);
    }

    return cant;
}

/// Dar de baja o alta a un usuario, 1(baja), 0(alta)
void bajarUsuario(char a[], int usuario, int bajaOalta){
    int cant=0, pos;
    Usuario us1;
    FILE *archivo = fopen(a, "r+b");

    if(archivo != NULL){
        fseek(archivo, 0, SEEK_SET);

        while(cant < usuario){
            fread(&us1, sizeof(Usuario), 1, archivo);
            if(us1.eliminado == !bajaOalta){
                cant++;
            }
        }

        pos = ftell(archivo)-sizeof(Usuario);

        us1.eliminado = bajaOalta;

        fseek(archivo, pos, SEEK_SET);

        fwrite(&us1, sizeof(Usuario),1, archivo);

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

/// Modificar usuario
void modificarUsuario(char a[], int usuario, int opcion){
    Usuario us1;
    FILE *archivo = fopen(a, "r+b");
    hidecursor(1);

    if(archivo != NULL){
        fseek(archivo, (usuario-1) * sizeof(Usuario), SEEK_SET);
        fread(&us1, sizeof(Usuario), 1, archivo);

        if(opcion == 1){
            fflush(stdin);
            gotoxy(70, 9); printf("               ");
            gotoxy(70, 9); scanf("%i", &us1.idUsuario);
        }
        else if(opcion == 2){
            gotoxy(70, 12); printf("                   ");
            fflush(stdin);
            gotoxy(70, 12); gets(us1.nombreUsuario);
        }
        else if(opcion == 3){
            gotoxy(70, 15); printf("                   ");
            fflush(stdin);
            gotoxy(70, 15); gets(us1.pass);
        }
        else if(opcion == 4){
            gotoxy(70, 18); printf("            ");
            fflush(stdin);
            gotoxy(70, 18); gets(us1.anioNacimiento);
        }
        else if(opcion == 5){
            gotoxy(70, 21); printf(" ");
            fflush(stdin);
            gotoxy(70, 21); scanf("%c", &us1.genero);
        }
        else if(opcion == 6){
            gotoxy(70, 24); printf("              ");
            fflush(stdin);
            gotoxy(70, 24); gets(us1.pais);
        }else{
            gotoxy(70, 27); printf(" ");
            fflush(stdin);
            gotoxy(70, 27); scanf("%i", &us1.eliminado);
        }

        fseek(archivo, (usuario-1) * sizeof(Usuario), SEEK_SET);
        fwrite(&us1, sizeof(Usuario), 1, archivo);

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

/// Encuentra el usuario por medio del usuario y contraseña, devuelve la posicion
int encontrarUsuario(char arch[], char a[], char b[]){
    int pos, flag = 0;
    FILE *archivo = fopen(arch, "rb");
    Usuario us1;

    if(archivo != NULL){
        while(fread(&us1, sizeof(Usuario), 1, archivo) > 0 && !flag){
            if(strcmpi(us1.nombreUsuario, a) == 0 && strcmpi(us1.pass, b) == 0){
                flag++;
                pos = ftell(archivo) - sizeof(Usuario);
            }
        }

        if(fclose(archivo) != 0){
            system("cls");
            printf("\n Error al cerrar el archivo\n");
        }
    }
    else{
        system("cls");
        printf("\n Error al abrir el archivo\n");
    }

    pos/=sizeof(Usuario);

    return pos+1;
}

/// Devuelve la la id de la pocision pasada por parametro
int posId(char a[], int usuario, int pos){
    FILE *archivo = fopen(a, "rb");
    Usuario aux;

    if(archivo != NULL){
        fseek(archivo, (usuario-1)*sizeof(Usuario), SEEK_SET);
        fread(&aux, sizeof(Usuario), 1, archivo);

        if(fclose(archivo) != 0){
            system("cls");
            printf("\n Error al cerrar el archivo\n");
        }
    }
    else{
        system("cls");
        printf("\n Error al abrir el archivo\n");
    }

    return aux.playlist[pos-1];
}

/// Configuracion por parte del usuario
void configurarUsuario(char a[], int pos, int opcion){
        Usuario us1;
    FILE *archivo = fopen(a, "r+b");
    hidecursor(1);

    if(archivo != NULL){
        fseek(archivo, (pos-1) * sizeof(Usuario), SEEK_SET);
        fread(&us1, sizeof(Usuario), 1, archivo);

        if(opcion == 1){
            gotoxy(70, 12); printf("                   ");
            fflush(stdin);
            gotoxy(70, 12); gets(us1.nombreUsuario);
        }
        else if(opcion == 2){
            gotoxy(70, 15); printf("                   ");
            fflush(stdin);
            gotoxy(70, 15); gets(us1.pass);
        }
        else if(opcion == 3){
            gotoxy(70, 18); printf("            ");
            fflush(stdin);
            gotoxy(70, 18); gets(us1.anioNacimiento);
        }
        else if(opcion == 4){
            gotoxy(70, 21); printf(" ");
            fflush(stdin);
            gotoxy(70, 21); scanf("%c", &us1.genero);
        }
        else if(opcion == 5){
            gotoxy(70, 24); printf("              ");
            fflush(stdin);
            gotoxy(70, 24); gets(us1.pais);
        }

        fseek(archivo, (pos-1) * sizeof(Usuario), SEEK_SET);
        fwrite(&us1, sizeof(Usuario), 1, archivo);

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






