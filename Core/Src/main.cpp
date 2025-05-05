#ifndef SIM_ON
#include "main.h"

#include "lwip.h"
#endif

#include "ST-LIB.hpp"

int main(void) {
#ifdef SIM_ON
    SharedMemory::start();
#endif

    DigitalOutput led_on(PG8);
    STLIB::start("00:80:e1:00:01:04");

    Time::register_low_precision_alarm(500, [&]() { led_on.toggle(); });

    while (1) {
        STLIB::update();
    }
}

void Error_Handler(void) {
    ErrorHandler("HAL error handler triggered");
    while (1) {
    }
}
