/**
 ******************************************************************************
Taller 4 de TallerV, se ha enseñado
	la secuencia switch es más eficiente,
	se vio while (sirve más para banderas o interrupciones,
	se vio también el do while, este es más útil en otros ambientes de desarrollo

 */
#include <stdint.h>

int16_t resultadoOperacion(int8_t num1, int8_t num2, uint8_t operacion);

#define SUMA '+'
#define MULTIPLICACION '*'
#define RESTA '-'
#define DIVISION '/'

int main(void)
{
	int8_t variableA = 15;
	int16_t variableB = 25;

	int16_t resultadoSuma = resultadoOperacion(variableA,(int8_t)variableB , SUMA); // Casteo, obligo que la variable sólo sea de este tamaño en la ejecución

	resultadoSuma++;

    /* Loop forever */
	while(1)
	{

	}
}


int16_t resultadoOperacion(int8_t num1, int8_t num2, uint8_t operacion)
{
	int16_t resultado = 0;
	switch(operacion)
	{
	case SUMA:
	{
		resultado = num1 + num2;
		break;
	}
	case RESTA:
	{
		resultado = num1 - num2;
		break;
	}
	case MULTIPLICACION:
	{
		resultado =  num1 * num2;
		break;
	}
	case DIVISION:
	{
		resultado = num1 / num2;
		break;
	}
	default:
	{
		resultado = 0;
		break;
	}

	}

	return resultado;

}
