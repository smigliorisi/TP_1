#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include  <ctype.h>
#include "controller.h"

/** \brief menu de opciones del inicio del programa
 *
 * \return int opcion ingresada
 *
 */
int controller_menuInico()
{
    int opcion;

    printf("\n                          ****** MENU ******\n\n");
    printf("1. Cargar los datos de los pasajeros desde el archivo data.csv (modo texto).\n");
    printf("2. Cargar los datos de los pasajeros desde el archivo data.csv (modo binario).\n");
    printf("3. Alta de pasajero.\n");
    printf("4. Modificar datos de pasajero.\n");
    printf("5. Baja de pasajero.\n");
    printf("6. Listar pasajeros.\n");
    printf("7. Ordenar pasajeros.\n");
    printf("8. Guardar los datos de los pasajeros en el archivo data.csv (modo texto).\n");
    printf("9. Guardar los datos de los pasajeros en el archivo data.csv (modo binario).\n");
    printf("10. Salir\n");
    pidoValidoNumero(&opcion, "Opcion ");

    return opcion;
}

/** \brief permite confirmar si se desea salir
 *
 * \param x char* puntero a el char de confirmacion de salida
 * \return void
 *
 */
void controller_confirmarSalida(char* x, int flagS)
{
    if(x != NULL && flagS < 1)
    {
        printf("Presione 's' para confirmar salida: ");
        fflush(stdin);
        scanf("%c", x);
        *x = tolower(*x);
        printf("Hasta pronto!\n");
    }
    else
    {
        printf("ERROR! No se realizo el guardado de archivo\n");
    }

}

/** \brief Carga los datos de los pasajeros desde el archivo data.csv (modo texto).
 *
 * \param path char* nombre del archivo de texto
 * \param pArrayListPassenger LinkedList* puntero a la lista de pasajeros
 * \return int 1 si pudo leer 0 si no pudo
 *
 */
int controller_loadFromText(char* path, LinkedList* pArrayListPassenger, int* pNextId, eTipo tipos[], int tam, eVuelo vuelos[], int tamV, int* flag)
{
    int todoOk = 0;
    if(path != NULL && pArrayListPassenger != NULL && *flag == 1)
    {
        FILE* f = fopen(path, "r");

        if(f == NULL)
        {
            printf("No se pudo abrir el archivo");
            exit(1);
        }
        else
        {
            parser_PassengerFromText(f, pArrayListPassenger, pNextId, tipos, tam, vuelos, tamV);
            printf("Lista de pasajeros cargada con exito!\n");
        }
        fclose(f);
        *flag = 0;
        todoOk = 1;

    }
    else
    {
    	printf("ERROR!! La lista de pasajeros ya fue cargada!\n");
    }
    return todoOk;
}

/** \brief Carga los datos de los pasajeros desde el archivo data.bin (modo binario).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path, LinkedList* pArrayListPassenger, int* pNextId, eTipo tipos[], int tam, eVuelo vuelos[], int tamV, int* flag)
{
    int todoOk = 0;
    if(path != NULL && pArrayListPassenger != NULL && *flag == 1)
    {
        FILE* f = fopen(path, "rb");

        if(f == NULL)
        {
            printf("No se pudo abrir el archivo");
            exit(1);
        }
        else
        {
            parser_PassengerFromBinary(f, pArrayListPassenger, pNextId, tipos, tam, vuelos, tamV);
            printf("Lista de pasajeros cargada con exito!\n");
        }
        fclose(f);
        *flag = 0;
        todoOk = 1;
    }
    else
        {
        	printf("ERROR!! La lista de pasajeros ya fue cargada!\n");
        }
    return todoOk;
}

/** \brief permite levantar de un texto el ultimo id utilizado
 *
 * \param path char*
 * \param pNextId int*
 * \return int
 *
 */
int controller_loadTextId(char* path, int* pNextId)
{
    int todoOk = 0;
    int proximoId = 0;
    if(path != NULL)
    {
        FILE* f = fopen(path, "r");

        if(f == NULL)
        {
            printf("No se pudo abrir el archivo");
            exit(1);
        }
        else
        {
            fscanf(f, "%d", &proximoId);
            *pNextId = proximoId;
            printf("El proximoId es: %d\n", proximoId);
        }
        fclose(f);
        todoOk = 1;
    }
    return todoOk;
}

