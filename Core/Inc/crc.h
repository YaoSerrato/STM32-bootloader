/**
  ******************************************************************************
  * File Name          : CRC.h
  * Description        : This file provides code for the configuration
  *                      of the CRC instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __crc_H
#define __crc_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern CRC_HandleTypeDef hcrc;

/* USER CODE BEGIN Private defines */

#define		CRC_MASK_BYTE1		(0xFF000000)
#define		CRC_MASK_BYTE2		(0x00FF0000)
#define		CRC_MASK_BYTE3		(0x0000FF00)
#define		CRC_MASK_BYTE4		(0x000000FF)

#define		CRC_SHIFT_24		(24)
#define		CRC_SHIFT_16		(16)
#define		CRC_SHIFT_8			(8)
#define		CRC_SHIFT_0			(0)

typedef enum
{
	VERIFY_CRC_FAIL = 0,
	VERIFY_CRC_SUCCESS = 1
}CRC_VERIFY_STATUS;

/* USER CODE END Private defines */

void MX_CRC_Init(void);

/* USER CODE BEGIN Prototypes */

CRC_VERIFY_STATUS	BL_verify_crc(uint8_t *pData, uint32_t len, uint32_t crc_host);
uint32_t			BL_get_crc(uint8_t *pData, uint32_t len);
void				BL_append_crc(uint8_t *pData, uint32_t len);
uint32_t			BL_extract_crc(uint8_t* pData, uint8_t len);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ crc_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
