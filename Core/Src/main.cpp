#include "main.h"
#include "lwip.h"

#include "ST-LIB.hpp"
#include "Runes/Runes.hpp"

//  when including free-rtos files
// use the following notation
// 		<free-rtos/path-to-file>
// note the use of the root path free-rtos
// and the angle brackets

#include <freeRTOS-lib/inc/Thread.hpp>
#include <freeRTOS-lib/inc/GlobalMutexHandler.hpp>
#include <freeRTOS-lib/inc/defs.hpp>

#include "TUD.hpp"

class Monolithic{



	public:
	Monolithic(){
	
	}

		// void run_tests(){
		// 	auto ref = rtos::this_thread::get_time_reference();
		// 	uint32_t val = 0;
		// 	for(;;){	
		// 		xTaskNotifyWait(pdFALSE,ULONG_MAX,&val,portMAX_DELAY);
		// 		ref = rtos::this_thread::get_time_reference();
		// 		for(int i = 0; i < 20; i++)
		// 		{
		// 			testing_led.toggle();
		// 			rtos::this_thread::sleep_for(&ref,100);
		// 		}
		// 		//go to booting mode
		// 		testing_led.turn_off();
		// 		xTaskNotifyGive(threads[1]->get_handle());
		// 	}

		// }

		void receive_orders(){
			tud.receive_orders();
			xTaskNotifyGive(threads[1]->get_handle());
			vTaskDelete(NULL);
		}
		void run_all_tests(){
			for(;;){
				xTaskNotifyWait(pdFALSE,ULONG_MAX,NULL,portMAX_DELAY);
				tud.run_tests();
			}

		}
		void flash_booting_led(){
			auto ref = rtos::this_thread::get_time_reference();
			uint32_t val = 0;
			for(;;)
			{
				if(not is_first_run){
					xTaskNotifyWait(0,ULONG_MAX,&val,portMAX_DELAY);
				}				
				for(int i = 0; i < 10;i++)
				{
					ref = rtos::this_thread::get_time_reference();
					booting_led.toggle();
					rtos::this_thread::sleep_for(&ref,500);
					
				}
				is_first_run = false;
				xTaskNotifyGive(threads[0]->get_handle());

			}
		}
		void add_thread(rtos::thread* t){
			threads[index] = t;
			index++;
		}
	private:
		int index{};
		DigitalOutput booting_led;
		DigitalOutput testing_led;
		std::array<rtos::thread*,2> threads{};
		bool is_first_run{true};
		TUD tud;
};

Monolithic* mono;

int main(void)
{
	mono = new Monolithic();
	// Declare peripherals to be used
	//Monolithic* monolithic = new Monolithic();
	// All peripherals must have been declared before calling start()
	STLIB::start();
	//define tasks for FreeRTOS
	rtos::thread* t  = new rtos::thread(&Monolithic::receive_orders,"receiving",512,1,mono);
	rtos::thread* t2 = new rtos::thread(&Monolithic::run_all_tests,"running",512,1,mono);
	mono->add_thread(t);
	mono->add_thread(t2);
	//start the freeRTOS task scheduler
	//any code below vTaskStartScheduler will NOT execute
	vTaskStartScheduler();

}

void Error_Handler(void)
{
	ErrorHandler("HAL error handler triggered");
	while (1){}
}