/** \brief Alta de pasajero
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_addPassenger(LinkedList* pArrayListPassenger, int* pNextId, eTipo tipos[], int tam, eVuelo vuelos[], int tamV, int flag)
{
    int todoOk = 1;
    char buffer[4][50];
    int tipoPasajero;
    int precio;
    int ok;
    Passenger* unPasajero = NULL;

    if(pArrayListPassenger != NULL && pNextId != NULL && tipos != NULL && vuelos != NULL && tam > 0 && tamV > 0 && flag == 0)
    {

        pidoValidoLetras(buffer[0], 50, "Nombre ");

        pidoValidoLetras(buffer[1], 50, "Apellido");


        pidoValidoNumero(&precio, "Precio");

        listarTipos(tipos, tam);
        pidoValidoNumero(&tipoPasajero, "Tipo de pasajero");
        while(!validarTipo(tipos, tam, tipoPasajero))
        {
            printf("Ingreso Invalido Reintente.\n");
            listarTipos(tipos, tam);
            pidoValidoNumero(&tipoPasajero, "Tipo de pasajero");
        }
        cargarDescripcionTipo(tipos, tam, tipoPasajero, buffer[2]);

        ok = menuVuelos(vuelos, tamV, buffer[3]);
        while(!ok)
        {
            ok = menuVuelos(vuelos, tamV, buffer[3]);
        }
        cargarEstadoVuelo(vuelos, tamV, buffer[3], buffer[4]);
        fflush(stdin);
        unPasajero = Passenger_newAddParam(buffer[0], buffer[1],precio, buffer[3],
                                           buffer[2], buffer[4], pNextId, tipos, tam, vuelos, tamV);
        if( unPasajero != NULL)
        {
            todoOk = ll_add(pArrayListPassenger, unPasajero);
            printf("Pasajero cargado con exito!\n");
        }
    }
    else
    {
    	printf("Primero debe cargar los pasajeros de la base de datos\n");
	}
    return todoOk;
}
/** \brief menu de opciones para editar pasajero
 *
 * \return int
 *
 */
