/*
 ============================================================================
 Name        : TP1.c
 Author      :  Sebastián Migliorisi
 Description : TP 1 - UTN 2022
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "Funciones.h"

int main(void) {

	setbuf(stdout, NULL);
// Se realizan todos los calculos/impresiones en la funcion de abajo
	OperarMenu();
	system("pause");

	return EXIT_SUCCESS;
}
