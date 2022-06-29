#include "Passenger.h"
#include  <ctype.h>
#include  <stdio.h>
#include  <string.h>
#include  <stdlib.h>


// constructores
Passenger* Passenger_new()
{
    Passenger* nuevoPasajero = (Passenger*) malloc(sizeof(Passenger));
    if(nuevoPasajero != NULL)
    {
        nuevoPasajero->id = 0;
        strcpy(nuevoPasajero->nombre, "");
        strcpy(nuevoPasajero->apellido, "");
        nuevoPasajero->precio = 0;
        nuevoPasajero->tipoPasajero = 0;
        strcpy(nuevoPasajero->codigoVuelo, "");
        nuevoPasajero->estadoVuelo = 0;
    }
    return nuevoPasajero;
}

Passenger* Passenger_newParametros(char* idStr,char* nombreStr,char* apellidoStr,char* precioStr,
                                   char* codigoVueloStr,char* tipoPasajeroStr,char* estadoVueloStr, int* pNextId, eTipo tipo[], int tam, eVuelo vuelos[], int tamV)
{
    Passenger* nuevoPasajero = Passenger_new();
    int id;
    int precio;

    validaConvierteChar_Int(idStr, &id);
    validaConvierteChar_Int(precioStr, &precio);

    if(pNextId != NULL)
    {
        if(!(Passenger_setId(nuevoPasajero, id, pNextId) &&
                Passenger_setNombre(nuevoPasajero, nombreStr) &&
                Passenger_setApellido(nuevoPasajero, apellidoStr) &&
                Passenger_setCodigoVuelo(nuevoPasajero, codigoVueloStr) &&
                Passenger_setTipoPasajero(nuevoPasajero, tipoPasajeroStr, tipo, tam) &&
                Passenger_setPrecio(nuevoPasajero, precio) &&
                Passenger_setEstadoVuelo(nuevoPasajero, estadoVueloStr, vuelos, tam)))
        {
            free(nuevoPasajero);
            nuevoPasajero = NULL;
        }
    }
    return nuevoPasajero;
}

Passenger* Passenger_newAddParam(char* nombreStr,char* apellidoStr,int precio,
                                 char* codigoVueloStr,char* tipoPasajeroStr,char* estadoVueloStr, int* pNextId, eTipo tipo[], int tam, eVuelo vuelos[], int tamV)
{
    Passenger* nuevoPasajero = Passenger_new();
    int id;
    id = *pNextId;

    if(pNextId != NULL)
    {
    	if(!(Passenger_setId(nuevoPasajero, id, pNextId) &&
                Passenger_setNombre(nuevoPasajero, nombreStr) &&
                Passenger_setApellido(nuevoPasajero, apellidoStr) &&
                Passenger_setCodigoVuelo(nuevoPasajero, codigoVueloStr) &&
                Passenger_setTipoPasajero(nuevoPasajero, tipoPasajeroStr, tipo, tam) &&
                Passenger_setPrecio(nuevoPasajero, precio) &&
                Passenger_setEstadoVuelo(nuevoPasajero, estadoVueloStr, vuelos, tam)))
        {
            free(nuevoPasajero);
            nuevoPasajero = NULL;
        }
    }
    return nuevoPasajero;
}

Passenger* Passenger_newParamBin(int id,char* nombreStr,char* apellidoStr,int precio,
                                 char* codigoVueloStr,char* tipoPasajeroStr,char* estadoVueloStr, int* pNextId, eTipo tipo[], int tam, eVuelo vuelos[], int tamV)
{
    Passenger* nuevoPasajero = Passenger_new();


    if(pNextId != NULL)
    {
        if(!(Passenger_setId(nuevoPasajero, id, pNextId) &&
                Passenger_setNombre(nuevoPasajero, nombreStr) &&
                Passenger_setApellido(nuevoPasajero, apellidoStr) &&
                Passenger_setCodigoVuelo(nuevoPasajero, codigoVueloStr) &&
                Passenger_setTipoPasajero(nuevoPasajero, tipoPasajeroStr, tipo, tam) &&
                Passenger_setPrecio(nuevoPasajero, precio) &&
                Passenger_setEstadoVuelo(nuevoPasajero, estadoVueloStr, vuelos, tamV)))
        {
            free(nuevoPasajero);
            nuevoPasajero = NULL;
        }
    }
    return nuevoPasajero;
}

//destructor

void Passenger_delete(Passenger* this)
{
    free(this);
}

