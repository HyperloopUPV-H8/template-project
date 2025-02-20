#ifndef SIM_ON
#include "main.h"

#include "lwip.h"
#endif

#include "ST-LIB.hpp"

int main(void) {
#ifdef SIM_ON
    SharedMemory::start();
#endif
    int id = FDCAN::inscribe(FDCAN::fdcan1); 
    std::string data = "Hello2";
    STLIB::start();
    Time::register_low_precision_alarm(500,[&](){
        FDCAN::transmit(id, 1, data.c_str(), FDCAN::DLC::BYTES_6);
    });
    FDCAN::Packet packet;
    Time::register_low_precision_alarm(500,[&](){
        FDCAN::read(id, &packet);
    });
    while(1){
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        STLIB::update();
    }
}


void Error_Handler(void) {
    ErrorHandler("HAL error handler triggered");
    while (1) {
    }
}
