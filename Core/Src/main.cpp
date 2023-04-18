#include "main.h"
#include "lwip.h"

#include "ST-LIB.hpp"
#include "Runes/Runes.hpp"
#include "Examples/examples_includes.hpp"

extern struct netif gnetif;

int main(void)
{

	while(1) {
    
	}
}

void Error_Handler(void)
{
	ErrorHandler("HAL error handler triggered");
  while (1){}
}
