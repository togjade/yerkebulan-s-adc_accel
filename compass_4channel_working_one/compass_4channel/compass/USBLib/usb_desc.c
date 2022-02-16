/**
  ******************************************************************************
  * @file    usb_desc.c
  * @author  MCD Application Team
  * @version V4.0.0
  * @date    21-January-2013
  * @brief   Descriptors for Audio MICROPHONE Demo
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
#include "usb_lib.h"
#include "usb_desc.h"
#include "main.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants----------------------------------------------------------*/
/* USB Standard Device Descriptor */
const uint8_t MICROPHONE_DeviceDescriptor[] =
  {
    MICROPHONE_SIZ_DEVICE_DESC,          /* bLength */
    USB_DEVICE_DESCRIPTOR_TYPE,           /* bDescriptorType */
    0x00,          /* 2.00 */             /* bcdUSB */
    0x01,
    0x00,                                 /* bDeviceClass */
    0x00,                                 /* bDeviceSubClass */
    0x00,                                 /* bDeviceProtocol */
    0x40,                                 /* bMaxPacketSize 40 */
    0x83,                                 /* idVendor */
    0x04,
    0x30,                                 /* idProduct  = 0x5730*/
    0x57,
    0x00,          /* 2.00 */             /* bcdDevice */
    0x02,
    1,                                    /* iManufacturer */
    2,                                    /* iProduct */
    3,                                    /* iSerialNumber */
    0x01                                  /* bNumConfigurations */
  };

/* USB Configuration Descriptor */
/*   All Descriptors (Configuration, Interface, Endpoint, Class, Vendor */
const uint8_t MICROPHONE_ConfigDescriptor[] =
  {
    /* Configuration 1 */
    0x09,                                 /* bLength */
    USB_CONFIGURATION_DESCRIPTOR_TYPE,    /* bDescriptorType */
    0x64,                                 /* wTotalLength  100 bytes*/
    0x00,
    0x02,                                 /* bNumInterfaces */
    0x01,                                 /* bConfigurationValue */
    0x00,                                 /* iConfiguration */
    0x80,                                 /* bmAttributes Self Powred*/
    0x32,                                 /* bMaxPower = 100 mA*/
    /* 09 byte*/

    /* USB MICROPHONE Standard interface descriptor */
    MICROPHONE_SIZ_INTERFACE_DESC_SIZE,      /* bLength */
    USB_INTERFACE_DESCRIPTOR_TYPE,        /* bDescriptorType */
    0x00,                                 /* bInterfaceNumber */
    0x00,                                 /* bAlternateSetting */
    0x00,                                 /* bNumEndpoints */
    USB_DEVICE_CLASS_AUDIO,               /* bInterfaceClass */
    AUDIO_SUBCLASS_AUDIOCONTROL,          /* bInterfaceSubClass */
    AUDIO_PROTOCOL_UNDEFINED,             /* bInterfaceProtocol */
    0x00,                                 /* iInterface */
    /* 09 byte*/

    /* USB MICROPHONE Class-specific AC Interface Descriptor */
    MICROPHONE_SIZ_INTERFACE_DESC_SIZE,   /* bLength */
    AUDIO_INTERFACE_DESCRIPTOR_TYPE,      /* bDescriptorType */
    AUDIO_CONTROL_HEADER,                 /* bDescriptorSubtype */
    0x00,          /* 1.00 */             /* bcdADC */
    0x01,
    0x1e,                                 /* wTotalLength = 30*/
    0x00,
    0x01,                                 /* bInCollection */
    0x01,                                 /* baInterfaceNr */
    /* 09 byte*/

    /* USB MICROPHONE Input Terminal Descriptor */
    AUDIO_INPUT_TERMINAL_DESC_SIZE,       /* bLength */
    AUDIO_INTERFACE_DESCRIPTOR_TYPE,      /* bDescriptorType */
    AUDIO_CONTROL_INPUT_TERMINAL,         /* bDescriptorSubtype */
    0x01,                                 /* bTerminalID */
    0x01,                                 /* wTerminalType MICROPHONE   0x0201 */
    0x02,
    0x00,                                 /* bAssocTerminal */
    SPI1_datasize,                        /* bNrChannels */
    wChannelConfig&0x00ff,
    (wChannelConfig&0xff00)>>8,   /* wChannelConfig 0x0300  Stereo */
    0x00,                                 /* iChannelNames */
    0x00,                                 /* iTerminal */
    /* 12 byte*/


    /*USB MICROPHONE Output Terminal Descriptor */
    0x09,      /* bLength */
    AUDIO_INTERFACE_DESCRIPTOR_TYPE,      /* bDescriptorType */
    AUDIO_CONTROL_OUTPUT_TERMINAL,        /* bDescriptorSubtype */
    0x02,                                 /* bTerminalID */
    0x01,                                 /* wTerminalType  AUDIO Streaming 0x0101*/
    0x01,
    0x00,                                 /* bAssocTerminal */
    0x01,                                 /* bSourceID */
    0x00,	                                 /* iTerminal */
    /* 09 byte*/

    /* USB MICROPHONE Standard AS Interface Descriptor - Audio Streaming Zero Bandwith */
    /* Interface 1, Alternate Setting 0                                             */
    MICROPHONE_SIZ_INTERFACE_DESC_SIZE,  /* bLength */
    USB_INTERFACE_DESCRIPTOR_TYPE,        /* bDescriptorType */
    0x01,                                 /* bInterfaceNumber */
    0x00,                                 /* bAlternateSetting */
    0x00,                                 /* bNumEndpoints */
    USB_DEVICE_CLASS_AUDIO,               /* bInterfaceClass */
    AUDIO_SUBCLASS_AUDIOSTREAMING,        /* bInterfaceSubClass */
    AUDIO_PROTOCOL_UNDEFINED,             /* bInterfaceProtocol */
    0x00,                                 /* iInterface */
    /* 09 byte*/

    /* USB MICROPHONE Standard AS Interface Descriptor - Audio Streaming Operational */
    /* Interface 1, Alternate Setting 1                                           */
    MICROPHONE_SIZ_INTERFACE_DESC_SIZE,  /* bLength */
    USB_INTERFACE_DESCRIPTOR_TYPE,        /* bDescriptorType */
    0x01,                                 /* bInterfaceNumber */
    0x01,                                 /* bAlternateSetting */
    0x01,                                 /* bNumEndpoints */
    USB_DEVICE_CLASS_AUDIO,               /* bInterfaceClass */
    AUDIO_SUBCLASS_AUDIOSTREAMING,        /* bInterfaceSubClass */
    AUDIO_PROTOCOL_UNDEFINED,             /* bInterfaceProtocol */
    0x00,                                 /* iInterface */
    /* 09 byte*/

    /* USB MICROPHONE Audio Streaming Interface Descriptor */
    AUDIO_STREAMING_INTERFACE_DESC_SIZE,  /* bLength */
    AUDIO_INTERFACE_DESCRIPTOR_TYPE,      /* bDescriptorType */
    AUDIO_STREAMING_GENERAL,              /* bDescriptorSubtype */
    0x02,                                 /* bTerminalLink */
    0x01,                                 /* bDelay */
    0x01,                                 /* wFormatTag AUDIO_FORMAT_PCM16  0x0001*/
    0x00,
    /* 07 byte*/

    /* USB MICROPHONE Audio Type I Format Interface Descriptor */
    0x0B,                                 /* bLength */
    AUDIO_INTERFACE_DESCRIPTOR_TYPE,      /* bDescriptorType */
    AUDIO_STREAMING_FORMAT_TYPE,          /* bDescriptorSubtype */
    AUDIO_FORMAT_TYPE_I,                  /* bFormatType */
    SPI1_datasize,                        /* bNrChannels */
    0x02,                                 /* bSubFrameSize */
    0x10,                                 /* bBitResolution */
    0x01,                                 /* bSamFreqType */
    0x40,                                 /* tSamFreq 16000 = 0x3e80 */
    0x1f,
    0x00,
    /* 11 byte*/

    /* Endpoint 1 - Standard Descriptor */
    AUDIO_STANDARD_ENDPOINT_DESC_SIZE,    /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,         /* bDescriptorType */
    0x81,                                 /* bEndpointAddress 1 out endpoint*/
    0x05,        /* bmAttributes */
    SPI1_datasize*16,                                 /* wMaxPacketSize 64 bytes*/
    0x00,
    0x01,                                 /* bInterval */
    0x01,                                 /* bRefresh */
    0x00,                                 /* bSynchAddress */
    /* 09 byte*/

    /* Endpoint - Audio Streaming Descriptor*/
    AUDIO_STREAMING_ENDPOINT_DESC_SIZE,   /* bLength */
    AUDIO_ENDPOINT_DESCRIPTOR_TYPE,       /* bDescriptorType */
    AUDIO_ENDPOINT_GENERAL,               /* bDescriptor */
    0x00,                                 /* bmAttributes */
    0x02,                                 /* bLockDelayUnits */
    0x00,                                 /* wLockDelay */
    0x00,
    /* 07 byte*/
  };

