/**
  ******************************************************************************
  * File Name          : CRC.c
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

/* Includes ------------------------------------------------------------------*/
#include "crc.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

CRC_HandleTypeDef hcrc;

/* CRC init function */
void MX_CRC_Init(void)
{

  hcrc.Instance = CRC;
  hcrc.Init.DefaultPolynomialUse = DEFAULT_POLYNOMIAL_ENABLE;
  hcrc.Init.DefaultInitValueUse = DEFAULT_INIT_VALUE_ENABLE;
  hcrc.Init.InputDataInversionMode = CRC_INPUTDATA_INVERSION_NONE;
  hcrc.Init.OutputDataInversionMode = CRC_OUTPUTDATA_INVERSION_DISABLE;
  hcrc.InputDataFormat = CRC_INPUTDATA_FORMAT_BYTES;
  if (HAL_CRC_Init(&hcrc) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_CRC_MspInit(CRC_HandleTypeDef* crcHandle)
{

  if(crcHandle->Instance==CRC)
  {
  /* USER CODE BEGIN CRC_MspInit 0 */

  /* USER CODE END CRC_MspInit 0 */
    /* CRC clock enable */
    __HAL_RCC_CRC_CLK_ENABLE();
  /* USER CODE BEGIN CRC_MspInit 1 */

  /* USER CODE END CRC_MspInit 1 */
  }
}

void HAL_CRC_MspDeInit(CRC_HandleTypeDef* crcHandle)
{

  if(crcHandle->Instance==CRC)
  {
  /* USER CODE BEGIN CRC_MspDeInit 0 */

  /* USER CODE END CRC_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CRC_CLK_DISABLE();
  /* USER CODE BEGIN CRC_MspDeInit 1 */

  /* USER CODE END CRC_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

/* TODO: check if CRC is calculated as you expect [MSByte, Byte, Byte, LSByte ] */

/**
  * @brief Bootloader commands handler.
  * @retval None
  */
CRC_VERIFY_STATUS BL_verify_crc(uint8_t *pData, uint32_t len, uint32_t crc_host)
{
	uint32_t uwCRCvalue = BL_get_crc(pData, len);

	if(uwCRCvalue == crc_host)
	{
		return VERIFY_CRC_SUCCESS;
	}

	return VERIFY_CRC_FAIL;
}

/**
  * @brief Bootloader commands handler.
  * @retval None
  */
uint32_t BL_get_crc(uint8_t *pData, uint32_t len)
{
	uint32_t uwCRCvalue = 0;
	uint32_t i_data = 0;

	for(uint32_t i = 0; i < len; ++i)
	{
		i_data = (uint32_t)pData[i];
		uwCRCvalue = HAL_CRC_Accumulate(&hcrc, &i_data, 1);
		/* TODO: check how the HAL return a CRC value and see if it matches what you are expecting */
		/* TODO: HAL_CRC_Accumulate() is producing a different CRC value every time it is called, no matter if the data is
		 * the same. Review its implementation and see what is happening. */
	}

	return uwCRCvalue;
}

/**
  * @brief Bootloader commands handler.
  * @retval None
  */
void BL_append_crc(uint8_t *pData, uint32_t len)
{
	uint32_t uwCRCvalue = 0;

	/* Obtaining CRC value */
	uwCRCvalue = BL_get_crc(pData, len);

	/* Appending CRC value */
	pData[len + 0] = (uint8_t)((uwCRCvalue & CRC_MASK_BYTE1) >> CRC_SHIFT_24);		/* Most significant byte */
	pData[len + 1] = (uint8_t)((uwCRCvalue & CRC_MASK_BYTE2) >> CRC_SHIFT_16);
	pData[len + 2] = (uint8_t)((uwCRCvalue & CRC_MASK_BYTE3) >> CRC_SHIFT_8);
	pData[len + 3] = (uint8_t)((uwCRCvalue & CRC_MASK_BYTE4) >> CRC_SHIFT_0);		/* Least significant byte */
}

/**
  * @brief Bootloader commands handler.
  * @retval None
  */
uint32_t BL_extract_crc(uint8_t* pData, uint8_t len)
{
	uint32_t crc_1 = (uint32_t)pData[len + 0];		/* Most significant byte */
	uint32_t crc_2 = (uint32_t)pData[len + 1];
	uint32_t crc_3 = (uint32_t)pData[len + 2];
	uint32_t crc_4 = (uint32_t)pData[len + 3];		/* Least significant byte */

	uint32_t temp_crc = ( (crc_1 << CRC_SHIFT_24) | (crc_2 << CRC_SHIFT_16) | (crc_3 << CRC_SHIFT_8) | (crc_4 << CRC_SHIFT_0) );

	return temp_crc;
}

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
