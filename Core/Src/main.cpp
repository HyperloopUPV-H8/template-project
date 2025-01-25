#ifndef SIM_ON
#include "main.h"

#include "lwip.h"
#endif
#include "ST-LIB.hpp"
enum class digitalOut : uint8_t{
    OFF,
    ON
};

digitalOut p1;
int32_t value_to_send{};
uint16_t id_packet1 = 0;
uint16_t id_packet2 = 1;
uint32_t local_serversocket_port = 8202;
uint32_t local_port_socket = 9002;
uint32_t remote_port_server_socket = 10012;
std::string localip = "127.0.0.1";
std::unique_ptr<ServerSocket> serversocket = nullptr;
std::unique_ptr<Socket> mysocket = nullptr;
HeapOrder *order1 = nullptr;
HeapOrder *order2 = nullptr;
void send_echo(){
    mysocket->send_order(*order1);
}
void print_value(){
    value_to_send += 5;
    serversocket->send_order(*order2);
}
int main(void) {
#ifdef SIM_ON
    SharedMemory::start();
#endif

    STLIB::start();
    order1 = new HeapOrder(id_packet1,&send_echo);
    order2 = new HeapOrder(id_packet2,&print_value,&value_to_send);
    serversocket = std::make_unique<ServerSocket>(localip,local_serversocket_port);
    mysocket = std::make_unique<Socket>(localip,local_port_socket,localip,remote_port_server_socket);
    Time::register_low_precision_alarm(100,[&](){
        if(mysocket->is_connected() == false){
            mysocket->reconnect();
        }
   });
    while (1) {
        STLIB::update();
    }
}

void Error_Handler(void) {
    ErrorHandler("HAL error handler triggered");
    while (1) {
    }
}
