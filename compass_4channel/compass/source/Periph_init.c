

#include "Periph_init.h"
#include "stm32f30x_tim.h"
#include "MS5611.h"

uint8_t k=0;
void PWM_init()
{
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;
GPIO_InitTypeDef GPIO_InitStructure;
RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC | RCC_AHBPeriph_GPIOB, ENABLE);


TIM_TimeBaseStructure.TIM_ClockDivision=0;
TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
TIM_TimeBaseStructure.TIM_Period=(uint16_t)(PWM_frequency/PWM_main_frequency-1);
TIM_TimeBaseStructure.TIM_Prescaler=(uint16_t) ((SystemCoreClock) / PWM_frequency) - 1;
TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
TIM_OCInitStructure.TIM_Pulse=0;
TIM_OC1Init(TIM3, &TIM_OCInitStructure);
TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

TIM_OC2Init(TIM3, &TIM_OCInitStructure);
TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
TIM_OC3Init(TIM3, &TIM_OCInitStructure);
TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
TIM_OC4Init(TIM3, &TIM_OCInitStructure);
TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);

TIM_ARRPreloadConfig(TIM3, ENABLE);

 /* TIM3 enable counter */
 TIM_Cmd(TIM3, ENABLE);
//GPIO initialization
GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;
GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;

GPIO_Init(GPIOC, &GPIO_InitStructure);
GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_2);
GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_2);
GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_2);
GPIO_PinAFConfig(GPIOC, GPIO_PinSource9, GPIO_AF_2);



 //TIM_CtrlPWMOutputs(TIM3, ENABLE);
 TIM_CCxCmd(TIM3,TIM_Channel_1,TIM_CCx_Enable);
 TIM_CCxCmd(TIM3,TIM_Channel_2,TIM_CCx_Enable);
 TIM_CCxCmd(TIM3,TIM_Channel_3,TIM_CCx_Enable);
 TIM_CCxCmd(TIM3,TIM_Channel_4,TIM_CCx_Enable);
}

void Input_PWM()
{
TIM_TimeBaseInitTypeDef  timer_init;
TIM_ICInitTypeDef  TIM_ICInitStructure;
NVIC_InitTypeDef NVIC_InitStructure;


	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);

	TIM_TimeBaseStructInit(&timer_init);

	timer_init.TIM_CounterMode=TIM_CounterMode_Up;
	timer_init.TIM_Period=PWM_frequency/50-1;
	timer_init.TIM_Prescaler=(uint16_t) ((SystemCoreClock) / PWM_frequency) - 1;
	TIM_TimeBaseInit(TIM2, &timer_init);


	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;

	//TIM2, channel 2
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_1);


	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_ICInitStructure.TIM_Channel=TIM_Channel_2;
	TIM_ICInitStructure.TIM_ICFilter=0x05;
	TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_BothEdge;
	TIM_ICInitStructure.TIM_ICPrescaler=TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;
	TIM_ICInit(TIM2,&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel=TIM_Channel_1;
	TIM_ICInit(TIM2,&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel=TIM_Channel_3;
	TIM_ICInit(TIM2,&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel=TIM_Channel_4;
	TIM_ICInit(TIM2,&TIM_ICInitStructure);

	//TIM_SelectInputTrigger(TIM2,TIM_TS_TI2FP2);
	//TIM_SelectSlaveMode(TIM2,TIM_SlaveMode_Reset);
	//TIM_SelectMasterSlaveMode(TIM2,TIM_MasterSlaveMode_Enable);
	/* TIM3 enable counter */
	//TIM_ARRPreloadConfig(TIM2, ENABLE);
	//TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_ENABLE);
	TIM_Cmd(TIM2, ENABLE);
	TIM_ITConfig(TIM2,TIM_IT_CC2,ENABLE);
	TIM_ITConfig(TIM2,TIM_IT_CC1,ENABLE);
	TIM_ITConfig(TIM2,TIM_IT_CC3,ENABLE);
	TIM_ITConfig(TIM2,TIM_IT_CC4,ENABLE);

}

void TIM1_init()
{
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
NVIC_InitTypeDef NVIC_InitStructure;
RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);


TIM_TimeBaseStructure.TIM_ClockDivision=0;
TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
TIM_TimeBaseStructure.TIM_Period=PWM_frequency/Loop_time-1;
TIM_TimeBaseStructure.TIM_Prescaler=(uint16_t) ((SystemCoreClock) / PWM_frequency) - 1;
TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
TIM_TimeBaseStructure.TIM_Period=PWM_frequency/Pressure_time-1;
TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);


NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&NVIC_InitStructure);
NVIC_EnableIRQ(TIM4_IRQn);

NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 7;
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0xff;
NVIC_Init(&NVIC_InitStructure);
NVIC_EnableIRQ(TIM7_IRQn);

//TIM_Cmd(TIM4, ENABLE);
//TIM_Cmd(TIM7, ENABLE);


}


void Timer_init()
{
	TIM_TimeBaseInitTypeDef  timer_init;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	TIM_TimeBaseStructInit(&timer_init);

	timer_init.TIM_CounterMode=TIM_CounterMode_Up;
	timer_init.TIM_Period=0xffffffff;
	timer_init.TIM_Prescaler=TIM_CKD_DIV1;

	TIM_TimeBaseInit(TIM4, &timer_init);
	TIM_Cmd(TIM4, ENABLE);

}

