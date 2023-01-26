#pragma once

#ifdef HAL_TIM_MODULE_ENABLED

extern TIM_HandleTypeDef htim2;

void setup_input_capture_runes(){
	 InputCapture::available_instances = {
			{PA0, InputCapture::Instance(PA0, &timer2, TIM_CHANNEL_1, TIM_CHANNEL_2)}
	};
}

#endif
