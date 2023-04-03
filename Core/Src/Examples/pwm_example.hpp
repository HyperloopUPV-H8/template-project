/*
 * adc_example.hpp
 *
 *  Created on: 30 Jan. 2022
 *      Author: Alejandro
 */
#pragma once

#include "ST-LIB.hpp"

int pwm_example(void)
{
	PWM pwm1(PB15);
	PhasedPWM phased_pwm1(PB4);
	PhasedPWM phased_pwm2(PE14);
	DualPhasedPWM dp_pwm(PE11, PE10);
	DualPhasedPWM dp_pwm2(PE13, PE12);
	STLIB::start();

	pwm1.turn_on();
	pwm1.set_duty_cycle(50);

	dp_pwm.turn_on();
	dp_pwm.set_duty_cycle(50);

	dp_pwm2.turn_on();
	dp_pwm2.set_duty_cycle(50);

	phased_pwm1.turn_on();
	phased_pwm1.set_duty_cycle(50);

	phased_pwm2.turn_on();
	phased_pwm2.set_duty_cycle(50);

	float my_phase = 50;
	float increase = 0.1;

	Time::register_low_precision_alarm(10, [&](){
		STLIB::update();

		dp_pwm2.set_phase(my_phase);
		dp_pwm.set_phase(-my_phase);

		my_phase += increase;
		increase += 0.005;
		if (my_phase > 99) {
			my_phase = 1;
			increase = 0.1;
		}
	});

	while (1) {

	}
}
