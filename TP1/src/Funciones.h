/*
 ============================================================================
 Name        : Funciones.c
 Author      :  Sebastian Migliorisi
 Description : Libreria de  headers de funciones/procedimientos
 ============================================================================
 */

#ifndef FUNCIONES_H_
#define FUNCIONES_H_
#include <stdio.h>
#include <stdlib.h>

int PrintMenu();
void IngresoKilometros(int *);
void IngresoPrecios(float *, float *);
float CalculoDebito(float *);
float CalculoCredito(float *);
float CalculoBTC(float *);
float CalculoPrecioUnitario(int *, float *);
float CalculoDiferenciaPrecios(float *, float *);
void ImprimirResultados(int *, float *, float *, float, float, float, float, float, float, float, float, float);
void ImprimirResultadosForzados();
void OperarMenu( );


#endif /* FUNCIONES_H_ */
