#ifndef SIM_ON
#include "main.h"

#include "lwip.h"
#endif

#include "ST-LIB.hpp"

int main(void) {
#ifdef SIM_ON
    SharedMemory::start();
#endif

    DigitalOutput led_on(PB1);
    STLIB::start();

    Time::register_low_precision_alarm(5, [&]() { led_on.toggle(); 
    //  auto tiempo_actual = std::chrono::system_clock::now();
    // auto tiempo_ms = std::chrono::duration_cast<std::chrono::milliseconds>(tiempo_actual.time_since_epoch()).count();

    // // Imprimir el tiempo en milisegundos
    // std::cout << "Tiempo en milisegundos: " << tiempo_ms << " ms\n";
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
