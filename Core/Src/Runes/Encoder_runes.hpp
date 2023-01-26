#pragma once

#ifdef HAL_TIM_MODULE_ENABLED

extern TIM_HandleTypeDef htim8;

TimerPeripheral encoder_timer = TimerPeripheral(&htim8, {TIM8, 0, 65535});

void setup_encoder_runes(){
	 Encoder::pin_timer_map = {
			{{PC6, PC7}, &encoder_timer}
	};
}

#endif
