#include "Pins.hpp"
#include "HALALMock/Services/Communication/SPI/SPI.hpp"

/************************************************
 *              Communication-FDCAN
 ***********************************************/

// TODO IP and ports. Wait for Firmware meeting to clarify concepts

FDCAN::Instance FDCAN::instance1 = {
    .TX = PD1,
    .RX = PD0,
    .dlc = DLC::BYTES_64,
    .rx_location = FDCAN_RX_FIFO0,
    .fdcan_number = 1
    //.socket
};

FDCAN::Peripheral FDCAN::fdcan1 = FDCAN::Peripheral::peripheral1;

unordered_map<FDCAN::Peripheral, FDCAN::Instance*> FDCAN::available_fdcans = {
    {FDCAN::fdcan1, &FDCAN::instance1}
};

/************************************************
 *              Communication-SPI
 ***********************************************/

std::string SPI::ip = "192.168.1.10";

SPI::Instance SPI::instance3 = {
    .SCK = &PC10,
    .MOSI = &PC12,
    .MISO = &PC11,
    .SS = &PD3,
    .mode = SPIMode::MASTER,
    .use_DMA = false,
    .port = 2002
};

SPI::Peripheral SPI::spi3 = SPI::Peripheral::peripheral3;

unordered_map<SPI::Peripheral, SPI::Instance*> SPI::available_spi = {
    {SPI::spi3, &SPI::instance3}};

/************************************************
 *                 	  Encoder
 ***********************************************/

map<pair<Pin, Pin>, TimerPeripheral*> Encoder::pin_timer_map = {
    {{PC6, PC7}, nullptr}};

/************************************************
 *                 Input Capture
 ***********************************************/

map<Pin, InputCapture::Instance> InputCapture::availale_instances = {
    {PF0, InputCapture::Instance{PF0, nullptr, nullptr, nullptr}}
};

/************************************************
 *					   ADC
 ***********************************************/

map<Pin, ADC::Instance> ADC::available_instances = {
    {PF11, Instance(ADC::ADCResolution::ADC_RES_16BITS)},
    {PF12, Instance(ADC::ADCResolution::ADC_RES_16BITS)},
    {PF13, Instance(ADC::ADCResolution::ADC_RES_16BITS)},
    {PF14, Instance(ADC::ADCResolution::ADC_RES_16BITS)},
    {PF5, Instance(ADC::ADCResolution::ADC_RES_12BITS)},
    {PF6, Instance(ADC::ADCResolution::ADC_RES_12BITS)},
    {PF7, Instance(ADC::ADCResolution::ADC_RES_12BITS)},
    {PF8, Instance(ADC::ADCResolution::ADC_RES_12BITS)},
    {PF9, Instance(ADC::ADCResolution::ADC_RES_12BITS)},
    {PF10, Instance(ADC::ADCResolution::ADC_RES_12BITS)},
    {PC2, Instance(ADC::ADCResolution::ADC_RES_16BITS)},
    {PC3, Instance(ADC::ADCResolution::ADC_RES_16BITS)},
    {PF10, Instance(ADC::ADCResolution::ADC_RES_16BITS)},
    {PC0, Instance(ADC::ADCResolution::ADC_RES_16BITS)},
    {PA0, Instance(ADC::ADCResolution::ADC_RES_16BITS)},
    {PA3, Instance(ADC::ADCResolution::ADC_RES_16BITS)},
    {PA4, Instance(ADC::ADCResolution::ADC_RES_16BITS)},
    {PA5, Instance(ADC::ADCResolution::ADC_RES_16BITS)},
    {PA6, Instance(ADC::ADCResolution::ADC_RES_16BITS)},
    {PB0, Instance(ADC::ADCResolution::ADC_RES_16BITS)},
    {PB1, Instance(ADC::ADCResolution::ADC_RES_16BITS)}
};

/************************************************
 *					   EXTI
 ***********************************************/

map<uint16_t, ExternalInterrupt::Instance> ExternalInterrupt::instances = {
    {PE0.gpio_pin, Instance()},
    {PE1.gpio_pin, Instance()}
};

