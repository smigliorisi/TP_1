/*
 * Controller.c
 *
 *  Created on: 10 jun. 2022
 *      Author: Sebastian
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Passenger.h"
#include "parser.h"
#include "UTN_SebaLib.h"

/** \brief Carga los datos de los pasajeros desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListPassenger)
{
	int retorno=1;
	FILE* pFile;

	ll_clear(pArrayListPassenger);
	pFile = fopen(path, "r");
	printf("Paso el open");
	if(path!=NULL && pArrayListPassenger!=NULL && pFile!=NULL)
	{
		printf("entra if controller\n");
		if(!parser_PassengerFromText(pFile,pArrayListPassenger))
				retorno=0;

	}

	fclose(pFile);
    return retorno;
}

/** \brief Carga los datos de los pasajeros desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListPassenger)
{
	int retorno=1;
	FILE* pFile;

	ll_clear(pArrayListPassenger);
	pFile = fopen(path, "rb");

	if(path!=NULL && pArrayListPassenger!=NULL && pFile!=NULL)
	{
		if(!parser_PassengerFromBinary(pFile,pArrayListPassenger))
				retorno=0;
	}

	fclose(pFile);
    return retorno;
}

int lastId(LinkedList* pArrayListPassenger)
{
    int retorno=-1;
    int mayor=0;
    int flag=0;
    Passenger* auxPass;
    int tam=ll_len(pArrayListPassenger);

    if(pArrayListPassenger!=NULL)
    {
        for(int i=0;i<tam;i++)
        {
        	auxPass = (Passenger*) ll_get(pArrayListPassenger,i);
            if(auxPass!=NULL)
            {
                if(auxPass->id > mayor || flag==0)
                {
                    mayor = auxPass->id;
                    flag = 1;
                }
            }
        }
        retorno = mayor;
    }
    return retorno;
}



/** \brief Alta de pasajero
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_addPassenger(LinkedList* pArrayListPassenger)
{
	int retorno=1;
    Passenger* pasajero;
    int idAux;
    int tipoPasajeroAux;
    float precioAux;
    char id[20];
	char nombre[50];
	char apellido[50];
	char tipoPasajero[12];
	char precio[20];
	char codigoVuelo[7];
	char statusFlight[10];
    char confirm='n';
    int statusFlightAux;

    if(pArrayListPassenger!=NULL)
    {

    	if(		utn_getString(nombre,"Ingrese Nombre: ","Error (3 a 50 caracteres)\n",3,50,2)==0
    	    &&  utn_getString(apellido,"Ingrese Apellido: ","Error (3 a 50 caracteres)\n",3,50,2)==0
			&&  utn_getNumeroFloat(&precioAux,"Ingrese Precio: ", "Error (Máximo 10000000)\n",0,10000000,2)==0
        	&&  utn_getNumeroInt(&tipoPasajeroAux,"Ingrese tipo de pasajero (1-PRIMERA CLASE 2-EJECUTIVA  3-ECONOMICA) ", "Error (Máximo 3)\n",0,3,2)==0
			&&  utn_getString(codigoVuelo,"Ingrese Codigo de vuelo: ","Error (3 a 20 caracteres)\n",3,20,2)==0
    		&&  utn_getNumeroInt(&statusFlightAux,"Ingrese Estado de vuelo (1-ATERRIZADO 2-EN HORARIO  3-EN VUELO  4-DEMORADO) ", "Error (Máximo 4)\n",0,4,2)==0)

    	{

    		idAux = lastId(pArrayListPassenger)+1;
			sprintf(id,"%d",idAux);
			sprintf(tipoPasajero,"%d",tipoPasajeroAux);
			sprintf(precio,"%f",precioAux);
			sprintf(statusFlight,"%d",statusFlightAux);

			if(utn_getCharacter(&confirm,"¿Confirma los datos ingresados? ('s' para confirmar)\n","Error ('s' para confirmar)\n",'A','z',1)==0
					&& (confirm=='s' || confirm=='S'))
			{
				pasajero = Passenger_newParametros(id, nombre, apellido, precio, tipoPasajero, codigoVuelo, statusFlight);
				if(!ll_add(pArrayListPassenger,pasajero))
					retorno=0;
			}
			else
			{
				printf("Proceso cancelado\n");
			}
		}
    }
    return retorno;
}

/** \brief Listar pasajeros
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_ListPassenger(LinkedList* pArrayListPassenger)
{
	int retorno=-1;
	int tam=ll_len(pArrayListPassenger);
	Passenger* auxPass;

	if(pArrayListPassenger!=NULL)
	{
		if(ll_isEmpty(pArrayListPassenger)==0)
		{
			printf("ID             NOMBRE            APELLIDO      PRECIO       TIPO PASAJERO        CODIGO VUELO      ESTADO VUELO\n");
			for(int i=0;i<tam;i++)
			{
				auxPass = (Passenger*) ll_get(pArrayListPassenger,i);
				if( auxPass != NULL)
				{
					mostrarPasajeros(auxPass);
					retorno=1;
				}
			}
		}
		else
		{
			printf("No hay pasajeros que mostrar\n\n");
			retorno=0;
		}
	}
	return retorno;
}

/** \brief Modificar datos de pasajero
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_editPassenger(LinkedList* pArrayListPassenger)
{
	int retorno=1;
    int id;
    Passenger* pasajero;
    char confirm;
    int opcion;
    char dato[50];
    char dato2[4];
    float precioAux;
    int tipoPasajeroAux;
    int statusFlightAux;

    if(controller_ListPassenger(pArrayListPassenger))
    {
        if(pArrayListPassenger!=NULL && utn_getNumeroInt(&id,"Ingrese el id del pasajero a modificar: ","Error, reingrese un id valido", 0, 1000000,2)==0)
        {
            pasajero = Passenger_find(pArrayListPassenger,id);

            if(pasajero!=NULL)
            {
                printf("ID             NOMBRE            APELLIDO      PRECIO       TIPO PASAJERO        CODIGO VUELO     ESTADO VUELO\n");
                printf("---------------------------------------------------------------------------------------------------------------\n");
                mostrarPasajeros(pasajero);

                if(utn_getCharacter(&confirm,"¿Confirma el pasajero seleccionado? ('s' para confirmar)\n","Error ('s' para confirmar)\n",'A','z',1)==0
                		&& (confirm=='s' || confirm=='S'))
                {
                	do
                	{
						if(utn_getNumeroInt(&opcion,"¿Qué dato desea modificar?\n"
										 "1. Nombre\n"
										 "2. Apellido\n"
										 "3. Precio\n"
										 "4. Tipo Pasajero\n",
										 "5. Codigo Vuelo\n"
										 "6. Estado Vuelo"
										 "7. Salir\n"
										 "Error, reingrese opcion (1 a 7)\n", 1, 7, 1)==0)
						{
							switch(opcion)
							{
							case 1:
								if(utn_getString(dato,"Ingrese Nombre: ","Error (3 a 50 caracteres)\n",3,50,2)==0)
								{
									Passenger_setNombre(pasajero,dato);
									printf("Nombre modificado\n");
									retorno=0;
								}
								else
									printf("Operacion cancelada\n");
								break;
							case 2:
								if(utn_getString(dato,"Ingrese Apellido: ","Error (3 a 50 caracteres)\n",3,50,2)==0)
								{
									Passenger_setApellido(pasajero,dato);
									printf("Apellido modificado\n");
									retorno=0;
								}
								else
									printf("Operacion cancelada\n");
								break;
							case 3:
								if(utn_getNumeroFloat(&precioAux,"Ingrese Precio: ", "Error (Máximo 10000000)\n",0,10000000,2)==0)
								{
									sprintf(dato,"%f",precioAux);
									Passenger_setPrecio(pasajero,precioAux);
									printf("Precio modificado\n");
									retorno=0;
								}
								else
									printf("Operacion cancelada\n");
								break;
							case 4:
								if(utn_getNumeroInt(&tipoPasajeroAux,"Ingrese Tipo Pasajero: ", "Error (Máximo 3)\n",0,3,2)==0)
								{
									sprintf(dato,"%d",tipoPasajeroAux);
									Passenger_setTipoPasajero(pasajero,tipoPasajeroAux);
									printf("Tipo Pasajero\n");
									retorno=0;
								}
								else
									printf("Operacion cancelada\n");
								break;
							case 5:
								if(utn_getString(dato2,"Ingrese Codigo Vuelo: ","Error (3 a 20 caracteres)\n",3,20,2)==0)
								{
									Passenger_setNombre(pasajero,dato2);
									printf("Codigo Vuelo\n");
									retorno=0;
								}
								else
									printf("Operacion cancelada\n");
								break;
							case 6:
								if(utn_getNumeroInt(&statusFlightAux,"Ingrese Estado de Vuelo (1-ATERRIZADO 2-EN HORARIO  3-EN VUELO  4-DEMORADO) ", "Error (Máximo 4)\n",0,4,2)==0)
								{
									sprintf(dato,"%d",statusFlightAux);
									Passenger_setEstadoVuelo(pasajero,statusFlightAux);
									printf("Estado de Vuelo\n");
									retorno=0;
								}
								else
									printf("Operacion cancelada\n");
								break;
							case 7:
								break;

							}
						}
                    }while(opcion!=7);
                }

            }
            else
            	printf("No se encontró el pasajero ingresado\n");
        }
    }
    return retorno;
}

/** \brief Baja de pasajero
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_removePassenger(LinkedList* pArrayListPassenger)
{
	int retorno=1;
    int id;
    Passenger* pasajero;
    int index;
    char confirm;

    if(pArrayListPassenger!=NULL && controller_ListPassenger(pArrayListPassenger)
    	&& utn_getNumeroInt(&id,"Ingrese el id del pasajero a eliminar: ","Error, reingrese un id valido", 0, 1000000,2)==0)
    {
            pasajero = Passenger_find(pArrayListPassenger,id);

            if(pasajero!=NULL)
            {
            	printf("ID             NOMBRE            APELLIDO      PRECIO       TIPO PASAJERO        CODIGO VUELO     ESTADO VUELO\n");
            	printf("---------------------------------------------------------------------------------------------------------------\n");
                mostrarPasajeros(pasajero);

                if(utn_getCharacter(&confirm,"¿Confirma el pasajero seleccionado? ('s' para confirmar)\n","Error ('s' para confirmar)\n",'A','z',1)==0
                		&& (confirm=='s' || confirm=='S'))
                {
                    index = ll_indexOf(pArrayListPassenger,pasajero);
                    ll_remove(pArrayListPassenger,index);
                    retorno=0;
                }
            }
            else
            	printf("No se encontró el pasajero ingresado\n");
    }
    return retorno;
}

int compareId (void* datoA , void* datoB)
{
   int retorno=0;

   if(((Passenger*) datoA)->id > ((Passenger*) datoB)->id)
       retorno=1;
   if(((Passenger*) datoA)->id < ((Passenger*) datoB)->id)
       retorno=-1;

   return retorno;
}

int compareNombre (void* datoA , void* datoB)
{
   int retorno=0;

   if(strcmp(((Passenger*) datoA)->nombre,((Passenger*) datoB)->nombre) > 0)
       retorno=1;
   if(strcmp(((Passenger*) datoA)->nombre,((Passenger*) datoB)->nombre) < 0)
       retorno=-1;

   return retorno;
}

int compareApellido (void* datoA , void* datoB)
{
   int retorno=0;

   if(strcmp(((Passenger*) datoA)->apellido,((Passenger*) datoB)->apellido) > 0)
       retorno=1;
   if(strcmp(((Passenger*) datoA)->apellido,((Passenger*) datoB)->apellido) < 0)
       retorno=-1;

   return retorno;
}

int comparePrecio (void* datoA , void* datoB)
{
   int retorno=0;

   if(((Passenger*) datoA)->precio > ((Passenger*) datoB)->precio)
       retorno=1;
   if(((Passenger*) datoA)->precio < ((Passenger*) datoB)->precio)
       retorno=-1;

   return retorno;
}

int compareTipoPasajero (void* datoA , void* datoB)
{
   int retorno=0;

   if(((Passenger*) datoA)->tipoPasajero > ((Passenger*) datoB)->tipoPasajero)
       retorno=1;
   if(((Passenger*) datoA)->tipoPasajero < ((Passenger*) datoB)->tipoPasajero)
       retorno=-1;

   return retorno;
}

int compareCodigoVuelo(void* datoA , void* datoB)
{
   int retorno=0;

   if(strcmp(((Passenger*) datoA)->codigoVuelo,((Passenger*) datoB)->codigoVuelo) > 0)
       retorno=1;
   if(strcmp(((Passenger*) datoA)->codigoVuelo,((Passenger*) datoB)->codigoVuelo) < 0)
       retorno=-1;

   return retorno;
}

int compareEstadoVuelo (void* datoA , void* datoB)
{
   int retorno=0;

   if(((Passenger*) datoA)->statusFlight > ((Passenger*) datoB)->statusFlight)
       retorno=1;
   if(((Passenger*) datoA)->statusFlight < ((Passenger*) datoB)->statusFlight)
       retorno=-1;

   return retorno;
}

/** \brief Ordenar pasajeros
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_sortPassenger(LinkedList* pArrayListPassenger)
{
    int retorno=1;
    int opcion;
    int orden;
    char ordenIngresado;

    if(pArrayListPassenger!=NULL)
    {
    	if(utn_getNumeroInt(&opcion,"¿En base a que dato desea ordenar?\n"
    								"1. Id\n"
    								"2. Nombre\n"
    								"3. Apellido\n"
								 	"4. Precio\n"
									"5. Tipo de pasajero\n"
									"6. Codigo Vuelo\n"
    								"7. Estado de Vuelo",
									"Error, reingrese opcion (1 a 7)\n", 1, 7, 1)==0
    		&& utn_getCharacter(&ordenIngresado,"Seleccione el tipo de ordenamiento\n"
    									"A: Ascendente\n"
    									"B: Descendente\n",
										"Error, reingrese opcion ('A' a 'B')\n", 'A', 'B', 1)==0)
		{
    		if(ordenIngresado=='A')
    		{
    			orden=1;
    		}
    		if(ordenIngresado=='B')
    		{
    			orden=0;
    		}

			switch(opcion)
			{
				case 1:
					printf("Ordenando. Aguarde un momento...\n");
					if(!ll_sort(pArrayListPassenger,compareId,orden))
					{
						printf("Lista ordenada por Id\n");
						retorno=0;
					}
					else
						printf("Error. Operacion cancelada\n");
					break;
				case 2:
					printf("Ordenando. Aguarde un momento...\n");
					if(!ll_sort(pArrayListPassenger,compareNombre,orden))
					{
						printf("Lista ordenada por Nombre\n");
						retorno=0;
					}
					else
						printf("Error. Operacion cancelada\n");
					break;
				case 3:
					printf("Ordenando. Aguarde un momento...\n");
					if(!ll_sort(pArrayListPassenger,compareApellido,orden))
					{
						printf("Lista ordenada por Apellido\n");
						retorno=0;
					}
					else
						printf("Error. Operacion cancelada\n");
					break;
				case 4:
					printf("Ordenando. Aguarde un momento...\n");
					if(!ll_sort(pArrayListPassenger,comparePrecio,orden))
					{
						printf("Lista ordenada por Precio\n");
						retorno=0;
					}
					else
						printf("Error. Operacion cancelada\n");
					break;
				case 5:
					printf("Ordenando. Aguarde un momento...\n");
					if(!ll_sort(pArrayListPassenger,compareTipoPasajero,orden))
					{
						printf("Lista ordenada por Tipo de Pasajero\n");
						retorno=0;
					}
					else
						printf("Error. Operacion cancelada\n");
					break;
				case 6:
					printf("Ordenando. Aguarde un momento...\n");
					if(!ll_sort(pArrayListPassenger,compareCodigoVuelo,orden))
					{
						printf("Lista ordenada por Codigo de Vuelo\n");
						retorno=0;
					}
					else
						printf("Error. Operacion cancelada\n");
					break;
				case 7:
					printf("Ordenando. Aguarde un momento...\n");
					if(!ll_sort(pArrayListPassenger,compareEstadoVuelo,orden))
					{
						printf("Lista ordenada por Estado de Vuelo\n");
						retorno=0;
					}
					else
						printf("Error. Operacion cancelada\n");
					break;

			}
		}
    }
    return retorno;
}

/** \brief Guarda los datos de los pasajeros en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListPassenger)
{
	int retorno=1;
	int tam=ll_len(pArrayListPassenger);
	FILE* pFile;
	Passenger* auxPass;

	if(pArrayListPassenger!=NULL)
	{
		pFile = fopen(path,"w");

		if(pFile!=NULL)
		{
			fprintf(pFile,"id,nombre,apellido,precio,tipoPasajero,codigoVuelo,estadoVuelo\n");
			for(int i=0;i<tam;i++)
			{
				auxPass = (Passenger*) ll_get(pArrayListPassenger,i);
				fprintf(pFile,"%d,%s,%s,%f,%d,%s,%d\n",auxPass->id,auxPass->nombre,auxPass->apellido,auxPass->precio,auxPass->tipoPasajero,auxPass->codigoVuelo,auxPass->statusFlight);
			}
		retorno=0;
		}
		fclose(pFile);
	}
	return retorno;
}

/** \brief Guarda los datos de los pasajeros en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListPassenger)
{
	int retorno=1;
	int tam=ll_len(pArrayListPassenger);
	FILE* pFile;
	Passenger* auxPass;

	if(pArrayListPassenger!=NULL)
	{
		pFile = fopen(path,"wb");

		if(pFile!=NULL)
		{
			for(int i=0;i<tam;i++)
			{
				auxPass = (Passenger*) ll_get(pArrayListPassenger,i);
				fwrite(auxPass,sizeof(Passenger),1,pFile);
			}
		retorno=0;
		}
		fclose(pFile);
	}
	return retorno;
}


