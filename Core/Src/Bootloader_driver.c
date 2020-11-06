/*
 * Bootloader_driver.c
 *
 *  Created on: 2 Nov 2020
 *      Author: Serrato
 */

#include "Bootloader_driver.h"


/* Function definitions */

/**
  * @brief Bootloader commands handler.
  * @retval None
  */
void BL_Process_Command(uint8_t* Pkt)
{
	uint8_t* payload = &Pkt[BL_CMDIDX_PAYLOAD_START];
	uint8_t payload_size = Pkt[BL_CMDIDX_PAYLOAD_LENGTH];

	/* Here I must check the CRC value. If success, send ACK and process the packet; if failure, send NACK and exit function */


	/* Checking for a correct packet header */
	if(Pkt[BL_CMDIDX_PACKET_START] != BL_CMD_PACKET_START)
		return;

	/* Parsing command code */
	switch(Pkt[BL_CMDIDX_CMDCODE])
	{
		case BL_GET_VER:
			BL_process_BL_GET_VER(payload, payload_size);
			break;

		case BL_GET_HELP:
			break;

		case BL_GET_CID:
			break;

		case BL_GET_RDP_STATUS:
			break;

		case BL_GO_TO_ADDR:
			break;

		case BL_FLASH_ERASE:
			break;

		case BL_MEM_WRITE:
			break;

		case BL_EN_R_W_PROTECT:
			break;

		case BL_MEM_READ:
			break;

		case BL_READ_SECTOR_STATUS:
			break;

		case BL_OTP_READ:
			break;

		case BL_DIS_R_W_PROTECT:
			break;

		default:
			/* TODO: replay with "invalid command" message */
			break;
	}

}

/**
  * @brief Bootloader commands handler.
  * @retval None
  */
void 	BL_process_BL_GET_VER(uint8_t* payload, uint8_t payload_size)
{

}

/**
  * @brief Bootloader commands handler.
  * @retval None
  */
void	BL_process_BL_GET_HELP(void)
{

}

/**
  * @brief Bootloader commands handler.
  * @retval None
  */
void	BL_process_BL_GET_CID(void)
{

}

/**
  * @brief Bootloader commands handler.
  * @retval None
  */
void	BL_process_BL_GET_RDP_STATUS(void)
{

}

/**
  * @brief Bootloader commands handler.
  * @retval None
  */
void	BL_process_BL_GO_TO_ADDR(void)
{

}

/**
  * @brief Bootloader commands handler.
  * @retval None
  */
void	BL_process_BL_FLASH_ERASE(void)
{

}

/**
  * @brief Bootloader commands handler.
  * @retval None
  */
void	BL_process_BL_MEM_WRITE(void)
{

}

/**
  * @brief Bootloader commands handler.
  * @retval None
  */
void	BL_process_BL_EN_R_W_PROTECT(void)
{

}

/**
  * @brief Bootloader commands handler.
  * @retval None
  */
void	BL_process_BL_MEM_READ(void)
{

}

/**
  * @brief Bootloader commands handler.
  * @retval None
  */
void	BL_process_BL_READ_SECTOR_STATUS(void)
{

}

/**
  * @brief Bootloader commands handler.
  * @retval None
  */
void	BL_process_BL_OTP_READ(void)
{

}

/**
  * @brief Bootloader commands handler.
  * @retval None
  */
void	BL_process_BL_DIS_R_W_PROTECT(void)
{

}

