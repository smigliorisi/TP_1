/*
 * UTN_SebaLib.h
 *
 *  Created on: 10 jun. 2022
 *      Author: EChevy
 */

#ifndef UTN_SEBALIB_H_
#define UTN_SEBALIB_H_

int utn_getNumeroInt(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos);
int utn_getNumeroFloat(float* pResultado, char* mensaje, char* mensajeError, float minimo, float maximo, int reintentos);
int utn_getCharacter(char* pResultado, char* mensaje, char* mensajeError, char minimo, char maximo, int reintentos);
int utn_getString(char* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos);

int calcularMayor (int *pResultado, int num1, int num2);
int calcularMenor (int *pResultado, int num1, int num2);

#endif /* UTN_SEBALIB_H_ */
