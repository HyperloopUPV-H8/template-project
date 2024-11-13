#ifndef SIM_ON
#include "main.h"

#include "lwip.h"
#endif

#include "ST-LIB.hpp"

int main(void) {
    STLIB::start();

    while (1) {
        STLIB::update();
    }
}

void Error_Handler(void) {
    ErrorHandler("HAL error handler triggered");
    while (1) {
    }
}
