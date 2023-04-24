#include "main.h"
#include "lwip.h"
#include "ST-LIB.hpp"
#include "Runes/Runes.hpp"
#include "LCU.hpp"
#include "Examples/examples_includes.hpp"

float duty_cycle, frequency;

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

void change_duty_cycle(){
	toggle_led();
	if(LCUMaster::LCU_MASTER.lcu_actuators.EMS_2_H1.duty_cycle>0){
		LCUMaster::LCU_MASTER.lcu_actuators.EMS_2_H1.set_duty_cycle(duty_cycle);
	}else{
		LCUMaster::LCU_MASTER.lcu_actuators.EMS_2_H2.set_duty_cycle(duty_cycle);
	}
	Time::set_timeout(500, toggle_led);
}

void change_frequency(){
	toggle_led();
	if(LCUMaster::LCU_MASTER.lcu_actuators.EMS_2_H1.duty_cycle>0){
		LCUMaster::LCU_MASTER.lcu_actuators.EMS_2_H1.set_frequency(frequency);
	}else{
		LCUMaster::LCU_MASTER.lcu_actuators.EMS_2_H2.set_frequency(frequency);
	}
	Time::set_timeout(500, toggle_led);
}

void start_commuting(){
	toggle_led();
	LCUMaster::LCU_MASTER.lcu_actuators.HEMS_2_H1.set_duty_cycle(duty_cycle);
	LCUMaster::LCU_MASTER.lcu_actuators.HEMS_2_H1.set_frequency(frequency);
	LCUMaster::LCU_MASTER.lcu_actuators.EMS_2_H1.set_duty_cycle(100);
	LCUMaster::LCU_MASTER.lcu_actuators.EMS_2_H1.set_frequency(frequency);
	Time::set_timeout(500, toggle_led);
}

void stop_commuting(){
	toggle_led();
	LCUMaster::LCU_MASTER.lcu_actuators.HEMS_2_H1.set_duty_cycle(0);
	LCUMaster::LCU_MASTER.lcu_actuators.HEMS_2_H2.set_duty_cycle(0);
	LCUMaster::LCU_MASTER.lcu_actuators.EMS_2_H1.set_duty_cycle(0);
	LCUMaster::LCU_MASTER.lcu_actuators.EMS_2_H2.set_duty_cycle(0);
	Time::set_timeout(500, toggle_led);
}

void invert_current_sense(){
	toggle_led();
	if(LCUMaster::LCU_MASTER.lcu_actuators.EMS_2_H1.duty_cycle>0){
		float temp = LCUMaster::LCU_MASTER.lcu_actuators.EMS_2_H1.duty_cycle;
		LCUMaster::LCU_MASTER.lcu_actuators.EMS_2_H1.set_duty_cycle(0);
		LCUMaster::LCU_MASTER.lcu_actuators.HEMS_2_H1.set_duty_cycle(0);
		LCUMaster::LCU_MASTER.lcu_actuators.HEMS_2_H2.set_duty_cycle(100);
		LCUMaster::LCU_MASTER.lcu_actuators.EMS_2_H2.set_duty_cycle(temp);
		LCUMaster::LCU_MASTER.lcu_actuators.EMS_2_H2.set_frequency(frequency);
	}else{
		float temp = LCUMaster::LCU_MASTER.lcu_actuators.EMS_2_H2.duty_cycle;
		LCUMaster::LCU_MASTER.lcu_actuators.EMS_2_H2.set_duty_cycle(0);
		LCUMaster::LCU_MASTER.lcu_actuators.HEMS_2_H2.set_duty_cycle(0);
		LCUMaster::LCU_MASTER.lcu_actuators.HEMS_2_H1.set_duty_cycle(100);
		LCUMaster::LCU_MASTER.lcu_actuators.EMS_2_H1.set_duty_cycle(temp);
		LCUMaster::LCU_MASTER.lcu_actuators.EMS_2_H1.set_frequency(frequency);

	}
	Time::set_timeout(500, toggle_led);
}

LCUMaster LCUMaster::LCU_MASTER;
int main(void)
{

	ProtectionManager_add_protection(&LCUMaster::LCU_MASTER.control_state, NOT_EQUALS, true);
	[[maybe_unused]]StackOrder<0> take_off_order = {
			300,
			take_off
	};

	[[maybe_unused]]StackOrder<0> landing_order = {
			301,
			landing
	};

	[[maybe_unused]]StackOrder<0> stick_down_order = {
			302,
			stick_down
	};

	[[maybe_unused]]StackOrder<0> stick_up_order = {
			303,
			stick_up
	};

	[[maybe_unused]]StackOrder<0> set_parameters_order = {
			304,
			set_parameters
	};

	[[maybe_unused]]StackOrder start_commuting_order = {
			320,
			start_commuting,
			&duty_cycle,
			&frequency
	};
	[[maybe_unused]]StackOrder<0> stop_commuting_order = {
			321,
			stop_commuting
	};
	[[maybe_unused]]StackOrder<0> invert_current_sense_order = {
			322,
			invert_current_sense
	};

	[[maybe_unused]]StackOrder change_duty_cycle_order = {323,change_duty_cycle ,&duty_cycle};
	[[maybe_unused]]StackOrder change_duty_frequency_order = {324,change_frequency ,&frequency};

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
