/*
 * GPIOxDriver.c
 *
 *  Created on: 30 ago. 2022
 *      Author: Valentina Quintero
 *
 *	Este archivp es la parte del programa donde escribimos adecuadamente el control,
 *	para que sea lo más genérico posible, de forma que independiente del grupo GPIO y
 *	el PIN seleccionados, el programa se ejecute y configure todo correctamente.
 *
 */

#include "GPIOxDriver.h"

/**
 * Para cualquier periférico, hay varios pasos que siempre se deben seguir en un
 * orden estricto para poder que el sistema permita configurar en periférico X.
 * Lo primero y más importante es ACTIVAR LA SEÑAL DEL RELOJ principal hacia ese
 * elemento específico (relacionado con el periférico RCC), a esto llamaremos
 * simplemente "activar el periférico" o "activar la señal del reloj del periférico"
 */
void GPIO_Config (GPIO_Handler_t *pGPIOHandler)
{
	// Variable para hacer todo paso a paso
	uint32_t auxConfig = 0;
	uint32_t auxPosition = 0;

	// 1) Activar el periférico
	// Verificamos para GPIOA
	if(pGPIOHandler->pGPIOx == GPIOA){
		// Escribimos 1 (SET) en la posición correspondiente al GPIOA
		RCC->AHB1ENR |= (SET << RCC_AHB1ENR_GPIOA_EN);
	}
	// Verificamos para GPIOB
	else if(pGPIOHandler->pGPIOx == GPIOB){
		// Escribimos 1 (SET) en la posición correspondiente al GPIOB
		RCC->AHB1ENR |= (SET << RCC_AHB1ENR_GPIOB_EN);
	}
	// Verificamos para GPIOC
	else if(pGPIOHandler->pGPIOx == GPIOC){
		// Escribimos 1 (SET) en la posición correspondiente al GPIOC
		RCC->AHB1ENR |= (SET << RCC_AHB1ENR_GPIOC_EN);
	}
	// Verificamos para GPIOD
	else if(pGPIOHandler->pGPIOx == GPIOD){
		// Escribimos 1 (SET) en la posición correspondiente al GPIOD
		RCC->AHB1ENR |= (SET << RCC_AHB1ENR_GPIOD_EN);
	}
	// Verificamos para GPIOE
	else if(pGPIOHandler->pGPIOx == GPIOE){
		// Escribimos 1 (SET) en la posición correspondiente al GPIOE
		RCC->AHB1ENR |= (SET << RCC_AHB1ENR_GPIOE_EN);
	}
	// Verificamos para GPIOH
	else if(pGPIOHandler->pGPIOx == GPIOH){
		// Escribimos 1 (SET) en la posición correspondiente al GPIOH
		RCC->AHB1ENR |= (SET << RCC_AHB1ENR_GPIOH_EN);
	}

	// Después de activado, podemos comenzar a configurar.

	// 2) Configurando el registro GPIOx_MODER
	// Acá estamos leyendo la config, moviendo "PinNumber" veces hacia la izquierda ese valor (shift-left)
	// y todo eso lo cargamos en la variable auxConfig
	auxConfig = (pGPIOHandler ->GPIO_PinConfig.GPIO_PinMode << 2 * pGPIOHandler->GPIO_PinConfig.GPIO_PinNumber);

	// Antes de cargar el nuevo valor, limpiamos los bits específicos de ese registro (debemos escribir 0b00)
	// para lo cual aplicamos una máscara y una operación bitwise AND
	pGPIOHandler ->pGPIOx->MODER &= ~(0b00 << 2 * pGPIOHandler->GPIO_PinConfig.GPIO_PinNumber);

	// Cargamos a auxConfig en el registro MODER
	pGPIOHandler->pGPIOx->MODER |= auxConfig;

	// 3) Configurando el refistro GPIOx_OTYPER
	// De nuevo, leemos y movemos el valor un número "PinNumber" de veces
	auxConfig = (pGPIOHandler->GPIO_PinConfig.GPIO_PinOPType << pGPIOHandler->GPIO_PinConfig.GPIO_PinNumber);

	// Limpiamos antes de cargar
	pGPIOHandler->pGPIOx->OTYPER &= ~(SET << pGPIOHandler->GPIO_PinConfig.GPIO_PinNumber);

	// Cargamos el resultado sobre el registro adecuado
	pGPIOHandler->pGPIOx->OTYPER |= auxConfig;

	//4) Configurando ahora la velocidad
	auxConfig = (pGPIOHandler->GPIO_PinConfig.GPIO_PinSpeed << 2*pGPIOHandler->GPIO_PinConfig.GPIO_PinNumber);

	// Limpiando la posición antes de cargar la nueva configuración
	pGPIOHandler->pGPIOx->OSPEEDR &= ~(0b11 << 2 * pGPIOHandler->GPIO_PinConfig.GPIO_PinNumber);

	// Cargamos el resultado sobre el registro adecuado
	pGPIOHandler->pGPIOx->OSPEEDR |= auxConfig;

	// 5) Configurando si se desea pull-up, pull-down o flotante.
	auxConfig = (pGPIOHandler->GPIO_PinConfig.GPIO_PinPuPdControl << 2*pGPIOHandler->GPIO_PinConfig.GPIO_PinNumber);

	// Limpiando la posición antes de cargar la nueva configuración
	pGPIOHandler->pGPIOx->PUPDR &= ~(0b11 << 2 * pGPIOHandler->GPIO_PinConfig.GPIO_PinNumber);

	// cargamos el resultado sobre el registro adecuado
	pGPIOHandler->pGPIOx->PUPDR |= auxConfig;

	// Esta es la parte para la configuración de las funciones alternativas... se verá luego
	if(pGPIOHandler->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN){

		// Seleccionamos primero si se debe utilizar el registro bajo (AFRL) o el alto (ARFH)
		if(pGPIOHandler->GPIO_PinConfig.GPIO_PinNumber < 8)
		{
			// Estamos en el registro AFRL, que controla los pines del PIN_0 al PIN_7
			auxPosition = 4 * pGPIOHandler->GPIO_PinConfig.GPIO_PinNumber;

			// Limpiamos primero la posición del registro que deseamos escribir a continuación
			pGPIOHandler->pGPIOx->AFRL &= ~(0b1111 << auxPosition);

			// Y escribimos el valor configurado en la posición seleccionada
			pGPIOHandler->pGPIOx->AFRL |= (pGPIOHandler->GPIO_PinConfig.GPIO_PinAltFunMode << auxPosition);
		}
		else{
			// Estamos en el registro AFRH, que lo controla los pines del PIN_8 al PIN_15
			auxPosition = 4 * (pGPIOHandler->GPIO_PinConfig.GPIO_PinNumber -8);

			// Limpiamos primero la posición del registro que deseamos escribir a continuación
			pGPIOHandler->pGPIOx->AFRH &= ~(0b1111 << auxPosition);

			// Y escribimos el valor configurado en la posición seleccionada
			pGPIOHandler ->pGPIOx->AFRH |= (pGPIOHandler->GPIO_PinConfig.GPIO_PinAltFunMode << auxPosition);

		}
	}
} // FIN del GPIO_config

