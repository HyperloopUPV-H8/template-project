#include "main.h"
#include "lwip.h"

#include "ST-LIB.hpp"
#include "Runes/Runes.hpp"
#include "Examples/examples_includes.hpp"

extern struct netif gnetif;

int main(void)
{
	STLIB::start(Nucleo, "192.168.1.4", "255.255.0.0", "192.168.1.1");
	printf("freq = %lu", HAL_RCC_GetSysClockFreq());
	while(1) {
		STLIB::update();

	}
}

void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	ErrorHandler("HAL error handler triggered");
  /* User can add his own implementation to report the HAL error return state */
  //__disable_irq();
  //while (1){}
  /* USER CODE END Error_Handler_Debug */
}
