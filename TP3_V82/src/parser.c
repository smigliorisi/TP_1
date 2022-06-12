/*
 * parser.c
 *
 *  Created on: 10 jun. 2022
 *      Author: Sebastian
 */

#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Passenger.h"
#include "Controller.h"
#include "LinkedList.h"

/** \brief Parsea los datos los datos de los pasajeros desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int parser_PassengerFromText(FILE* pFile , LinkedList* pArrayListPassenger)
{
	int retorno=1;
	int cant;
	char idAux[10];
	char name[10];
	char lastName[20];
	char priceAux[10];
	char flyCode[10];
	char psgrType[10];
	char flightStatus[10];
	Passenger* auxPass;

	printf("Entra al parser\n");

	if(pFile!=NULL && pArrayListPassenger!=NULL)
	{
		fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", idAux, name, lastName, priceAux, flyCode, psgrType, flightStatus);
		printf("pasa el scanf1\n");
		while(!feof(pFile))
		{
			cant = fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", idAux, name, lastName, priceAux, flyCode, psgrType, flightStatus);
			printf("pasa el scanf2\n");
			if(cant==7)
			{
				auxPass = Passenger_newParametros(idAux, name, lastName, priceAux, flyCode, psgrType, flightStatus);
				if(!ll_add(pArrayListPassenger, auxPass))
				{
					printf("entra if final\n");
					retorno=0;
				}
			}
		}
	}

    return retorno;
}

/** \brief Parsea los datos los datos de los pasajeros desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int parser_PassengerFromBinary(FILE* pFile , LinkedList* pArrayListPassenger)
{
	int retorno=1;
	int cant;
	Passenger* auxPass;

	if(pFile!=NULL && pArrayListPassenger!=NULL)
	{
		while(!feof(pFile))
		{
			auxPass = Passenger_new();
			cant = fread(auxPass,sizeof(Passenger),1,pFile);
			if(cant==1)
			{
				if(!ll_add(pArrayListPassenger, auxPass))
					retorno=0;
			}
		}
	}

    return retorno;
}


