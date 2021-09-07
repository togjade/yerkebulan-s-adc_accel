#ifndef __MS5611_H
#define __MS5611_H





#ifdef __cplusplus
 extern "C" {
#endif
#include "stm32f30x.h"
#include "main.h"

#define CMD_RESET 0x1E // ADC reset command
#define CMD_ADC_READ 0x00 // ADC read command
#define CMD_ADC_CONV 0x40 // ADC conversion command
#define CMD_ADC_D1 0x00 // ADC D1 conversion
#define CMD_ADC_D2 0x10 // ADC D2 conversion
#define CMD_ADC_256 0x00 // ADC OSR=256
#define CMD_ADC_512 0x02 // ADC OSR=512
#define CMD_ADC_1024 0x04 // ADC OSR=1024
#define CMD_ADC_2048 0x06 // ADC OSR=2056
#define CMD_ADC_4096 0x08 // ADC OSR=4096
#define CMD_PROM_RD 0xA2 // Prom read command

#define MS5611_CS_pin  GPIO_Pin_8
#define MS5611_CS_GPIO  GPIOD

uint8_t SPI2_send_byte(uint8_t data);
#ifdef __cplusplus
}
#endif


#endif
