/* Includes ------------------------------------------------------------------*/

#include "main.h"

EXTI_InitTypeDef exti;


 uint16_t USB_bufferZeros[64];
//Kalman variables
float32_t Gain_Mult1[6];
float32_t Gain_Mult2[6];
float32_t Gain_result[6];

Gyro   G;
Accelerometer A;
Accelerometer A_pred;
Quaternion    Q;
Quaternion    Q_new;
Kalman K;
/////////////////////////



uint8_t needsend=0;
int Sys_delay;
uint16_t i=0,j=0;
float gyro_body[3];


uint8_t usb_data_count;
int Sys_delay;
void delay_ms(int time);
void delay_us(int time);
uint8_t gyro_count=10;

bool start_flight=0;
/*
PA5,PA6,PA7-SCK,MISO,MOSI
PD5,PD0-CS,IRQ
*/


/*
*/

uint8_t SPI_write_byte(uint16_t data)
{
while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE)==RESET)
{
}

  SPI1->DR=data;
while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE)==RESET)
{
}

}

void delay_ms(int time)
{
	Sys_delay=time*1000;
	while(Sys_delay!=0);
}

void delay_us(int time)
{
	Sys_delay=time;
	//time=SystemCoreClock;
	while(Sys_delay!=0);
}





void TX_byte(uint8_t* data,uint8_t size)
{
	USB_SIL_Write(EP1_IN,data,size);
	SetEPTxValid(ENDP1);

}

void MPU6000_Write_reg(uint8_t Register,uint8_t data)
{
	uint16_t register_value;
	uint16_t data_SPI;
	register_value=Register<<8;
	register_value|=data;
	GPIO_ResetBits(MPU6000_CS_GPIO,MPU6000_CS_Pin);
	delay_ms(1);
	data_SPI=SPI_write_byte(register_value);
	delay_ms(1);
	GPIO_SetBits(MPU6000_CS_GPIO,MPU6000_CS_Pin);
}

void MPU6000_init()
{
	uint16_t data;
	MPU6000_Write_reg(0x1b,0x10);
	delay_ms(1);
	MPU6000_Write_reg(0x1c,0x08);
	delay_ms(1);
	MPU6000_Write_reg(0x6b,0x01);
	delay_ms(1);
	MPU6000_Write_reg(0x37,0xb0);
	delay_ms(1);
	MPU6000_Write_reg(0x38,0x01);
	delay_ms(1);

	GPIO_ResetBits(MPU6000_CS_GPIO,MPU6000_CS_Pin);
	delay_ms(1);
	data=SPI_write_byte(0xffff);
	data=SPI_write_byte(0xffff);
	delay_ms(1);
	GPIO_SetBits(MPU6000_CS_GPIO,MPU6000_CS_Pin);

}

void Enable_interrupts()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	//SPI DMA:
		NVIC_InitStructure.NVIC_IRQChannel=DMA1_Channel2_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority=5;
		NVIC_Init(&NVIC_InitStructure);

		//SPI DMA:
		NVIC_InitStructure.NVIC_IRQChannel=DMA1_Channel3_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority=4;
		NVIC_Init(&NVIC_InitStructure);

		NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn ;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
		//data transfer complete interrupt enable

	NVIC_EnableIRQ(DMA1_Channel3_IRQn);
	NVIC_EnableIRQ(DMA1_Channel2_IRQn);

	SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Rx, ENABLE);
	SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Tx, ENABLE);
	DMA_ITConfig(DMA1_Channel3, DMA_IT_TC, ENABLE);
	DMA_ITConfig(DMA1_Channel2, DMA_IT_TC, ENABLE);

}

void Init_SPI1_buffer()
{
	uint8_t i;
	SPI1_data_Tx[0]=0xff;
	SPI1_data_Tx[1]=0xff;

}

int main(void)
{
	int i=0;
	clockChange=0;
	SOFCount=0;;
	sendSOF=0;
	sizeBuffer=512;
	meanValue=0;
	counterPWMBuffer=0;
	for(i=0;i<sizeBuffer;i++)
	{
		external_signal_buffer[i]=0;
	}

	numberOfSamplesPerFrame=samplingFrequency*SPI1_datasize/1000;
	sendBytes=numberOfSamplesPerFrame*2;
	time_counter=0;
	incrementEnc1=-32;
	incrementEnc2=32;
	checkIncrement1=0;
	checkIncrement2=0;
	SysTick_Config(SystemCoreClock/1000000);
	delay_ms(100);
    for(i=0;i<64;i++)
    {
    	USB_buffer2[i]=15000;

    }
    for(i=0;i<16;i++)
    {

    		USB_buffer3[i]=i*500;

    }




	Init_SPI1_buffer();

	//_ToggleDTOG_TX(ENDP1);
	LED_config();

	//GPIO_SetBits(LED_GPIO,LED_Pin3);
	Set_System();
	Set_USBClock();
	USB_Config();
	USB_Init();
	SPI_init();
	GPIO_ResetBits(MPU6000_CS_GPIO,MPU6000_CS_Pin);
	TIM1_init();



	delay_ms(1000);
	//SPI_init();
    Enable_interrupts();
    Ext_int_IRQ();





	while(1)
{

		// if(send_data==1)
		//{
		//	GPIO_SetBits(LED_GPIO,LED_Pin3);
		//send_data=0;
		  /* Use the memory interface function to write to the selected endpoint */
		  //UserToPMABufferCopy(((uint8_t *)&USB_buffer), GetEPTxAddr(EP1_IN & 0x7F), sendBytes);
		  /* Update the data length in the control register */
		 // SetEPTxCount((EP1_IN & 0x7F), sendBytes);
		 // SetEPTxValid(ENDP1);
		//  GPIO_ResetBits(LED_GPIO,LED_Pin3);
		//}




}
}




