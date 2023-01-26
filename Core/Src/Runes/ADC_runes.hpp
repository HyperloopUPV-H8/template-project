#pragma once

#if defined(HAL_ADC_MODULE_ENABLED) && defined(HAL_LPTIM_MODULE_ENABLED)

extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc2;
extern ADC_HandleTypeDef hadc3;

extern LPTIM_HandleTypeDef hlptim1;
extern LPTIM_HandleTypeDef hlptim2;
extern LPTIM_HandleTypeDef hlptim3;

uint16_t adc_buf1[ADC_BUF_LEN];
uint16_t adc_buf2[ADC_BUF_LEN];
uint16_t adc_buf3[ADC_BUF_LEN];

LowPowerTimer lptim1 = LowPowerTimer(LPTIM1, &hlptim1, LPTIM1_PERIOD);
LowPowerTimer lptim2 = LowPowerTimer(LPTIM2, &hlptim2, LPTIM2_PERIOD);
LowPowerTimer lptim3 = LowPowerTimer(LPTIM3, &hlptim3, LPTIM3_PERIOD);

vector<uint32_t> channels1 = {};
vector<uint32_t> channels2 = {};
vector<uint32_t> channels3 = {};

ADC::InitData init_data1 = { ADC1, ADC_RESOLUTION_16B, ADC_EXTERNALTRIG_LPTIM1_OUT, channels1 };
ADC::InitData init_data2 = { ADC2, ADC_RESOLUTION_16B, ADC_EXTERNALTRIG_LPTIM2_OUT, channels2 };
ADC::InitData init_data3 = { ADC3, ADC_RESOLUTION_12B, ADC_EXTERNALTRIG_LPTIM3_OUT, channels3 };

template<typename T>
void copy_args(T* ptr, const std::initializer_list<T>& list) {
	int i = 0;
	for(auto& ref : list)
		ptr[i++] = ref;
}

void setup_adc_runes(){

	copy_args(	ADC::ranks, {
			 	(uint32_t) ADC_REGULAR_RANK_1,
				(uint32_t) ADC_REGULAR_RANK_2,
				(uint32_t) ADC_REGULAR_RANK_3,
				(uint32_t) ADC_REGULAR_RANK_4,
				(uint32_t) ADC_REGULAR_RANK_5,
				(uint32_t) ADC_REGULAR_RANK_6,
				(uint32_t) ADC_REGULAR_RANK_7,
				(uint32_t) ADC_REGULAR_RANK_8,
				(uint32_t) ADC_REGULAR_RANK_9,
				(uint32_t) ADC_REGULAR_RANK_10,
				(uint32_t) ADC_REGULAR_RANK_11,
				(uint32_t) ADC_REGULAR_RANK_12,
				(uint32_t) ADC_REGULAR_RANK_13,
				(uint32_t) ADC_REGULAR_RANK_14,
				(uint32_t) ADC_REGULAR_RANK_15,
				(uint32_t) ADC_REGULAR_RANK_16 });

	copy_args(	ADC::peripherals,{
				ADC::Peripheral(&hadc1, adc_buf1, lptim1, init_data1),
				ADC::Peripheral(&hadc2, adc_buf2, lptim2, init_data2),
				ADC::Peripheral(&hadc3, adc_buf3, lptim3, init_data3) });

	ADC::available_instances = {
			{PF11, ADC::Instance(&ADC::peripherals[0], ADC_CHANNEL_2)},
			{PF12, ADC::Instance(&ADC::peripherals[0], ADC_CHANNEL_6)},
			{PF13, ADC::Instance(&ADC::peripherals[1], ADC_CHANNEL_2)},
			{PF14, ADC::Instance(&ADC::peripherals[1], ADC_CHANNEL_6)},
			{PF5, ADC::Instance(&ADC::peripherals[2], ADC_CHANNEL_4)},
			{PF6, ADC::Instance(&ADC::peripherals[2], ADC_CHANNEL_8)},
			{PF7, ADC::Instance(&ADC::peripherals[2], ADC_CHANNEL_3)},
			{PF8, ADC::Instance(&ADC::peripherals[2], ADC_CHANNEL_7)},
			{PF9, ADC::Instance(&ADC::peripherals[2], ADC_CHANNEL_2)},
			{PF10, ADC::Instance(&ADC::peripherals[2], ADC_CHANNEL_6)},
			{PC2, ADC::Instance(&ADC::peripherals[2], ADC_CHANNEL_0)},
			{PC3, ADC::Instance(&ADC::peripherals[2], ADC_CHANNEL_1)},
			{PF10, ADC::Instance(&ADC::peripherals[2], ADC_CHANNEL_6)},
			{PC0, ADC::Instance(&ADC::peripherals[0], ADC_CHANNEL_10)},
			{PA0, ADC::Instance(&ADC::peripherals[0], ADC_CHANNEL_16)},
			{PA3, ADC::Instance(&ADC::peripherals[0], ADC_CHANNEL_15)},
			{PA4, ADC::Instance(&ADC::peripherals[0], ADC_CHANNEL_18)},
			{PA5, ADC::Instance(&ADC::peripherals[0], ADC_CHANNEL_19)},
			{PA6, ADC::Instance(&ADC::peripherals[0], ADC_CHANNEL_3)},
			{PB0, ADC::Instance(&ADC::peripherals[0], ADC_CHANNEL_9)},
			{PB1, ADC::Instance(&ADC::peripherals[0], ADC_CHANNEL_5)}
	};

}

#endif

