#include "main.h"

#include "Runes/Runes.hpp"
#include "ST-LIB.hpp"
#include "lwip.h"

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