//Mostrar
void Passenger_printOne(Passenger* unPasajero, eTipo tipo[], int tam, eVuelo vuelos[], int tamV)
{
    int id = 0;
    int precio = 0;
    int tipoP = 0;
    char buffer[6][50];

    Passenger_getId(unPasajero, &id);
    sprintf(buffer[0], "%d", id);

    Passenger_getNombre(unPasajero, buffer[1]);

    Passenger_getApellido(unPasajero, buffer[2]);

    Passenger_getPrecio(unPasajero, &precio);
    sprintf(buffer[3], "%d", precio);

    Passenger_getTipoPasajero(unPasajero, &tipoP);

    Passenger_getCodigoVuelo(unPasajero, buffer[4]);

    cargarDescripcionTipo(tipo, tam, tipoP, buffer[5]);
    cargarEstadoVuelo(vuelos, tamV, buffer[4], buffer[6]);

    printf("%4s      %20s      %20s      %10s      %20s      %20s      %20s\n",
    	   buffer[0],
           buffer[1],
           buffer[2],
		   buffer[3],
           buffer[4],
           buffer[5],
           buffer[6]);
}

// Setters - Getters
int Passenger_setId(Passenger* this,int id, int* pNextId)
{
    int todoOk = 0;

    if(this != NULL && id > 0)
    {
        this->id = id;
        (*pNextId) = id+1;
        todoOk = 1;
    }
    return todoOk;
}
int Passenger_getId(Passenger* this, int* id)
{
    int todoOk = 0;

    if(this != NULL && id != NULL)
    {

        *id = this->id;
        todoOk = 1;
    }
    return todoOk;
}

int Passenger_setNombre(Passenger* this,char* nombre)
{
    int todoOk = 0;

    if(this != NULL && nombre != NULL && strlen(nombre) < 50 && strlen(nombre) > 0)
    {
        if(validarLetras(nombre) != 0 || stricmp(nombre, "\n") != 0)
        {
            strcpy(this->nombre, nombre);
            strlwr(this->nombre);
            this->nombre[0] = toupper(this->nombre[0]);
            todoOk = 1;
        }

    }
    return todoOk;
}

int Passenger_getNombre(Passenger* this,char* nombre)
{
    int todoOk = 0;

    if(this != NULL && nombre != NULL)
    {
        strcpy(nombre, this->nombre);
        todoOk = 1;
    }
    return todoOk;
}

int Passenger_setApellido(Passenger* this,char* apellido)
{
    int todoOk = 0;

    if(this != NULL && apellido != NULL && strlen(apellido) < 50 && strlen(apellido) > 0)
    {
        if(validarLetras(apellido) != 0 || stricmp(apellido, "\n") != 0)
        {
            strcpy(this->apellido, apellido);
            strlwr(this->apellido);
            this->apellido[0] = toupper(this->apellido[0]);
            todoOk = 1;
        }
    }
    return todoOk;
}
int Passenger_getApellido(Passenger* this,char* apellido)
{
    int todoOk = 0;

    if(this != NULL && apellido != NULL)
    {
        strcpy(apellido, this->apellido);
        todoOk = 1;
    }
    return todoOk;
}

int Passenger_setCodigoVuelo(Passenger* unPasajero,char* codigoVuelo)
{
    int todoOk = 0;

    if(unPasajero != NULL && codigoVuelo != NULL && strlen(codigoVuelo) <= 8 && strlen(codigoVuelo) > 4)
    {
        strcpy(unPasajero->codigoVuelo, codigoVuelo);
        todoOk = 1;
    }
    return todoOk;
}
int Passenger_getCodigoVuelo(Passenger* unPasajero,char* codigoVuelo)
{
    int todoOk = 0;

    if(unPasajero != NULL && codigoVuelo != NULL)
    {
        strcpy(codigoVuelo, unPasajero->codigoVuelo);
        todoOk = 1;
    }
    return todoOk;
}

int Passenger_setTipoPasajero(Passenger* this,char* tipoPasajero, eTipo tipo[], int tam)
{
    int todoOk = 0;

    if(this != NULL && tipoPasajero != NULL && strlen(tipoPasajero) < 20 && strlen(tipoPasajero) > 2)
    {
        this->tipoPasajero = cargarIntTipo(tipo, tam, tipoPasajero);
        todoOk = 1;
    }
    return todoOk;
}
int Passenger_getTipoPasajero(Passenger* this, int* tipoPasajero)
{
    int todoOk = 0;

    if(this != NULL)
    {
        *tipoPasajero = this->tipoPasajero;
        todoOk = 1;
    }
    return todoOk;
}
int Passenger_setPrecio(Passenger* unPasajero, int precio)
{
    int todoOk = 0;

    if(unPasajero != NULL && precio > 0)
    {
        unPasajero->precio = precio;
        todoOk = 1;
    }
    return todoOk;
}
int Passenger_getPrecio(Passenger* unPasajero,int* precio)
{
    int todoOk = 0;

    if(unPasajero != NULL)
    {
        *precio = unPasajero->precio;
        todoOk = 1;
    }
    return todoOk;
}

