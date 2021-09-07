/**
  ******************************************************************************
  * @file    stm32_it.c
  * @author  MCD Application Team
  * @version V4.0.0
  * @date    21-January-2013
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "hw_config.h"
#include "stm32_it.h"
#include "usb_lib.h"
#include "usb_istr.h"
#include "usb_pwr.h"



#define DUMMYDATA  0x1111

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint16_t Out_Data_Offset;
extern uint16_t In_Data_Offset;
extern uint8_t Stream_Buff[24];
extern uint32_t MUTE_DATA;
extern uint8_t numberOfSamplesPerFrame;



uint16_t wait_clock=0;;


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/******************************************************************************/
/*            Cortex-M Processor Exceptions Handlers                         */
/******************************************************************************/

/*******************************************************************************
* Function Name  : NMI_Handler
* Description    : This function handles NMI exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NMI_Handler(void)
{
}

/*******************************************************************************
* Function Name  : HardFault_Handler
* Description    : This function handles Hard Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : MemManage_Handler
* Description    : This function handles Memory Manage exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : BusFault_Handler
* Description    : This function handles Bus Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : UsageFault_Handler
* Description    : This function handles Usage Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : SVC_Handler
* Description    : This function handles SVCall exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SVC_Handler(void)
{
}

/*******************************************************************************
* Function Name  : DebugMon_Handler
* Description    : This function handles Debug Monitor exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DebugMon_Handler(void)
{
}

/*******************************************************************************
* Function Name  : PendSV_Handler
* Description    : This function handles PendSV_Handler exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void PendSV_Handler(void)
{
}

/*******************************************************************************
* Function Name  : SysTick_Handler
* Description    : This function handles SysTick Handler.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/


float32_t check_update[16]={ -0.6219, -0.2010, 0.2010, 0,  0.4020,-0.31095,0
		,0.2010,  -0.4020,0,-0.31095,0.2010,0,-0.2010,-0.2010,-0.31095 };
uint8_t i,j;
uint8_t count=0;
uint8_t start_Kalman=0;
void USB_LP_CAN1_RX0_IRQHandler(void)
{
  USB_Istr();
}

void USB_HP_CAN1_TX_IRQHandler(void)
{
  CTR_HP();
}


void USBWakeUp_IRQHandler(void)
{
  EXTI_ClearITPendingBit(EXTI_Line18);
}

void USB_HP_IRQHandler(void)
{
  CTR_HP();
}
/*******************************************************************************
* Function Name  : EVAL_COM1_IRQHandler
* Description    : This function handles EVAL_COM1 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/



void DMA1_Channel3_IRQHandler(void) {


    if (DMA_GetFlagStatus(DMA1_IT_TC3) == SET) {

       while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE) == RESET);
     // while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_BSY) == SET);
      DMA_Cmd(DMA1_Channel3, DISABLE);
	 DMA_SetCurrDataCounter(DMA1_Channel3,SPI1_datasize);
      DMA_ClearITPendingBit(DMA1_IT_TC3);
	//	GPIO_SetBits(LED_GPIO, LED_Pin3);
    }
    GPIO_ResetBits(MPU6000_CS_GPIO,MPU6000_CS_Pin);
  }

void DMA1_Channel2_IRQHandler(void) {

    if (DMA_GetFlagStatus(DMA1_IT_TC2) == SET) {
    	//while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE) == RESET);
    	DMA_Cmd(DMA1_Channel2, DISABLE);
    	DMA_SetCurrDataCounter(DMA1_Channel2,SPI1_datasize);

      DMA_ClearITPendingBit(DMA1_IT_TC2);
     // GPIO_ResetBits(LED_GPIO, LED_Pin3);

    }

  }

void TIM4_IRQHandler(void)
{

if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
    {
     TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
     dataCheck++;
     /*
      * Channel 0= acc1 y axis
      * Channel 1= acc1 x axis
      * Channel 8= acc3 z axis
      *
      * Channel 3=
      * Channel 4= acc2 z axis
      * Channel 5= acc1 z axis
      * Channel 2= acc3 x axis
      * Channel 3= acc3 y axis
      * Channel 6= acc2 y axis
      * Channel 7= acc2 x axis
      */
            // acc_data[6]=(int16_t)(32768-SPI1_data_Rx[4]);
            // acc_data[7]=(int16_t)(32768-SPI1_data_Rx[5]);
            // acc_data[8]=(int16_t)(32768-SPI1_data_Rx[8]);


     	 	 //accelerometer 1 x:
             //
     	 	 GPIO_SetBits(LED_GPIO,LED_Pin1);

     	 	 //5
//     	 	pwmValue=(int16_t)(32767-SPI1_data_Rx[0]);
//     	 	meanValue=meanValue+pwmValue-external_signal_buffer[counterPWMBuffer];
//     	 	external_signal_buffer[counterPWMBuffer]=pwmValue;
//
//     	 	pwmValue=pwmValue-(int16_t)(meanValue/sizeBuffer);
//     	 	USB_buffer[time_counter]=(int16_t)pwmValue;
//     	 	time_counter++;
//     	 	USB_buffer[time_counter]=(int16_t)(32767-SPI1_data_Rx[1]);
//     	 	time_counter++;
     	 	 for(i=0;i<SPI1_datasize;i++)
     	 	 {
     	 		USB_buffer[time_counter]=(int16_t)(32767-SPI1_data_Rx[i]);
     	 		time_counter++;
     	 	 }
     	 	counterPWMBuffer++;
     	 	if (counterPWMBuffer==sizeBuffer )
			{
				counterPWMBuffer=0;
			}
			if(time_counter==numberOfSamplesPerFrame)
			UserToPMABufferCopy(((uint8_t *)&USB_buffer), addresBuffer, sendBytes);

		   GPIO_SetBits(MPU6000_CS_GPIO,MPU6000_CS_Pin);
		   GPIO_ResetBits(LED_GPIO,LED_Pin3);
		   //the program stops in this while loop, it means that there is a problem with the connectors
		   while(GPIO_ReadInputDataBit(MPU6000_IRQ_GPIO,MPU6000_IRQ_Pin )==0);
		   //but in general the usb works. k i'll replace them and try again

		   //usb is working properly.
		   DMA_Cmd(DMA1_Channel2, ENABLE);
		   DMA_Cmd(DMA1_Channel3, ENABLE);


		   GPIO_ResetBits(LED_GPIO,LED_Pin1);

    }



}

void TIM7_IRQHandler(void)
{
if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)
    {
     TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
    }
}


void SysTick_Handler(void)
{
	if(Sys_delay!=0)
	{
	Sys_delay--;
	}
}

void TIM2_IRQHandler(void)
{
if(TIM_GetITStatus(TIM2, TIM_IT_CC1)==SET)
	{


	}


	if(TIM_GetITStatus(TIM2, TIM_IT_CC2)==SET)
	{

	}

if(TIM_GetITStatus(TIM2, TIM_IT_CC3)==SET)
	{

	}



if(TIM_GetITStatus(TIM2, TIM_IT_CC4)==SET)
	{
	TIM_ClearITPendingBit(TIM2, TIM_IT_CC4);
    }
}


