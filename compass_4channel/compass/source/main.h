#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f30x.h"
#include "hw_config.h"
#include "usb_lib.h"
#include "usb_desc.h"
#include "usb_pwr.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stm32f30x_dma.h>
#include <Kalman.h>
#include <Quaternion.h>

#define Rad_to_deg         57.3
#define Acc_filter   			 98
#define Gyro_moving_average_length  5
#define Yaw_shift           0
#define Roll_shift            6.5
#define Pitch_shift           1.5
//4
#define SPI1_datasize        4

#if SPI1_datasize==2
#define wChannelConfig        0x0300   //2 channels
#elif SPI1_datasize==4
#define wChannelConfig        0x0107   //4 channels
#elif SPI1_datasize==6
#define wChannelConfig        0x0707   //6 channels
#elif SPI1_datasize==8
#define wChannelConfig        0x0f0f   //8 channels
#endif

//#define wChannelConfig        0x0107 //4 channels
//#define wChannelConfig        0x0707 //6 channels
//#define wChannelConfig        0x0f0f //8 channels
//#define wChannelConfig        0x0f3f //10 channels

#define MPU6000_CS_Pin            GPIO_Pin_1
#define MPU6000_CS_GPIO           GPIOB
#define MPU6000_IRQ_Pin            GPIO_Pin_4
#define MPU6000_IRQ_GPIO           GPIOA

#define LED_Pin1            GPIO_Pin_15
#define LED_Pin2            GPIO_Pin_10
#define LED_Pin3            GPIO_Pin_9
#define LED_GPIO           GPIOE
#define samplingFrequency    8000
#define window_size          700
uint8_t time_counter;
uint8_t SOFCount;
uint8_t sendSOF;
uint8_t sendBytes;
 uint16_t  USB_buffer[128];
 uint16_t  USB_buffer2[64];
 uint16_t  USB_buffer3[64];
 uint16_t addresBuffer;
 uint8_t startSample;
 uint16_t clockChange;
 uint16_t SPI1_data_Tx[SPI1_datasize];
 uint16_t SPI1_data_Rx[SPI1_datasize];
uint8_t numberOfSamplesPerFrame;
int16_t dataCheck;


int8_t incrementEnc1;
 int8_t incrementEnc2;
 uint8_t checkIncrement1;
 uint8_t checkIncrement2;

uint8_t usbStartdata;
uint8_t send_data;

uint16_t counterPWMBuffer;
int16_t external_signal_buffer[512];
int32_t meanValue;
uint16_t sizeBuffer;
int16_t pwmValue;


#endif /* __MAIN_H */
