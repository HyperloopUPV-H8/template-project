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

float slope{1.0};
float offset{};

float real_value{};
std::vector<std::pair<float, float>> points;

DatagramSocket* packets_endpoint{nullptr};
ServerSocket* control_station{nullptr};

void characterize() {
    sensor->read();
    float raw_value = ADC::get_value(sensor_id);
    points.push_back(std::make_pair(raw_value, real_value));

    if (points.size() >= 2) {
        double sum_x = 0, sum_y = 0, sum_xx = 0, sum_xy = 0;
        for (const auto& [x, y] : points) {
            sum_x += x;
            sum_y += y;
            sum_xx += x * x;
            sum_xy += x * y;
        }
        const size_t n = points.size();
        double denominator = n * sum_xx - sum_x * sum_x;
        if (denominator != 0.0) {
            slope =
                static_cast<float>((n * sum_xy - sum_x * sum_y) / denominator);
            offset = static_cast<float>((sum_y - slope * sum_x) / n);

            sensor->set_gain(slope);
            sensor->set_offset(offset);
        }
    }
}

HeapPacket reading_packet{100, &raw, &reading};
HeapPacket characterization_packet{101, &slope, &offset};
HeapOrder* order{nullptr};

int main(void) {
#ifdef SIM_ON
    SharedMemory::start();
#endif

    sensor = new LinearSensor<float>(PIN_SENSOR, slope, offset, reading);

    sensor_id = sensor->get_id();

    STLIB::start(IP);

    control_station = new ServerSocket(IPV4(IP), 50500);
    packets_endpoint =
        new DatagramSocket(IPV4(IP), 50400, IPV4("192.168.0.9"), 50400);

    order = new HeapOrder{110, characterize, &real_value};

    Time::register_low_precision_alarm(10, [&]() {
        sensor->read();
        raw = ADC::get_value(sensor_id);
    });

    Time::register_low_precision_alarm(100, [&]() {
        packets_endpoint->send_packet(reading_packet);
        packets_endpoint->send_packet(characterization_packet);
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
