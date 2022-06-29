#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "typePassenger.h"

int cargarIntTipo(eTipo tipo[], int tam, char* desc)
{
    int id = 0;

    if(tipo != NULL && desc != NULL && tam > 0)
    {
      for(int i = 0; i < tam; i++)
      {
          if(stricmp(desc,tipo[i].descripcion) == 0)
          {
              id = tipo[i].id;
              break;
          }
      }
    }
    return id;
}

int cargarDescripcionTipo(eTipo tipo[], int tam, int id, char desc[])
{
    int todoOk = 0;

    if(tipo != NULL && desc != NULL && tam > 0)
    {
      for(int i = 0; i < tam; i++)
      {
          if(tipo[i].id == id)
          {
              strcpy(desc, tipo[i].descripcion);
              todoOk = 1;
              break;
          }
      }
    }
    return todoOk;
}

int validarTipo(eTipo tipo[], int tam, int id)
{
    int esValido = 0;

    if(tipo != NULL && tam > 0)
    {
      for(int i=0; i < tam; i++)
      {
          if(id == tipo[i].id)
          {
              esValido = 1;
              break;
          }
      }
    }
    return esValido;
}

int listarTipos(eTipo tipos[], int tam)
{
    int todoOk = 0;

    if(tipos != NULL && tam > 0)
    {
        printf("    *** TIPOS DE CLASES ***    \n");
        printf("    ID     DESCRIPCION\n");
        printf("-----------------------\n");
      for(int i=0; i<tam; i++)
      {
            printf("    %4d         %10s\n", tipos[i].id, tipos[i].descripcion);
      }
      todoOk = 1;
    }
    return todoOk;
}

