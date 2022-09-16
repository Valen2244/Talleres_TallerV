/*
 * Taller5.c
 *
 *  Created on: Sep 15, 2022
 *      Author: Valentina Quintero
 *
 *
 *      PUNTEROS
 *  Con el asterisco * defino el puntero y con el & pregunto la ruta de un puntero
 *  Lo de antes del asterisco es la forma que tiene lo que está buscando mi puntero.
 *
 *  uint8_t *pDato = &Dato;		Bien porque el puntero contiene la información sobre la posición de Dato en la memoria
 *  uint32_t direccion = &Dato; MAL porque
 *  en lugar de lo anterior, puedo copiar
 *  uint32_t direccion = (uint32_t)&Dato; 	Casteo
 *
 *  Lo siguiente es equivalente
 *  Dato = 5;
 *  *pDato = 5; ya que el * también cambio el valor que tengo en
 *
 *
 *	Plot Twist! Los arreglos son punteros
 *
 *	3. Estructuras
 *
 *
 */
#include <stdint.h>

int main(void)
{
	uint16_t dato = 243;

	uint16_t *ptrDato = &dato;

	uint16_t valorDato = *ptrDato;		// Aquí accedemos al valor que está en la posición de memoria al que está apuntando
										// el puntero


	uint32_t direccionDato = (uint32_t) &dato;	// Debe ser de 32 porque esto es una dirección de memoria


	//*ptrDato ++;						// Así se cambia la dirección CUIDADO

	*ptrDato = *ptrDato + 1;			// Pero así el valor que está en la posición de memoria... se incrementa en uno

	ptrDato ++;							// Con esto estamos en la posición de memoria después de dato.

	*ptrDato = 561;



	uint8_t miPrimerArreglo[5] = {0x43, 'A', 0x22, 0xFF, 12};

	uint8_t contenido = 0;
	//  Para recorrer posiciones de memoria del arreglo
	for (uint8_t i = 0; i < 5; i++) {

		contenido = miPrimerArreglo[i];

	}
	// Otra forma es con punteros
	for(uint8_t j = 0; j < 5; j++)
	{
		contenido = *(miPrimerArreglo + j);		// Estamos accediendo a la posición de la memoria de miPrimerArreglo + j
												// equivalente a miPrimerArreglo[j]

												// *miPrimerArreglo corresponde a lo que está en la posición cero del arreglo.
	}

	// Para cambiar un dato de mi arreglo
	miPrimerArreglo[2] = 0xAD;
	* (miPrimerArreglo + 2) =0x42;


	/*************************************************************************************/
	typedef struct
	{
		uint8_t Elemento1;
		uint16_t Elemento2;
		uint64_t Elemento3;
		uint8_t ElementoArreglo[3];
	}miEstructura_t;

	miEstructura_t miPrimeraEstructura = {0};

	miPrimeraEstructura.Elemento2 = 0x45;
	miPrimeraEstructura.ElementoArreglo[1] = 123;


	//Creando un puntero a este tipo de estructura
	miEstructura_t *ptrEstructura;				// Este es un puntero hacia una

	ptrEstructura->Elemento1 = 5;
	ptrEstructura->Elemento3 = 0xff;			// La diferencia entre el punto y flecha es que tenemos el puntero
												// a la estructura, en cambio con los puntos estamos yendo hacia un tipo
												// de dato dentro de una estructura.
												// Resumen: flechita para puntero y punto para estructura

	// Hay estructuras que contienen estructuras

	while(1)
	{

	}

}
