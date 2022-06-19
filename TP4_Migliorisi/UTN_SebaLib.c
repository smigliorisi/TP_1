#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * \brief Lee de stdin hasta que encuentra un '\n' o hasta que haya copiado
 * 			en cadena un maximo de 'longitud-1' caracteres
 *
 * \param cadena puntero al espacio de memoria donde se copiara la cadena
 * \param longitud define el tamaño de la cadena
 * \return retorna 0 si se obtiene una cadena y 1 si no
 */
static int myGets(char* cadena, int longitud)
{
	fflush(stdin);
	fgets(cadena,longitud,stdin);
	cadena[strlen(cadena)-1]='\0';
	return 0;
}

/**
 * \brief Verifica si la cadena ingresada es numerica
 *
 * \param cadena Cadena de caracteres a ser analizada
 * \return Retorna 1 si la cadena es numerica y 0 si no lo es
 */
static int esNumerica(char* cadena)
{
	int retorno=1;
	int i=0, cPunto=0;
	if(cadena[0]=='-')
		i++;
	for( ; cadena[i]!='\0'; i++)
	{
		if(cadena[i]<'0' || cadena[i]>'9')
		{
			if(cadena[i]=='.' && cPunto==0)
				cPunto=1;
			else
			{
				retorno=0;
				break;
			}
		}
	}
	return retorno;
}

/**
 * \brief Convierte una cadena de caracteres en numero entero
 *
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \return Retorna 0 si se obtiene un numero entero y 1 si no
 */
static int getInt(int* pResultado)
{
	int retorno=-1;
	char buffer[4096];

	if(myGets(buffer,sizeof(buffer))==0 && esNumerica(buffer))
	{
		retorno=0;
		*pResultado=atoi(buffer);
	}
	return retorno;
}

/**
 * \brief Convierte una cadena de caracteres en numero flotante
 *
 * \param pResultado Puntero al espacio de memoria donde se dejara la funcion
 * \return Retorna 0 si se obtiene un numero flotante y 1 si no
 */
static int getFloat(float* pResultado)
{
	int retorno=-1;
	char buffer[4096];

	if(myGets(buffer,sizeof(buffer))==0 && esNumerica(buffer))
	{
		retorno=0;
		*pResultado=atof(buffer);
	}
	return retorno;
}

/**
 * \brief Solicita un numero entero al usuario, lo verifica y devuelve el resultado
 *
 * \param pResultado: puntero a donde se carga el resultado
 * \param mensaje: texto que pide ingreso de numero
 * \param mensajeError: texto de error
 * \param minimo: minimo valor
 * \param maximo: maximo valor
 * \param reintentos: cant. de reintentos para el ingreso
 * \return
 */
int utn_getNumeroInt(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos)
{
	int retorno=-1;
	int buffer;

	if(pResultado!=NULL && mensaje!=NULL && mensajeError!=NULL && minimo<=maximo && reintentos>=0)
	{
		do
		{
			printf("%s", mensaje);
			if(getInt(&buffer)==0 && buffer>=minimo && buffer<=maximo)
			{
				*pResultado=buffer;
				retorno=0;
				break;
			}
			printf("%s", mensajeError);
			reintentos--;
		}while(reintentos>=0);
	}
	return retorno;
}

/**
 * \brief Solicita un numero flotante al usuario, lo verifica y devuelve el resultado
 *
 * \param pResultado: puntero a donde se carga el resultado
 * \param mensaje: texto que pide ingreso de numero
 * \param mensajeError: texto de error
 * \param minimo: minimo valor
 * \param maximo: maximo valor
 * \param reintentos: cant. de reintentos para el ingreso
 * \return
 */
