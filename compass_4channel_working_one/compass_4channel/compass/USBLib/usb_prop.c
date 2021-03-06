/**
  ******************************************************************************
  * @file    usb_prop.c
  * @author  MCD Application Team
  * @version V4.0.0
  * @date    21-January-2013
  * @brief   All processing related to Audio MICROPHONE Demo
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
#include "usb_lib.h"
#include "usb_conf.h"
#include "usb_prop.h"
#include "usb_desc.h"
#include "usb_pwr.h"
#include "main.h"
//
//extern uint8_t sendBytes;
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t MUTE_DATA = 0;

DEVICE Device_Table =
  {
    EP_NUM,
    1
  };

DEVICE_PROP Device_Property =
  {
    MICROPHONE_init,
    MICROPHONE_Reset,
    MICROPHONE_Status_In,
    MICROPHONE_Status_Out,
    MICROPHONE_Data_Setup,
    MICROPHONE_NoData_Setup,
    MICROPHONE_Get_Interface_Setting,
    MICROPHONE_GetDeviceDescriptor,
    MICROPHONE_GetConfigDescriptor,
    MICROPHONE_GetStringDescriptor,
    0,
    0x40 /*MAX PACKET SIZE*/
  };

USER_STANDARD_REQUESTS User_Standard_Requests =
  {
    MICROPHONE_GetConfiguration,
    MICROPHONE_SetConfiguration,
    MICROPHONE_GetInterface,
    MICROPHONE_SetInterface,
    MICROPHONE_GetStatus,
    MICROPHONE_ClearFeature,
    MICROPHONE_SetEndPointFeature,
    MICROPHONE_SetDeviceFeature,
    MICROPHONE_SetDeviceAddress
  };

ONE_DESCRIPTOR Device_Descriptor =
  {
    (uint8_t*)MICROPHONE_DeviceDescriptor,
    MICROPHONE_SIZ_DEVICE_DESC
  };

ONE_DESCRIPTOR Config_Descriptor =
  {
    (uint8_t*)MICROPHONE_ConfigDescriptor,
    MICROPHONE_SIZ_CONFIG_DESC
  };

ONE_DESCRIPTOR String_Descriptor[4] =
  {
    {(uint8_t*)MICROPHONE_StringLangID, MICROPHONE_SIZ_STRING_LANGID},
    {(uint8_t*)MICROPHONE_StringVendor, MICROPHONE_SIZ_STRING_VENDOR},
    {(uint8_t*)MICROPHONE_StringProduct, MICROPHONE_SIZ_STRING_PRODUCT},
    {(uint8_t*)MICROPHONE_StringSerial, MICROPHONE_SIZ_STRING_SERIAL},
  };

/* Extern variables ----------------------------------------------------------*/
/* Extern variables ----------------------------------------------------------*/
extern uint16_t In_Data_Offset;
extern uint16_t Out_Data_Offset;

/* Private function prototypes -----------------------------------------------*/
/* Extern function prototypes ------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : MICROPHONE_init.
* Description    : MICROPHONE init routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void MICROPHONE_init()
{
  /* Update the serial number string descriptor with the data from the unique
  ID*/
  Get_SerialNum();

  /* Initialize the current configuration */
  pInformation->Current_Configuration = 0;

  /* Connect the device */
  PowerOn();

  /* Perform basic device initialization operations */
  USB_SIL_Init();

  bDeviceState = UNCONNECTED;
}

