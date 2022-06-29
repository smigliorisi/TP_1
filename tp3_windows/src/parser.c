#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Passenger.h"

/** \brief Parsea los datos los datos de los pasajeros desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int parser_PassengerFromText(FILE* pFile, LinkedList* pArrayListPassenger, int* pNextId, eTipo tipos[], int tam, eVuelo vuelos[], int tamV)
{
    int todoOk = 0;
    char buffer[6][50];
    char falsa[6][50];
    Passenger* unPasajero = NULL;

    if(pFile != NULL && pArrayListPassenger != NULL && tipos != NULL && vuelos != NULL && tam > 0 && tamV > 0)
    {
        fscanf(pFile, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", falsa[0], falsa[1], falsa[2], falsa[3], falsa[4], falsa[5], falsa[6]);
        while(!feof(pFile))
        {
            todoOk = fscanf(pFile, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5], buffer[6]);

            if(todoOk!=7)
            {
                printf("Hubo un problema para leer el pasajero\n");
                exit(1);
            }
            else
            {
                unPasajero = Passenger_newParametros(buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5], buffer[6], pNextId, tipos, tam, vuelos, tamV);

                if( unPasajero != NULL)
                {
                    todoOk = ll_add(pArrayListPassenger, unPasajero);
                }
            }
        }
    }
    return todoOk;
}

/** \brief Parsea los datos los datos de los pasajeros desde el archivo datab.bin (modo binario).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int parser_PassengerFromBinary(FILE* pFile, LinkedList* pArrayListPassenger, int* pNextId, eTipo tipos[], int tam, eVuelo vuelos[], int tamV)
{

    int todoOk = 0;
    Passenger miPasajero;
    char buffer[20];
    char buffer1[20];
    char falsa[6][50];

    Passenger* unPasajero = NULL;

    if(pFile != NULL && pArrayListPassenger != NULL && tipos != NULL && vuelos != NULL && tam > 0 && tamV > 0)
    {
    	fscanf(pFile, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", falsa[0], falsa[1], falsa[2], falsa[3], falsa[4], falsa[5], falsa[6]);
        while(!feof(pFile))
        {
            fread(&miPasajero, sizeof(Passenger), 1,pFile);

            cargarDescripcionTipo(tipos, tam, miPasajero.tipoPasajero, buffer);
            cargarDescripcionEstadoVuelo(vuelos, tamV, miPasajero.estadoVuelo, buffer1);

            unPasajero = Passenger_newParamBin(miPasajero.id, miPasajero.nombre, miPasajero.apellido, miPasajero.precio, miPasajero.codigoVuelo, buffer, buffer1, pNextId, tipos, tam, vuelos, tamV);

            if( unPasajero != NULL)
            {
                todoOk = ll_add(pArrayListPassenger, unPasajero);
            }
        }
    }
    return todoOk;
}
