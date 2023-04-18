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

	void take_off();

	void landing();

	void stick_down();

	void stick_up();

	void set_parameters();

	void set_slave_parameters();

struct LCUMasterData{
	float coil_current_hems_1 = 0;
	float coil_current_hems_3 = 0;
	float coil_current_ems_1 = 0;
	float coil_current_ems_3  = 0;

	float slave_coil_current_hems_2 = 0;
	float slave_coil_current_hems_4 = 0;
	float slave_coil_current_ems_2 = 0;
	float slave_coil_current_ems_4 = 0;

	float coil_temp_1 = 0;
	float coil_temp_2 = 0;
	float coil_temp_3 = 0;
	float coil_temp_4 = 0;

	float slave_coil_temp_1 = 0;
	float slave_coil_temp_2 = 0;
	float slave_coil_temp_3 = 0;
	float slave_coil_temp_4 = 0;

	float lpu_temp_1 = 0;
	float lpu_temp_2 = 0;
	float lpu_temp_3 = 0;
	float lpu_temp_4 = 0;

	float slave_lpu_temp_1 = 0;
	float slave_lpu_temp_2 = 0;
	float slave_lpu_temp_3 = 0;
	float slave_lpu_temp_4 = 0;

	float batt_current_1 = 0;
	float batt_current_2 = 0;

	float slave_batt_current_1 = 0;
	float slave_batt_current_2 = 0;

	float batt_voltage_1 = 0;
	float batt_voltage_2 = 0;

	float slave_batt_voltage_1 = 0;
	float slave_batt_voltage_2 = 0;

	float airgap_1 = 0;
	float airgap_3 = 0;
	float airgap_5 = 0;
	float airgap_7 = 0;

	float slave_airgap_2 = 0;
	float slave_airgap_4 = 0;
	float slave_airgap_6 = 0;
	float slave_airgap_8 = 0;

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

	void set_protections(){

	}
};

LCUMasterData LCU_data;

class LCUActuators{
public:
	DigitalOutput buffer_enable;

	DigitalOutput sleep_led;
	DigitalOutput can_led;
	DigitalOutput flash_led;
	DigitalOutput fault_led;
	DigitalOutput operational_led;

	PWM HEMS_2_H1;
	PWM HEMS_2_H2;

	void inscribe_digital_outputs(){
		sleep_led = DigitalOutput(PG4);
		can_led = DigitalOutput(PG5);
		flash_led = DigitalOutput(PG6);
		fault_led = DigitalOutput(PG7);
		operational_led = DigitalOutput(PG8);

		buffer_enable = DigitalOutput(PD14);

		HEMS_2_H1 = PWM(PE11);
		HEMS_2_H2 = PWM(PE5);
	}

	void start(){
		buffer_enable.turn_off();
		HEMS_2_H1.turn_on();
		HEMS_2_H2.turn_on();
		HEMS_2_H1.set_frequency(30000);
		HEMS_2_H2.set_frequency(30000);
		HEMS_2_H1.set_duty_cycle(0);
		HEMS_2_H2.set_duty_cycle(0);
	}
};

LCUActuators LCU_actuators;

class LCUSensors{
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

	static void read_adcs();
};

LCUSensors LCU_sensors;

