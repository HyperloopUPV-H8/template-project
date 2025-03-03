#ifndef SIM_ON
#include "main.h"

#include "lwip.h"
#endif

#include "ST-LIB.hpp"

int main(void) {
#ifdef SIM_ON
    SharedMemory::start();
#endif
    enum state_id{
        connecting =0,
        operational =1,
    };
    PinState led_state = PinState::OFF;
    uint8_t id = DigitalInput::inscribe(PB2);
    STLIB::start();
    StateMachine state_machine(connecting);
    state_machine.add_state(operational);
    state_machine.add_transition(connecting, operational, [&](){
        return led_state;

    });
    state_machine.add_low_precision_cyclic_action([&](){
        led_state = DigitalInput::read_pin_state(id);
    }, std::chrono::milliseconds(1000), {connecting, operational});
    while(1){
        STLIB::update();
        state_machine.check_transitions();
        
    }
}

void Error_Handler(void) {
    ErrorHandler("HAL error handler triggered");
    while (1) {
    }
}
