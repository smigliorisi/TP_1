#include "vuelos.h"
#include "LinkedList.h"
#include "typePassenger.h"
#include "validaciones.h"

#ifndef PASSENGER_H_
#define PASSENGER_H_

typedef struct
{
	int id;
	char nombre[50];
	char apellido[50];
	int precio;
	int tipoPasajero;
	char codigoVuelo[8];
	int estadoVuelo;

}Passenger;

Passenger* Passenger_new();
Passenger* Passenger_newParametros(char* idStr,char* nombreStr,char* apellidoStr,char* precioStr,
                                   char* codigoVueloStr,char* tipoPasajeroStr,char* estadoVueloStr, int* pNextId, eTipo tipo[], int tam, eVuelo vuelos[], int tamV);
Passenger* Passenger_newParamBin(int id,char* nombreStr,char* apellidoStr,int precio,
                                   char* codigoVueloStr,char* tipoPasajeroStr,char* estadoVueloStr, int* pNextId, eTipo tipo[], int tam, eVuelo vuelos[], int tamV);
Passenger* Passenger_newAddParam(char* nombreStr,char* apellidoStr,int precio,
                                   char* codigoVueloStr,char* tipoPasajeroStr,char* estadoVueloStr, int* pNextId, eTipo tipo[], int tam, eVuelo vuelos[], int tamV);

void Passenger_delete(Passenger* this);
void Passenger_printOne(Passenger* unPasajero, eTipo tipo[], int tam, eVuelo vuelos[], int tamV);

int Passenger_setId(Passenger* this,int id, int* pNextId);
int Passenger_getId(Passenger* this,int* id);

int Passenger_setNombre(Passenger* this,char* nombre);
int Passenger_getNombre(Passenger* this,char* nombre);

int Passenger_setApellido(Passenger* this,char* apellido);
int Passenger_getApellido(Passenger* this,char* apellido);

int Passenger_setCodigoVuelo(Passenger* this,char* codigoVuelo);
int Passenger_getCodigoVuelo(Passenger* this,char* codigoVuelo);

int Passenger_setTipoPasajero(Passenger* this,char* tipoPasajero, eTipo tipo[], int tam);
int Passenger_getTipoPasajero(Passenger* this,int* tipoPasajero);

int Passenger_setPrecio(Passenger* this, int precio);
int Passenger_getPrecio(Passenger* this,int* precio);

int Passenger_setEstadoVuelo(Passenger* this,char* estadoVuelo, eVuelo vuelos[], int tam);
int Passenger_getEstadoVuelo(Passenger* this,int* estadoVuelo);

int Passenger_buscarId(LinkedList* pArrayListPassenger, int *pIndex, int id);
int Passenger_compareId(void* pElement1, void* pElement2);
int Passenger_compareNombre(void* pElement1, void* pElement2);
int Passenger_compareApellido(void* pElement1, void* pElement2);
int Passenger_comparePrecio(void* pElement1, void* pElement2);
int Passenger_compareCodigoVuelo(void* pElement1, void* pElement2);
int Passenger_compareTipoPasajero(void* pElement1, void* pElement2);



#endif /* PASSENGER_H_ */
