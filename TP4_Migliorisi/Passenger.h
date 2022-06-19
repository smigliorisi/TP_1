#ifndef passenger_H_INCLUDED
#define passenger_H_INCLUDED
typedef struct
{
    int id;
    char nombre[128];
    int kilometrosViaje;
    int precio;
}Passenger;


int menu (int* opcion);
int mostrarPasajero(Passenger* pasajero);
Passenger* passenger_find(LinkedList* pArrayListPassenger, int id);

Passenger* passenger_new();
Passenger* passenger_newParametros(char* idStr,char* nombreStr,char* kilometrosViajeStr, char* precio);
int passenger_delete(Passenger* emp);

int passenger_setId(Passenger* this,int id);
int passenger_getId(Passenger* this,int* id);

int passenger_setNombre(Passenger* this,char* nombre);
int passenger_getNombre(Passenger* this,char* nombre);

int passenger_setKilometrosViaje(Passenger* this,int kilometrosViaje);
int passenger_getKilometrosViaje(Passenger* this,int* kilometrosViaje);

int passenger_setPrecio(Passenger* this,int precio);
int passenger_getPrecio(Passenger* this,int* precio);

#endif // passenger_H_INCLUDED