int utn_getNumeroFloat(float* pResultado, char* mensaje, char* mensajeError, float minimo, float maximo, int reintentos)
{
	int retorno=-1;
	float buffer;

	if(pResultado!=NULL && mensaje!=NULL && mensajeError!=NULL && minimo<=maximo && reintentos>=0)
	{
		do
		{
			printf("%s", mensaje);
			if(getFloat(&buffer)==0 && buffer>=minimo && buffer<=maximo)
			{
				*pResultado=buffer;
				retorno=0;
				break;
			}
			printf("%s", mensajeError);
			reintentos--;
		}while(reintentos>=0);
	}
	return retorno;
}

/**
 * \brief Solicita un caracter al usuario, la verifica y devuelve el resultado
 *
 * \param pResultado: puntero a donde se carga el resultado
 * \param mensaje: texto que pide ingreso de caracter
 * \param mensajeError: texto de error
 * \param minimo: minimo caracter valido
 * \param maximo: maximo caracter valido
 * \param reintentos: cant. de reintentos para el ingreso
 * \return
 */
int utn_getCharacter(char* pResultado, char* mensaje, char* mensajeError, char minimo, char maximo, int reintentos)
{
	int retorno=-1;
	char buffer[4096];

	if(pResultado!=NULL && mensaje!=NULL && mensajeError!=NULL && minimo>=0 &&  minimo<=maximo && reintentos>=0)
	{
		do
		{
			printf("%s", mensaje);
			//fflush(stdin);
			//scanf("%c", &buffer);
			if(myGets(buffer,sizeof(buffer))==0 && strlen(buffer)==1 && buffer[0]>=minimo && buffer[0]<=maximo)
			{
				*pResultado=buffer[0];
				retorno=0;
				break;
			}
			printf("%s", mensajeError);
			reintentos--;
		}while(reintentos>=0);
	}

	return retorno;
}

/**
 * \brief Solicita una cadena al usuario, lo verifica y devuelve el resultado
 *
 * \param pResultado: puntero a donde se carga el resultado
 * \param mensaje: texto que pide ingreso de caracter
 * \param mensajeError: texto de error
 * \param minimo: minimo cantidad de caracteres validos
 * \param maximo: maxima cantidad de caracteres (tamaño del vector)
 * \param reintentos: cant. de reintentos para el ingreso
 * \return
 */
int utn_getString(char* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos)
{
	int retorno=-1;
	char buffer[4096];

	if(pResultado!=NULL && mensaje!=NULL && mensajeError!=NULL && minimo>=0 && minimo<=maximo && reintentos>=0)
	{
		do
		{
			printf("%s", mensaje);

			if(myGets(buffer,sizeof(buffer))==0 && strnlen(buffer,4096)>=minimo && strnlen(buffer,4096)<=maximo)
			{
				strncpy(pResultado,buffer,maximo);
				pResultado[maximo] = '\0';
				retorno=0;
				break;
			}
			printf("%s", mensajeError);
			reintentos--;
		}while(reintentos>=0);
	}

	return retorno;
}

/**
 * \brief Calcula el mayor de dos enteros
 *
 * \param pResultado puntero a donde se carga el resultado
 * \param num1 primer numero entero a comparar
 * \param num2 segundo numero entero a comparar
 * \return retorna 0 si son iguales, 1 si encontro un mayor y -1 si hubo un error
 */
int calcularMayor (int *pResultado, int num1, int num2)
{
	int retorno=-1;

	if(pResultado!=NULL)
	{
		if(num1==num2)
			retorno=0;
		else if(num1>num2)
			*pResultado=num1;
		else
			*pResultado=num2;
	}
	return retorno;
}

/**
 * \brief Calcula el menor de dos enteros
 *
 * \param pResultado puntero a donde se carga el resultado
 * \param num1 primer numero entero a comparar
 * \param num2 segundo numero entero a comparar
 * \return retorna 0 si son iguales, 1 si encontro un mayor y -1 si hubo un error
 */
int calcularMenor (int *pResultado, int num1, int num2)
{
	int retorno=-1;

	if(pResultado!=NULL)
	{
		if(num1==num2)
			retorno=0;
		else if(num1>num2)
			*pResultado=num1;
		else
			*pResultado=num2;
	}
	return retorno;
}