void LCUSensors::read_adcs(){
		LCU_data.coil_current_hems_1 = ADC::get_value(LCU_sensors.cur_hems_1_id);
		LCU_data.coil_current_hems_3 = ADC::get_value(LCU_sensors.cur_hems_3_id);
		LCU_data.coil_current_ems_1 = ADC::get_value(LCU_sensors.cur_ems_1_id);
		LCU_data.coil_current_ems_3 = ADC::get_value(LCU_sensors.cur_ems_3_id);

		LCU_data.coil_temp_1 = ADC::get_value(LCU_sensors.coil_temp_1_id);
		LCU_data.coil_temp_2 = ADC::get_value(LCU_sensors.coil_temp_2_id);
		LCU_data.coil_temp_3 = ADC::get_value(LCU_sensors.coil_temp_3_id);
		LCU_data.coil_temp_4 = ADC::get_value(LCU_sensors.coil_temp_4_id);

		LCU_data.lpu_temp_1 = ADC::get_value(LCU_sensors.lpu_temp_1_id);
		LCU_data.lpu_temp_2 = ADC::get_value(LCU_sensors.lpu_temp_2_id);
		LCU_data.lpu_temp_3 = ADC::get_value(LCU_sensors.lpu_temp_3_id);
		LCU_data.lpu_temp_4 = ADC::get_value(LCU_sensors.lpu_temp_4_id);

		LCU_data.batt_current_1 = ADC::get_value(LCU_sensors.batt_cur_1_id);
		LCU_data.batt_current_2 = ADC::get_value(LCU_sensors.batt_cur_2_id);

		LCU_data.batt_voltage_1 = ADC::get_value(LCU_sensors.batt_volt_1_id);
		LCU_data.batt_voltage_2 = ADC::get_value(LCU_sensors.batt_volt_2_id);
		LCU_data.airgap_1 = ADC::get_value(LCU_sensors.airgap_1_id);
		LCU_data.airgap_3 = ADC::get_value(LCU_sensors.airgap_3_id);
		LCU_data.airgap_5 = ADC::get_value(LCU_sensors.airgap_5_id);
		LCU_data.airgap_7 = ADC::get_value(LCU_sensors.airgap_7_id);
}

class LCUUDP{
public:
	DatagramSocket vcu_udp;
//
//	StackPacket<5,uint8_t,uint8_t,uint8_t,uint8_t,bool> state_machine_data = {
//		306,
//		&LCU.general_state,
//		&LCU_data.slave_general_state,
//		&LCU_data.specific_state,
//		&LCU_data.slave_specific_state,
//		&LCU_data.control_state
//	};

	StackPacket<32,float,float,float,float,float,float,float,float> airgaps_data{
		307,
		&LCU_data.airgap_1,
		&LCU_data.airgap_3,
		&LCU_data.airgap_5,
		&LCU_data.airgap_7,
		&LCU_data.slave_airgap_2,
		&LCU_data.slave_airgap_4,
		&LCU_data.slave_airgap_6,
		&LCU_data.slave_airgap_8
	};

	StackPacket<32,float,float,float,float,float,float,float,float> coil_currents{
		313,
		&LCU_data.coil_current_hems_1,
		&LCU_data.coil_current_hems_3,
		&LCU_data.coil_current_ems_1,
		&LCU_data.coil_current_ems_3,
		&LCU_data.slave_coil_current_hems_2,
		&LCU_data.slave_coil_current_hems_4,
		&LCU_data.slave_coil_current_ems_2,
		&LCU_data.slave_coil_current_ems_4
	};

	StackPacket<32,float,float,float,float,float,float,float,float> coil_temperatures{
		310,
		&LCU_data.coil_temp_1,
		&LCU_data.coil_temp_2,
		&LCU_data.coil_temp_3,
		&LCU_data.coil_temp_4,
		&LCU_data.slave_coil_temp_1,
		&LCU_data.slave_coil_temp_2,
		&LCU_data.slave_coil_temp_3,
		&LCU_data.slave_coil_temp_4
	};

	StackPacket<32,float,float,float,float,float,float,float,float> lpu_temperatures{
		314,
		&LCU_data.lpu_temp_1,
		&LCU_data.lpu_temp_2,
		&LCU_data.lpu_temp_3,
		&LCU_data.lpu_temp_4,
		&LCU_data.slave_lpu_temp_1,
		&LCU_data.slave_lpu_temp_2,
		&LCU_data.slave_lpu_temp_3,
		&LCU_data.slave_lpu_temp_4
	};

	StackPacket<32,float,float,float,float,float,float,float,float> battery_data{
		312,
		&LCU_data.batt_voltage_1,
		&LCU_data.batt_voltage_2,
		&LCU_data.slave_batt_voltage_1,
		&LCU_data.slave_batt_voltage_2,
		&LCU_data.batt_current_1,
		&LCU_data.batt_current_2,
		&LCU_data.slave_batt_current_1,
		&LCU_data.slave_batt_current_2
	};

