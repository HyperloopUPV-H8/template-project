/*
 * LCU.hpp
 *
 *  Created on: Apr 6, 2023
 *      Author: stefa
 */

#pragma once

#include "main.h"
#include "lwip.h"
#include "ST-LIB.hpp"
#include "../Src/Runes/Runes.hpp"

class LCUMaster{
public:
	static LCUMaster LCU_MASTER;

	LCUMaster() = default;
	void operator=(LCUMaster&& other){
		memcpy(this,&other,sizeof(LCUMaster));
	}

	enum General_SM_States : uint8_t {
		INITIAL,
		OPERATIONAL,
		FAULT
	};

	DigitalOutput sleep_led;
	DigitalOutput can_led;
	DigitalOutput flash_led;
	DigitalOutput fault_led;
	DigitalOutput operational_led;

	float coil_current_hems_1;
	float coil_current_hems_3;
	float coil_current_ems_1 ;
	float coil_current_ems_3 ;

	float slave_coil_current_hems_2;
	float slave_coil_current_hems_4;
	float slave_coil_current_ems_2 ;
	float slave_coil_current_ems_4 ;

	float coil_temp_1;
	float coil_temp_2;
	float coil_temp_3;
	float coil_temp_4;

	float slave_coil_temp_1;
	float slave_coil_temp_2;
	float slave_coil_temp_3;
	float slave_coil_temp_4;

	float lpu_temp_1;
	float lpu_temp_2;
	float lpu_temp_3;
	float lpu_temp_4 ;

	float slave_lpu_temp_1;
	float slave_lpu_temp_2;
	float slave_lpu_temp_3;
	float slave_lpu_temp_4 ;

	float batt_current_1;
	float batt_current_2 ;

	float slave_batt_current_1;
	float slave_batt_current_2;

	float batt_voltage_1;
	float batt_voltage_2;

	float slave_batt_voltage_1;
	float slave_batt_voltage_2;

	float airgap_1;
	float airgap_3;
	float airgap_5;
	float airgap_7;

	float slave_airgap_2;
	float slave_airgap_4;
	float slave_airgap_6;
	float slave_airgap_8;

	double rotx = 0;
	double roty = 0;
	double rotz = 0;

	double reference_current_hems_1 = 0;
	double reference_current_hems_3 = 0;
	double reference_current_ems_1 = 0;
	double reference_current_ems_3 = 0;

	double slave_reference_current_hems_2 = 0;
	double slave_reference_current_hems_4 = 0;
	double slave_reference_current_ems_2 = 0;
	double slave_reference_current_ems_4 = 0;

	StateMachine general_sm = StateMachine(General_SM_States::INITIAL);

	uint8_t& general_state = general_sm.current_state;

	uint8_t slave_general_state;

	uint8_t specific_state = 0;

	uint8_t slave_specific_state = 0;

	bool control_state;

	DatagramSocket vcu_udp;

	ServerSocket tcp_server;

public:
	static void take_off(){
		LCU_MASTER.flash_led.toggle();
	}

	static void landing(){
		LCU_MASTER.flash_led.toggle();
	}

	static void stick_down(){
		LCU_MASTER.flash_led.toggle();
	}

	static void stick_up(){
		LCU_MASTER.flash_led.toggle();
	}

	static void set_parameters(){
		LCU_MASTER.flash_led.toggle();
	}

	static void set_slave_parameters(){
		LCU_MASTER.flash_led.toggle();
	}
public:
	Order<> take_off_order = {
			300,
			take_off
	};

	Order<> landing_order = {
			301,
			landing
	};

	Order<> stick_down_order = {
			302,
			stick_down
	};

	Order<> stick_up_order = {
			303,
			stick_up
	};

	Order<> set_parameters_order = {
			304,
			set_parameters
	};

	Order<> set_slave_parameters_order = {
			305,
			set_slave_parameters
	};

	Packet<uint8_t,uint8_t,uint8_t,uint8_t,bool> state_machine_data = {
			306,
			PacketValue(&general_state),
			PacketValue(&slave_general_state),
			PacketValue(&specific_state),
			PacketValue(&slave_specific_state),
			PacketValue(&control_state)
	};

	Packet<float,float,float,float,float,float,float,float> airgaps_data{
		307,
		PacketValue(&airgap_1),
		PacketValue(&airgap_3),
		PacketValue(&airgap_5),
		PacketValue(&airgap_7),
		PacketValue(&slave_airgap_2),
		PacketValue(&slave_airgap_4),
		PacketValue(&slave_airgap_6),
		PacketValue(&slave_airgap_8)
	};

