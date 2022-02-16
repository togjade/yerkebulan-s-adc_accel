
#include "MS5611.h"

uint8_t SPI2_send_byte(uint8_t data)
{
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE)==RESET)
	{
	}

	SPI_SendData8(SPI2, data);
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE)==RESET)
	{
	}
	return SPI_ReceiveData8(SPI2);

}

void PROM_read(uint16_t* buffer)
{
uint8_t i;
uint16_t result;
GPIO_ResetBits(MS5611_CS_GPIO,MS5611_CS_pin);
SPI2_send_byte(CMD_PROM_RD);
for(i=0;i<6;i++)
{
	*(buffer+i)=SPI2_send_byte(0x00)<<8;
	(*(buffer+i))|=SPI2_send_byte(0x00);

}
GPIO_SetBits(MS5611_CS_GPIO,MS5611_CS_pin);

}

//this function sends ADC conversion command
//
//Conversion time varies depending on the sampling number
void Send_adc_command(uint8_t Sampling_num)
{
	GPIO_ResetBits(MS5611_CS_GPIO,MS5611_CS_pin);
	SPI2_send_byte(Sampling_num);
	GPIO_SetBits(MS5611_CS_GPIO,MS5611_CS_pin);
}

int Read_Pressue_Tmp()
{
	int result=0;
	GPIO_ResetBits(MS5611_CS_GPIO,MS5611_CS_pin);
	SPI2_send_byte(CMD_ADC_READ);
	result=SPI2_send_byte(0x00)<<2;
	result|=SPI2_send_byte(0x00)<<1;
	result|=SPI2_send_byte(0x00);
	GPIO_SetBits(MS5611_CS_GPIO,MS5611_CS_pin);
	return result;
}