/* USB String Descriptor (optional) */
const uint8_t MICROPHONE_StringLangID[MICROPHONE_SIZ_STRING_LANGID] =
  {
    0x04,
    0x03,
    0x09,
    0x04
  }
  ; /* LangID = 0x0409: U.S. English */

const uint8_t MICROPHONE_StringVendor[MICROPHONE_SIZ_STRING_VENDOR] =
  {
    MICROPHONE_SIZ_STRING_VENDOR, /* Size of manufacturer string */
    USB_STRING_DESCRIPTOR_TYPE,  /* bDescriptorType*/
    /* Manufacturer: "STMicroelectronics" */
    'A', 0, 'L', 0, 'E', 0, 'H', 0, 'Y', 0, 'E', 0, 'R', 0, 'K', 0,
    'E', 0, 'e', 0, 'l', 0, 'e', 0, 'c', 0, 't', 0, 'r', 0, 'o', 0,
    'n', 0, 's', 0
  };

const uint8_t MICROPHONE_StringProduct[MICROPHONE_SIZ_STRING_PRODUCT] =
  {
    MICROPHONE_SIZ_STRING_PRODUCT,  /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
    'A', 0, 'C', 0, 'C', 0, 'E', 0, 'L', 0, 'E', 0,
    'R', 0, 'O', 0, 'M', 0, 'E', 0, 'T', 0, 'E', 0, 'R', 0
  };

uint8_t MICROPHONE_StringSerial[MICROPHONE_SIZ_STRING_SERIAL] =
  {
    MICROPHONE_SIZ_STRING_SERIAL,  /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
    'S', 0, 'T', 0, 'M', 0, '3', 0, '2', 0
  };
/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Extern function prototypes ------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
