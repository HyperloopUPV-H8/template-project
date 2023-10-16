/**
 * @file TUD.hpp
 * @author gonzalo
 * @brief 
 * @version 0.1
 * @date 2023-10-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#pragma once


#include <array>
#include <functional>

#include <ST-LIB_LOW/DigitalOutput/DigitalOutput.hpp>
#include <ST-LIB.hpp>


#include <freeRTOS-lib/inc/defs.hpp>
#include <freeRTOS-lib/inc/Thread.hpp>

class TUD
{
    using State = uint8_t;
public:
	HyperEnum(testing_states,RECEIVING,TESTING);
    TUD()=default;
    void run_tests();
    void receive_orders();
protected:
    void generate_order(string can_order);
private:
    uint8_t next_order_index{0};
    DigitalOutput testing_led{PB14};
    DigitalOutput output_led{PE1};
    DigitalOutput receiving_led{PB0};
    bool finished_receiving{false};
    static constexpr uint8_t MAX_ORDERS = 10;
    std::array<std::function<void()>,MAX_ORDERS> orders;
};

