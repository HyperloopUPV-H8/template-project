#include "main.h"
#include "lwip.h"

#include "ST-LIB.hpp"
#include "Runes/Runes.hpp"
#include "DigitalOutput/DigitalOutput.hpp"
#include "Communication/Ethernet/TCP/ServerSocket.hpp"
	DigitalOutput high_pressure_indicator;
	DigitalOutput pressure_data_incoming;
	float pressure;
void check_pressure(){
	if(pressure > 20)
	{		
		high_pressure_indicator.turn_on();
	}
	pressure +=1.0;

		pressure_data_incoming.toggle();
}

int main(void)
{

	high_pressure_indicator = DigitalOutput(PB14);
	pressure_data_incoming = DigitalOutput(PB0);
	DigitalOutput connect = DigitalOutput(PE1);
	
	STLIB::start("192.168.0.3");
	
	ServerSocket server(IPV4{"192.168.0.3"},30000);
	bool first_time = true;
	pressure = 0.0f;
	StackOrder pressure_order(69,check_pressure,&pressure);


	while(1) {
		STLIB::update();
		if( first_time && server.is_connected()){
			connect.turn_on();
			first_time = false;
		}
		if(server.is_connected()){
			server.send_order(pressure_order);	
			HAL_Delay(100);
		}
	}
}

void Error_Handler(void)
{
	ErrorHandler("HAL error handler triggered");
	while (1){}
}
