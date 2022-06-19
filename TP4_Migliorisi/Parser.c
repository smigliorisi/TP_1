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

int parser_PassengerFromText(FILE* pFile , LinkedList* pArrayListPassenger)
{
	int retorno=1;
	int cant;
	char buffer[4][128];
	Passenger* auxPass;

	if(pFile!=NULL && pArrayListPassenger!=NULL)
	{
		fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n", buffer[0], buffer[1], buffer[2], buffer[3]);

		while(!feof(pFile))
		{
			cant = fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n", buffer[0], buffer[1], buffer[2], buffer[3]);
			if(cant==4)
			{
				auxPass = passenger_newParametros(buffer[0], buffer[1], buffer[2], buffer[3]);
				if(!ll_add(pArrayListPassenger, auxPass))
				{
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
			auxPass = passenger_new();
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
