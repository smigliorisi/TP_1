/*
 ============================================================================
 Name        : TP_2_Sebastian_Migliorisi.c
 Author      : Sebastian Migliorisi
 Version     :
 Copyright   : 
 Description : TP 2
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ArrayPassengers.h"
#include "utn_Migliorisi.h"

#define TAM 1000

int main(void) {
	setbuf(stdout, NULL);
	int opcion;
	int proximoId=100;
	char salida='n';
	ePassenger lista[TAM];
	ePassenger auxPasajero;

	initPassengers(lista,TAM);

	do
	{
		if(menu(&opcion)==0)
		{
			switch(opcion)
			{
				case 1:
					printf("\n******* Alta de Pasajeros *******\n\n");
					if(	utn_getString(auxPasajero.name,"Ingrese nombre\n","ERROR (Rango->0,20)\n",0,20,2)==0 &&
						utn_getString(auxPasajero.lastName,"Ingrese apellido\n","ERROR (Rango->0,20)\n",0,20,2)==0 &&
						utn_getNumeroFloat(&auxPasajero.price,"Ingrese precio\n","ERROR (Rango->0,10000000)\n",0,10000000,2)==0 &&
						utn_getNumeroInt(&auxPasajero.statusFlight,"Ingrese estado de vuelo (1-ACTIVO 2-CANCELADO  3-DEMORADO)\n","ERROR (Rango->1,3)\n",1,3,2)==0 &&
						utn_getNumeroInt(&auxPasajero.typePassenger,"Ingrese tipo de pasajero (1-Ejecutivo 2-Premium  3-Primer Clase)\n","ERROR (Rango->1,3)\n",1,3,2)==0 &&
						utn_getString(auxPasajero.flyCode,"Ingrese codigo de vuelo\n","ERROR (Rango->0,10)\n",0,10,2)==0
						)
					{
						if(addPassenger(lista, TAM, proximoId, auxPasajero.name,auxPasajero.lastName,auxPasajero.price,auxPasajero.typePassenger, auxPasajero.flyCode))
							proximoId+=1;
					}
					else
						printf("No se ingresó el pasajero por errores en el ingreso de datos\n");
					break;
				case 2:
					if(checkEmpty(lista, TAM)==1)
					{
						if(utn_getNumeroInt(&auxPasajero.id,"Ingrese id\n","ERROR (Rango->0,10000)\n",0,1000,2)==0)
							modifyPassenger(lista,TAM,auxPasajero.id);
						else
							printf("No se ingresó el empleado por errores en el ingreso de datos\n");
					}
					else
						printf("\n******* No hay empleados que modificar *******\n\n");
					break;
				case 3:
					if(checkEmpty(lista, TAM)==1)
					{
						if(utn_getNumeroInt(&auxPasajero.id,"Ingrese id\n","ERROR (Rango->0,10000)\n",0,1000,2)==0)
							removePassenger(lista,TAM,auxPasajero.id);
						else
							printf("No se ingresó el empleado por errores en el ingreso de datos\n");
					}
					else
						printf("\n******* No hay empleados que dar de baja *******\n\n");
					break;

				case 4:
					informarPasajeros(lista, TAM);
					break;
				case 5:
					utn_getCharacter(&salida, "¿Confirma Salida? (ingrese 's' para salir)\n", "",'a','z',0);
					break;
			}
		}


	}while(salida!='s');

	return 0;
}
