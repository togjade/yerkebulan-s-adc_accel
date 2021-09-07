/**
  ******************************************************************************
  * @file    usb_prop.h
  * @author  MCD Application Team
  * @version V4.0.0
  * @date    21-January-2013
  * @brief   All processing related to Mass Storage Demo (Endpoint 0)
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
#ifndef __usb_prop_H
#define __usb_prop_H
#include "main.h"
/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void MICROPHONE_init(void);
void MICROPHONE_Reset(void);
void MICROPHONE_SetConfiguration(void);
void MICROPHONE_SetDeviceAddress (void);
void MICROPHONE_Status_In (void);
void MICROPHONE_Status_Out (void);
RESULT MICROPHONE_Data_Setup(uint8_t);
RESULT MICROPHONE_NoData_Setup(uint8_t);
RESULT MICROPHONE_Get_Interface_Setting(uint8_t Interface, uint8_t AlternateSetting);
uint8_t *MICROPHONE_GetDeviceDescriptor(uint16_t );
uint8_t *MICROPHONE_GetConfigDescriptor(uint16_t);
uint8_t *MICROPHONE_GetStringDescriptor(uint16_t);
uint8_t *Mute_Command(uint16_t Length);

/* Exported define -----------------------------------------------------------*/
#define MICROPHONE_GetConfiguration          NOP_Process
//#define MICROPHONE_SetConfiguration          NOP_Process
#define MICROPHONE_GetInterface              NOP_Process
#define MICROPHONE_SetInterface              NOP_Process
#define MICROPHONE_GetStatus                 NOP_Process
#define MICROPHONE_ClearFeature              NOP_Process
#define MICROPHONE_SetEndPointFeature        NOP_Process
#define MICROPHONE_SetDeviceFeature          NOP_Process
//#define MICROPHONE_SetDeviceAddress          NOP_Process
#define GET_CUR                           0x81
#define SET_CUR                           0x01

#endif /* __usb_prop_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

