#include "main.h"
#include "lwip.h"

#include "ST-LIB.hpp"
#include "Runes/Runes.hpp"

int main(void)
{
	STLIB::start();
	int a = 5;
	DatagramSocket udp_socket = DatagramSocket( IPV4("192.168.1.4"), 50400, IPV4("192.168.1.3"), 50400);
	HeapPacket pack = {1, &a};

	while(1) {
		udp_socket.send(pack);
		STLIB::update();
	}
}

void Error_Handler(void)
{
	ErrorHandler("HAL error handler triggered");
	while (1){}
}
