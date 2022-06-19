#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Parser.h"
#include "Passenger.h"
#include "UTN_SebaLib.h"

/** \brief Listar pasajeros
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int -1=Error, 0=Lista vacia, 1=Se muestran datos
 *
 */
int controller_ListPassenger(LinkedList* pArrayListPassenger)
{
	int retorno=-1;
	int tam=ll_len(pArrayListPassenger);
	Passenger* auxPass;

	if(pArrayListPassenger!=NULL)
	{
		printf("ID             NOMBRE      KILOMETROS          PRECIO\n");
		for(int i=0;i<tam;i++)
		{
			auxPass = (Passenger*) ll_get(pArrayListPassenger,i);
			if( auxPass != NULL)
			{
				mostrarPasajero(auxPass);
				retorno=1;
			}
		}
		if (retorno==-1)
		{
			printf("No hay pasajeros que mostrar\n\n");
			retorno=0;
		}
	}
	return retorno;
}
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

	if(path!=NULL && pArrayListPassenger!=NULL && pFile!=NULL)
	{
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

/** \brief Encuentra el ultimo id asociado en la LinkedList
 *
 * \param pArrayListPassenger LinkedList*
 * \return int
 */
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

/** \brief Alta de pasajeros
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
    int kilometrosViajeAux;
    int precioAux;
    char id[20];
	char nombre[128];
	char kilometrosViaje[20];
	char precio[20];
    char confirm='n';

    if(pArrayListPassenger!=NULL)
    {

    	if(	utn_getString(nombre,"Ingrese Nombre: ","Error (3 a 128 caracteres)\n",3,128,2)==0
        	&&  utn_getNumeroInt(&kilometrosViajeAux,"Ingrese Kilometros del Viaje: ", "Error (Máximo 100000000km.)\n",0,100000000,2)==0
			&&  utn_getNumeroInt(&precioAux,"Ingrese Precio: ", "Error (Máximo 1000000)\n",0,1000000,2)==0)
    	{

    		idAux = lastId(pArrayListPassenger)+1;
			sprintf(id,"%d",idAux);
			sprintf(kilometrosViaje,"%d",kilometrosViajeAux);
			sprintf(precio,"%d",precioAux);

			if(utn_getCharacter(&confirm,"¿Confirma los datos ingresados? ('s' para confirmar)\n","Proceso cancelado\n",'s','s',0)==0)
			{
				pasajero = passenger_newParametros(id,nombre,kilometrosViaje,precio);
				if(!ll_add(pArrayListPassenger,pasajero))
					retorno=0;
			}
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
    char dato[128];
    int kilometrosViajeAux;
    int precioAux;

    if(controller_ListPassenger(pArrayListPassenger))
    {
        if(pArrayListPassenger!=NULL && utn_getNumeroInt(&id,"Ingrese el id del pasajero a modificar: ","Error, reingrese un id valido", 0, 1000000,2)==0)
        {
            pasajero = passenger_find(pArrayListPassenger,id);

            if(pasajero!=NULL)
            {
                printf("ID             NOMBRE      KILOMETROS          PRECIO\n");
                printf("--------------------------------------------------\n");
                mostrarPasajero(pasajero);

                if(utn_getCharacter(&confirm,"¿Confirma el pasajero seleccionado? ('s' para confirmar)\n","Proceso cancelado\n",'s','s',1)==0)
                {
                	do
                	{
						if(utn_getNumeroInt(&opcion,"¿Qué dato desea modificar?\n"
										 "1. Nombre\n"
										 "2. Kilometros del Viaje\n"
										 "3. Precio\n"
										 "4. Salir\n",
										 "Error, reingrese opcion (1 a 4)\n", 1, 4, 1)==0)
						{
							switch(opcion)
							{
							case 1:
								if(utn_getString(dato,"Ingrese Nombre: ","Error (3 a 128 caracteres)\n",3,128,2)==0)
								{
									passenger_setNombre(pasajero,dato);
									printf("Nombre modificado\n");
									retorno=0;
								}
								else
									printf("Operacion cancelada\n");
								break;
							case 2:
								if(utn_getNumeroInt(&kilometrosViajeAux,"Ingrese Kilometros del Viaje: ", "Error (Máximo 100000000km.)\n",0,100000000,2)==0)
								{
									sprintf(dato,"%d",kilometrosViajeAux);
									passenger_setNombre(pasajero,dato);
									printf("Horas trabajadas modificadas\n");
									retorno=0;
								}
								else
									printf("Operacion cancelada\n");
								break;
							case 3:
								if(utn_getNumeroInt(&precioAux,"Ingrese Precio: ", "Error (Máximo 1000000)\n",0,1000000,2)==0)
								{
									sprintf(dato,"%d",precioAux);
									passenger_setNombre(pasajero,dato);
									printf("Precio modificado\n");
									retorno=0;
								}
								else
									printf("Operacion cancelada\n");
								break;
							case 4:
								break;
							}
						}
                    }while(opcion!=4);
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
    	&& utn_getNumeroInt(&id,"Ingrese el id del pasajero a modificar: ","Error, reingrese un id valido", 0, 1000000,2)==0)
    {
            pasajero = passenger_find(pArrayListPassenger,id);

            if(pasajero!=NULL)
            {
                printf("ID             NOMBRE      KILOMETROS          PRECIO\n");
                printf("--------------------------------------------------\n");
                mostrarPasajero(pasajero);

                if(utn_getCharacter(&confirm,"¿Confirma el pasajero seleccionado? ('s' para confirmar)\n","Proceso cancelado\n",'s','s',1)==0)
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
/** \brief Compara dos id y devuelve cual es mayor
 *
 * \param void* datoA
 * \param void* datoB
 * \return int
 */
int compareId (void* datoA , void* datoB)
{
   int retorno=0;

   if(((Passenger*) datoA)->id > ((Passenger*) datoB)->id)
       retorno=1;
   if(((Passenger*) datoA)->id < ((Passenger*) datoB)->id)
       retorno=-1;

   return retorno;
}
/** \brief Compara dos nombres y devuelve cual es mayor
 *
 * \param void* datoA
 * \param void* datoB
 * \return int
 */
int compareNombre (void* datoA , void* datoB)
{
   int retorno=0;

   if(strcmp(((Passenger*) datoA)->nombre,((Passenger*) datoB)->nombre) > 0)
       retorno=1;
   if(strcmp(((Passenger*) datoA)->nombre,((Passenger*) datoB)->nombre) < 0)
       retorno=-1;

   return retorno;
}
/** \brief Compara dos cantidades de horas y devuelve cual es mayor
 *
 * \param void* datoA
 * \param void* datoB
 * \return int
 */
int compareKilometrosViaje (void* datoA , void* datoB)
{
   int retorno=0;

   if(((Passenger*) datoA)->kilometrosViaje > ((Passenger*) datoB)->kilometrosViaje)
       retorno=1;
   if(((Passenger*) datoA)->kilometrosViaje < ((Passenger*) datoB)->kilometrosViaje)
       retorno=-1;

   return retorno;
}
/** \brief Compara dos precios y devuelve cual es mayor
 *
 * \param void* datoA
 * \param void* datoB
 * \return int
 */
int comparePrecio (void* datoA , void* datoB)
{
   int retorno=0;

   if(((Passenger*) datoA)->precio > ((Passenger*) datoB)->precio)
       retorno=1;
   if(((Passenger*) datoA)->precio < ((Passenger*) datoB)->precio)
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
    								"3. Kilometros del Viaje\n"
								 	"4. Precio\n",
									"Error, reingrese opcion (1 a 4)\n", 1, 4, 1)==0
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
					if(!ll_sort(pArrayListPassenger,compareKilometrosViaje,orden))
					{
						printf("Lista ordenada por Kilometros del Viaje\n");
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
			fprintf(pFile,"id,nombre,kilometrosViaje,precio\n");
			for(int i=0;i<tam;i++)
			{
				auxPass = (Passenger*) ll_get(pArrayListPassenger,i);
				fprintf(pFile,"%d,%s,%d,%d\n",auxPass->id,auxPass->nombre,auxPass->kilometrosViaje,auxPass->precio);
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

