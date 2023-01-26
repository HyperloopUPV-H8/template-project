#pragma once

#ifdef HAL_TIM_MODULE_ENABLED

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim12;
extern TIM_HandleTypeDef htim16;
extern TIM_HandleTypeDef htim17;
extern TIM_HandleTypeDef htim15;
extern TIM_HandleTypeDef htim23;

TimerPeripheral::InitData init_data_timer1(TIM1);
TimerPeripheral::InitData init_data_timer2(TIM2);
TimerPeripheral::InitData init_data_timer3(TIM3);
TimerPeripheral::InitData init_data_timer4(TIM4);
TimerPeripheral::InitData init_data_timer12(TIM12);
TimerPeripheral::InitData init_data_timer16(TIM16);
TimerPeripheral::InitData init_data_timer17(TIM17);
TimerPeripheral::InitData init_data_timer15(TIM15);
TimerPeripheral::InitData init_data_timer23(TIM23);

TimerPeripheral timer1(&htim1, init_data_timer1);
TimerPeripheral timer2(&htim2, init_data_timer2);
TimerPeripheral timer3(&htim3, init_data_timer3);
TimerPeripheral timer4(&htim4, init_data_timer4);
TimerPeripheral timer12(&htim12, init_data_timer12);
TimerPeripheral timer16(&htim16, init_data_timer16);
TimerPeripheral timer17(&htim17, init_data_timer17);
TimerPeripheral timer15(&htim15, init_data_timer15);
TimerPeripheral timer23(&htim23, init_data_timer23);


void setup_timer_runes() {

	PWMservice::available_instances_dual = {
		{{PB8,PB6}, PWMservice::Instance(&timer16, TIM_CHANNEL_1, PWMservice::DUAL)},
		{{PB9,PB7}, PWMservice::Instance(&timer17, TIM_CHANNEL_1, PWMservice::DUAL)},
		{{PE11,PE10}, PWMservice::Instance(&timer1, TIM_CHANNEL_2, PWMservice::DUAL)},
		{{PE13,PE12}, PWMservice::Instance(&timer1, TIM_CHANNEL_3, PWMservice::DUAL)},
		{{PE5,PE4}, PWMservice::Instance(&timer15, TIM_CHANNEL_1, PWMservice::DUAL)},
		{{PE9,PE8}, PWMservice::Instance(&timer1, TIM_CHANNEL_1, PWMservice::DUAL)},
	};

	PWMservice::available_instances_dual = {
		{{PB8,PB6}, PWMservice::Instance(&timer16, TIM_CHANNEL_1, PWMservice::DUAL)},
		{{PE11,PE10}, PWMservice::Instance(&timer1, TIM_CHANNEL_2, PWMservice::DUAL)},
		{{PE13,PE12}, PWMservice::Instance(&timer1, TIM_CHANNEL_3, PWMservice::DUAL)},
		{{PE5,PE4}, PWMservice::Instance(&timer15, TIM_CHANNEL_1, PWMservice::DUAL)},
		{{PE9,PE8}, PWMservice::Instance(&timer1, TIM_CHANNEL_1, PWMservice::DUAL)},
	};

	PWMservice::available_instances_negated = {};

	PWMservice::available_instances = {
		{PB9, PWMservice::Instance(&timer17, TIM_CHANNEL_1, PWMservice::NORMAL)},
		{PB14, PWMservice::Instance(&timer12, TIM_CHANNEL_1, PWMservice::NORMAL)},
		{PB15, PWMservice::Instance(&timer12, TIM_CHANNEL_2, PWMservice::NORMAL)},
		{PB4, PWMservice::Instance(&timer3, TIM_CHANNEL_1, PWMservice::NORMAL)},
		{PB5, PWMservice::Instance(&timer3, TIM_CHANNEL_2, PWMservice::NORMAL)},
		{PC8, PWMservice::Instance(&timer3, TIM_CHANNEL_3, PWMservice::NORMAL)},
		{PD12, PWMservice::Instance(&timer4, TIM_CHANNEL_1, PWMservice::NORMAL)},
		{PD13, PWMservice::Instance(&timer4, TIM_CHANNEL_2, PWMservice::NORMAL)},
		{PD15, PWMservice::Instance(&timer4, TIM_CHANNEL_4, PWMservice::NORMAL)},
		{PE14, PWMservice::Instance(&timer1, TIM_CHANNEL_4, PWMservice::NORMAL)},
		{PE6, PWMservice::Instance(&timer15, TIM_CHANNEL_2, PWMservice::NORMAL)},
		{PF1, PWMservice::Instance(&timer23, TIM_CHANNEL_2, PWMservice::NORMAL)},
		{PF2, PWMservice::Instance(&timer23, TIM_CHANNEL_3, PWMservice::NORMAL)},
		{PF3, PWMservice::Instance(&timer23, TIM_CHANNEL_4, PWMservice::NORMAL)},
	};

	TimerPeripheral::timers = {
			timer1,
			timer2,
			timer3,
			timer4,
			timer12,
			timer15,
			timer16,
			timer23
	};
}

#endif
