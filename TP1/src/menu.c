#include "menu.h"

int menu(int* pKm, float* pP1, float* pP2)
{
	int opcion;
	int opcionIngresada;
	system("cls");

	if(pKm != NULL && pP1 != NULL && pP2 != NULL)
	{
		printf("*** Menu de Opciones *** \n\n");
		printf("1- Ingresar Kilometros: (%d Km).\n",*pKm);
		printf("2- Ingresar Precio de Vuelos: (Areolineas: $%.2f , Latam: $%.2f )\n", *pP1, *pP2);
		printf("3- Calcular todos los costos:\n");
		printf("4- Informar Resultados\n");
		printf("5- Carga forzada de datos: \n");
		printf("6- Salir: \n");

        printf("Ingrese opcion: ");
        fflush(stdin);
        opcionIngresada = scanf("%d", &opcion);
        if(opcionIngresada == 0)
        {
            opcion = 7;
        }
	}
	return opcion;
}

int IngresarKm(int* pFlag, int* pKm)
{
    int todoOk = 0;
    if(pFlag != NULL && pKm != NULL)
    {
        printf("Ingrese Cantidad de Kilometros: \n");
        scanf("%d", pKm);
        *pFlag = 1;
        todoOk = 1;
    }

    return todoOk;
}

int subMenuPrecio()
{
    int opcion;
    int opcionIngresada;

    printf("1- Ingresar Precio de Vuelo Aerolineas: \n");
    printf("2- Ingresar Precio de Vuelo Latam: \n");

    printf("Ingrese opcion: ");
    fflush(stdin);
    opcionIngresada = scanf("%d", &opcion);
    if(opcionIngresada == 0)
    {
        opcion = 7;
    }
    return opcion;
}

int ingresarPrecio(int* pFlag, float* pPrecio)
{
    int todoOk = 0;
    if(pFlag != NULL && pPrecio != NULL)
    {
        printf("Ingresar Precio: \n");
        scanf("%f", pPrecio);
        *pFlag = 1;
        todoOk = 1;
    }
    return todoOk;
}

int calcularCostos(float a, float b, float c, float d, float* p1, float* p2, float* p3, int e, float* p4, int flag1, int flag2, int* pFlagCostos)
{
    int todoOk = 0;
    if(pFlagCostos != NULL && p1 != NULL && p2 != NULL && p3 != NULL && p4 != NULL)
    {
        if(flag1 == 1 && flag2 == 1)
        {
            *p1 = calcularDescuento(a,b);
            *p2 = calcularInteres(a,c);
            *p3 = precioABtc(a,d);
            *p4 = precioUnitario(a,e);
            *pFlagCostos = 1;
            todoOk = 1;
        }
        else
        {
            if(flag1 == 1)
            {
                printf("Primero cargue precios.\n");
            }
            else
            {
                printf("Primero cargue Kms.\n");
            }
        }
    }


    return todoOk;
}

int informar(int flagCostos,float a, float b, float c, float d)
{
    int todoOk = 0;

    if(flagCostos == 1)
    {
        printf(" a) Precio con tarjeta de debito:$ %.2f\n", a);
        printf(" b) Precio con tarjeta de credito:$ %.2f\n", b);
        printf(" c) Precio pagando con bitcoin: %.2f BTC\n", c);
        printf(" d) Precio unitario:$ %.2f\n\n", d);
        todoOk = 1;
    }
    else
    {
        printf("Primero debe calcular costos!\n");
    }
    return todoOk;
}

int cargaForzadaDatos(int* pKm, float* pPrecio1, float* pPrecio2, int* pFlagKm, int* pFlag1, int* pFlag2)
{
    int todoOk = 0;
    if(pKm != NULL && pPrecio1 != NULL && pPrecio2 != NULL && pFlag1 != NULL && pFlag2 != NULL)
    {
        *pKm = 7090;
        *pPrecio1 = 162965.00;
        *pPrecio2 = 159339.00;
        *pFlagKm = 1;
        *pFlag1 = 1;
        *pFlag2 = 1;
        todoOk = 1;
    }

    return todoOk;
}

void confirmarSalida(char* x)
{
    printf("Presione 's' para salir: ");
    fflush(stdin);
    scanf("%c", x);
}

void informarNoEsNumero()
{
    printf("Eso no es un numero.\n");
}

