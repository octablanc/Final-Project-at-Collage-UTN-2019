#ifndef MANEJODEUSUARIOS_H_INCLUDED
#define MANEJODEUSUARIOS_H_INCLUDED

typedef struct {
     int idUsuario;
     char nombreUsuario[30];
     char pass[20];
     char anioNacimiento[20];
     char genero;
     char pais[20];
     int playlist[50]; //Guarda los id de las canciones.
     int cantidad;     // Es el válidos de la playlist.
     int eliminado;    // indica 1 o 0 si el cliente fue eliminado
}Usuario;

/// Ingresar el primer
void crearUsuario(char a[]);

/// Cargar un usuario
Usuario cargarUsuario();

/// Verifica si los datos ingresados son correctos
int validarIngreso(char a[], char b[], char c[]);

/// Ingresa usuario y contraseña
void ingresarCuenta(char b[], char c[]);

/// Permite iniciar sesion
int iniciarSesion(char a[], char b[], char c[]);

/// Muestra los usuarios
void mostrarUsuarios(char a[]);

/// Muestra usuarios dados de baja
int mostrarUsuariosAltaBaja(char a[],int b);

/// Muestra un usuario
void mostrarUnUsuario(char a[], int opcion, int opcio2);

/// Cantidad de usuarios
int cantUsers(char a[], int b);

/// Dar de baja o alta a un usuario, 1(baja), 0(alta)
void bajarUsuario(char a[], int usuario, int bajaOalta);

/// Modificar un usuario
void modificarUsuario(char a[], int usuario, int opcion);

/// Encuentra el usuario por medio del usuario y contraseña, devuelve la posicion en bytes
int encontrarUsuario(char arch[], char a[], char b[]);

/// Devuelve la la id de la pocision pasada por parametro
int posId(char a[], int usuario, int pos);

#endif // MANEJODEUSUARIOS_H_INCLUDED
