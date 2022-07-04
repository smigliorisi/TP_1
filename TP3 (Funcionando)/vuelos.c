#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vuelos.h"


int cargarIntEstadoVuelo(eVuelo vuelo[], int tam, char* desc)
{
    int estadoVuelo = 0;

    if(vuelo != NULL && desc != NULL && tam > 0)
    {
        for(int i=0; i < tam; i++)
        {
            if(stricmp(desc,vuelo[i].descEstado) == 0)
            {
                estadoVuelo = vuelo[i].estadoVuelo;
                break;
            }
        }
    }
    return estadoVuelo;
}

int cargarDescripcionEstadoVuelo(eVuelo vuelo[], int tam, int estadoVuelo, char desc[])
{
    int todoOk = 0;

    if(vuelo != NULL && desc != NULL && tam > 0)
    {
        for(int i = 0; i < tam; i++)
        {
            if(vuelo[i].estadoVuelo == estadoVuelo)
            {
                strcpy(desc, vuelo[i].descEstado);
                todoOk = 1;
                break;
            }
        }
    }
    return todoOk;
}

int validarEstado(eVuelo vuelo[], int tam, int id)
{
    int esValido = 0;

    if(vuelo != NULL && tam > 0)
    {
        for(int i=0; i<tam; i++)
        {
            if(id == vuelo[i].estadoVuelo)
            {
                esValido = 1;
                break;
            }
        }
    }
    return esValido;
}

int menuVuelos(eVuelo vuelos[], int tam, char* codigoVuelo)
{
    int todoOk = 0;
    int opcion;

    if(vuelos != NULL && tam > 0)
    {
        printf("    *** VUELOS ***    \n");
        printf("           CODIGOS           ESTADO\n");
        printf("---------------------------------------\n");
        for(int i=0; i<tam; i++)
        {
            printf("%d ) ", i+1);
            printf("    %10s         %10s\n", vuelos[i].codigoVuelo, vuelos[i].descEstado);
        }
        printf("Ingrese vuelo: ");
        scanf("%d", &opcion);

        switch(opcion)
        {
        case 1:
            strcpy(codigoVuelo, "BA2491A");
            todoOk = 1;
            break;
        case 2:
            strcpy(codigoVuelo, "IB0800A");
            todoOk = 1;
            break;
        case 3:
            strcpy(codigoVuelo, "MM0987B");
            todoOk = 1;
            break;
        case 4:
            strcpy(codigoVuelo, "TU6789B");
            todoOk = 1;
            break;
        case 5:
            strcpy(codigoVuelo, "GU2345F");
            todoOk = 1;
            break;
        case 6:
            strcpy(codigoVuelo, "HY4567D");
            todoOk = 1;
            break;
        case 7:
            strcpy(codigoVuelo, "FR5678G");
            todoOk = 1;
            break;
        case 8:
            strcpy(codigoVuelo, "BR3456J");
            todoOk = 1;
            break;
        default:
            printf("Ingreso Invalido.\n");
            break;
        }

    }
    return todoOk;
}

int cargarEstadoVuelo(eVuelo vuelo[], int tam, char* codigoVuelo, char* estadoVuelo)
{
    int todoOk = 0;

    if(vuelo != NULL && codigoVuelo != NULL && tam > 0)
    {
        for(int i = 0; i<tam; i++)
        {
            if(stricmp(vuelo[i].codigoVuelo, codigoVuelo) == 0)
            {
                strcpy(estadoVuelo, vuelo[i].descEstado);
                todoOk = 1;
                break;
            }
        }
    }
    return todoOk;
}


