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
	//remember to re activate i2c on runes
	/*uint8_t id = I2C::inscribe(I2C::i2c2,2).value_or(69);
	STLIB::start();
	I2C::start();
	uint8_t buf[4];
	buf[0] = 1;
	buf[1] = 2;
	buf[2] = 4;
	buf[3] = 8;
	I2CPacket paquete(4,buf,4);
	printf("\n\n\n\n\n\n\n\n\n\n");

	while (1) {
		if(!I2C::is_busy(id)){
			if(I2C::transmit_next_packet(id, paquete)){
				while(I2C::is_busy(id)){

				}
				if(I2C::has_next_packet(id)){
					if(I2C::receive_next_packet(id, paquete)){
						printf("done \n");
					}
				}
			}
		}
		ErrorHandlerModel::ErrorHandlerUpdate();
	}*/
}
