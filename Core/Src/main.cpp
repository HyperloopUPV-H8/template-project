#ifndef SIM_ON
#include "main.h"
#include "lwip.h"
#endif
#include "ST-LIB.hpp"
enum class digitalOut : uint8_t{
    OFF,
    ON
};
struct packet1_struct{
    digitalOut dout{};
};
struct packet2_struct{
    uint16_t par1{};
    int32_t par2{};
    digitalOut par3{};
    float par4{};
    void change_values(){
        par1++;
        par2 -= 5;
        par3 = digitalOut::OFF;
        par4 += 2.0;
    }
};

packet1_struct packet1_values;
packet2_struct packet2_values;
uint32_t local_port= 9006;
uint32_t remote_port = 9015;
std::string ip = "127.0.0.1";
std::unique_ptr<DatagramSocket> datagramsocket = nullptr;
std::unique_ptr<Socket> mysocket = nullptr;
HeapPacket *packet1 = nullptr;
HeapPacket *packet2 = nullptr;

int main(void) {
#ifdef SIM_ON
    SharedMemory::start();
#endif

    STLIB::start();
    packet1 = new HeapPacket(0,&packet1_values.dout);
    packet2 = new HeapPacket(1,&packet2_values.par1,&packet2_values.par2,&packet2_values.par3,&packet2_values.par4);
    datagramsocket = std::make_unique<DatagramSocket>(ip,local_port,ip,remote_port);
    Time::register_low_precision_alarm(100,[&](){
        if(packet1_values.dout == digitalOut::ON){
            packet1_values.dout = digitalOut::OFF;
            packet2_values.change_values();
            datagramsocket->send_packet(*packet2);
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