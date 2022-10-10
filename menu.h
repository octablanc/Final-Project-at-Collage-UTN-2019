#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

/// Prototipados
void marcoMenu();
void textoMusicLib();
int menu1();
void menu3();
int moverCursor(int X, int Y, int arriba, int abajo, int saltos);
void vistaAdmin();

/// Mueve la flechita en la pantalla de usuarios
int moverCursorUsuarios(int users);

/// Mueve la flechita en la pantalla de modificacion
int moverCursorModificacion(int users);

/// Mueve la flechita en la pantalla de modificacion de configuracion
int moverCursorConfiguracion(int cant);

#endif // MENU_H_INCLUDED
