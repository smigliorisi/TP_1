/*
 * ArrayPassengers.c
 *
 *  Created on: 4 may. 2022
 *      Author: Sebsastian Migliorisi
 */
#include "ArrayPassengers.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn_Migliorisi.h"

/** \brief To indicate that all position in the array are empty,
* this function put the flag (isEmpty) in TRUE in all
* position of the array
* \param list Passenger* Pointer to array of passenger
* \param len int Array length
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*
*/
int initPassengers(ePassenger* list, int len)
{
	int retorno=-1;
	if(list!=NULL)
	{
		for(int i=0; i<len; i++)
		{
			list[i].isEmpty=1;
		}
		retorno=0;
	}
	return retorno;
}

/** \brief print the content of passengers array
*
* \param list Passenger*
* \param length int
* \return int
*
*/
int printPassengers(ePassenger* list, int length)
{
	int retorno=-1;
	int vacio=0;
	if(list!=NULL)
	{
		printf("\n******* Lista de Pasajeros *******\n\n");
		printf(" Id          Nombre         Apellido     Precio   Tipo de Pasajero   Codigo de vuelo   Estado\n\n");

		for(int i=0;i<length;i++)
		{
			if (list[i].isEmpty==0)
			{
				printf(" %d	%10s	%10s	%8.2f	%d   %10s   %d\n", list[i].id, list[i].name, list[i].lastName, list[i].price, list[i].typePassenger, list[i].flyCode, list[i].statusFlight);
				vacio=1;
			}
		}
		if(!vacio)
			printf("\n******* No hay Pasajeros que listar *******\n\n");
		retorno=0;
	}
	return retorno;
}

int printPassengersXEstCod(ePassenger* list, int length, int opcion)
{
	int retorno=-1;
	int vacio=0;
	ePassenger auxPasajero;
	if(list!=NULL)
	{
		if (opcion==1){
			if (utn_getString(auxPasajero.flyCode,"Ingrese codigo de vuelo\n","ERROR (Rango->0,10)\n",0,10,2)==0){
				printf("\n******* Lista de Pasajeros x Codigo de vuelo *******\n\n");
				printf(" Id          Nombre         Apellido     Precio   Tipo de Pasajero   Codigo de vuelo    Estado\n\n");
				for(int i=0;i<length;i++)
				{
					if (list[i].isEmpty==0 && (strcmp(list[i].flyCode, auxPasajero.flyCode)==0))
					{
						printf(" %d	%10s	%10s	%8.2f	%d   %10s   %d\n", list[i].id, list[i].name, list[i].lastName, list[i].price, list[i].typePassenger,list[i].flyCode,list[i].statusFlight);
						vacio=1;
					}
				}
			}
		}else{
			printf("\n******* Lista de Pasajeros x Estado Activo *******\n\n");
			printf(" Id          Nombre         Apellido     Precio   Tipo de Pasajero   Codigo de vuelo    Estado\n\n");
			for(int i=0;i<length;i++)
			{
				if (list[i].isEmpty==0 && list[i].statusFlight==1)
				{
					printf(" %d	%10s	%10s	%8.2f	%d   %10s  %d\n", list[i].id, list[i].name, list[i].lastName, list[i].price, list[i].typePassenger,list[i].flyCode,list[i].statusFlight);
					vacio=1;
				}
			}
		}
		if(!vacio)
			printf("\n******* No hay Pasajeros que listar *******\n\n");
		retorno=0;
	}
	return retorno;
}

/** \brief add in a existing list of passengers the values received as parameters
* in the first empty position
* \param list passenger*
* \param len int
* \param id int
* \param name[] char
* \param lastName[] char
* \param price float
* \param typePassenger int
* \param flycode[] char
* \return int Return (-1) if Error [Invalid length or NULL pointer or without
free space] - (0) if Ok */

int addPassenger(ePassenger* list, int len, int id, char name[],char lastName[],float price,int typePassenger, char flycode[])
{
	int retorno=-1;
	int indice = findEmpty(list,len);

	if(list!=NULL)
	{
		if(indice==-1)
		{
			printf("Sistema Completo\n\n");
			retorno=0;
		}
		else
		{
			if(findPassengerById(list,len,id)==-1)
			{
						list[indice].isEmpty=0;
						list[indice].id=id;
						strcpy(list[indice].name,name);
						strcpy(list[indice].lastName,lastName);
						list[indice].price=price;
						strcpy(list[indice].flyCode,flycode);
						list[indice].typePassenger=typePassenger;
						list[indice].statusFlight=1;
						printf("\nAlta de Pasajero exitosa\n");
						retorno=1;
			}
			else
			{
				printf("Ya existe un Pasajero registrado con ese id \n\n");
				retorno=0;
			}
		}

	}
	return retorno;
}

