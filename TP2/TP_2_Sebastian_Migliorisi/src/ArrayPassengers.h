/*
 * ArrayPassengers.h
 *
 *  Created on: 4 may. 2022
 *      Author: Sebastian Migliorisi
 */

#ifndef ARRAYPASSENGERS_H_
#define ARRAYPASSENGERS_H_

struct {
	int id;
	char name[51];
	char lastName[51];
	float price;
	char flyCode[10];
	int typePassenger;
	int statusFlight;
	int isEmpty;
} typedef ePassenger;



//void hardCodearPasajeros(ePassenger vec[], int cant);

int initPassengers(ePassenger* list, int len);
int printPassengers(ePassenger* list, int length);
int printPassengersXEstCod(ePassenger* list,int length, int opcion);
int addPassenger(ePassenger* list, int len, int id, char name[],char lastName[],float price,int typePassenger, char flyCode[]);
int findEmpty (ePassenger vec[], int tam);
int findPassengerById(ePassenger* list, int len,int id);
int removePassenger(ePassenger* list, int len, int id);
int sortPassengers(ePassenger* list, int len, int order);
int sortPassengersXEstCod(ePassenger* list, int len, int order);
int modifyPassenger (ePassenger* list, int len, int id);
int checkEmpty(ePassenger* list, int len);
void informarPasajeros(ePassenger* list, int len);
void listarPasajerosXApYTip(ePassenger* list, int len);
void listarPasajerosXCodpYEstadoActiv(ePassenger* list, int len);
void listarTotalyPromedioPasajes(ePassenger* list, int len);
int menu (int* op);

#endif /* ARRAYPASSENGERS_H_ */
