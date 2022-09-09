/*
 * GPIO_Ejemplos.c
 *
 *  Created on: Sep 8, 2022
 *      Author: Valentina Quintero
 */

#include <stm32f4xx_hal.h>
#include <stdint.h>
#include <stdbool.h>
#include "GPIOxDriver.h"

void delay(uint32_t iteraciones);


int main()
{
	uint8_t sumatoria = 0;

	GPIO_Handler_t handlerUserLedPin = {0};

	handlerUserLedPin.pGPIOx = GPIOA;
	handlerUserLedPin.GPIO_PinConfig.GPIO_PinNumber			= PIN_5;
	handlerUserLedPin.GPIO_PinConfig.GPIO_PinMode			= GPIO_MODE_OUT;
	handlerUserLedPin.GPIO_PinConfig.GPIO_PinOPType			= GPIO_OTYPE_PUSHPULL;
	handlerUserLedPin.GPIO_PinConfig.GPIO_PinPuPdControl	= GPIO_PUPDR_NOTHING;
	handlerUserLedPin.GPIO_PinConfig.GPIO_PinSpeed			= GPIO_OSPEED_MEDIUM;
	handlerUserLedPin.GPIO_PinConfig.GPIO_PinAltFunMode		= AF0;

	// Cargamos la configuración del PIN específico
	GPIO_Config(&handlerUserLedPin);



	do
	{
		sumatoria++;
	}
	while(sumatoria < 10);

	/*Main Loop*/
	while(1)
	{
		GPIOxTooglePin(&handlerUserLedPin);
		delay(100000);
	}

}

void delay(uint32_t iteraciones)		// Se utilizan los delays para cuando uno está configurando algo por ejemplo una pantalla
{										// donde hay que esperar un tiempo para
	uint32_t i = 0;

	while(i < iteraciones)
	{
		i++;
		NOP();
	}
}