/** \brief find a Passenger by Id en returns the index position in array.
*
* \param list Passenger*
* \param len int
* \param id int
* \return Return passenger index position or (-1) if [Invalid length or
NULL pointer received or passenger not found]
*
*/
int findPassengerById(ePassenger* list, int len,int id)
{
	int indice=-1;

		for(int i=0;i<len;i++)
			if(list[i].id == id && list[i].isEmpty==0)
			{
				indice=i;
				break;
			}

		return indice;
}
/**
 * \brief find an empty slot and returns the index position in array.
 *
 * \param vec Passenger
 * \param tam int
 * \return Return empty index position or (-1) if [Invalid length or NULL pointer received or Passenger not found]
 */
int findEmpty(ePassenger list[], int tam)
{
	int indice=-1;

	for(int i=0; i<tam; i++)
		if(list[i].isEmpty)
		{
			indice=i;
			break;
		}
	return indice;
}

/** \brief Remove a Passenger by Id (put isEmpty Flag in 1)
*
* \param list Passenger*
* \param len int
* \param id int
* \return int Return (-1) if Error [Invalid length or NULL pointer or if can't
find a passenger] - (0) if Ok
*
*/
int removePassenger(ePassenger* list, int len, int id)
{
	int i;
	char confirma;
	int retorno =-1;

	if(list!=NULL)
	{

		printf("\n******* Baja de Pasajero *******\n");

			i = findPassengerById(list,len,id);
			if(i==-1)
			{
				printf("No hay registro de un Pasajero con el id: %d\n", id);
			}
			else
			{
				printf("Id          Nombre         Apellido     Precio        Tipo de pasajero   Codigo de vuelo   Estado\n");
				printf(" %d	        %10s	       %10s	        %.2f	       %d      %10s      %d\n", list[i].id, list[i].name, list[i].lastName, list[i].price, list[i].typePassenger, list[i].flyCode, list[i].statusFlight);

				if(utn_getCharacter(&confirma,"\nConfirma la baja? ('s' para confirmar)\n","ERROR ('s' para confirmar)",'n','s',2)==0 && confirma=='s')
				{
					list[i].isEmpty=1;
					printf("Se realizó la baja con éxito\n");
				}
				else
				{
					printf("Se canceló la operación\n");
				}
			}
			retorno=0;
	}
	return retorno;
}

/** \brief Sort the elements in the array of passengers, the argument order
indicate UP or DOWN order
*
* \param list Passenger*
* \param len int
* \param order int [1] indicate UP - [0] indicate DOWN
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*
*/
int sortPassengers(ePassenger* list, int len, int order)
{
	int retorno=-1;
	ePassenger auxPasajero;

	if(list!=NULL)
	{
		for(int i=0;i<len;i++)
		{
			for(int i=0;i<len-1;i++)
			{
				for(int j=i+1;j<len;j++)
				{
					if(strcmp(list[i].lastName, list[j].lastName)>0 && order==1)
					{
						auxPasajero=list[i];
						list[i]=list[j];
						list[j]=auxPasajero;
					}
					else if(strcmp(list[i].lastName, list[j].lastName)==0 && list[i].typePassenger>list[j].typePassenger && order==1)
					{
						auxPasajero=list[i];
						list[i]=list[j];
						list[j]=auxPasajero;
					}
					if(strcmp(list[i].lastName, list[j].lastName)<0 && order==0)
					{
						auxPasajero=list[i];
						list[i]=list[j];
						list[j]=auxPasajero;
					}
					else if(strcmp(list[i].lastName, list[j].lastName)==0 && list[i].typePassenger<list[j].typePassenger && order==0)
					{
						auxPasajero=list[i];
						list[i]=list[j];
						list[j]=auxPasajero;
					}
				}
			}
		}
		printf("\nOrdenamiento exitoso\n");
		retorno=0;
	}
	else
		printf("\nOperación cancelada\n");

	return retorno;
}

int sortPassengersXEstCod(ePassenger* list, int len, int order)
{
	int retorno=-1;
	ePassenger auxPasajero;

	if(list!=NULL)
	{
		for(int i=0;i<len;i++)
		{
			for(int i=0;i<len-1;i++)
			{
				for(int j=i+1;j<len;j++)
				{
					if(strcmp(list[i].flyCode, list[j].flyCode)>0 && order==1)
					{
						auxPasajero=list[i];
						list[i]=list[j];
						list[j]=auxPasajero;
					}
					else if(strcmp(list[i].flyCode, list[j].flyCode)==0 && list[i].typePassenger>list[j].typePassenger && order==1)
					{
						auxPasajero=list[i];
						list[i]=list[j];
						list[j]=auxPasajero;
					}
					if(strcmp(list[i].lastName, list[j].lastName)<0 && order==0)
					{
						auxPasajero=list[i];
						list[i]=list[j];
						list[j]=auxPasajero;
					}
					else if(strcmp(list[i].lastName, list[j].lastName)==0 && list[i].typePassenger<list[j].typePassenger && order==0)
					{
						auxPasajero=list[i];
						list[i]=list[j];
						list[j]=auxPasajero;
					}
				}
			}
		}
		printf("\nOrdenamiento exitoso\n");
		retorno=0;
	}
	else
		printf("\nOperación cancelada\n");

	return retorno;
}


