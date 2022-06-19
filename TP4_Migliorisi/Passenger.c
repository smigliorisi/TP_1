#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Passenger.h"
#include "UTN_SebaLib.h"

/**
 * \brief Muestra el menu de opciones de pasajero
 *
 * \param option
 * \return
 */
int menu(int* option)
{
	int retorno=-1;
	int opcIngresada;
	if(utn_getNumeroInt(&opcIngresada,"\nMenu de opciones\n"
	    			 "1. Cargar los datos de los pasajeros desde el archivo data.csv (modo texto).\n"
	    			 "2. Cargar los datos de los pasajeros desde el archivo data.bin (modo binario).\n"
	    			 "3. Alta de pasajero\n"
	    			 "4. Modificar datos de pasajero\n"
	    			 "5. Baja de pasajero\n"
	    			 "6. Listar pasajeros\n"
	    			 "7. Ordenar pasajeros\n"
	    			 "8. Guardar los datos de los pasajeros en el archivo data.csv (modo texto).\n"
	    			 "9. Guardar los datos de los pasajeros en el archivo data.bin (modo binario).\n"
	    			 "10. Salir\n",
	    	     	 "Error, reingrese opcion (1 a 10)\n", 1, 10, 1)==0)
	{
		retorno=0;
		*option=opcIngresada;
	}
	return retorno;
}
/**
 * \brief Encuentra un pasajero por id y lo devuelve
 *
 * \param pArrayListPassenger
 * \param id
 * \return
 */
Passenger* passenger_find(LinkedList* pArrayListPassenger, int id)
{
    int tam = ll_len(pArrayListPassenger);
    Passenger* pasajero;

    if(pArrayListPassenger!=NULL)
    {
        for(int i=0;i<tam;i++)
        {
        	pasajero = (Passenger*)ll_get(pArrayListPassenger,i);
            if(pasajero->id == id)
                break;
            pasajero=NULL;
        }
    }
    return pasajero;
}
/**
 * \brief Muestra en pantalla un pasajero
 *
 * \param pasajero
 * \return
 */
int mostrarPasajero(Passenger* pasajero)
{
    int retorno=-1;

    if(pasajero!=NULL)
    {
        printf(" %d    %20s    %d    %d\n", pasajero->id, pasajero->nombre, pasajero->kilometrosViaje, pasajero->precio);
        retorno=0;
    }
    return retorno;
}
/**
 * \brief Asigna memoria para un pasajero y lo inicializa
 *
 * \return
 */
Passenger* passenger_new()
{
    Passenger* newPassenger;
    newPassenger= (Passenger*) malloc(sizeof(Passenger));

    if(newPassenger!=NULL)
    {
            newPassenger->id =0;
            strcpy(newPassenger->nombre, "");
            newPassenger->kilometrosViaje=0;
            newPassenger->precio=0;
    }

    return newPassenger;
}

/**
 * \brief Carga datos a una estructura pasajero
 *
 * \param idStr
 * \param nombreStr
 * \param kilometrosViajeStr
 * \param precioStr
 * \return
 */
Passenger* passenger_newParametros(char* idStr,char* nombreStr,char* kilometrosViajeStr, char* precioStr)
{
    int id;
    int kilometrosViaje;
    float precio;
    Passenger* newPassenger;
    newPassenger = passenger_new();


    if(newPassenger!=NULL)
    {
        id = atoi(idStr);
        kilometrosViaje = atoi(kilometrosViajeStr);
        precio = atof(precioStr);

        if(    passenger_setId(newPassenger,id)
            || passenger_setNombre(newPassenger, nombreStr)
            || passenger_setKilometrosViaje(newPassenger, kilometrosViaje)
			|| passenger_setPrecio(newPassenger, precio)
           )
        {
            free(newPassenger);
            newPassenger=NULL;
        }
    }

    return newPassenger;
}

/**
 * \brief Libera espacio en memoria reservada a un pasajero
 *
 * \param emp
 * \return
 */
int passenger_delete(Passenger* emp)
{
    int retorno=1;

    if(emp!=NULL)
    {
        free(emp);
        retorno=0;
    }

    return retorno;
}

/**
 * \brief Carga id a un pasajero
 *
 * \param this
 * \param id
 * \return
 */
int passenger_setId(Passenger* this,int id)
{
    int retorno=1;

    if(this!=NULL && id>0 && id<2000)
    {
    	this->id=id;
        retorno=0;
    }
    return retorno;
}
/**
 * \brief Obtiene id de un pasajero
 *
 * \param this
 * \param id
 * \return
 */
int passenger_getId(Passenger* this,int* id)
{
    int retorno=1;

    if(this!=NULL && id!=NULL)
    {
        *id=this->id;
        retorno=0;
    }
    return retorno;
}
/**
 * \brief Carga nombre de un pasajero
 *
 * \param this
 * \param nombre
 * \return
 */
int passenger_setNombre(Passenger* this,char* nombre)
{
    int retorno=1;

    if(this!=NULL && strlen(nombre)>=3 && strlen(nombre)<=20)
    {
        strcpy(this->nombre,nombre);
        retorno=0;
    }
    return retorno;
}
/**
 * \brief Obtiene nombre de un pasajero
 *
 * \param this
 * \param nombre
 * \return
 */
int passenger_getNombre(Passenger* this,char* nombre)
{
    int retorno=1;

    if(this!=NULL && nombre!=NULL)
    {
        strcpy(nombre,this->nombre);
        retorno=0;
    }
    return retorno;
}
/**
 * \brief Carga kilometros recorridos de un pasajero
 *
 * \param this
 * \param kilometrosViaje
 * \return
 */
int passenger_setKilometrosViaje(Passenger* this,int kilometrosViaje)
{
    int retorno=1;

    if(this!=NULL && kilometrosViaje>0)
    {
    	this->kilometrosViaje=kilometrosViaje;
        retorno=0;
    }
    return retorno;
}
/**
 * \brief Obtiene kilometros recorridos de un pasajero
 *
 * \param this
 * \param kilometrosViaje
 * \return
 */
int passenger_getKilometrosViaje(Passenger* this,int* kilometrosViaje)
{
    int retorno=1;

    if(this!=NULL && kilometrosViaje!=NULL)
    {
        *kilometrosViaje=this->kilometrosViaje;
        retorno=0;
    }
    return retorno;
}
/**
 * \brief Carga precio de boleto de un pasajero
 *
 * \param this
 * \param precio
 * \return
 */
int passenger_setPrecio(Passenger* this,int precio)
{
    int retorno=1;

    if(this!=NULL && precio>0 && precio<1000000)
    {
    	this->precio=precio;
        retorno=0;
    }
    return retorno;
}
/**
 * \brief Obtiene precio de boleto un pasajero
 *
 * \param this
 * \param precio
 * \return
 */
int passenger_getPrecio(Passenger* this,int* precio)
{
    int retorno=1;

    if(this!=NULL && precio!=NULL)
    {
        *precio=this->precio;
        retorno=0;
    }
    return retorno;
}


