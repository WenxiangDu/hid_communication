/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file            : usb_host.c
  * @version         : v1.0_Cube
  * @brief           : This file implements the USB Host
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/

#include "usb_host.h"
#include "usbh_core.h"
#include "usbh_hid.h"

/* USER CODE BEGIN Includes */
#include "usart.h"
/* USER CODE END Includes */

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USB Host core handle declaration */
USBH_HandleTypeDef hUsbHostFS;
ApplicationTypeDef Appli_state = APPLICATION_IDLE;

/*
 * -- Insert your variables declaration here --
 */
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*
 * user callback declaration
 */
static void USBH_UserProcess(USBH_HandleTypeDef *phost, uint8_t id);

/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 1 */
void USBH_HID_EventCallback(USBH_HandleTypeDef *phost)
{
  HID_TypeTypeDef type = HID_UNKNOWN;

  type = USBH_HID_GetDeviceType(phost);
  switch (type)
  {

  case HID_MOUSE:
    {
      HID_MOUSE_Info_TypeDef *mouse_info;
      mouse_info = USBH_HID_GetMouseInfo(phost);
      uint8_t mousebuffer[5];
      mousebuffer[0] = 0x02;
      mousebuffer[1] = (mouse_info->buttons[0] << 0) |
                       (mouse_info->buttons[1] << 1) |
                       (mouse_info->buttons[2] << 2);
      mousebuffer[2] = (mouse_info->x);
      mousebuffer[3] = (mouse_info->y);
      mousebuffer[4] = (mouse_info->wheel);
      HAL_UART_Transmit(&huart2,mousebuffer,5,0xff);
    }
    break;

  case HID_KEYBOARD:
    {
      HID_KEYBD_Info_TypeDef *keyboard_info;
      keyboard_info = USBH_HID_GetKeybdInfo(phost);
      uint8_t keybdbuffer[8];
      keybdbuffer[0] = 0x06;
      keybdbuffer[1] = (keyboard_info->lctrl<<0x00)|
                       (keyboard_info->lshift<<0x01)|
                       (keyboard_info->lalt<<0x02)|
                       (keyboard_info->lgui<<0x03)|
                       (keyboard_info->rctrl<<0x04)|
                       (keyboard_info->rshift<<0x05)|
                       (keyboard_info->ralt<<0x06)|
                       (keyboard_info->rgui<<0x07);
      for (int i = 2; i < 8; i++)
      {
        keybdbuffer[i] = keyboard_info->keys[i-2];
      }
      HAL_UART_Transmit(&huart2,keybdbuffer,8,0xff);
    }
    break;

  default:
    break;
  }
}
/* USER CODE END 1 */

/**
  * Init USB host library, add supported class and start the library
  * @retval None
  */
void MX_USB_HOST_Init(void)
{
  /* USER CODE BEGIN USB_HOST_Init_PreTreatment */

  /* USER CODE END USB_HOST_Init_PreTreatment */

  /* Init host Library, add supported class and start the library. */
  if (USBH_Init(&hUsbHostFS, USBH_UserProcess, HOST_FS) != USBH_OK)
  {
    Error_Handler();
  }
  if (USBH_RegisterClass(&hUsbHostFS, USBH_HID_CLASS) != USBH_OK)
  {
    Error_Handler();
  }
  if (USBH_Start(&hUsbHostFS) != USBH_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USB_HOST_Init_PostTreatment */

  /* USER CODE END USB_HOST_Init_PostTreatment */
}

/*
 * Background task
 */
void MX_USB_HOST_Process(void)
{
  /* USB Host Background task */
  USBH_Process(&hUsbHostFS);
}
/*
 * user callback definition
 */
static void USBH_UserProcess  (USBH_HandleTypeDef *phost, uint8_t id)
{
  /* USER CODE BEGIN CALL_BACK_1 */
  switch(id)
  {
  case HOST_USER_SELECT_CONFIGURATION:
  break;

  case HOST_USER_DISCONNECTION:
  Appli_state = APPLICATION_DISCONNECT;
  break;

  case HOST_USER_CLASS_ACTIVE:
  Appli_state = APPLICATION_READY;
  break;

  case HOST_USER_CONNECTION:
  Appli_state = APPLICATION_START;
  break;

  default:
  break;
  }
  /* USER CODE END CALL_BACK_1 */
}

/**
  * @}
  */

/**
  * @}
  */

