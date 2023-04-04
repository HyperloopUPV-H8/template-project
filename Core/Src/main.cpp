#include "main.h"
#include "lwip.h"

#include "ST-LIB.hpp"
#include "Runes/Runes.hpp"
#include "Examples/examples_includes.hpp"

extern struct netif gnetif;

int main(void)
{
	PWM pwm1(PB14);

	STLIB::start();

	uint8_t duty_cycle = 50;
	pwm1.set_duty_cycle(duty_cycle);
	pwm1.turn_on();

	DatagramSocket socket = DatagramSocket("192.168.1.4", 6969, "192.168.1.3", 6969);

	double data = 1234.0;
	Packet packet = {
			69,
			PacketValue<uint16_t>(&data, 1),
	};

	socket.send(packet);
	while(1) {
		if (duty_cycle > 95) duty_cycle = 0;
		duty_cycle++;
		pwm1.set_duty_cycle(duty_cycle);
		HAL_Delay(10);
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