/**
 * \brief Permite modificar Nombre o Apellido o Precio o Tipo de pasajero o Código de vuelo
 * \param list ePassenger* lista de Pasajeros
 * \param len int tamaño de la lista
 * \param id int id del Pasajero a modificar
 * \return
 */
int modifyPassenger (ePassenger* list, int len, int id)
{
	int i;
	int retorno=-1;
	int opcion;
	char confirma;
	ePassenger auxPasajero;

	printf("\n******* Modificar Pasajero *******\n\n");
	if(list!=NULL)
	{
		i = findPassengerById(list,len,id);
		if(i==-1)
		{
			printf("No hay registro de un Pasajero con el id: %d\n", id);
		}
		else
		{
			printf("Id          Nombre         Apellido     Precio        Tipo de pasajero       Codigo de vuelo          Estado\n");
			printf(" %d	        %10s	    %10s	       %8.2f	    %d            %10s            %d\n", list[i].id, list[i].name, list[i].lastName, list[i].price, list[i].typePassenger, list[i].flyCode, list[i].statusFlight);

			if(utn_getCharacter(&confirma,"\n Confirma el Pasajero seleccionado? ('s' para confirmar)\n","ERROR ('s' para confirmar)",'n','s',2)==0 && confirma=='s')
			{
				do
				{
					if(utn_getNumeroInt(&opcion,"\n Ingrese variable a modificar: 1-Nombre 2-Apellido 3-Precio 4-Tipo de pasajero 5-Codigo de vuelo 6-Salir\n", "ERROR (Rango 1->6)",1,6,2)==0)
					{
						switch(opcion)
						{
							case 1:
								if(utn_getString(auxPasajero.name,"Ingrese nombre\n","ERROR (Rango->0,20)\n",0,20,2)==0)
								{
									strcpy(list[i].name,auxPasajero.name);
									printf("Se realizó la modificación con éxito\n");
								}
								else
									printf("\nNo se modificaron datos\n");
								break;
							case 2:
								if(utn_getString(auxPasajero.lastName,"Ingrese apellido\n","ERROR (Rango->0,20)\n",0,20,2)==0)
								{
									strcpy(list[i].lastName,auxPasajero.lastName);
									printf("Se realizó la modificación con éxito\n");
								}
								else
									printf("\nNo se modificaron datos\n");
								break;
							case 3:
								if(utn_getNumeroFloat(&auxPasajero.price,"Ingrese nuevo precio\n","ERROR (Rango->0,10000000)\n",0,10000000,2)==0)
								{
									list[i].price=auxPasajero.price;
									printf("Se realizó la modificación con éxito\n");
								}
								else
									printf("\nNo se modificaron datos\n");
								break;
							case 4:
								if(utn_getNumeroInt(&auxPasajero.typePassenger,"Ingrese nuevo tipo de pasajero\n","ERROR (Rango->1,10)\n",1,10,2)==0)
								{
									list[i].typePassenger=auxPasajero.typePassenger;
									printf("Se realizó la modificación con éxito\n");
								}
								else
									printf("\nNo se modificaron datos\n");
								break;
							case 5:
								if(utn_getString(auxPasajero.flyCode,"Ingrese codigo de vuelo\n","ERROR (Rango->0,10)\n",0,10,2)==0)
								{
									strcpy(list[i].flyCode,auxPasajero.flyCode);
									printf("Se realizó la modificación con éxito\n");
								}
								else
									printf("\nNo se modificaron datos\n");
								break;
							case 6:
								break;
						}
					}
				}while(opcion != 6);
			}
			else
			{
				printf("\nSe canceló la operación\n");
			}
		}
		retorno=0;
	}
	return retorno;

}
/**
 * \brief Indica si la lista está vacía
 *
 * \param list Passenger*
 * \param len int
 * \return -1 Error - 0 Vacia - 1 No vacía
 */
