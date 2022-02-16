/**
  ******************************************************************************
  * @file    stm32_it.h
  * @author  MCD Application Team
  * @version V4.0.0
  * @date    21-January-2013
  * @brief   This file contains the headers of the interrupt handlers.
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


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32_IT_H
#define __STM32_IT_H

/* Includes ------------------------------------------------------------------*/
#include "platform_config.h"
#include "main.h"
#include <stdbool.h>
#include <stdio.h>

//#define ADD_correleation;

uint16_t global_incrementer;
int16_t data_sample;
int16_t window_increment;
int32_t sqr1[window_size];
int32_t sqr2[window_size];
int32_t sqr3[window_size];



int32_t product[window_size];
int32_t product3[window_size];



int32_t mean1[window_size];
int32_t mean2[window_size];
int32_t mean3[window_size];

int32_t tempdata1;
int32_t tempdata2;
int64_t tempdata3;
int64_t tempdata4;
int64_t tempdata5;

int64_t sum_sqr1;
int64_t sum_sqr2;
int64_t sum_sqr3;

int64_t sum_product;
int64_t sum_product3;
int16_t corr_final[window_size];
int64_t sum_sqrt1;
int64_t sum_sqrt2;

int32_t sum_mean1;
int32_t sum_mean2;
int32_t sum_mean3;


int16_t corr_result;
int16_t corr_result3;


int16_t acc_data[SPI1_datasize];
int16_t corData1;
int16_t corData2;
int16_t corData3;
uint8_t checkMov1;
uint8_t checkMov2;

uint8_t slippagetime;
int corrSum;

int16_t positionEncoder;
int16_t positionEncoder2;
int16_t positionEncoderOld;
int16_t positionEncoder2Old;




uint8_t encDirect;
extern int Sys_delay;

uint8_t start_computing_Gain;
void USB_LP_CAN1_RX0_IRQHandler(void);
void USART1_IRQHandler(void);
void DMA1_Channel2_IRQHandler(void);
void DMA1_Channel3_IRQHandler(void);
void TIM4_IRQHandler(void);
void SysTick_Handler(void);
void TIM2_IRQHandler(void);
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);

#endif /* __STM32_IT_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
