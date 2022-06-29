#include "calculos.h"

float calcularDescuento (float a, float b)
{
    float descuento;
    float precioConDescuento;

    descuento = a * b;
    precioConDescuento = a - descuento;
    return precioConDescuento;
}

float calcularInteres (float a, float b)
{
    float interes;
    float precioConInteres;

    interes = a * b;
    precioConInteres = a + interes;
    return precioConInteres;
}

float precioABtc(float a, float b)
{
    float precioEnBtc;

    precioEnBtc = a / b;

    return precioEnBtc;
}

float precioUnitario(float a, int b)
{
    float precioUnit;

    precioUnit = a / b;

    return precioUnit;
}

float diferenciaPrecios(float a, float b)
{
    float diferencia;

    if(a>b)
    {
        diferencia = a - b;
    }
    else
    {
        diferencia = b - a;
    }
    return diferencia;
}