int Passenger_setEstadoVuelo(Passenger* this,char* estadoVuelo, eVuelo vuelos[], int tam)
{
    int todoOk = 0;

    if(this != NULL && estadoVuelo != NULL && strlen(estadoVuelo) < 20 && strlen(estadoVuelo) > 2)
    {
        this->estadoVuelo = cargarIntEstadoVuelo(vuelos, tam, estadoVuelo);
        todoOk = 1;
    }
    return todoOk;
}
int Passenger_getEstadoVuelo(Passenger* this,int* estadoVuelo)
{
    int todoOk = 0;

    if(this != NULL)
    {
        *estadoVuelo = this->estadoVuelo;
        todoOk = 1;
    }
    return todoOk;
}

//Otras funciones

int Passenger_buscarId(LinkedList* pArrayListPassenger, int *pIndex, int id)
{
    int todoOk = 0;
    int idAux;
    Passenger *auxPasajero = NULL;

    if(pArrayListPassenger != NULL && pIndex >= 0 && id >= 0)
    {
        for(int i=0; i < ll_len(pArrayListPassenger); i++)
        {
            auxPasajero = ll_get(pArrayListPassenger, i);
            if(auxPasajero != NULL)
            {
                Passenger_getId(auxPasajero, &idAux);
                if(id == idAux)
                {
                    *pIndex = i;
                    todoOk = 1;
                }
            }
        }
    }
    return todoOk;
}

int Passenger_compareId(void* pElement1, void* pElement2)
{
    int todoOk = 0;
    int id1;
    int id2;

    if(pElement1 != NULL && pElement2 != NULL)
    {
        Passenger_getId(pElement1, &id1);
        Passenger_getId(pElement2, &id2);
        if(id1 > id2)
        {
            todoOk = 1;
        }
        else
        {
            if(id1 < id2)
            {
                todoOk = -1;
            }
        }

    }
    return todoOk;
}

int Passenger_compareNombre(void* pElement1, void* pElement2)
{
    int todoOk = 0;
    char nombre1[50];
    char nombre2[50];

    if(pElement1 != NULL && pElement2 != NULL)
    {
        Passenger_getNombre(pElement1, nombre1);
        Passenger_getNombre(pElement2, nombre2);
        if(stricmp(nombre1, nombre2) > 0)
        {
            todoOk = 1;
        }
        else
        {
            if(stricmp(nombre1, nombre2) < 0)
            {
                todoOk = -1;
            }
        }

    }
    return todoOk;
}

int Passenger_compareApellido(void* pElement1, void* pElement2)
{
    int todoOk = 0;
    char apellido1[50];
    char apellido2[50];

    if(pElement1 != NULL && pElement2 != NULL)
    {
        Passenger_getApellido(pElement1, apellido1);
        Passenger_getApellido(pElement2, apellido2);
        if(stricmp(apellido1, apellido2) > 0)
        {
            todoOk = 1;
        }
        else
        {
            if(stricmp(apellido1, apellido2) < 0)
            {
                todoOk = -1;
            }
        }

    }
    return todoOk;
}

int Passenger_comparePrecio(void* pElement1, void* pElement2)
{
    int todoOk = 0;
    int precio1;
    int precio2;

    if(pElement1 != NULL && pElement2 != NULL)
    {
        Passenger_getPrecio(pElement1, &precio1);
        Passenger_getPrecio(pElement2, &precio2);
        if(precio1 > precio2)
        {
            todoOk = 1;
        }
        else
        {
            if(precio1 < precio2)
            {
                todoOk = -1;
            }
        }

    }
    return todoOk;
}

int Passenger_compareCodigoVuelo(void* pElement1, void* pElement2)
{
    int todoOk = 0;
    char codigo1[50];
    char codigo2[50];

    if(pElement1 != NULL && pElement2 != NULL)
    {
        Passenger_getCodigoVuelo(pElement1, codigo1);
        Passenger_getCodigoVuelo(pElement2, codigo2);
        if(stricmp(codigo1, codigo2) > 0)
        {
            todoOk = 1;
        }
        else
        {
            if(stricmp(codigo1, codigo2) < 0)
            {
                todoOk = -1;
            }
        }

    }
    return todoOk;
}

int Passenger_compareTipoPasajero(void* pElement1, void* pElement2)
{
    int todoOk = 0;
    int tipo1;
    int tipo2;

    if(pElement1 != NULL && pElement2 != NULL)
    {
        Passenger_getTipoPasajero(pElement1, &tipo1);
        Passenger_getTipoPasajero(pElement2, &tipo2);
        if(tipo1 > tipo2)
        {
            todoOk = 1;
        }
        else
        {
            if(tipo1 < tipo2)
            {
                todoOk = -1;
            }
        }

    }
    return todoOk;
}
