#pragma once

#ifdef HAL_UART_MODULE_ENABLED

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

void setup_uart_runes(){
	UART::uart1 = UART::Peripheral::peripheral1;
	UART::uart2 = UART::Peripheral::peripheral2;

	UART::instance1 = { PA9, PA10, &huart1, USART1, 115200, UART_WORDLENGTH_8B };
	UART::instance2 = { PD5, PD6, &huart2, USART2,115200, UART_WORDLENGTH_8B, };

	UART::available_uarts = {
		{UART::uart1, &UART::instance1},
		{UART::uart2, &UART::instance2}
	};
}

#endif
