#pragma once

#define HAL_TIM_MODULE_ENABLED
#define HAL_SPI_MODULE_ENABLED
#define HAL_ADC_MODULE_ENABLED
#define HAL_LPTIM_MODULE_ENABLED
#define HAL_TIM_MODULE_ENABLED
#define HAL_UART_MODULE_ENABLED

#include "ST-LIB.hpp"
#include "ADC_runes.hpp"
#include "Timer_runes.hpp"
#include "SPI_runes.hpp"
#include "UART_runes.hpp"
#include "Encoder_runes.hpp"
#include "InputCapture_runes.hpp"
#include "EXTI_runes.hpp"

void setup_runes(){
	setup_adc_runes();
	setup_timer_runes();
	setup_spi_runes();
	setup_uart_runes();
	setup_encoder_runes();
	setup_input_capture_runes();
	setup_exti_runes();
}
