///*
// * CurrentControl.hpp
// *
// *  Created on: Apr 15, 2023
// *      Author: stefancostea
// */
//
//#ifndef INC_CURRENTCONTROL_HPP_
//#define INC_CURRENTCONTROL_HPP_
//
//#include "ST-LIB.hpp"
//
//class CurrentControl{
//public:
//	PI current_pi;
//	Saturator<float> target_voltage_saturator;
//	float reference_current = 10;
//	PWM& positive_h, negative_h;
//	float target_voltage;
//	const float battery_voltage = 20;
//	float target_duty_cyle;
//	CurrentControl(PWM& positive_h, PWM& negative_h){
//		current_pi.set_kp(20);
//		current_pi.set_ki(200);
//		target_voltage_saturator = Saturator(0,-200,200);
//	}
//
//	void set_reference_current(float new_reference){
//		reference_current = new_reference;
//	}
//
//	void control(float real_current){
//		current_pi.input(reference_current - real_current);
//		target_voltage_saturator.input(current_pi.output_value);
//		target_voltage = target_voltage_saturator.output_value;
//		calculate_duty();
//		apply_control();
//	}
//	void calculate_duty(){
//		target_duty_cyle = target_voltage/battery_voltage;
//	}
//
//	void apply_control(){
//		if(target_duty_cyle>0){
//			positive_h.set_duty_cycle(abs(target_duty_cyle));
//		}else{
//			negative_h.set_duty_cycle(abs(target_duty_cyle));
//		}
//	}
//
//
//
//};





#endif /* INC_CURRENTCONTROL_HPP_ */
