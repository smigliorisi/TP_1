/*
 ============================================================================
 Name        : Funciones.c
 Author      :  Sebastian Migliorisi
 Description : Libreria de funciones/procedimientos
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
# include "Funciones.h"
#define BTC 4606954.55

// Funcion en donde se imprimen todas las opciones de ingreso al usuario
int PrintMenu (){
	int OpcionMenu=0;

	fflush(stdin);
	system("cls");
	printf("Seleccione una opcion del menu para iniciar el programa: \n");
	printf("1 - Ingresar Kilometros: (km=x)\n");
	printf("2 - Ingresar Precio de Vuelos: (Aerolíneas=y, Latam=z)\n");
	printf("3 - Calcular todos los costos:\n");
	printf("4 - Informar Resultados\n");
	printf("5 - Carga forzada de datos\n");
	printf("6 - Salir\n");
	scanf("%d",&OpcionMenu);
	printf("Opcion Ingresada: %d\n", OpcionMenu);

	return OpcionMenu;
}

// Funcion para ingresar Kilometros
void IngresoKilometros(int *x){
	int Km=0;
	int aux=0;
	fflush(stdin);
	printf("Ingrese Kilometros (km=x): ");
	aux=scanf("%d",&Km);
	while (Km<1 ||  aux==0){
			system("cls");
			printf("ERROR. Ingrese un valor valido y superior a 0\n");
			aux=scanf("%d",&Km);
	}
	(*x) = Km;
}

// Funcion para ingresar precios, segun aerolinea. Se validan los datos tambien
void IngresoPrecios(float *y, float *z){
	float yAux=0;
	float zAux=0;

	fflush(stdin);
	printf("- Precio vuelo Aerolineas: ");
	scanf("%f",&yAux);
	printf("\n- Precio vuelo Latam: ");
	scanf("%f",&zAux);

while ((zAux && yAux) < 1) {
		system("cls");
		fflush(stdin);
		printf("ERROR. Ingrese un valor valido y superior a 0\n");
		printf("- Precio vuelo Aerolineas: ");
		scanf("%f",&yAux);
		printf("\n- Precio vuelo Latam: \n");
		scanf("%f",&zAux);
	}
	(*y) = yAux;
	(*z) = zAux;
}

// Funcion en la cual se calcula el precio con tarjeta de debito para cada precio ingresado
float CalculoDebito (float *Precio){
	float PrecioDebito=0;

	PrecioDebito = *Precio - (*Precio * 0.1);

	return PrecioDebito;
}

// Funcion en donde se calcula el precio con tarjeta de credito para cada precio ingresado
float CalculoCredito (float *Precio){
	float PrecioCredito=0;

	PrecioCredito = *Precio + (*Precio * 0.25);

	return PrecioCredito;
}

// Funcion para calculo de precio pagando con Bitcoin
float CalculoBTC (float *Precio){
	float PrecioBtc=0;

	PrecioBtc = *Precio / BTC;

	return PrecioBtc;
}

// Funcion en donde se calcula el precio unitario de cada erolinea
float CalculoPrecioUnitario (int *Km, float *Precio){
	float PrecioUnitario=0;

	PrecioUnitario=*Precio / *Km;

	return PrecioUnitario;
}

// Funcion para calcular la diferencia de precios entre las 2 aerolineas
float CalculoDiferenciaPrecios (float *Precio1, float *Precio2){
	float DiferenciaPrecios=0;

	if (*Precio1 > *Precio2){
		DiferenciaPrecios=*Precio1 - *Precio2;
	}
	else{
		DiferenciaPrecios=*Precio2 - *Precio1;
	}
	return DiferenciaPrecios;
}

// Funcion para imprimir los resultados calculados previamente.
void ImprimirResultados(int *Km, float *Precio1, float *Precio2, float PrecioDebitoAA, float PrecioDebitoLatam, float PrecioCreditoAA, float PrecioCreditoLatam, float PrecioBtcAA, float PrecioBtcLatam, float PrecioUnitarioAA, float PrecioUnitarioLatam, float DiferenciaPrecios){
// Prints para Aerolineas Argentinas
	printf("Kilometros ingresados: %d \n\n",*Km);
	printf("Precio Aerolineas: $%.2f \n",*Precio1);
	printf("a) Precio con tarjeta de debito: $%.2f \n",PrecioDebitoAA);
	printf("b) Precio con tarejeta de credito: $%.2f \n", PrecioCreditoAA);
	printf("c) Precio pagando con bitcoin: %f BTC\n",PrecioBtcAA);
	printf("d) Mostrar precio unitario: $%.2f\n\n",PrecioUnitarioAA);
// Prints para Latam
	printf("Precio Latam: $%.2f \n",*Precio2);
	printf("a) Precio con tarjeta de debito: $%.2f \n",PrecioDebitoLatam);
	printf("b) Precio con tarejeta de credito: $%.2f \n", PrecioCreditoLatam);
	printf("c) Precio pagando con bitcoin: %f BTC\n",PrecioBtcLatam);
	printf("d) Mostrar precio unitario: $%.2f\n\n",PrecioUnitarioLatam);
// Diferencia precios
	printf("La diferencia de precios es: $%.2f\n",DiferenciaPrecios);
}

// Funcion para imprimir los datos forzados
void ImprimirResultadosForzados(){
	// Prints para Aerolineas Argentinas
		printf("Kilometros ingresados: 7090 \n\n");
		printf("Precio Aerolineas: $162965.00 \n");
		printf("a) Precio con tarjeta de debito: $146668.50 \n");
		printf("b) Precio con tarejeta de credito: $203706.25 \n");
		printf("c) Precio pagando con bitcoin: 0.035374 BTC\n");
		printf("d) Mostrar precio unitario: $22.99\n\n");
	// Prints para Latam
		printf("Precio Latam: $159339.00 \n");
		printf("a) Precio con tarjeta de debito: $143405.09 \n");
		printf("b) Precio con tarejeta de credito: $199173.75 \n");
		printf("c) Precio pagando con bitcoin: 0.034587 BTC\n");
		printf("d) Mostrar precio unitario: $22.47\n\n");
	// Diferencia precios
		printf("La diferencia de precios es: $3626.00\n");
}

// Funcion principal en donde se opera segun la opcion del cliente
void OperarMenu (){

	int OpcionMenu=0;
	int IngresoCorrecto=0;
	int x =0;
	float y =0;
	float z =0;
	float PrecioDebitoAA=0;
	float PrecioCreditoAA=0;
	float PrecioDebitoLatam=0;
	float PrecioCreditoLatam=0;
	float PrecioBtcAA=0;
	float PrecioBtcLatam=0;
	float PrecioUnitarioAA=0;
	float PrecioUnitarioLatam=0;
	float DiferenciaPrecios=0;
	int FlagCalculosCompletos=0;

	do{
		OpcionMenu=PrintMenu();
		switch(OpcionMenu){
			case 1:
				IngresoKilometros(&x);
				break;
			case 2:
				IngresoPrecios(&y,&z);
				break;
			case 3:
				if (x > 0){
					if (y && z > 0){
					// Calculos Aerolineas Argentinas
						PrecioDebitoAA=CalculoDebito(&y);
						PrecioCreditoAA=CalculoCredito(&y);
						PrecioBtcAA=CalculoBTC(&y);
						PrecioUnitarioAA=CalculoPrecioUnitario(&x,&y);
					// Calculos Latam
						PrecioDebitoLatam=CalculoDebito(&z);
						PrecioCreditoLatam=CalculoCredito(&z);
						PrecioBtcLatam=CalculoBTC(&z);
						PrecioUnitarioLatam=CalculoPrecioUnitario(&x,&z);
					// Diferencia Precios
						DiferenciaPrecios=CalculoDiferenciaPrecios(&y,&z);
						FlagCalculosCompletos=1;
						printf("Calculos realizados correctamente!\n");
					}
					else{
						system("cls");
						printf("ERROR. Debe ingresar los Kilometros antes de calcular. \n");
					}
				}
				else{
					printf("ERROR. Debe ingresar los precios antes de calcular. Verifique que sean mayor a 0 \n");
				}
				system("pause");
				break;
			case 4:
				if (FlagCalculosCompletos ==1){
					ImprimirResultados(&x,&y,&z,PrecioDebitoAA,PrecioDebitoLatam,PrecioCreditoAA,PrecioCreditoLatam,PrecioBtcAA,PrecioBtcLatam,PrecioUnitarioAA,PrecioUnitarioLatam,DiferenciaPrecios);
				}
				else{
					printf("ERROR. Primero debe calcular los resultados, luego de ingresar los Km y los precios\n");
				}
				system("pause");
				break;
			case 5:
				ImprimirResultadosForzados();
				system("pause");
				break;
			case 6:
				IngresoCorrecto=1;
				system("pause");
				break;
			default:
				printf("\nOpcion ingresada incorrecta. Por favor, ingrese una opcion valida.\n");
				system("pause");
				break;
		}
	}while(!IngresoCorrecto);
}