void LED_config()
{
	GPIO_InitTypeDef led;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD,ENABLE);
	led.GPIO_Mode=GPIO_Mode_OUT;
	led.GPIO_OType=GPIO_OType_PP;
	led.GPIO_Pin=LED_Pin1 |LED_Pin2 |LED_Pin3 ;
	led.GPIO_PuPd=GPIO_PuPd_NOPULL;
	led.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(LED_GPIO,&led);
	led.GPIO_Pin=GPIO_Pin_1 ;
	GPIO_Init(GPIOA,&led);


}

void SPI_init()
	{
		SPI_InitTypeDef spi_init;
		GPIO_InitTypeDef gpio_init;
    DMA_InitTypeDef DMA_InitStructure;

		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB,ENABLE);
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB1Periph_SPI2,ENABLE);


		GPIO_PinAFConfig(GPIOB,GPIO_PinSource13,GPIO_AF_5);
		GPIO_PinAFConfig(GPIOB,GPIO_PinSource14,GPIO_AF_5);
		GPIO_PinAFConfig(GPIOB,GPIO_PinSource15,GPIO_AF_5);

		GPIO_PinAFConfig(GPIOA,GPIO_PinSource5,GPIO_AF_5);
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_5);
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_5);


		gpio_init.GPIO_Mode=GPIO_Mode_AF;
		gpio_init.GPIO_OType=GPIO_OType_PP;
		gpio_init.GPIO_Pin=GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
		gpio_init.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOA,&gpio_init);
		gpio_init.GPIO_Pin=GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
		GPIO_Init(GPIOB,&gpio_init);

		//SPI1 CS pin:
		gpio_init.GPIO_Mode=GPIO_Mode_OUT;
		gpio_init.GPIO_OType=GPIO_OType_PP;
		gpio_init.GPIO_PuPd=GPIO_PuPd_DOWN;
		gpio_init.GPIO_Pin=MPU6000_CS_Pin;
		gpio_init.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(MPU6000_CS_GPIO,&gpio_init);

		// SPI 1 IRQ Pin
		gpio_init.GPIO_Mode=GPIO_Mode_IN;
		gpio_init.GPIO_Pin=MPU6000_IRQ_Pin;
		//gpio_init.GPIO_PuPd=GPIO_PuPd_DOWN;
		gpio_init.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(MPU6000_IRQ_GPIO,&gpio_init);

		gpio_init.GPIO_Mode=GPIO_Mode_IN;
		gpio_init.GPIO_Pin=GPIO_Pin_0;
		gpio_init.GPIO_PuPd=GPIO_PuPd_UP;
		gpio_init.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOD,&gpio_init);



		gpio_init.GPIO_Mode=GPIO_Mode_OUT;
		gpio_init.GPIO_Pin=GPIO_Pin_7;
		gpio_init.GPIO_PuPd=GPIO_PuPd_UP;
		gpio_init.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOD,&gpio_init);

		spi_init.SPI_BaudRatePrescaler= SPI_BaudRatePrescaler_8;
		spi_init.SPI_CPHA=SPI_CPHA_2Edge ;
		spi_init.SPI_CPOL=SPI_CPOL_High;
		spi_init.SPI_Direction=SPI_Direction_2Lines_FullDuplex ;
		spi_init.SPI_FirstBit=SPI_FirstBit_MSB;
		spi_init.SPI_Mode=SPI_Mode_Master  ;
		spi_init.SPI_NSS=SPI_NSS_Soft;
		spi_init.SPI_DataSize=SPI_DataSize_16b;
		SPI_Init(SPI1,&spi_init);

		spi_init.SPI_DataSize=SPI_DataSize_8b;
		SPI_Init(SPI2,&spi_init);


		DMA_InitStructure.DMA_BufferSize=SPI1_datasize;
		DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralDST;
		DMA_InitStructure.DMA_M2M=DMA_M2M_Disable;
		DMA_InitStructure.DMA_MemoryBaseAddr=(uint32_t)SPI1_data_Tx;
		DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;
		DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable;
		DMA_InitStructure.DMA_Mode=DMA_Mode_Normal;
		DMA_InitStructure.DMA_PeripheralBaseAddr=(uint32_t)(&(SPI1->DR));
		DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;
		DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
		DMA_InitStructure.DMA_Priority=DMA_Priority_Medium;

		DMA_Init(DMA1_Channel3,&DMA_InitStructure);
		DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;
		DMA_InitStructure.DMA_BufferSize=SPI1_datasize;
		DMA_InitStructure.DMA_MemoryBaseAddr=(uint32_t)SPI1_data_Rx;
		DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralSRC;
		DMA_InitStructure.DMA_Mode=DMA_Mode_Normal;
		DMA_Init(DMA1_Channel2,&DMA_InitStructure);



		SPI_Cmd(SPI1,ENABLE);
		SPI_Cmd(SPI2,ENABLE);

	}

void Ext_int_IRQ()
{

	GPIO_InitTypeDef ext_int;
	EXTI_InitTypeDef   EXTI_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;


	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	//PIn initlialize
	ext_int.GPIO_Mode=GPIO_Mode_IN;
	ext_int.GPIO_OType= GPIO_OType_OD;
	ext_int.GPIO_Pin=GPIO_Pin_1|GPIO_Pin_0;
	ext_int.GPIO_Speed=GPIO_Speed_50MHz;

	GPIO_Init(GPIOC, &ext_int);

	ext_int.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_3;
	GPIO_Init(GPIOB, &ext_int);





	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource0);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource3);

	//Configuring the channel of external interrupt
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	EXTI_InitStructure.EXTI_Line = EXTI_Line3;
	EXTI_Init(&EXTI_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0xff;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
	NVIC_Init(&NVIC_InitStructure);
	}