/*******************************************************************************
* Function Name  : MICROPHONE_Reset.
* Description    : MICROPHONE reset routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void MICROPHONE_Reset()
{

  /* Set MICROPHONE device as not configured state */
  pInformation->Current_Configuration = 0;

  /* Current Feature initialization */
  pInformation->Current_Feature = MICROPHONE_ConfigDescriptor[7];

  SetBTABLE(BTABLE_ADDRESS);

  /* Initialize Endpoint 0 */
  SetEPType(ENDP0, EP_CONTROL);
  SetEPTxStatus(ENDP0, EP_TX_NAK);
  SetEPRxAddr(ENDP0, ENDP0_RXADDR);
  SetEPRxCount(ENDP0, Device_Property.MaxPacketSize);
  SetEPTxAddr(ENDP0, ENDP0_TXADDR);
  Clear_Status_Out(ENDP0);
  SetEPRxValid(ENDP0);

  /* Initialize Endpoint 1 */
  SetEPType(ENDP1, EP_ISOCHRONOUS);
  SetEPDblBuffAddr(ENDP1, ENDP1_BUF0Addr, ENDP1_BUF1Addr);
  SetEPDblBuffCount(ENDP1, EP_DBUF_IN, sendBytes);
  ClearDTOG_RX(ENDP1);
  ClearDTOG_TX(ENDP1);
  ToggleDTOG_RX(ENDP1);
  SetEPTxStatus(ENDP1, EP_TX_VALID);
  SetEPRxStatus(ENDP1, EP_RX_DIS);

  SetEPRxValid(ENDP0);
  /* Set this device to response on default address */
  SetDeviceAddress(0);

  bDeviceState = ATTACHED;

  In_Data_Offset = 0;
  Out_Data_Offset = 0;
}
/*******************************************************************************
* Function Name  : MICROPHONE_SetConfiguration.
* Description    : Update the device state to configured.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void MICROPHONE_SetConfiguration(void)
{
  DEVICE_INFO *pInfo = &Device_Info;

  if (pInfo->Current_Configuration != 0)
  {
    /* Device configured */
    bDeviceState = CONFIGURED;
  }
}
/*******************************************************************************
* Function Name  : MICROPHONE_SetConfiguration.
* Description    : Update the device state to addressed.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void MICROPHONE_SetDeviceAddress (void)
{
  bDeviceState = ADDRESSED;
}
/*******************************************************************************
* Function Name  : MICROPHONE_Status_In.
* Description    : MICROPHONE Status In routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void MICROPHONE_Status_In(void)
{}

/*******************************************************************************
* Function Name  : MICROPHONE_Status_Out.
* Description    : MICROPHONE Status Out routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void MICROPHONE_Status_Out (void)
{}

/*******************************************************************************
* Function Name  : MICROPHONE_Data_Setup
* Description    : Handle the data class specific requests.
* Input          : None.
* Output         : None.
* Return         : USB_UNSUPPORT or USB_SUCCESS.
*******************************************************************************/
RESULT MICROPHONE_Data_Setup(uint8_t RequestNo)
{
  uint8_t *(*CopyRoutine)(uint16_t);
  CopyRoutine = NULL;

  if ((RequestNo == GET_CUR) || (RequestNo == SET_CUR))
  {
    CopyRoutine = Mute_Command;
  }

  else
  {
    return USB_UNSUPPORT;
  }

  pInformation->Ctrl_Info.CopyData = CopyRoutine;
  pInformation->Ctrl_Info.Usb_wOffset = 0;
  (*CopyRoutine)(0);
  return USB_SUCCESS;
}

/*******************************************************************************
* Function Name  : MICROPHONE_NoData_Setup
* Description    : Handle the no data class specific requests.
* Input          : None.
* Output         : None.
* Return         : USB_UNSUPPORT or USB_SUCCESS.
*******************************************************************************/
RESULT MICROPHONE_NoData_Setup(uint8_t RequestNo)
{
  return USB_UNSUPPORT;
}

/*******************************************************************************
* Function Name  : MICROPHONE_GetDeviceDescriptor.
* Description    : Get the device descriptor.
* Input          : Length : uint16_t.
* Output         : None.
* Return         : The address of the device descriptor.
*******************************************************************************/
uint8_t *MICROPHONE_GetDeviceDescriptor(uint16_t Length)
{
  return Standard_GetDescriptorData(Length, &Device_Descriptor);
}

/*******************************************************************************
* Function Name  : MICROPHONE_GetConfigDescriptor.
* Description    : Get the configuration descriptor.
* Input          : Length : uint16_t.
* Output         : None.
* Return         : The address of the configuration descriptor.
*******************************************************************************/
uint8_t *MICROPHONE_GetConfigDescriptor(uint16_t Length)
{
  return Standard_GetDescriptorData(Length, &Config_Descriptor);
}

/*******************************************************************************
* Function Name  : MICROPHONE_GetStringDescriptor.
* Description    : Get the string descriptors according to the needed index.
* Input          : Length : uint16_t.
* Output         : None.
* Return         : The address of the string descriptors.
*******************************************************************************/
uint8_t *MICROPHONE_GetStringDescriptor(uint16_t Length)
{
  uint8_t wValue0 = pInformation->USBwValue0;

  if (wValue0 > 4)
  {
    return NULL;
  }
  else
  {
    return Standard_GetDescriptorData(Length, &String_Descriptor[wValue0]);
  }
}

/*******************************************************************************
* Function Name  : MICROPHONE_Get_Interface_Setting.
* Description    : test the interface and the alternate setting according to the
*                  supported one.
* Input1         : uint8_t: Interface : interface number.
* Input2         : uint8_t: AlternateSetting : Alternate Setting number.
* Output         : None.
* Return         : The address of the string descriptors.
*******************************************************************************/
RESULT MICROPHONE_Get_Interface_Setting(uint8_t Interface, uint8_t AlternateSetting)
{
  if (AlternateSetting > 1)
  {
    return USB_UNSUPPORT;
  }
  else if (Interface > 1)
  {
    return USB_UNSUPPORT;
  }
  return USB_SUCCESS;
}

/*******************************************************************************
* Function Name  : Mute_Command
* Description    : Handle the GET MUTE and SET MUTE command.
* Input          : Length : uint16_t.
* Output         : None.
* Return         : The address of the string descriptors.
*******************************************************************************/
uint8_t *Mute_Command(uint16_t Length)
{

  if (Length == 0)
  {
    pInformation->Ctrl_Info.Usb_wLength = pInformation->USBwLengths.w;
    return NULL;
  }
  else
  {
    return((uint8_t*)(&MUTE_DATA));
  }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

