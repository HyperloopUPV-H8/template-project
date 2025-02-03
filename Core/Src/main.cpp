#ifndef SIM_ON
#include "main.h"

#include "lwip.h"
#endif

#include "ST-LIB.hpp"

int main(void) {
#ifdef SIM_ON
    SharedMemory::start("gpio_SPI", "state_machine_SPI");
#endif
    uint8_t master1 = SPI::inscribe(SPI::spi1);
    uint8_t master2 = SPI::inscribe(SPI::spi2);
    uint8_t slave_selected = SPI::inscribe(SPI::spi3);
    uint8_t slave_not_selected = SPI::inscribe(SPI::spi4);
    STLIB::start();

    while (1) {
        STLIB::update();
        SPI::chip_select_off(master2);

        uint8_t data_array[12];
        std::span<uint8_t> data(data_array);
        SPI::receive(master1, data);

        const char* s_data = reinterpret_cast<const char*>(data.data());
        LOG_INFO(s_data);

        SPI::transmit(master1, data);

        uint8_t data_array_2[12];
        std::span<uint8_t> data_2(data_array_2);
        SPI::receive(slave_selected, data_2);

        const char* s_data_2 = reinterpret_cast<const char*>(data_2.data());
        LOG_INFO(s_data_2);

        SPI::transmit(slave_selected, data_2);

        uint8_t data_array_3[12];
        std::span<uint8_t> data_3(data_array_3);
        SPI::receive(slave_not_selected, data_3);

        const char* s_data_3 = reinterpret_cast<const char*>(data_3.data());
        LOG_INFO(s_data_3);

        SPI::transmit(slave_not_selected, data_3);
    }
}

void Error_Handler(void) {
    ErrorHandler("HAL error handler triggered");
    while (1) {
    }
}