int checkEmpty(ePassenger* list, int len)
{
	int retorno=-1;
	if(list!=NULL)
	{
		retorno=0;
		for(int i=0; i<len; i++)
		{
			if(list[i].isEmpty==0)
			{
				retorno=1;
				break;
			}
		}
	}
	return retorno;
}
/**
 * \brief Muestra el menu de informes de Pasajeros
 *
 * \param list Passenger* lista de Pasajeros
 * \param len int tamaño de la lista
 */
void informarPasajeros(ePassenger* list, int len)
{
	int opcion;
	char salida;
	do
	{
		if(utn_getNumeroInt(&opcion, "\n***** Menu de Informes *****\n\n"
				"1. Listar Pasajeros por Apellido y Tipo de Pasajero\n"
				"2. Total y promedio de los pasajes, y cantidad de Pasajeros que superan el promedio\n"
				"3. Listar Pasajeros por codigo de vuelo y estado activo\n"
				"4. Salir\n","\nReingrese Opcion (1 a 3)\n",1,4,2)==0)
		{
			switch(opcion)
			{
				case 1:
					listarPasajerosXApYTip(list,len);
					break;
				case 2:
					listarTotalyPromedioPasajes(list,len);
					break;
				case 3:
					listarPasajerosXCodpYEstadoActiv(list,len);
					break;
				case 4:
					utn_getCharacter(&salida, "¿Confirma Salida? (ingrese 's' para salir)\n", "",'a','z',0);
					break;
			}
		}

	}while(salida!='s');

}
/**
 * \brief Muestra una lista de Pasajeros ordenados por Apellido y tipo de vuelo
 *
 * \param list Passenger* lista de Pasajeros
 * \param len int tamaño de la lista
 */
void listarPasajerosXApYTip(ePassenger* list, int len)
{
	int orden;
	if(list!=NULL)
	{
		if(checkEmpty(list, len)==1)
		{
			if(utn_getNumeroInt(&orden,"Ingrese orden (1=ASC - 0=DESC)\n","ERROR ((1=ASC - 0=DESC))\n",0,1,2)==0)
			{
				sortPassengers(list,len,orden);
				printPassengers(list,len);
			}
			else
				printf("No se ordenó la lista por errores en el ingreso de datos\n");
		}
		else
			printf("\n******* No hay Pasajeros que ordenar *******\n\n");
	}
}
 /**
  * \brief Muestra una lista de Pasajeros ordenados por codigo de vuelo y estado activo
  *
  * \param list Passenger* lista de Pasajeros
  * \param len int tamaño de la lista
  */
 void listarPasajerosXCodpYEstadoActiv(ePassenger* list, int len)
 {
 	int opcion;
 	if(list!=NULL)
 	{
 		if(checkEmpty(list, len)==1)
 		{
 			if(utn_getNumeroInt(&opcion,"Ingrese que listar: (1=Por Codigo de vuelo - 0=Por estados activos)\n","ERROR ((1=ASC - 0=DESC))\n",0,1,2)==0)
 			{
 				printPassengersXEstCod(list,len,opcion);
 			}
 			else
 				printf("No se ordenó la lista por errores en el ingreso de datos\n");
 		}
 		else
 			printf("\n******* No hay Pasajeros que ordenar *******\n\n");
 	}
 }
/**
 * \brief Muestra el total de precios, el promedio de los mismos y la cantidad de Pasajeros que superan el promedio
 *
 * \param list Passenger* lista de Pasajeros
 * \param len int tamaño de la lista
 */
void listarTotalyPromedioPasajes(ePassenger* list, int len)
{
	int total=0;
	int promedio;
	int supPromedio=0;
	int cantEmp=0;

	if(list!=NULL && checkEmpty(list, len)==1)
	{
		for(int i=0;i<len;i++)
		{
			if (list[i].isEmpty==0)
			{
				total+=list[i].price;
				cantEmp++;
			}
		}
		promedio=total/cantEmp;
		for(int i=0;i<len;i++)
			if(list[i].isEmpty==0 && list[i].price>promedio)
				supPromedio++;
		printf("\n******* Precio Pasajes Total: $%d\n", total);
		printf("\n******* Promedio de precios de pasajes: %d\n", promedio);
		printf("\n******* Pasajeros que Superan el Promedio: %d\n", supPromedio);
	}
}
/**
 * \brief Muestra el menu de opciones
 *
 * \param op int
 * \return 0 si se ingresó correctamente, -1 si hay un error
 */
int menu (int* op)
{
	int retorno=-1;
	if(utn_getNumeroInt(op, "\n***** Gestion de Pasajeros *****\n\n"
			"1. Alta Pasajero\n"
			"2. Modificar Pasajero\n"
			"3. Baja Pasajero\n"
			"4. Informar\n"
			"5. Salir\n",
			"\nReingrese Opcion (1 a 5)\n",1,5,2)==0)
	{
		retorno=0;
	}
	return retorno;
}


