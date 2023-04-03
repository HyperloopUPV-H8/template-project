/*
 * halfbridge_example.hpp
 *
 *  Created on: 2 Feb. 2022
 *      Author: Pablo
 */
#pragma once

#include "ST-LIB.hpp"

void halfbridge_example(){

	HalfBridge half_bridge(PE11, PE10, PE13, PE12, PB8);
	STLIB::start();

	half_bridge.turn_on();
	half_bridge.set_duty_cycle(50);
	half_bridge.set_frequency(100000);
	float my_phase = 0;
	float increase = 0.4;

	Time::register_low_precision_alarm(100, [](){
		STLIB::update();
	});

	Time::register_low_precision_alarm(10, [&](){
		half_bridge.set_phase(my_phase);
		my_phase += increase;
		if (my_phase > 99) {
			my_phase = -99;
		}
	});
	while(1) {}
}
