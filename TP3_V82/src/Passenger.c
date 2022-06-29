/*
 * Passenger.c
 *
 *  Created on: 10 jun. 2022
 *      Author: Sebastian
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Passenger.h"
#include "UTN_SebaLib.h"

/*****
 * \brief Muestra un menu de opciones
 *
 * \param option opcion seleccionada
 * \return devuelve el numero entero valido ingresado
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

int mostrarPasajeros(Passenger* pasajero)
{
    int retorno=-1;

    if(pasajero!=NULL)
    {
        printf(" %d    %20s  %20s  %f   %d    %7s    %d\n", pasajero->id, pasajero->nombre, pasajero->apellido, pasajero->precio, pasajero->tipoPasajero, pasajero->codigoVuelo, pasajero->statusFlight);
        retorno=0;
    }
    return retorno;
}


Passenger* Passenger_find(LinkedList* pArrayListPassenger, int id)
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


Passenger* Passenger_new()
{
    Passenger* newPassenger;
    newPassenger= (Passenger*) malloc(sizeof(Passenger));

    if(newPassenger!=NULL)
    {
            newPassenger->id =0;
            strcpy(newPassenger->nombre, "");
            strcpy(newPassenger->apellido, "");
            newPassenger->precio=0;
            newPassenger->tipoPasajero=0;
            strcpy(newPassenger->codigoVuelo, "");
            newPassenger->statusFlight=0;
    }

    return newPassenger;
}
Passenger* Passenger_newParametros(char* idStr,char* nombreStr,char* apellidoStr, char* precioStr, char* tipoPasajeroStr, char* codigoVueloStr, char* statusFlightStr)
{
    int id;
    int tipoPasajero;
    float precio;
    int statusFlight;
    Passenger* newPassenger;
    newPassenger = Passenger_new();


    if(newPassenger!=NULL)
    {
        id = atoi(idStr);
        tipoPasajero = atoi(tipoPasajeroStr);
        precio = atof(precioStr);
        statusFlight = atoi(statusFlightStr);

        if(    Passenger_setId(newPassenger,id)
            || Passenger_setNombre(newPassenger, nombreStr)
			|| Passenger_setApellido(newPassenger, apellidoStr)
            || Passenger_setTipoPasajero(newPassenger, tipoPasajero)
			|| Passenger_setPrecio(newPassenger, precio)
            || Passenger_setCodigoVuelo(newPassenger, codigoVueloStr)
			|| Passenger_setEstadoVuelo(newPassenger, statusFlight)
           )
        {
            free(newPassenger);
            newPassenger=NULL;
        }
    }

    return newPassenger;
}

int Passenger_delete(Passenger* pasajero)
{
    int retorno=1;

    if(pasajero!=NULL)
    {
        free(pasajero);
        retorno=0;
    }

    return retorno;
}

int Passenger_setId(Passenger* this,int id)
{
    int retorno=1;

    if(this!=NULL && id>0 && id<1000)
    {
    	this->id=id;
        retorno=0;
    }
    return retorno;
}
int Passenger_getId(Passenger* this,int* id)
{
    int retorno=1;

    if(this!=NULL && id!=NULL)
    {
        *id=this->id;
        retorno=0;
    }
    return retorno;
}

int Passenger_setNombre(Passenger* this,char* nombre)
{
    int retorno=1;

    if(this!=NULL && strlen(nombre)>=3 && strlen(nombre)<=50)
    {
        strcpy(this->nombre,nombre);
        retorno=0;
    }
    return retorno;
}
int Passenger_getNombre(Passenger* this,char* nombre)
{
    int retorno=1;

    if(this!=NULL && nombre!=NULL)
    {
        strcpy(nombre,this->nombre);
        retorno=0;
    }
    return retorno;
}

int Passenger_setApellido(Passenger* this,char* apellido)
{
    int retorno=1;

    if(this!=NULL && strlen(apellido)>=3 && strlen(apellido)<=20)
    {
        strcpy(this->apellido,apellido);
        retorno=0;
    }
    return retorno;
}
int Passenger_getApellido(Passenger* this,char* apellido)
{
    int retorno=1;

    if(this!=NULL && apellido!=NULL)
    {
        strcpy(apellido,this->apellido);
        retorno=0;
    }
    return retorno;
}

int Passenger_setTipoPasajero(Passenger* this,int tipoPasajero)
{
    int retorno=1;

    if(this!=NULL && tipoPasajero>0)
    {
    	this->tipoPasajero=tipoPasajero;
        retorno=0;
    }
    return retorno;
}
int Passenger_getTipoPasajero(Passenger* this,int* tipoPasajero)
{
    int retorno=1;

    if(this!=NULL && tipoPasajero!=NULL)
    {
        *tipoPasajero=this->tipoPasajero;
        retorno=0;
    }
    return retorno;
}

int Passenger_setCodigoVuelo(Passenger* this,char* codigoVuelo)
{
    int retorno=1;

    if(this!=NULL && strlen(codigoVuelo)>=3 && strlen(codigoVuelo)<=20)
    {
        strcpy(this->codigoVuelo,codigoVuelo);
        retorno=0;
    }
    return retorno;
}

int Passenger_getCodigoVuelo(Passenger* this,char* codigoVuelo)
{
    int retorno=1;

    if(this!=NULL && codigoVuelo!=NULL)
    {
        strcpy(codigoVuelo,this->codigoVuelo);
        retorno=0;
    }
    return retorno;
}


int Passenger_setPrecio(Passenger* this,float precio)
{
    int retorno=1;

    if(this!=NULL && precio>0 && precio<10000000)
    {
    	this->precio=precio;
        retorno=0;
    }
    return retorno;
}

int Passenger_getPrecio(Passenger* this,float* precio)
{
    int retorno=1;

    if(this!=NULL && precio!=NULL)
    {
        *precio=this->precio;
        retorno=0;
    }
    return retorno;
}

int Passenger_setEstadoVuelo(Passenger* this,int statusFlight)
{
    int retorno=1;

    if(this!=NULL && statusFlight>0)
    {
    	this->statusFlight=statusFlight;
        retorno=0;
    }
    return retorno;
}
int Passenger_getEstadoVuelo(Passenger* this,int* statusFlight)
{
    int retorno=1;

    if(this!=NULL && statusFlight!=NULL)
    {
        *statusFlight=this->statusFlight;
        retorno=0;
    }
    return retorno;
}

