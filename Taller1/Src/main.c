/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Valen2244
 * @brief          : Main program body
 ******************************************************************************
 */

#include <stdint.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{
    /* Loop forever */
	while(1)
	{

	}
}