int controller_menuEditPassenger()
{
    int opcion;

    printf("\n   *** Seleccione campo a modificar ***\n\n");
    printf("1. Nombre.\n");
    printf("2. Apellido.\n");
    printf("3. Precio.\n");
    printf("4. Tipo de Pasajero.\n");
    printf("5. Codigo de vuelo.\n");
    printf("6. Salir\n");
    pidoValidoNumero(&opcion, "Opcion ");

    return opcion;
}
/** \brief Modificar datos de pasajero
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_editPassenger(LinkedList* pArrayListPassenger, eTipo tipos[], int tam, eVuelo vuelos[], int tamV, int flag)
{
    int todoOk = 0;
    int indice;
    int id;
    char buffer[50];
    int precio;
    int tipoPasajero;
    int ok;
    char estadoBuf[50];
    Passenger* auxPasajero = NULL;

    if(pArrayListPassenger != NULL && tipos != NULL && vuelos != NULL && tam > 0 && tamV > 0 && flag == 0)
    {
        controller_ListPassenger(pArrayListPassenger, tipos, tam, vuelos, tamV, flag);
        pidoValidoNumero(&id, "Id ");
        if(!Passenger_buscarId(pArrayListPassenger, &indice, id))
        {
            printf("No existe un Pasajero con ese Id en el sistema.\n");
        }
        else
        {
            auxPasajero = (ll_get(pArrayListPassenger, indice));
            if(auxPasajero != NULL)
            {
                printf("********PASAJERO A MODIFICAR********\n\n");
                printf(" ID                    NOMBRE                  APELLIDO            PRECIO           CODIGO DE VUELO             TIPO DE PASAJERO         ESTADO DEL VUELO\n");
                Passenger_printOne(auxPasajero, tipos, tam, vuelos, tamV);
                switch(controller_menuEditPassenger())
                {
                case 1:
                    if(pidoValidoLetras(buffer, 50, "Nuevo Nombre "))
                    {
                        Passenger_setNombre(auxPasajero, buffer);
                        printf("Nombre modificado con exito!\n");
                    }
                    break;
                case 2:
                    if(pidoValidoLetras(buffer, 50, "Nuevo Apellido "))
                    {
                        Passenger_setApellido(auxPasajero, buffer);
                        printf("Apellido modificado con exito!\n");
                    }
                    break;
                case 3:
                    if(pidoValidoNumero(&precio, "nuevo precio "))
                    {
                        Passenger_setPrecio(auxPasajero, precio);
                        printf("Precio modificado con exito!\n");
                    }
                    break;
                case 4:
                    listarTipos(tipos, tam);
                    pidoValidoNumero(&tipoPasajero, "Nuevo Tipo de pasajero");
                    while(!validarTipo(tipos, tam, tipoPasajero))
                    {
                        printf("Ingreso Invalido Reintente.\n");
                        listarTipos(tipos, tam);
                        pidoValidoNumero(&tipoPasajero, "Nuevo Tipo de pasajero");
                    }
                    cargarDescripcionTipo(tipos, tam, tipoPasajero, buffer);
                    Passenger_setTipoPasajero(auxPasajero, buffer, tipos, tam);
                    break;
                case 5:
                    ok = menuVuelos(vuelos, tamV, buffer);
                    while(!ok)
                    {
                        ok = menuVuelos(vuelos, tamV, buffer);
                    }
                    cargarEstadoVuelo(vuelos, tamV, buffer, estadoBuf);
                    Passenger_setCodigoVuelo(auxPasajero, buffer);
                    Passenger_setEstadoVuelo(auxPasajero, estadoBuf, vuelos, tamV);
                    break;
                case 6:

                    break;
                default:
                    printf("Opcion Invalida\n");
                    break;
                }
                todoOk = 1;
            }

        }
        Passenger_printOne(auxPasajero, tipos, tam, vuelos, tamV);
    }
    else
    {
        printf("Primero debe cargar Pasajeros\n");
    }
    return todoOk;
}

/** \brief Baja de pasajero
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_removePassenger(LinkedList* pArrayListPassenger, eTipo tipos[], int tam, eVuelo vuelos[], int tamV, int flag)
{
    int todoOk = 0;
    int indice;
    int id;
    char confirma;
    Passenger* auxPasajero = NULL;
    if(pArrayListPassenger != NULL && tipos != NULL && vuelos != NULL && tam > 0 && tamV > 0 && flag == 0)
    {
        controller_ListPassenger(pArrayListPassenger, tipos, tam, vuelos, tamV, flag);
        pidoValidoNumero(&id, "Id ");
        if(!Passenger_buscarId(pArrayListPassenger, &indice, id))
        {
            printf("No existe un Pasajero con ese Id en el sistema.\n");
        }
        else
        {
            printf("***PASAJERO A DAR DE BAJA***\n");
            Passenger_printOne(ll_get(pArrayListPassenger, indice), tipos, tam, vuelos, tamV);
            printf("Presion 's' para confirmar la baja del pasajero: ");
            fflush(stdin);
            scanf("%c", &confirma);
            if(confirma == 's' || confirma == 'S')
            {
                auxPasajero = ll_pop(pArrayListPassenger, indice);
                if(auxPasajero != NULL)
                {
                    Passenger_delete(auxPasajero);
                    printf("Baja exitosa!\n");
                }
            }
            else
            {
                printf("Baja cancelada por el usuario!\n");
            }
            todoOk = 1;
        }
    }
    else
    {
        printf("Primero debe cargar Pasajeros\n");
    }
    return todoOk;
}

/** \brief Listar pasajeros
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_ListPassenger(LinkedList* pArrayListPassenger, eTipo tipos[], int tam, eVuelo vuelos[], int tamV, int flag)
{
    int todoOk = 0;
    Passenger* unPasajero;
    int len = ll_len(pArrayListPassenger);

    if(pArrayListPassenger != NULL && tipos != NULL && vuelos != NULL && tam > 0 && tamV >0 && flag == 0)
    {
        printf("***************************************************************** LISTADO DE PASAJEROS *****************************************************************\n\n");
        printf(" ID                    NOMBRE                  APELLIDO            PRECIO           CODIGO DE VUELO             TIPO DE PASAJERO         ESTADO DEL VUELO\n");
        printf("----------------------------------------------------------------------------------------------------------------------------------------------------------\n");

        for(int i=0; i < len ; i++)
        {
            unPasajero = (Passenger*) ll_get(pArrayListPassenger, i);
            Passenger_printOne(unPasajero, tipos, tam, vuelos, tamV);
        }
        todoOk = 1;
    }
    else
    {
        printf("Primero debe cargar Pasajeros\n");
    }
    return todoOk;
}
/** \brief menu de opciones de ordenamientos
 *
 * \return int
 *
 */
