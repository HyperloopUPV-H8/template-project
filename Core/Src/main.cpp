#include "main.h"
#include "lwip.h"

#include "ST-LIB.hpp"
#include "Runes/Runes.hpp"
#include "Examples/examples_includes.hpp"


int main(void)
{
	i2c_example();
	printf("freq = %lu", HAL_RCC_GetSysClockFreq());
	while(1) {
		HAL_Delay(1000);
	}
}

void Error_Handler(void)
{
	ErrorHandler("HAL error handler triggered");
	while (1){}
}
