#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Passenger.h"
#include "UTN_SebaLib.h"

/****************************************************
    Menu:
     1. Cargar los datos de los pasajeros desde el archivo data.csv (modo texto).
     2. Cargar los datos de los pasajeros desde el archivo data.bin (modo binario).
     3. Alta de pasajero
     4. Modificar datos de pasajero
     5. Baja de pasajero
     6. Listar pasajeros
     7. Ordenar pasajeros
     8. Guardar los datos de los pasajeros en el archivo data.csv (modo texto).
     9. Guardar los datos de los pasajeros en el archivo data.bin (modo binario).
    10. Salir
*****************************************************/

int main()
{
	setbuf(stdout, NULL);
    int option = 0;
    char confirm;

    LinkedList* listaPasajeros = ll_newLinkedList();

    do{
    	if(!menu(&option))
    	{
			switch(option)
			{
				case 1:
					if(controller_loadFromText("data.csv",listaPasajeros))
						printf("Error al cargar los pasajeros\n");
					else
						printf("Carga de pasajeros exitosa\n");
					break;
				case 2:
					if(controller_loadFromBinary("data.bin",listaPasajeros))
						printf("Error al cargar los pasajeros\n");
					else
						printf("Carga de pasajeros exitosa\n");
					break;
				case 3:
					if(controller_addPassenger(listaPasajeros))
						printf("Ningún pasajero fue agregado\n");
					else
						printf("Pasajero agregado exitosamente\n");
					break;
				case 4:
					if(controller_editPassenger(listaPasajeros))
						printf("Ningún pasajero fue modificado\n");
					else
						printf("Pasajero modificado exitosamente\n");
					break;
				case 5:
					if(controller_removePassenger(listaPasajeros))
						printf("Ningún pasajero fue eliminado\n");
					else
						printf("Pasajero eliminado exitosamente\n");
					break;
				case 6:
					controller_ListPassenger(listaPasajeros);
					break;
				case 7:
					controller_sortPassenger(listaPasajeros);
					break;
				case 8:
					if(controller_saveAsText("data.csv",listaPasajeros))
						printf("Error al guardar el listado\n");
					else
						printf("Datos guardados en data.csv\n");
					break;
				case 9:
					if(controller_saveAsBinary("data.bin",listaPasajeros))
						printf("Error al guardar el listado\n");
					else
						printf("Datos guardados en data.bin\n");
					break;
				case 10:
					if(!(utn_getCharacter(&confirm,"¿Desea salir del programa? ('s' para confirmar)\n","Proceso cancelado\n",'s','s',0)==0))
						option=0;
					else
						ll_deleteLinkedList(listaPasajeros);
					break;

			}
    	}
    }while(option != 10);

    return 0;
}
