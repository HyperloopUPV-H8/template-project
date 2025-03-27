 /**
  * Bootloader.hpp
  *
  *  Created on: Jan 21, 2022
  *      Author: Pablo
  */

#include "FDCBootloader/FDCBootloader.hpp"

uint8_t FDCB::fdcan = 0;
bool FDCB::ready = false;


void FDCB::set_up(FDCAN::Peripheral&  fdcan){

	FDCB::fdcan = FDCAN::inscribe(fdcan);
	FDCB::ready = true;
}

bool FDCB::get_version(uint8_t& version){
	vector<uint8_t> data = vector<uint8_t>(64);
	FDCAN::Packet packet = FDCAN::Packet();
	version = 0;
	const char* data_ptr = reinterpret_cast<const char*>(data.data());  // Cast to const char*
	if (not FDCAN::transmit(FDCB::fdcan, FDCB::GET_VERSION, data_ptr, FDCAN::DLC::BYTES_64)){
		return false;
	}

	if (not __wait_for_ack(FDCB::GET_VERSION, packet)) {
		return false;
	}

	if (not __wait_for_data_message(FDCB::GET_VERSION, packet)) {
		return false;
	}
	version = packet.rx_data[0];

	if (not __wait_for_ack(FDCB::GET_VERSION, packet)) {
		version = 0;
		return false;
	}

	return true;
}

bool FDCB::read_memory(uint8_t sector, uint8_t* data){
	vector<uint8_t> tx_data = vector<uint8_t>(64);
	FDCAN::Packet packet = FDCAN::Packet();
	packet.rx_data.fill(0);
	uint16_t i;
	uint32_t index, counter;

	tx_data.at(0) = sector;
	const char* tx_data_ptr = reinterpret_cast<const char*>(tx_data.data());  // Cast to const char*
	FDCAN::transmit(FDCB::fdcan, FDCB::READ_MEMORY, tx_data_ptr, FDCAN::DLC::BYTES_64);

	if (not __wait_for_ack(FDCB::READ_MEMORY, packet)) {
		return false;
	}

	if (not __send_ack(FDCB::READ_MEMORY)) {
		return false;
	}

	index = 0;
	counter = 0;
	for (i = 0; i < 2048; ++i) {
		if(not FDCB::__wait_for_data_message(FDCB::READ_MEMORY, packet)) {
			return false;
		}

		memcpy(&data[index], &packet.rx_data[0], 64);
		index += 64;

		if (counter >= FDCB_BLOCK_SIZE) {
			if (not FDCB::__wait_for_ack(FDCB::READ_MEMORY, packet)) {
				return false;
			}

			FDCB::__send_ack(FDCB::READ_MEMORY);
			counter = 0;
		}
		counter++;
	}

	if (not __wait_for_ack(FDCB::READ_MEMORY, packet)) {
		return false;
	}

	return true;
}

bool FDCB::write_memory(uint8_t sector, uint8_t* data){
	vector<uint8_t> tx_data = vector<uint8_t>(64);
	FDCAN::Packet packet = FDCAN::Packet();
	packet.rx_data.fill(0);
	uint16_t i;
	uint32_t index, counter;

	tx_data.at(0) = sector;
	const char* tx_data_ptr = reinterpret_cast<const char*>(tx_data.data());  // Cast to const char*
	FDCAN::transmit(FDCB::fdcan, FDCB::WRITE_MEMORY, tx_data_ptr, FDCAN::DLC::BYTES_64);

	if (not __wait_for_ack(FDCB::WRITE_MEMORY, packet)) {
		return false;
	}

	if (not __send_ack(FDCB::WRITE_MEMORY)) {
		return false;
	}

	index = 0;
	counter = 1;
	for (i = 0; i < 2048; ++i) {
		memcpy(&tx_data[0], &data[index], 64);
		if(not FDCAN::transmit(FDCB::fdcan, FDCB::WRITE_MEMORY, tx_data_ptr, FDCAN::DLC::BYTES_64)) {
			return false;
		}
		index += 64;

		if (counter >= FDCB_BLOCK_SIZE) {
			if (not FDCB::__wait_for_ack(FDCB::WRITE_MEMORY, packet)) {
				return false;
			}

			FDCB::__send_ack(FDCB::WRITE_MEMORY);
			counter = 1;
		}else{
			counter++;
		}

	}

	if (not __wait_for_ack(FDCB::WRITE_MEMORY, packet)) {
		return false;
	}

	return true;
}



