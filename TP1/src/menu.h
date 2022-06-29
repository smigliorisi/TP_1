#ifndef MENU_H_
#define MENU_H_



#endif /* MENU_H_ */

#include <stdio.h>
#include <stdlib.h>
#include "calculos.h"

/// @brief imprime el menu de opciones del programa, recibe la opcion ingresada, la valida y muestra en pantalla la actualizacion de datos ingresados.
///
/// @param pKm int* acceso a los Km cargados en el sistema.
/// @param pP1 float* acceso a el precio cargado en el sistema de la primera aerolinea.
/// @param pP2 float* acceso a el precio cargado en el sistema de la segunda aerolinea.
/// @return retorna la opcion ingresada por el usuario.
int menu(int* pKm, float* pP1, float* pP2);

/// @brief permite al usuario ingresar la cantidad de kilometros
///
/// @param pFlag int* puntero a la bandera que indica que los Km ya fueron cargados
/// @param pKm int* puntero a la variable kilometros.
/// @return retorna 1 si los datos fueron cargados correctamente.
int IngresarKm(int* pFlag, int* pKm);

/// @brief permite al usuario elegir entre las opciones disponibles
///
/// @return retorna la opcion ingresada, validada.
int subMenuPrecio();

/// @brief permite al usuario cargar valores en la variable de precio
///
/// @param pFlag puntero a la bandera que indica si el precio fue cargado o no.
/// @param precio puntero a la variable del precio
/// @return retorna 1 si los datos pudieron cargarse correctamente.
int ingresarPrecio(int* pFlag, float* precio);

/// @brief realiza todos calculos solicitados
///
/// @param a float precio
/// @param b float porcentaje de descuento con debito
/// @param c float porcentaje de interes del credito
/// @param d float precio del bitcoin
/// @param p1 float* puntero al precio total con descuento de debito aplicado
/// @param p2 float* puntero al precio total con incremento por credito aplicado
/// @param p3 float* puntero al precio total calculado en bitcoin
/// @param e int kilometros ingresados
/// @param p4 float* puntero al precio del kilometro unitario
/// @param flag1 int bandera del kilometro ingresado
/// @param flag2 int bandera del precio ingresado
/// @param pFlagCostos int* puntero a la bandera que indica que los calculos fueron realizados
/// @return retorna 1 si todos los calculos fueron realizados con exito
int calcularCostos(float a, float b, float c, float d, float* p1, float* p2, float* p3, int e, float* p4, int flag1, int flag2, int* pFlagCostos);

/// @brief permite imprimir por pantalla todos los valores calculados
///
/// @param flagCostos int bandera que indica que los calculos fueron realizados
/// @param a float precio final con debito
/// @param b float precio final con credito
/// @param c float precio final en bitcoins
/// @param d float precio unitario del kilometro
/// @return retorna 1 si se pudieron informar los calculos realizados
int informar(int flagCostos,float a, float b, float c, float d);

/// @brief cambia los valores de kilometros, precios y sus respectivas banderas
///
/// @param pKm int* puntero para modificar los kilomentros ingresados
/// @param pPrecio1 float* puntero para modificar el precio 1
/// @param pPrecio2 float* puntero para modificar el precio 2
/// @param pFlagKm int* puntero al valor de la bandera que indica si el valor de kilometros fue ingresado
/// @param pFlag1 int* puntero al valor de la bandera que indica si el valor del precio 1 fue ingresado
/// @param pFlag2 int* puntero al valor de la bandera que indica si el valor del precio 2 fue ingresado
/// @return retorna 1 si todos los valores fueron cargados con exito
int cargaForzadaDatos(int* pKm, float* pPrecio1, float* pPrecio2, int* pFlagKm, int* pFlag1, int* pFlag2);

/// @brief  permite cambiar el valor de la variable de salida del bucle while
///
/// @param x char* puntero al valor de la variable de salida
void confirmarSalida(char* x);

/// @brief informa por pantalla que la opcion ingresada por el usuario no es un numero
///
void informarNoEsNumero();
