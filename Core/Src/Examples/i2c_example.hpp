/*
 * i2c_example.hpp
 *
 *  Created on: 8 Feb. 2023
 *      Author: Ricardo
 */
#pragma once

#include "ST-LIB.hpp"

int i2c_example(void)
{
	uint8_t id = I2C::inscribe(I2C::i2c2).value_or(69);
	STLIB::start();
	uint8_t *message = new uint8_t[3];
	uint8_t *data = new uint8_t[7];
	message[0] = 0xAA;
	message[1] = 0x00;
	message[2] = 0x00;
	I2CPacket send_packet(40<<1,message,3);
	I2CPacket check_packet(40<<1,data,1);
	I2CPacket receive_packet(40<<1,data,7);
	float temperature = 0;
	float pressure = 0;
	printf("\n\n\n\n\n\n\n\n\n\n");

	while (1) {
		if(I2C::transmit_next_packet_polling(id, send_packet)){
			I2C::receive_next_packet_polling(id, check_packet);
			data = check_packet.get_data();
			while((data[0] & 0x20) != 0x0){
				I2C::receive_next_packet_polling(id, check_packet);
			}
			I2C::receive_next_packet_polling(id, receive_packet);
			data = receive_packet.get_data();
			pressure = ((data[1]*65536.0 + data[2]*256 + data[3]) - 1677722)/(15099494 - 1677722);
			temperature = ((data[4]*65536.0 + data[5]*256 + data[6])* 200 / 16777215) - 50;
		}
		printf("i received %f ºC and %f bars\n",temperature,pressure);
		HAL_Delay(50);
		ErrorHandlerModel::ErrorHandlerUpdate();
	}
}
