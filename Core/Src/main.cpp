#include "main.h"
#include "lwip.h"

#include "ST-LIB.hpp"
#include "Runes/Runes.hpp"

DigitalOutput *led;
const uint16_t size = 1000;
uint16_t data_size = size;
int16_t data_array[size]{0};
int16_t data_result[size]{0};

void tog(){
	led->toggle();
}

int main(void)
{
	led = new DigitalOutput(PE1);
	for(int i = 0; i < data_size; i++){
		data_array[i] = 10000 + i;
	}

	MultiplierAccelerator::FIR_software_in_software_out_inscribe(2,8,8);
	STLIB::start("192.168.0.14");
	//StackOrder out(1404,MultiplierAccelerator::MemoryLayout.OutValues[0]);
	Server server("192.168.0.14",50500);

	MultiplierAccelerator::MemoryLayout.FFilterCoeffs[0] = 32767;
	MultiplierAccelerator::MemoryLayout.FFilterCoeffs[1] = 32767;
	while(!MultiplierAccelerator::is_ready()){}
	MultiplierAccelerator::software_preload(MultiplierAccelerator::MemoryLayout.FInValues);
	while(!MultiplierAccelerator::is_ready()){}
	MultiplierAccelerator::software_process(data_result, &data_size);
	while(!MultiplierAccelerator::is_ready()){}
	MultiplierAccelerator::software_load(data_array, &data_size);
	while(!MultiplierAccelerator::is_ready()){}
	MultiplierAccelerator::software_end_process();


	//Time::register_low_precision_alarm(100, [&](){server.broadcast_order(out);});
	while(1) {
		STLIB::update();

	}
}

void Error_Handler(void)
{
	ErrorHandler("HAL error handler triggered");
	while (1){}
}
