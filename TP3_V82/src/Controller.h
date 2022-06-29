/*
 * Controller.h
 *
 *  Created on: 10 jun. 2022
 *      Author: Sebastian
 */
int controller_loadFromText(char* path , LinkedList* pArrayListPassenger);
int controller_loadFromBinary(char* path , LinkedList* pArrayListPassenger);
int controller_addPassenger(LinkedList* pArrayListPassenger);
int controller_editPassenger(LinkedList* pArrayListPassenger);
int controller_removePassenger(LinkedList* pArrayListPassenger);
int controller_ListPassenger(LinkedList* pArrayListPassenger);
int controller_sortPassenger(LinkedList* pArrayListPassenger);
int controller_saveAsText(char* path , LinkedList* pArrayListPassenger);
int controller_saveAsBinary(char* path , LinkedList* pArrayListPassenger);
int lastId(LinkedList* pArrayListPassenger);
int compareId (void* datoA , void* datoB);
int compareNombre (void* datoA , void* datoB);
int compareApellido (void* datoA , void* datoB);
int comparePrecio (void* datoA , void* datoB);
int compareTipoPasajero (void* datoA , void* datoB);
int compareEstadoVuelo (void* datoA , void* datoB);
int compareCodigoVuelo (void* datoA , void* datoB);
int controller_setPassenger(LinkedList* pArrayListPassenger);
int controller_movePassenger(LinkedList* pArrayListPassenger);
