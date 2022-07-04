#ifndef TIPOPASAJERO_H_
#define TIPOPASAJERO_H_

typedef struct
{
   int id;
   char descripcion[20];
}eTipo;

int cargarIntTipo(eTipo tipo[], int tam, char* desc);
int cargarDescripcionTipo(eTipo tipo[], int tam, int id, char desc[]);
int validarTipo(eTipo tipo[], int tam, int id);
int listarTipos(eTipo tipos[], int tam);


#endif /* TIPOPASAJERO_H_ */