	Packet<float,float,float,float,float,float,float,float> coil_currents{
		313,
		PacketValue(&coil_current_hems_1),
		PacketValue(&coil_current_hems_3),
		PacketValue(&coil_current_ems_1),
		PacketValue(&coil_current_ems_3),
		PacketValue(&slave_coil_current_hems_2),
		PacketValue(&slave_coil_current_hems_4),
		PacketValue(&slave_coil_current_ems_2),
		PacketValue(&slave_coil_current_ems_4),
	};

	Packet<float,float,float,float,float,float,float,float> coil_temperatures{
		310,
		PacketValue(&coil_temp_1),
		PacketValue(&coil_temp_2),
		PacketValue(&coil_temp_3),
		PacketValue(&coil_temp_4),
		PacketValue(&slave_coil_temp_1),
		PacketValue(&slave_coil_temp_2),
		PacketValue(&slave_coil_temp_3),
		PacketValue(&slave_coil_temp_4),
	};

	Packet<float,float,float,float,float,float,float,float> lpu_temperatures{
		314,
		PacketValue(&lpu_temp_1),
		PacketValue(&lpu_temp_2),
		PacketValue(&lpu_temp_3),
		PacketValue(&lpu_temp_4),
		PacketValue(&slave_lpu_temp_1),
		PacketValue(&slave_lpu_temp_2),
		PacketValue(&slave_lpu_temp_3),
		PacketValue(&slave_lpu_temp_4),
	};

	Packet<float,float,float,float,float,float,float,float> battery_data{
		312,
		PacketValue(&batt_voltage_1),
		PacketValue(&batt_voltage_2),
		PacketValue(&slave_batt_voltage_1),
		PacketValue(&slave_batt_voltage_2),
		PacketValue(&batt_current_1),
		PacketValue(&batt_current_2),
		PacketValue(&slave_batt_current_1),
		PacketValue(&slave_batt_current_2),
	};


	Packet<double,double,double,double,double,double,double,double,double,double,double>
	levitation_data = {
		311,
		PacketValue(&reference_current_hems_1),
		PacketValue(&reference_current_hems_3),
		PacketValue(&reference_current_ems_1),
		PacketValue(&reference_current_ems_3),
		PacketValue(&slave_reference_current_hems_2),
		PacketValue(&slave_reference_current_hems_4),
		PacketValue(&slave_reference_current_ems_2),
		PacketValue(&slave_reference_current_ems_4),
		PacketValue(&rotx),
		PacketValue(&roty),
		PacketValue(&rotz),
	};

public:
	uint8_t cur_hems_1_id = 0;
	uint8_t cur_hems_3_id = 0;
	uint8_t cur_ems_1_id = 0;
	uint8_t cur_ems_3_id = 0;

	uint8_t coil_temp_1_id = 0;
	uint8_t coil_temp_2_id = 0;
	uint8_t coil_temp_3_id = 0;
	uint8_t coil_temp_4_id = 0;

	uint8_t lpu_temp_1_id = 0;
	uint8_t lpu_temp_2_id = 0;
	uint8_t lpu_temp_3_id = 0;
	uint8_t lpu_temp_4_id = 0;

	uint8_t batt_cur_1_id = 0;
	uint8_t batt_cur_2_id = 0;

	uint8_t batt_volt_1_id = 0;
	uint8_t batt_volt_2_id = 0;

	uint8_t airgap_1_id = 0;
	uint8_t airgap_3_id = 0;
	uint8_t airgap_5_id = 0;
	uint8_t airgap_7_id = 0;
	void inscribe_leds(){
		sleep_led = DigitalOutput(PG4);
		can_led = DigitalOutput(PG5);
		flash_led = DigitalOutput(PG6);
		fault_led = DigitalOutput(PG7);
		operational_led = DigitalOutput(PG8);
	}

