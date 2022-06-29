#ifndef CALCULOS_H_
#define CALCULOS_H_



#endif /* CALCULOS_H_ */

#include <stdio.h>
#include <stdlib.h>

/// @brief realiza el calculo de un descuento
///
/// @param a float de precio
/// @param b float de porcentaje de descuento
/// @return retorna el precio final con el descuento aplicado
float calcularDescuento(float a, float b);

/// @brief realiza el calculo de un interes
///
/// @param a float de precio
/// @param b float de porcentaje de interes
/// @return retorna el precio final con el incremento aplicado
float calcularInteres(float a, float b);

/// @brief permite pasar el valor ingresado a bitcoins
///
/// @param a float precio ingresado
/// @param b float valor del bitcoin
/// @return retorna el precio final calculado en bitcoins
float precioABtc(float a, float b);

/// @brief divide el valor de precio por la cantidad de kilometros
///
/// @param a float precio ingresado
/// @param b int cantidad de kilometros
/// @return retorna el valor del precio, por cada kilometro.
float precioUnitario(float a, int b);

/// @brief permite calcular la diferencia entre dos precios ingresados
///
/// @param a float precio 1
/// @param b float precio 2
/// @return retorna la diferencia entre los precios
float diferenciaPrecios(float a, float b);
