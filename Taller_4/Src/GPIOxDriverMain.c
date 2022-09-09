/*
 * GPIOxDriverMain.c
 *
 *  Created on: 30 ago. 2022
 *      Author: Valentina Quintero Osorio
 *      correo: vaquinteroo@unal.edu.co
 */

#include <stdint.h>

#include "stm32f4xx_hal.h"
#include "GPIOxDriver.h"

/* Función principal del programa. Es donde se ejecuta todo */
int main(void)
{


	/* *************************************** PUNTO 3 *******************************************/
								//Definición de LED y UserButton
	// User Led:
	// El User Led (verde) está conectado al PA5 por lo que se necesitará el puerto GPIO5,
	// para observar los cambios en el LED verde cuando se pulsa USER_BUTTON
	// Se inicializa el handler y luego se agregan los datos correspondientes para poder trabajar
	// con el PA5.
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


	/* User button:
	 * Este botón está conectado al PIN PC13, lo que implica que el puerto que se utilizará es GPIOC
	 * También se observa que el jumper de este pin sí está soldado.
	 * Cuando el USER_BUTTON no está presionado, el voltaje en PC13 es de 3.3V, y cuando se presiona,
	 * el voltaje es de  0V (Nucleo-F411RE-Reference-Diagram). Esta información se va a utilizar para
	 * crear la función capaz de cambiar el estado del LED cada vez que se pulse el USER_BUTTON.
	 */
	// Se define el handler para el PIN PC13
	GPIO_Handler_t handlerUserButtonPin = {0};

	handlerUserButtonPin.pGPIOx = GPIOC;
	handlerUserButtonPin.GPIO_PinConfig.GPIO_PinNumber			= PIN_13;
	handlerUserButtonPin.GPIO_PinConfig.GPIO_PinMode			= GPIO_MODE_IN;				// Entrada porque es un botón
	handlerUserButtonPin.GPIO_PinConfig.GPIO_PinOPType			= GPIO_OTYPE_PUSHPULL;
	handlerUserButtonPin.GPIO_PinConfig.GPIO_PinPuPdControl		= GPIO_PUPDR_PULLUP;		// En el diagrama de referencia se observa este tipo de configuración para el botón.
	handlerUserButtonPin.GPIO_PinConfig.GPIO_PinSpeed			= GPIO_OSPEED_MEDIUM;
	handlerUserButtonPin.GPIO_PinConfig.GPIO_PinAltFunMode		= AF0;

	// Se carga la información que se acaba de asignar al GPIO_Config
	GPIO_Config(&handlerUserButtonPin);

	/* Para poder pulsar cuantas veces se quiera, entramos en un ciclo infinito con
	 * la función que queremos ejecutar, el ciclo infinito está en la línea 156.
	 */

	uint32_t aux = 1; // Esta variable auxiliar me sirve para que al comienzo en el
					  // if de la línea 166 si se pulza el botón el programa ejecute
					  // de manera correcta.


	/* ******************************	Fin definiciones punto 3	********************************/






	/* ******************************** PUNTO 4  ***********************************************/
	//						Definiciones de botones y LEDs

	// Paso 1: Al PIN_C6 se le agregará un botón en modo Pull Down.

	GPIO_Handler_t handlerUserButtonC6 = {0};

		handlerUserButtonC6.pGPIOx 									= GPIOC;					// Esto debido a que el botón está en el puerto C
		handlerUserButtonC6.GPIO_PinConfig.GPIO_PinNumber			= PIN_6;					// El Pin Número 6
		handlerUserButtonC6.GPIO_PinConfig.GPIO_PinMode				= GPIO_MODE_IN;				// Entrada porque es botón
		handlerUserButtonC6.GPIO_PinConfig.GPIO_PinOPType			= GPIO_OTYPE_PUSHPULL;
		handlerUserButtonC6.GPIO_PinConfig.GPIO_PinPuPdControl		= GPIO_PUPDR_PULLDOWN;		// El modo en el que se configura el botón
		handlerUserButtonC6.GPIO_PinConfig.GPIO_PinSpeed			= GPIO_OSPEED_MEDIUM;
		handlerUserButtonC6.GPIO_PinConfig.GPIO_PinAltFunMode		= AF0;

		GPIO_Config(&handlerUserButtonC6);


	// Paso 2: Crear Handler para los pines PC10, PC11, PC12 como salidas, pues a estos
	// se conectarán LEDs

		GPIO_Handler_t handlerUserLedC10 = {0};		// EL PIN_C10
		handlerUserLedC10.pGPIOx = GPIOC;
		handlerUserLedC10.GPIO_PinConfig.GPIO_PinNumber			= PIN_10;
		handlerUserLedC10.GPIO_PinConfig.GPIO_PinMode			= GPIO_MODE_OUT;
		handlerUserLedC10.GPIO_PinConfig.GPIO_PinOPType			= GPIO_OTYPE_PUSHPULL;
		handlerUserLedC10.GPIO_PinConfig.GPIO_PinPuPdControl	= GPIO_PUPDR_NOTHING;
		handlerUserLedC10.GPIO_PinConfig.GPIO_PinSpeed			= GPIO_OSPEED_MEDIUM;
		handlerUserLedC10.GPIO_PinConfig.GPIO_PinAltFunMode		= AF0;

		GPIO_Config(&handlerUserLedC10);



		GPIO_Handler_t handlerUserLedC11 = {0};		// EL PIN_C11
		handlerUserLedC11.pGPIOx = GPIOC;
		handlerUserLedC11.GPIO_PinConfig.GPIO_PinNumber			= PIN_11;
		handlerUserLedC11.GPIO_PinConfig.GPIO_PinMode			= GPIO_MODE_OUT;
		handlerUserLedC11.GPIO_PinConfig.GPIO_PinOPType			= GPIO_OTYPE_PUSHPULL;
		handlerUserLedC11.GPIO_PinConfig.GPIO_PinPuPdControl	= GPIO_PUPDR_NOTHING;
		handlerUserLedC11.GPIO_PinConfig.GPIO_PinSpeed			= GPIO_OSPEED_MEDIUM;
		handlerUserLedC11.GPIO_PinConfig.GPIO_PinAltFunMode		= AF0;

		GPIO_Config(&handlerUserLedC11);




		GPIO_Handler_t handlerUserLedC12 = {0};		// EL PIN_C12
		handlerUserLedC12.pGPIOx = GPIOC;
		handlerUserLedC12.GPIO_PinConfig.GPIO_PinNumber			= PIN_12;
		handlerUserLedC12.GPIO_PinConfig.GPIO_PinMode			= GPIO_MODE_OUT;
		handlerUserLedC12.GPIO_PinConfig.GPIO_PinOPType			= GPIO_OTYPE_PUSHPULL;
		handlerUserLedC12.GPIO_PinConfig.GPIO_PinPuPdControl	= GPIO_PUPDR_NOTHING;
		handlerUserLedC12.GPIO_PinConfig.GPIO_PinSpeed			= GPIO_OSPEED_MEDIUM;
		handlerUserLedC12.GPIO_PinConfig.GPIO_PinAltFunMode		= AF0;

		GPIO_Config(&handlerUserLedC12);

		// Paso intermedio : configuramos todos los leds para que queden apagados al iniciar.

		GPIO_WritePin(&handlerUserLedC10, RESET);
		GPIO_WritePin(&handlerUserLedC11, RESET);
		GPIO_WritePin(&handlerUserLedC12, RESET);
		/* **************************  Fin definiciones punto 4 *********************************/




		/** Información general: El ciclo infinito comienza aquí para los puntos 3 y 4, esto es posible
		 * porque los pines de ambos son excluyentes 		 */

		while(1)
		{

			/** PUNTO 3 DENTRO DEL CICLO*/
			/* Queremos que el LED cambie de estado cada vez que se pulsa USER_BUTTON,
			 * para esto, necesitamos leer el valor de ese PIN */
			uint32_t buttonValue_3= 0;
			buttonValue_3 = GPIO_ReadPin(&handlerUserButtonPin);

			if(buttonValue_3 == 0 && aux == 1)        // Cuando se cumplen estas condiciones
			{										  // el LED cambia de estado
				GPIOxTooglePin(&handlerUserLedPin);
			}

			aux = buttonValue_3;					  // Aquí la variable auxiliar se le asigna el valor
													  // del botón, esto para asegurar que si el botón está siendo
													  // presionado, no cambie el estado del LED en este ciclo infinito, pero
													  // que si se suelta (aux toma valor de 1 pero botón está en 1) y se vuelve
													  // a pulsar(buttonValue_3 toma valor 0 y aux sigue en 1)
			  	  	  	  	  	  	  	  	  	  	  // sí cambie.
			/** Fin punto 3 */



			/** PUNTO 4	DENTRO DEL CICLO*/

			uint32_t buttonValue = 0;
			buttonValue = GPIO_ReadPin(&handlerUserButtonC6);
			// Paso 3 punto 4: Al pulsar PC_6 debemos encender PC10, PC11 y PC12.
			if(buttonValue == 1)
			{
				GPIOxTooglePin(&handlerUserLedC10);
				GPIOxTooglePin(&handlerUserLedC11);
				GPIOxTooglePin(&handlerUserLedC12);

				// Paso 4 punto 4: Apagar de manera descendente.
				for(uint32_t i = 0; i < 6000000; i++) 			// 5 segundos después apaga PC12 (1 segundo son 1.2M de ciclos for + NOP)
				{
					NOP();
				}
				GPIOxTooglePin(&handlerUserLedC12);

				for(uint32_t i = 0; i <= 2400000; i++)			// 2 segundos después apaga PC11
				{
					NOP();
				}
				GPIOxTooglePin(&handlerUserLedC11);

				for(uint32_t i = 0; i <= 1200000; i++)			// 1 segundos después apaga PC11
				{
					NOP();
				}
				GPIOxTooglePin(&handlerUserLedC10);

			}
		}

}