int controller_menuSorts()
{
    int opcion;

    printf("\n   *** Seleccione Ordenamiento ***\n\n");
    printf("1. Por Nombre.\n");
    printf("2. Por Apellido.\n");
    printf("3. Por Precio.\n");
    printf("4. Por Tipo de Pasajero.\n");
    printf("5. Por Codigo de vuelo.\n");
    printf("6. Por Id.\n");
    pidoValidoNumero(&opcion, "Opcion ");

    return opcion;
}

/** \brief Ordenar pasajeros por diferentes criterios
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_sortPassenger(LinkedList* pArrayListPassenger, int flag)
{
    int todoOk = 0;
    int criterio = -1;
    int ok;

    if(pArrayListPassenger != NULL && flag == 0)
    {
        ok = pidoValidoNumeroRango(&criterio, "criterio de ordenamiento '1' para ascendente '0' para descendente ", 0, 1);
        while(!ok)
        {
            ok = pidoValidoNumeroRango(&criterio, "criterio de ordenamiento '1' para ascendente '0' para descendente ", 0, 1);
        }
        switch(controller_menuSorts())
        {
        case 1:
        	printf("Ordenando por favor espere...\n");
            ll_sort(pArrayListPassenger, Passenger_compareNombre, criterio);
            printf("Listado de pasajeros ordenado con Exito!!\n");
            break;
        case 2:
        	printf("Ordenando por favor espere...\n");
            ll_sort(pArrayListPassenger, Passenger_compareApellido, criterio);
            printf("Listado de pasajeros ordenado con Exito!!\n");
            break;
        case 3:
        	printf("Ordenando por favor espere...\n");
            ll_sort(pArrayListPassenger, Passenger_comparePrecio, criterio);
            printf("Listado de pasajeros ordenado con Exito!!\n");
            break;
        case 4:
        	printf("Ordenando por favor espere...\n");
            ll_sort(pArrayListPassenger, Passenger_compareTipoPasajero, criterio);
            printf("Listado de pasajeros ordenado con Exito!!\n");
            break;
        case 5:
        	printf("Ordenando por favor espere...\n");
            ll_sort(pArrayListPassenger, Passenger_compareCodigoVuelo, criterio);
            printf("Listado de pasajeros ordenado con Exito!!\n");
            break;
        case 6:
        	printf("Ordenando por favor espere...\n");
            ll_sort(pArrayListPassenger, Passenger_compareId, criterio);
            printf("Listado de pasajeros ordenado con Exito!!\n");
            break;
        default:
            printf("Opcion Invalida...");
            break;
        }
        todoOk = 1;
    }
    else
    {
        printf("Primero debe cargar Pasajeros\n");
    }
    return todoOk;
}

/** \brief Guarda los datos de los pasajeros en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path, LinkedList* pArrayListPassenger, eTipo tipos[], int tam, eVuelo vuelos[], int tamV, int* pFlagS)
{
    int todoOk = 0;
    Passenger* auxPass = NULL;
    int id;
    int precio;
    int tipoPasajero;
    char buffer[6][50];

    if(path != NULL && pArrayListPassenger != NULL && tipos != NULL && vuelos != NULL && tam > 0 && tamV > 0)
    {
        FILE* f = fopen(path, "w");

        if(f == NULL)
        {
            printf("No se pudo abrir el archivo");
            exit(1);
        }
        else
        {
        	printf("Guardando por favor espere...\n");
        	ll_sort(pArrayListPassenger, Passenger_compareId, 1);
        	fprintf(f,"%s,%s,%s,%s,%s,%s,%s\n", "id", "name", "lastname", "price", "flycode", "typePassenger", "statusFlight");
        	for(int i=0; i<ll_len(pArrayListPassenger); i++)
            {
                auxPass = ll_get(pArrayListPassenger, i);
                if(Passenger_getId(auxPass, &id)
                        && Passenger_getNombre(auxPass,buffer[1])
                        && Passenger_getApellido(auxPass, buffer[2])
                        && Passenger_getPrecio(auxPass, &precio)
                        && Passenger_getTipoPasajero(auxPass, &tipoPasajero)
                        && Passenger_getCodigoVuelo(auxPass, buffer[4]))
                {
                	sprintf(buffer[0], "%d", id);
                	sprintf(buffer[3], "%d", precio);
                    cargarDescripcionTipo(tipos, tam, tipoPasajero, buffer[5]);
                    cargarEstadoVuelo(vuelos, tamV, buffer[4], buffer[6]);

                    fprintf(f,"%s,%s,%s,%s,%s,%s,%s\n", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5], buffer[6]);
                    todoOk = 1;
                }
                else
                {
                    printf("ERROR No se pudo escribir el archivo!\n");
                }
            }
            if(todoOk)
            {
                printf("Guardado con exito!\n");
                *pFlagS = 0;
            }
        }
        fclose(f);
    }
    return todoOk;
}

/** \brief Guarda los datos de los pasajeros en el archivo datab.bin (modo binario).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path, LinkedList* pArrayListPassenger, int* pFlagS)
{
    int todoOk = 0;
    Passenger* auxPass = NULL;
    int id;
    int precio;
    int tipoPasajero;
    char buffer[4][50];

    if(path != NULL && pArrayListPassenger != NULL)
    {
        FILE* f = fopen(path, "wb");

        if(f == NULL)
        {
            printf("No se pudo abrir el archivo");
            exit(1);
        }
        else
        {
        	printf("Guardando por favor espere...\n");
        	ll_sort(pArrayListPassenger, Passenger_compareId, 1);
        	fprintf(f,"%s,%s,%s,%s,%s,%s,%s\n", "id", "name", "lastname", "price", "flycode", "typePassenger", "statusFlight");
            for(int i=0; i<ll_len(pArrayListPassenger); i++)
            {
                auxPass = ll_get(pArrayListPassenger, i);
                if(Passenger_getId(auxPass, &id)
                        && Passenger_getNombre(auxPass,buffer[0])
                        && Passenger_getApellido(auxPass, buffer[1])
                        && Passenger_getPrecio(auxPass, &precio)
                        && Passenger_getTipoPasajero(auxPass, &tipoPasajero)
                        && Passenger_getCodigoVuelo(auxPass, buffer[2]))
                {
                    fwrite(auxPass, sizeof(Passenger), 1, f);
                    todoOk = 1;
                }
                else
                {
                    printf("ERROR No se pudo escribir el archivo!\n");
                }
            }
            if(todoOk)
            {
                printf("Guardado con exito!\n");
                *pFlagS = 0;
            }
        }
        fclose(f);
    }
    return todoOk;
}

/** \brief permite guardar en un texto el ultimo id utilizado
 *
 * \param path char*
 * \param pNextId int
 * \return int
 *
 */
int controller_SaveTextId(char* path, int pNextId)
{
    int todoOk = 0;
    if(path != NULL)
    {
        FILE* f = fopen(path, "w");

        if(f == NULL)
        {
            printf("No se pudo abrir el archivo");
            exit(1);
        }
        else
        {
            fprintf(f, "%d", pNextId);
        }
        fclose(f);
        todoOk = 1;
    }
    return todoOk;
}