/**
 * Función utilizada para cambiar de estado el pin entregado en el handler, asignando
 * el valor entregado en la variable newState
 */
void GPIO_WritePin(GPIO_Handler_t *pPinHandler, uint8_t newState){
	// Limpiando la posición que deseamos
	// pPinHandler->pGPIOx->ODR &= ~(SET << pPinHandler-GPIO_PinConfig.GPIO_PinNumber);
	if(newState == SET){
		// Trabajando con la parte baja del registro
		pPinHandler->pGPIOx->BSRR |= (SET << pPinHandler->GPIO_PinConfig.GPIO_PinNumber);
	}
	else{
		// Trabajando con la parte alta del registro
		pPinHandler->pGPIOx->BSRR |= (SET << (pPinHandler->GPIO_PinConfig.GPIO_PinNumber+16));
	}
}

/**
 * Funciónpara leer el estado de un PIN específico.
 */
uint32_t GPIO_ReadPin(GPIO_Handler_t *pPinHandler)
{
	// Creamos una variable auxiliar la cual luego retornaremos
	uint32_t pinValue = 0;

	// Cargamos el valor del registro IDR, esplazando a la derecha tantas veces como la
	// ubicación del PIN específico

	/*		*********	Punto 1 	**********
	 * a.	El error consistía en que no se hizo  la máscara al IDR, por lo cual, no se puede asegurar que
	 * 		el valor de retorno sea realmente 0 o 1.
	 *
	 * b.	Se puede solucionar haciendo una máscara, se le hace un and con un 1 que se mueva siendo ubicado en la posición
	 * 		que le corresponde al PIN de interés en IDR. para esto se realizó el shift izquierdo con
	 * 					pPinHandler ->GPIO_PinConfig.GPIO_PinNumber <- Un número
	 * 		de modo que sólo hubiese un 1 en la posición del PIN  ceros en el resto de casillas.
	 * 		Al hacer la operación & se eliminaron las casillas que no eran de interés dejando al PIN objetivo con el valor que
	 * 		siempre había tenido, luego se movió este valor hasta la última casilla para así permitir que
	 * 		cuando la función retornara cierto valor, este fuese en efecto, el valor que le correspondía al Pin requerido.
	 */
	pinValue = (pPinHandler->pGPIOx->IDR)&(0b1 << pPinHandler ->GPIO_PinConfig.GPIO_PinNumber);

	pinValue = (pinValue >> pPinHandler ->GPIO_PinConfig.GPIO_PinNumber);
	return pinValue;
}

/**  Punto 2  */
void GPIOxTooglePin(GPIO_Handler_t *pPinHandler)
{
	/* PUNTO 2: Inicialmente se busca el registro donde puedo modificar valores (BSRR o ODR)
	 * Luego se hace una operación XOR con una máscara con lo cual se modifica el valor
	 * del pin en cuestión convirtiendo 0 en 1 y 1 en 0. Este punto se pone a prueba en el punto 3 y 4.
	 */
	pPinHandler->pGPIOx->ODR ^= (0b1 << pPinHandler->GPIO_PinConfig.GPIO_PinNumber);
}
