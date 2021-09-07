#ifndef __PERIPH_INIT_H
#define __PERIPH_INIT_H

#ifdef __cplusplus
 extern "C" {
#endif
#include "stm32f30x.h"
#include "main.h"

#define Loop_time          8000
#define Pressure_time      100
 uint16_t PWM_main_frequency=400;
 uint32_t PWM_frequency=1000000;

 void PWM_init();
 void Input_PWM();
 void TIM1_init();
 void Timer_init();
 void LED_config();
 void SPI_init();
 void Ext_int_IRQ();
#ifdef __cplusplus
}
#endif

#endif
