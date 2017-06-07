#pragma once

#define USB_EP0_BUFF_SIZE 8
#define USB_MAX_NUM_INT 3 // For tracking Alternate Setting
#define USB_MAX_EP_NUMBER 4

//Device descriptor - if these two definitions are not defined then
//  a ROM USB_DEVICE_DESCRIPTOR variable by the exact name of device_dsc
//  must exist.
#define USB_USER_DEVICE_DESCRIPTOR &device_dsc
#define USB_USER_DEVICE_DESCRIPTOR_INCLUDE extern ROM USB_DEVICE_DESCRIPTOR device_dsc

//Configuration descriptors - if these two definitions do not exist then
//  a ROM BYTE *ROM variable named exactly USB_CD_Ptr[] must exist.
#define USB_USER_CONFIG_DESCRIPTOR USB_CD_Ptr
#define USB_USER_CONFIG_DESCRIPTOR_INCLUDE extern ROM BYTE *ROM USB_CD_Ptr[]

#define USB_PING_PONG_MODE USB_PING_PONG__FULL_PING_PONG
#define USB_INTERRUPT
#define USB_PULLUP_OPTION USB_PULLUP_ENABLE

#define USB_TRANSCEIVER_OPTION USB_INTERNAL_TRANSCEIVER
//External Transceiver support is not available on all product families.  Please
//  refer to the product family datasheet for more information if this feature
//  is available on the target processor.
//#define USB_TRANSCEIVER_OPTION USB_EXTERNAL_TRANSCEIVER

#define USB_SPEED_OPTION USB_FULL_SPEED

#define USB_ENABLE_STATUS_STAGE_TIMEOUTS
#define USB_STATUS_STAGE_TIMEOUT (BYTE)45 

#define USB_SUPPORT_DEVICE
#define USB_NUM_STRING_DESCRIPTORS 3

#define USB_USE_AUDIO_MIDI
#define MIDI_EP 1
