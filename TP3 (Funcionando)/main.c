#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Passenger.h"

#define TAM 3
#define TAMV 8

/****************************************************
    Menu:
     1. Cargar los datos de los pasajeros desde el archivo data.csv (modo texto).
     2. Cargar los datos de los pasajeros desde el archivo data.csv (modo binario).
     3. Alta de pasajero
     4. Modificar datos de pasajero
     5. Baja de pasajero
     6. Listar pasajeros
     7. Ordenar pasajeros
     8. Guardar los datos de los pasajeros en el archivo data.csv (modo texto).
     9. Guardar los datos de los pasajeros en el archivo data.csv (modo binario).
    10. Salir
*****************************************************/



int main()
{
    setbuf(stdout, NULL);
    int proximoId = 1;
    char salir = 'n';
    int flag_cargaArchivo = 1;
    int flag_guardadoArchivo = 1;
    eTipo tipos[TAM] =
    {
        {1, "EconomyClass"},
        {2, "ExecutiveClass"},
        {3, "FirstClass"}
    };
    eVuelo vuelos[TAMV] =
    {
        {"BA2491A", 1, "Aterrizado"},
        {"IB0800A", 1, "Aterrizado"},
        {"MM0987B", 3, "En Horario"},
        {"TU6789B", 1, "Aterrizado"},
        {"GU2345F", 4, "En Vuelo"},
        {"HY4567D", 2, "Demorado"},
        {"FR5678G", 3, "En Horario"},
        {"BR3456J", 2, "Demorado"}
    };

    LinkedList* listaPasajeros = ll_newLinkedList();

    do
    {
        switch(controller_menuInico())
        {
        case 1:
            controller_loadFromText("data.csv", listaPasajeros, &proximoId, tipos, TAM, vuelos, TAMV, &flag_cargaArchivo);
            system("pause");
            break;
        case 2:
            controller_loadFromBinary("data.bin", listaPasajeros, &proximoId, tipos, TAM, vuelos, TAMV, &flag_cargaArchivo);
            system("pause");
            break;
        case 3:
            controller_addPassenger(listaPasajeros, &proximoId, tipos, TAM, vuelos, TAMV, flag_cargaArchivo);
            system("pause");
            break;
        case 4:
            controller_editPassenger(listaPasajeros, tipos, TAM, vuelos, TAMV, flag_cargaArchivo);
            system("pause");
            break;
        case 5:
            controller_removePassenger(listaPasajeros, tipos, TAM, vuelos, TAMV, flag_cargaArchivo);
            system("pause");
            break;
        case 6:
            controller_ListPassenger(listaPasajeros, tipos, TAM, vuelos, TAMV, flag_cargaArchivo);
            system("pause");
            break;
        case 7:
            controller_sortPassenger(listaPasajeros, flag_cargaArchivo);
            system("pause");
            break;
        case 8:
            controller_saveAsText("data.csv", listaPasajeros, tipos, TAM, vuelos, TAMV, &flag_guardadoArchivo);
            system("pause");
            break;
        case 9:
            controller_saveAsBinary("data.bin", listaPasajeros, &flag_guardadoArchivo);
            system("pause");
            break;
        case 10:
            controller_confirmarSalida(&salir, flag_guardadoArchivo);
            system("pause");
            break;
        default:
            printf("Ingreso Invalido!\n");
            break;
        }
        //system("pause");
        //system("cls");
    }while(salir != 's');

    ll_deleteLinkedList(listaPasajeros);

    return EXIT_SUCCESS;
}

