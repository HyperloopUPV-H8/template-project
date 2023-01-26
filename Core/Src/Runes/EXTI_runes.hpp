#pragma once

/************************************************
 *					   EXTI
 ***********************************************/
#ifdef HAL_EXTI_MODULE_ENABLED

void setup_exti_runes(){
	ExternalInterrupt::instances = {
		{PE0.gpio_pin, ExternalInterrupt::Instance(EXTI0_IRQn)},
		{PE1.gpio_pin, ExternalInterrupt::Instance(EXTI1_IRQn)}
	};
}

#endif
