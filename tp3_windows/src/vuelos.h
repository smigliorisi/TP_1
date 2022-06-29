#ifndef VUELOS_H_
#define VUELOS_H_

typedef struct
{
    char codigoVuelo[10];
    int estadoVuelo;
    char descEstado[10];
}eVuelo;


int cargarIntEstadoVuelo(eVuelo vuelo[], int tam, char* desc);
int cargarDescripcionEstadoVuelo(eVuelo vuelo[], int tam, int estadoVuelo, char desc[]);
int validarEstado(eVuelo vuelo[], int tam, int id);
int listarVuelos(eVuelo vuelos[], int tam);
int menuVuelos(eVuelo vuelos[], int tam, char* codigoVuelo);
int cargarEstadoVuelo(eVuelo vuelo[], int tam, char* codigoVuelo, char* estadoVuelo);

#endif /* VUELOS_H_ */
