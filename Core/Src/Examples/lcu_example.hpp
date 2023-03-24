/*
 * adc_example.hpp
 *
 *  Created on: 30 Jan. 2022
 *      Author: Pablo
 */
#pragma once

#include "ST-LIB.hpp"


int lcu_example(void)
{
	uint8_t adc1 = ADC::inscribe(PF5).value();
	uint8_t adc2 = ADC::inscribe(PF6).value();
	uint8_t adc3 = ADC::inscribe(PF7).value();
	uint8_t adc4 = ADC::inscribe(PF8).value();
	uint8_t adc5 = ADC::inscribe(PF9).value();
	uint8_t adc6 = ADC::inscribe(PF10).value();
	uint8_t adc7 = ADC::inscribe(PF11).value();
	uint8_t adc8 = ADC::inscribe(PF12).value();
	uint8_t adc9 = ADC::inscribe(PF13).value();
	uint8_t adc10 = ADC::inscribe(PA0).value();
	uint8_t adc11 = ADC::inscribe(PA3).value();
	uint8_t adc12 = ADC::inscribe(PA4).value();
	uint8_t adc13 = ADC::inscribe(PA5).value();
	uint8_t adc14 = ADC::inscribe(PA6).value();



	uint8_t pwm1 = PWMservice::inscribe(PF1).value();
	uint8_t pwm2 = PWMservice::inscribe(PF2).value();
	uint8_t pwm3 = PWMservice::inscribe(PF3).value();

	STLIB::start(Nucleo, "192.168.1.4", "255.255.0.0", "192.168.1.1", UART::uart2);
	DatagramSocket socket = DatagramSocket("192.168.1.4", 6969, "192.168.1.3", 6969);


	ADC::turn_on(adc1);
	ADC::turn_on(adc2);
	ADC::turn_on(adc3);
	ADC::turn_on(adc5);
	ADC::turn_on(adc6);
	ADC::turn_on(adc7);
	ADC::turn_on(adc8);
	ADC::turn_on(adc9);
	ADC::turn_on(adc10);

	ADC::turn_on(adc11);
	ADC::turn_on(adc12);
	ADC::turn_on(adc13);
	ADC::turn_on(adc14);

	PWMservice::turn_on(pwm1);
	PWMservice::turn_on(pwm2);
	PWMservice::turn_on(pwm3);

	Time::register_high_precision_alarm(100, [&](){
		 double value1 = sin(cos(tan( ADC::get_value(adc1).value())));
		 double value2 = sin(cos(tan( ADC::get_value(adc2).value())));
		 double value3 = sin(cos(tan( ADC::get_value(adc3).value())));
		 double value4 = sin(cos(tan( ADC::get_value(adc4).value())));
		 double value5 = sin(cos(tan( ADC::get_value(adc5).value())));
		 double value6 = sin(cos(tan( ADC::get_value(adc6).value())));
		 double value7 = sin(cos(tan( ADC::get_value(adc7).value())));
		 double value8 = sin(cos(tan( ADC::get_value(adc8).value())));
		 double value9 = sin(cos(tan( ADC::get_value(adc9).value())));
		 double value10 = sin(cos(tan( ADC::get_value(adc10).value())));

		 double value11 = sin(cos(tan( ADC::get_value(adc11).value())));
		 double value12 = sin(cos(tan( ADC::get_value(adc12).value())));
		 double value13 = sin(cos(tan( ADC::get_value(adc13).value())));
		 double value14 = sin(cos(tan( ADC::get_value(adc14).value())));
		//42

//		 double value1 = sin(cos(tan( 1)));
//		 double value2 = sin(cos(tan( 2)));
//		 double value3 = sin(cos(tan( 3)));
//		 double value4 = sin(cos(tan( 4)));
//		 double value5 = sin(cos(tan( 5)));
//		 double value6 = sin(cos(tan( 6)));
//		 double value7 = sin(cos(tan( 7)));
//		 double value8 = sin(cos(tan( 8)));
//		 double value9 = sin(cos(tan( 9)));
//		 double value10 = sin(cos(tan( 10)));
//
//		 double value11 = sin(cos(tan( 11)));
//		 double value12 = sin(cos(tan( 12)));
//		 double value13 = sin(cos(tan( 13)));
//		 double value14 = sin(cos(tan( 14)));


		 Packet packet = {
				420,
				PacketValue<uint16_t>(&value1, 1),
				PacketValue<uint16_t>(&value2, 1),
				PacketValue<uint16_t>(&value3, 1),
				PacketValue<uint16_t>(&value4, 1),
				PacketValue<uint16_t>(&value5, 1),
				PacketValue<uint16_t>(&value6, 1),
				PacketValue<uint16_t>(&value7, 1),
				PacketValue<uint16_t>(&value8, 1),
				PacketValue<uint16_t>(&value9, 1),
				PacketValue<uint16_t>(&value10, 1),
		};

		Packet packet2 = {
				421,
				PacketValue<uint16_t>(&value11, 5),
				PacketValue<uint16_t>(&value12, 5),
				PacketValue<uint16_t>(&value13, 5),
				PacketValue<uint16_t>(&value14, 5),
		};

		socket.send(packet);
		socket.send(packet2);

	});

	Time::register_high_precision_alarm(100, [&](){
		PWMservice::set_duty_cycle(pwm1, 50);
		PWMservice::set_duty_cycle(pwm2, 50);
		PWMservice::set_duty_cycle(pwm3, 50);

		STLIB::update();
	});

	// 56

//	double data = 1234.0;
//	Packet packet = {
//			69,
//			PacketValue<uint16_t>(&data, 1),
//	};

	while (1) {
//		STLIB::update();
//		socket.send(packet);
		
	}
}