bool FDCB::erase_memory(){
	vector<uint8_t> data = vector<uint8_t>(64);
	FDCAN::Packet packet = FDCAN::Packet();
	data.at(0) = 0;
	data.at(1) = 6;

	const char* data_ptr = reinterpret_cast<const char*>(data.data());  // Cast to const char*
	FDCAN::transmit(FDCB::fdcan, FDCB::ERASE_MEMORY, data_ptr, FDCAN::DLC::BYTES_64);

	if (not __wait_for_ack(FDCB::ERASE_MEMORY, packet)) {
		return false;
	}

	if (not __wait_for_ack(FDCB::ERASE_MEMORY, packet)) {
		return false;
	}

	return true;
}

//*******************************************************
//				Private functions
//*******************************************************

bool FDCB::__wait_for_data_message(uint8_t order, FDCAN::Packet& packet){
	if (not __wait_for_bootloader_message()) {
		return false;
	}

	if (not FDCAN::read(fdcan, &packet)) {
		return false;
	}

	if (packet.identifier != order) {
		return false;
	}

	return true;
}

bool FDCB::__wait_for_ack(uint8_t order, FDCAN::Packet& packet){
	if (not __wait_for_bootloader_message()) {
		return false;
	}

	FDCAN::read(fdcan, &packet);

	if (packet.identifier != order) {
		return false;
	}else if(packet.rx_data[0] != FDCB_ACK){
		return false;
	}

	return true;
}

bool FDCB::__send_ack(uint8_t order){
	vector<uint8_t> data = vector<uint8_t>(64);
	data.at(0) = FDCB_ACK;
	const char* data_ptr = reinterpret_cast<const char*>(data.data());  // Cast to const char*
	return FDCAN::transmit(FDCB::fdcan, order, data_ptr, FDCAN::DLC::BYTES_64);
}

bool FDCB::__send_nack(uint8_t order){
	vector<uint8_t> data = vector<uint8_t>(64);
	data.at(0) = FDCB_NACK;
	const char* data_ptr = reinterpret_cast<const char*>(data.data());  // Cast to const char*
	return FDCAN::transmit(FDCB::fdcan, order, data_ptr, FDCAN::DLC::BYTES_64);
}

bool FDCB::__wait_for_bootloader_message(){
     bool exit = true;

 	uint8_t id = Time::register_low_precision_alarm(FDCB_TIMEOUT_MS, [&](){
 		exit = false;
 		printf("Salto!\n");
 	});

     while(exit){
    	 if (FDCAN::received_test(fdcan)) {
    		 Time::unregister_low_precision_alarm(id);
			return true;
    	 }
     }

     Time::unregister_low_precision_alarm(id);
     //TODO:: Warning timeout
     return false;
}

void FDCB::__copy_data_from_packet(FDCAN::Packet& packet, uint8_t* data){
	//memcpy(data, &packet.rx_data[0], 64);

	uint8_t i;
	for (i = 0; i < 64; ++i) {
		data[i] = packet.rx_data.at(i);
	}
}

void FDCB::__addr_to_byte_vector(vector<uint8_t>& v, uint32_t addr){
	v.push_back( addr >> 24 );
	v.push_back( addr >> 16 );
	v.push_back( addr >>  8 );
	v.push_back( addr       );
}


