/**
 * @file TUD.cpp
 * @author gonzalo
 * @brief 
 * @version 0.1
 * @date 2023-10-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "TUD.hpp"

void TUD::receive_orders()
{
    auto ref = rtos::this_thread::get_time_reference();

    //listen to CAN
    receiving_led.turn_on();
    //store orders in array
    rtos::this_thread::sleep_for(&ref,2000);

    while(not finished_receiving)
    {
        ////////////////////////////
        //flow is  in FDCAN interrupt
        generate_order("0");
        generate_order("1");
        generate_order("2");
        generate_order("3");
        generate_order("4");
        generate_order("5");
        generate_order("6");
        generate_order("7");
        generate_order("8");
        generate_order("9");    
        //receive ACK of last msg
        finished_receiving = true;
        ////////////////////////////
    }

    //change  to TESTING
    receiving_led.turn_off();
}

void TUD::generate_order(string can_order)
{
    //parse order
    //store order in array
    orders[next_order_index] = [this](){
        uint8_t secs = 10;
        float period_in_ms = 500;
        auto start = xTaskGetTickCount();
        auto ref = rtos::this_thread::get_time_reference();
        for(;;)
        {
            if(xTaskGetTickCount() - start > configTICK_RATE_HZ*secs)
            {
               break;
            }
            output_led.toggle();
            rtos::this_thread::sleep_for(&ref,period_in_ms);
        }
        output_led.turn_off();
    };
    next_order_index++;
}


void TUD::run_tests()
{
    //run tests
    testing_led.turn_on();
    for(auto& order : orders)
    {
        order();
    }
    //clean up
    testing_led.turn_off();
    vTaskDelete(NULL);
}