/*
 * rtc_example.hpp
 *
 * Created on: 14 Feb. 2023
 * 		Author: Ricardo
 */

#pragma once
#include "main.h"
#include "lwip.h"
#include "ST-LIB.hpp"

int rtc_example(void){
	STLIB::start(Nucleo,"192.168.1.4","255.255.0.0","192.168.1.1");
	uint32_t a = HAL_RCC_GetSysClockFreq();
	printf("%lu",a);

	SNTP::sntp_update("192.168.1.3");

	printf("\n\n\n\n\n\n\n\n\n\n");
	while(1){
		STLIB::update();
		Time::RTCData now = Time::get_rtc_data();
		printf("%u:%u:%u::%u  %u-%u-%u \n",now.hour,now.minute,now.second,now.counter,now.day,now.month,now.year);
	}
}

