#ifndef SIM_ON
#include "main.h"

#include "lwip.h"
#endif

#include "ST-LIB.hpp"

#define PIN_SENSOR PA0
#define IP "192.168.1.7"

float raw{};
float reading{};
LinearSensor<float>* sensor{nullptr};
uint8_t sensor_id{};

float slope{};
float offset{};

DatagramSocket* packets_endpoint{nullptr};
ServerSocket* control_station{nullptr};

void characterize() {
    sensor->set_gain(slope);
    sensor->set_offset(offset);
}

HeapPacket packet{100, &raw, &reading};
HeapOrder order{101, characterize, &slope, &offset};

int main(void) {
#ifdef SIM_ON
    SharedMemory::start();
#endif

    sensor = new LinearSensor<float>(PIN_SENSOR, 1.0, 0.0, &reading);

    sensor_id = sensor->get_id();

    STLIB::start(IP);

    control_station = new ServerSocket(IPV4(IP), 50500);
    packets_endpoint =
        new DatagramSocket(IPV4(IP), 50400, IPV4("192.168.0.9"), 50400);

    Time::register_low_precision_alarm(10, [&]() {
        sensor->read();
        raw = ADC::get_value(sensor_id);
    });

    Time::register_low_precision_alarm(
        100, [&]() { packets_endpoint->send_packet(packet); });

    while (1) {
        STLIB::update();
    }
}

void Error_Handler(void) {
    ErrorHandler("HAL error handler triggered");
    while (1) {
    }
}
