#pragma once

#ifdef HAL_SPI_MODULE_ENABLED

extern SPI_HandleTypeDef hspi3;

void setup_spi_runes() {
	SPI::instance3 = {&PC10, &PC12, &PC11, &PD0, &hspi3,SPI3, SPI_BAUDRATEPRESCALER_256 };
	SPI::spi3 = SPI::Peripheral::peripheral3;
	SPI::available_spi = {
		{SPI::spi3, &SPI::instance3}
	};
}

#endif
