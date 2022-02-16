/* Includes ------------------------------------------------------------------*/

#include "main.h"

EXTI_InitTypeDef exti;

 uint16_t SPI1_data_Tx[SPI1_datasize];
 uint16_t SPI1_data_Rx[SPI1_datasize]={5};
 uint8_t  USB_buffer[64]={0x15};

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

uint8_t send_data=0;


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
	register_value=Register<<8;
	register_value|=data;
	GPIO_ResetBits(MPU6000_CS_GPIO,MPU6000_CS_Pin);
	delay_ms(1);
	SPI_write_byte(register_value);
	delay_ms(1);
	GPIO_SetBits(MPU6000_CS_GPIO,MPU6000_CS_Pin);
}

void MPU6000_init()
{
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


    /*
	MPU6000_Write_reg(0x27,0x0e);
	delay_ms(1);
	MPU6000_Write_reg(0x28,0x01);
	delay_ms(1);
	MPU6000_Write_reg(0x29,0x02);
	delay_ms(1);
	MPU6000_Write_reg(0x2a,0x03);
	delay_ms(1);
	MPU6000_Write_reg(0x2b,0x04);
	delay_ms(1);
	MPU6000_Write_reg(0x2c,0x05);
	delay_ms(1);
	MPU6000_Write_reg(0x2d,0x06);
	delay_ms(1);

	MPU6000_Write_reg(0x2e,0x07);
	delay_ms(1);
	MPU6000_Write_reg(0x2f,0x08);
	delay_ms(1);
	MPU6000_Write_reg(0x30,0x09);
	delay_ms(1);
	MPU6000_Write_reg(0x31,0x0a);
	delay_ms(1);
	MPU6000_Write_reg(0x32,0x0b);
	delay_ms(1);
	MPU6000_Write_reg(0x33,0x0c);
	delay_ms(1);
	MPU6000_Write_reg(0x34,0x0d);
	delay_ms(1);
	*/

}

void Enable_interrupts()
{

	NVIC_EnableIRQ(DMA1_Channel3_IRQn);
	NVIC_EnableIRQ(DMA1_Channel2_IRQn);
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	//SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Rx, ENABLE);
	//SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Tx, ENABLE);
	//DMA_ITConfig(DMA1_Channel3, DMA_IT_TC, ENABLE);
	//DMA_ITConfig(DMA1_Channel2, DMA_IT_TC, ENABLE);

}

void Init_SPI1_buffer()
{
	uint8_t i;
	SPI1_data_Tx[0]=0x3a00;
	SPI1_data_Tx[0]|=0x8000;

}

int main(void)
{
	int i=0;

	G.p=0.07f;
	G.q=0.08f;
	G.r=0.06f;

	Q.s=-0.6219f;
	Q.x=0.4020f;
	Q.y=-0.4020f;
	Q.z=0.0f;

	A.X=0.7664f;
	A.Y=0.17165f;
	A.Z=0.865f;


	SysTick_Config(SystemCoreClock/1000000);

	delay_ms(100);
	Set_System();
	Set_USBClock();
	USB_Config();
	USB_Init();
	delay_ms(3000);
	Init_Kalman(&K);
	Init_SPI1_buffer();

	LED_config();
	GPIO_SetBits(GPIOD,GPIO_Pin_15);
	SPI_init();
	GPIO_SetBits(MPU6000_CS_GPIO,MPU6000_CS_Pin);
	TIM1_init();
	MPU6000_init();
	delay_ms(1000);
	SPI_init();
    Enable_interrupts();
	while(1)
{

		if(send_data==1)
		{
		GPIO_SetBits(GPIOD,GPIO_Pin_13);
		send_data=0;
		TX_byte((uint8_t *)&USB_buffer,64);
		GPIO_ResetBits(GPIOD,GPIO_Pin_13);
		}

}
}




