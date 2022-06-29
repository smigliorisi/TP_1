#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "calculos.h"

int main(void)
{
	setbuf(stdout, NULL);

	char salir = 'n';
	int flagKm = 0;
	int km = 0;
	int flagPrecioLatam = 0;
    int flagPrecioAerolineas = 0;
    int flagCalculoCostosA = 0;
    int flagCalculoCostosL = 0;
	float precioLatam = 0;
	float precioAerolineas = 0;
    float descuentoDebito = 0.1;
    float interesCredito = 0.25;
    float bitcoin = 4809760.23;
    float precioDebitoA;
    float precioDebitoL;
    float precioCreditoA;
    float precioCreditoL;
    float precioBtcA;
    float precioBtcL;
    float precioUnitarioA;
    float precioUnitarioL;

	do
	{
		switch(menu(&km, &precioAerolineas, &precioLatam))
		{
		case 1:
			IngresarKm(&flagKm, &km);
		break;
		case 2:
			switch(subMenuPrecio())
			{
			case 1:
				ingresarPrecio(&flagPrecioAerolineas, &precioAerolineas);
				break;
			case 2:
				ingresarPrecio(&flagPrecioLatam, &precioLatam);
				break;
			}
		break;
		case 3:
            calcularCostos(precioAerolineas, descuentoDebito, interesCredito, bitcoin, &precioDebitoA, &precioCreditoA, &precioBtcA, km, &precioUnitarioA, flagKm, flagPrecioAerolineas, &flagCalculoCostosA);
            calcularCostos(precioLatam, descuentoDebito, interesCredito, bitcoin, &precioDebitoL, &precioCreditoL, &precioBtcL, km, &precioUnitarioL, flagKm, flagPrecioAerolineas, &flagCalculoCostosL);
		break;
		case 4:
			system("cls");
            printf("Precio Aerolineas:$ %.2f\n", precioAerolineas);
            informar(flagCalculoCostosA,precioDebitoA, precioCreditoA, precioBtcA, precioUnitarioA);
            printf("Precio Latam:$ %.2f\n", precioLatam);
            informar(flagCalculoCostosL,precioDebitoL, precioCreditoL, precioBtcL, precioUnitarioL);
            if(flagCalculoCostosA != 0 && flagCalculoCostosL != 0)
            {
            	printf("La diferencia de precio es:$ %.2f\n\n", diferenciaPrecios(precioAerolineas, precioLatam));
            }
		break;
		case 5:
			system("cls");
            cargaForzadaDatos(&km, &precioAerolineas, &precioLatam, &flagKm, &flagPrecioAerolineas, &flagPrecioLatam);
            calcularCostos(precioAerolineas, descuentoDebito, interesCredito, bitcoin, &precioDebitoA, &precioCreditoA, &precioBtcA, km, &precioUnitarioA, flagKm, flagPrecioAerolineas, &flagCalculoCostosA);
            calcularCostos(precioLatam, descuentoDebito, interesCredito, bitcoin, &precioDebitoL, &precioCreditoL, &precioBtcL, km, &precioUnitarioL, flagKm, flagPrecioAerolineas, &flagCalculoCostosL);
            printf("Precio Aerolineas:$ %.2f\n", precioAerolineas);
            informar(flagCalculoCostosA,precioDebitoA, precioCreditoA, precioBtcA, precioUnitarioA);
            printf("Precio Latam:$ %.2f\n", precioLatam);
            informar(flagCalculoCostosL,precioDebitoL, precioCreditoL, precioBtcL, precioUnitarioL);
            printf("La diferencia de precio es:$ %.2f\n\n", diferenciaPrecios(precioAerolineas, precioLatam));
            //carga forzada de datos - Km: 7090 - Aerolineas Argentinas: $162965 - Latam: $ 159339
		break;
		case 6:
            confirmarSalida(&salir);
		break;
		case 7:
            informarNoEsNumero();
		break;
        default:
            printf("Opcion invalida\n");
        break;
		}
		fflush(stdin);
		system("pause");
	}while(salir != 's');

	return EXIT_SUCCESS;
}

