#include "main.h"
#include "lwip.h"

#include "ST-LIB.hpp"
#include "Runes/Runes.hpp"

//  when including free-rtos files
// use the following notation
// 		<free-rtos/path-to-file>
// note the use of the root path free-rtos
// and the angle brackets

#include <FreeRTOS-Lib/inc/thread.hpp>
#include <FreeRTOS-Lib/inc/GlobalMutexHandler.hpp>

int main(void)
{

	// Declare peripherals to be used
	
	// All peripherals must have been declared before calling start()
	STLIB::start();

	//define tasks for FreeRTOS
	


	//start the freeRTOS task scheduler
	//any code below vTaskStartScheduler will NOT execute
	vTaskStartScheduler();

}

void Error_Handler(void)
{
	ErrorHandler("HAL error handler triggered");
	while (1){}
}
