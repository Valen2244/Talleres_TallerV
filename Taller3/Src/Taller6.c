/*
 * Taller6.c
 *
 *  Created on: 29 sept. 2022
 *      Author: Valentina Quintero
 *
 *
 *  Lenguajes de programación pasados por valor
 *  	No se modifican las variables originales
 *  	Como C es un lenguaje de este tipo, nos vemos obligados a utilizar
 *  	punteros que son como pasar por referencia.
 *
 *  	En el siguiente ejemplo no se modifica el valor de var.
 *  	void Duplicar(uint8_t n)
 *  	{
 *  		n *= n;
 *  	}
 *
 *  	Pero en el siguiente ejemplo sí se modifica el valor de var.
 *  	void Duplicar (uint8_t *n)
 *  	{
 *  		(*n) = (*n) * 2;
 *  	}
 *
 *  	uint8_t var = 2;
 *  	Duplicar(var);
 *
 *  	Los arreglos están relacionados con punteros
 *
 *  	uint8_t array[5];
 *  	*array;			es el valor del primer elemento del arreglo
 *  	*(array + 1); 	es el valor del segundo elemento del arreglo...
 *
 *
 *
 *
 *  Lenguajes de programación pasados por referencia
 */

#include <stdint.h>
void duplicar(uint8_t numero);
void duplicarReferencia(uint8_t* numero);
uint8_t duplicarReasignar(uint8_t numero);
void abonarDeudas (uint16_t deudas[], uint8_t cantidad);

void stringCaseConverter(uint8_t string[]);

char msgToSend[64] = {};

int main(void){

	uint8_t variable = 10;

	duplicar(variable);

	variable = duplicarReasignar(variable);

	uint8_t variableRef = 15;

	duplicarReferencia(&variableRef);

	variable = 0;

	char String[] = "Hola Mundo";

	char test1 = *String;

	(void) test1;

	test1 = *(String + 2);

	test1 = *(String + 8);

	*(String + 5) = 'I';

	uint16_t deudas[5] = {15000, 2000, 1300, 50000, 10000};

	abonarDeudas(deudas, 5);



	// 1.5 EJERCICIO:

	// Crear una función llamada stringCaseConverter que no retorne ningún
	// valor, y reciba una string.

	// Esta función deberá cambiar las minúsculas por mayúsculas y viceversa
	// del string original.

	uint8_t mensaje[] = "4di0s MuNdO";

	stringCaseConverter(mensaje);


	while(1){

	}
}

void duplicar(uint8_t numero){
	numero *= 2;
}

void duplicarReferencia(uint8_t* numero){
	*numero = (*numero)*2;
}

uint8_t duplicarReasignar(uint8_t numero){
	numero *= 2;
	return numero;
}

void abonarDeudas (uint16_t deudas[], uint8_t cantidad){

	for(uint8_t i = 0; i < cantidad; i++){

		*(deudas+i) = *(deudas+i)/2;

	}

}

void stringCaseConverter(uint8_t string[]){

	uint8_t i = 0;

	while(*(string+i) != '\0'){

		if(*(string + i) >= 97  && *(string + i) <= 122){

			*(string + i) = *(string + i) - 32;

		}else if(*(string + i) <= 90  && *(string + i) >= 65){

			*(string + i) = *(string + i) + 32;

		}else{
			*(string + i) = *(string + i);
		}

		i++;
	}

}
