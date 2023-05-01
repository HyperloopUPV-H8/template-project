#include "main.h"
#include "lwip.h"

#include "ST-LIB.hpp"
#include "Runes/Runes.hpp"

int main(void)
{
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
