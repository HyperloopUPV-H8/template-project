#include "main.h"
#include "lwip.h"
#include "ST-LIB.hpp"
#include "Runes/Runes.hpp"
#include "LCU.hpp"
#include "Examples/examples_includes.hpp"

void toggle_led(){
	LCUMaster::LCU_MASTER.lcu_actuators.fault_led.toggle();
}

void take_off(){
	toggle_led();
	Time::set_timeout(500, toggle_led);
}

void landing(){
	toggle_led();
	Time::set_timeout(500, toggle_led);
}

void stick_down(){
	toggle_led();
	Time::set_timeout(500, toggle_led);
}

void stick_up(){
	toggle_led();
	Time::set_timeout(500, toggle_led);
}

void set_parameters(){
	toggle_led();
	Time::set_timeout(500, toggle_led);
}

void set_slave_parameters(){
	toggle_led();
	Time::set_timeout(500, toggle_led);
}

LCUMaster LCUMaster::LCU_MASTER;
int main(void)
{
	StackOrder<0> take_off_order = {
			300,
			take_off
	};

	StackOrder<0> landing_order = {
			301,
			landing
	};

	StackOrder<0> stick_down_order = {
			302,
			stick_down
	};

	StackOrder<0> stick_up_order = {
			303,
			stick_up
	};

	StackOrder<0> set_parameters_order = {
			304,
			set_parameters
	};
	LCUMaster& LCU = LCUMaster::LCU_MASTER;
	LCU.start();
	ServerSocket tcp_server(IPV4("192.168.1.4"),50500);
	while(1);
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