	//	StackPacket<88,double,double,double,double,double,double,double,double,double,double,double> levitation_data = {
	//		311,
	//		&reference_current_hems_1,
	//		&reference_current_hems_3,
	//		&reference_current_ems_1,
	//		&reference_current_ems_3,
	//		&slave_reference_current_hems_2,
	//		&slave_reference_current_hems_4,
	//		&slave_reference_current_ems_2,
	//		&slave_reference_current_ems_4,
	//		&rotx,
	//		&roty,
	//		&rotz,
	//	};

public:
	void register_connections(){
		vcu_udp = DatagramSocket( IPV4("192.168.1.4"), 50400, IPV4("192.168.0.9"), 50400);
		vcu_udp.local_ip = "192.168.1.4";
		vcu_udp.local_port = 50400;
		vcu_udp.remote_ip = "192.168.0.9";
		vcu_udp.remote_port = 50400;
		vcu_udp.udp_control_block->local_ip = vcu_udp.local_ip.address;
		vcu_udp.udp_control_block->remote_ip = vcu_udp.remote_ip.address;
		vcu_udp.udp_control_block->remote_port = 50400;
		vcu_udp.udp_control_block->local_port = 50400;
	}

	static void send_all_data();
};



LCUUDP LCU_udp;

void LCUUDP::send_all_data(){
//		LCU_MASTER.vcu_udp.send(LCU_MASTER.state_machine_data);
	LCU_udp.vcu_udp.send(LCU_udp.airgaps_data);
	LCU_udp.vcu_udp.send(LCU_udp.coil_currents);
	LCU_udp.vcu_udp.send(LCU_udp.coil_temperatures);
	LCU_udp.vcu_udp.send(LCU_udp.lpu_temperatures);
	LCU_udp.vcu_udp.send(LCU_udp.battery_data);
}
//
//class LCUTCP{
////	ServerSocket tcp_server;
//	StackOrder<0> take_off_order = {
//			300,
//			take_off
//	};
//
//	StackOrder<0> landing_order = {
//			301,
//			landing
//	};
//
//	StackOrder<0> stick_down_order = {
//			302,
//			stick_down
//	};
//
//	StackOrder<0> stick_up_order = {
//			303,
//			stick_up
//	};
//
//	StackOrder<0> set_parameters_order = {
//			304,
//			set_parameters
//	};
//
//	StackOrder<0> set_slave_parameters_order = {
//			305,
//			set_slave_parameters
//	};
////public:
//////	void register_connections(){
//////		tcp_server = ServerSocket(IPV4("192.168.1.4"),50500);
//////	}
//};
//
//LCUTCP LCU_tcp;

class LCUMaster{
public:
	static LCUMaster LCU_MASTER;

	LCUMasterData& lcu_data = LCU_data;
	LCUSensors& lcu_sensors = LCU_sensors;
	LCUActuators& lcu_actuators = LCU_actuators;
	LCUUDP& lcu_backend_udp = LCU_udp;
//	LCUTCP& lcu_tcp_server = LCU_tcp;
	LCUMaster() = default;

	enum General_SM_States : uint8_t {
		INITIAL,
		OPERATIONAL,
		FAULT
	};

	StateMachine general_sm = StateMachine(General_SM_States::INITIAL);

	uint8_t& general_state = general_sm.current_state;

	uint8_t slave_general_state;

	uint8_t specific_state = 0;

	uint8_t slave_specific_state = 0;

	bool control_state;

public:

	void execute_control(){

	}

	void register_cyclic_actions(){
		Time::register_low_precision_alarm(16, LCUUDP::send_all_data);
		Time::register_high_precision_alarm(100, LCUSensors::read_adcs);
		Time::register_low_precision_alarm(1, Ethernet::update);
		Time::register_high_precision_alarm(100, ErrorHandlerModel::ErrorHandlerUpdate);
	}

	void start(){
		lcu_actuators.inscribe_digital_outputs();
		lcu_sensors.inscribe_adcs();
		STLIB::start("192.168.1.4", "255.255.0.0", "192.168.1.1");
		lcu_sensors.turn_on_adcs();
		lcu_backend_udp.register_connections();
//		lcu_tcp_server.register_connections();
		register_cyclic_actions();
		lcu_actuators.start();
	}
};
////


