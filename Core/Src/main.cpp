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

void start_commuting(){
	toggle_led();
	LCUMaster::LCU_MASTER.lcu_actuators.HEMS_2_H1.set_duty_cycle(40);
	Time::set_timeout(500, toggle_led);
}

void stop_commuting(){
	toggle_led();
	LCUMaster::LCU_MASTER.lcu_actuators.HEMS_2_H1.set_duty_cycle(0);
	LCUMaster::LCU_MASTER.lcu_actuators.HEMS_2_H2.set_duty_cycle(0);
	Time::set_timeout(500, toggle_led);
}

void invert_current_sense(){
	if(LCUMaster::LCU_MASTER.lcu_actuators.HEMS_2_H1.duty_cycle>0){
		float temp = LCUMaster::LCU_MASTER.lcu_actuators.HEMS_2_H1.duty_cycle;
		LCUMaster::LCU_MASTER.lcu_actuators.HEMS_2_H1.set_duty_cycle(0);
		LCUMaster::LCU_MASTER.lcu_actuators.HEMS_2_H2.set_duty_cycle(temp);
	}else{
		float temp = LCUMaster::LCU_MASTER.lcu_actuators.HEMS_2_H2.duty_cycle;
		LCUMaster::LCU_MASTER.lcu_actuators.HEMS_2_H2.set_duty_cycle(0);
		LCUMaster::LCU_MASTER.lcu_actuators.HEMS_2_H1.set_duty_cycle(temp);
	}
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

	StackOrder<0> start_commuting_order = {
			320,
			start_commuting
	};
	StackOrder<0> stop_commuting_order = {
			321,
			stop_commuting
	};
	StackOrder<0> invert_current_sense_order = {
			322,
			invert_current_sense
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
