#ifndef SIM_ON
#include "main.h"

#include "lwip.h"
#endif

#include "ST-LIB.hpp"

int main(void) {
    SharedMemory::start("gpio", "gpio_sm");
    uint8_t master = SPI::inscribe(SPI::spi1);
    uint8_t slave = SPI::inscribe(SPI::spi2);
    STLIB::start();

    while (1) {
        STLIB::update();

        uint8_t data_array[11];
        std::span<uint8_t> data(data_array);
        SPI::receive(master, data);

        const char* s_data = reinterpret_cast<const char*>(data.data());
        LOG_INFO(s_data);

        SPI::transmit(master, data);

        uint8_t data_array_2[13];
        std::span<uint8_t> data_2(data_array_2);
        SPI::receive(slave, data_2);

        const char* s_data_2 = reinterpret_cast<const char*>(data_2.data());
        LOG_INFO(s_data_2);

        SPI::transmit(slave, data_2);
    }
}

void Error_Handler(void) {
    ErrorHandler("HAL error handler triggered");
    while (1) {
    }
}
