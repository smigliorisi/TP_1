#include "LinkedList.h"
#include "Passenger.h"
#include "vuelos.h"
#include "tipoPasajero.h"
#include "parser.h"
#include "validar.h"


int controller_menuInico();
void controller_confirmarSalida(char* x, int flagS);
int controller_loadFromText(char* path , LinkedList* pArrayListPassenger, int*pNextId, eTipo tipos[], int tam, eVuelo vuelos[], int tamV, int* flag);
int controller_loadFromBinary(char* path , LinkedList* pArrayListPassenger, int* pNextId, eTipo tipos[], int tam, eVuelo vuelos[], int tamV, int* flag);
int controller_loadTextId(char* path, int* pNextId);
int controller_addPassenger(LinkedList* pArrayListPassenger, int* pNextId, eTipo tipos[], int tam, eVuelo vuelos[], int tamV, int flag);
int controller_menuEditPassenger();
int controller_editPassenger(LinkedList* pArrayListPassenger, eTipo tipos[], int tam, eVuelo vuelos[], int tamV, int flag);
int controller_removePassenger(LinkedList* pArrayListPassenger, eTipo tipos[], int tam, eVuelo vuelos[], int tamV, int flag);
int controller_ListPassenger(LinkedList* pArrayListPassenger, eTipo tipos[], int tam, eVuelo vuelos[], int tamV, int flag);
int controller_sortPassenger(LinkedList* pArrayListPassenger, int flag);
int controller_saveAsText(char* path, LinkedList* pArrayListPassenger, eTipo tipos[], int tam, eVuelo vuelos[], int tamV, int* pFlagS);
int controller_saveAsBinary(char* path, LinkedList* pArrayListPassenger, int* pFlagS);
int controller_SaveTextId(char* path, int pNextId);


