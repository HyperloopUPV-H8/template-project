#ifndef SIM_ON
#include "main.h"

#include "lwip.h"
#endif
#include "HALAL/Services/DataWatchpointTrace/DataWatchpointTrace.hpp"
#include "ST-LIB.hpp"
#include "look_up_table.hpp"
#define TWO_PI 2 * M_PI
#define REPS 1000000

float fast_sin_lut(float angle) {
    angle = fmod(angle, TWO_PI);
    if (angle < 0) angle += TWO_PI;
    int idx = round((angle * NUMBER_POINTS) / TWO_PI);
    return look_up_table_sin[idx];
}
int main(void) {
#ifdef SIM_ON
    SharedMemory::start();
#endif
    float freq = 50.0f;
    float time = 0.0f;
    float sin_u = 0.0f, sin_v = 0.0f, sin_w = 0.0f;
    DataWatchpointTrace::start();
    STLIB::start();
    unsigned int start_cycle = DataWatchpointTrace::start_count();
    sin_u = sin(TWO_PI * freq * time);
    sin_v = sin(TWO_PI * freq * time + TWO_PI / 3.0f);
    sin_w = sin(TWO_PI * freq * time - TWO_PI / 3.0f);
    unsigned int end_cycle = DataWatchpointTrace::stop_count();

    unsigned int cycle_time = end_cycle - start_cycle;
    start_cycle = cycle_time + 1;

    start_cycle = DataWatchpointTrace::start_count();
    sin_u = fast_sin_lut(TWO_PI * freq * time);
    sin_v = fast_sin_lut(TWO_PI * freq * time + TWO_PI / 3.0f);
    sin_w = fast_sin_lut(TWO_PI * freq * time - TWO_PI / 3.0f);
    end_cycle = DataWatchpointTrace::stop_count();
    cycle_time = end_cycle - start_cycle;

    sin_u = sin_v;
    sin_v = sin_w;
    sin_w = sin_u;
    while (1) {
        STLIB::update();
    }
}

void Error_Handler(void) {
    ErrorHandler("HAL error handler triggered");
    while (1) {
    }
}