	void inscribe_adcs(){
		cur_hems_1_id = ADC::inscribe(PB0).value();
		cur_hems_3_id = ADC::inscribe(PB1).value();
		cur_ems_1_id = ADC::inscribe(PF11).value();
		cur_ems_3_id = ADC::inscribe(PF12).value();

		coil_temp_1_id = ADC::inscribe(PF5).value();
		coil_temp_2_id = ADC::inscribe(PF6).value();
		coil_temp_3_id = ADC::inscribe(PF7).value();
		coil_temp_4_id = ADC::inscribe(PF8).value();

		lpu_temp_1_id = ADC::inscribe(PC2).value();
		lpu_temp_2_id = ADC::inscribe(PC3).value();
		lpu_temp_3_id = ADC::inscribe(PF9).value();
		lpu_temp_4_id = ADC::inscribe(PF10).value();

		batt_cur_1_id = ADC::inscribe(PC0).value();
		batt_cur_2_id = ADC::inscribe(PF13).value();

		batt_volt_1_id = ADC::inscribe(PA0).value();
		batt_volt_2_id = ADC::inscribe(PF14).value();

		airgap_1_id = ADC::inscribe(PA5).value();
		airgap_3_id = ADC::inscribe(PA6).value();
		airgap_5_id = ADC::inscribe(PA4).value();
		airgap_7_id = ADC::inscribe(PA3).value();

	}

	void turn_on_adcs(){
		ADC::turn_on(cur_hems_1_id);
		ADC::turn_on(cur_hems_3_id);
		ADC::turn_on(cur_ems_1_id);
		ADC::turn_on(cur_ems_3_id);

		ADC::turn_on(coil_temp_1_id);
		ADC::turn_on(coil_temp_2_id);
		ADC::turn_on(coil_temp_3_id);
		ADC::turn_on(coil_temp_4_id);

		ADC::turn_on(lpu_temp_1_id);
		ADC::turn_on(lpu_temp_2_id);
		ADC::turn_on(lpu_temp_3_id);
		ADC::turn_on(lpu_temp_4_id);

		ADC::turn_on(batt_cur_1_id);
		ADC::turn_on(batt_cur_2_id);

		ADC::turn_on(batt_volt_1_id);
		ADC::turn_on(batt_volt_2_id);

		ADC::turn_on(airgap_1_id);
		ADC::turn_on(airgap_3_id);
		ADC::turn_on(airgap_5_id);
		ADC::turn_on(airgap_7_id);
	}

	void read_adcs(){
		coil_current_hems_1 = ADC::get_value(cur_hems_1_id).value();
		coil_current_hems_3 = ADC::get_value(cur_hems_3_id).value();
		coil_current_ems_1 = ADC::get_value(cur_ems_1_id).value();
		coil_current_ems_3 = ADC::get_value(cur_ems_3_id).value();

		coil_temp_1 = ADC::get_value(coil_temp_1_id).value();
		coil_temp_2 = ADC::get_value(coil_temp_2_id).value();
		coil_temp_3 = ADC::get_value(coil_temp_3_id).value();
		coil_temp_4 = ADC::get_value(coil_temp_4_id).value();

		lpu_temp_1 = ADC::get_value(lpu_temp_1_id).value();
		lpu_temp_2 = ADC::get_value(lpu_temp_2_id).value();
		lpu_temp_3 = ADC::get_value(lpu_temp_3_id).value();
		lpu_temp_4 = ADC::get_value(lpu_temp_4_id).value();

		batt_current_1 = ADC::get_value(batt_cur_1_id).value();
		batt_current_2 = ADC::get_value(batt_cur_2_id).value();

		batt_voltage_1 = ADC::get_value(batt_volt_1_id).value();
		batt_voltage_2 = ADC::get_value(batt_volt_2_id).value();

		airgap_1 = ADC::get_value(airgap_1_id).value();
		airgap_3 = ADC::get_value(airgap_3_id).value();
		airgap_5 = ADC::get_value(airgap_5_id).value();
		airgap_7 = ADC::get_value(airgap_7_id).value();
	}

	void setup_state_machine(){
		general_sm.add_state(General_SM_States::OPERATIONAL);
		general_sm.add_state(General_SM_States::FAULT);
	}

	void set_protections(){

	}

	void configure_connections(){
		vcu_udp = DatagramSocket("192.168.1.4",0,"192.168.1.3",0);
	}

//	void register_cyclic_actions(){
//		Time::register_low_precision_alarm(16, [&,this](){
//
//		});
//	}

	void start(){
		setup_state_machine();
		inscribe_leds();
		inscribe_adcs();
		STLIB::start( "192.168.1.4", "255.255.255.0", "192.168.1.1");
		turn_on_adcs();
		configure_connections();
//		register_cyclic_actions();
	}

	void update(){
		read_adcs();
		STLIB::update();
	}
};

