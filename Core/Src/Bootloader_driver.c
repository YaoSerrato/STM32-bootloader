/*
 * Bootloader_driver.c
 *
 *  Created on: 2 Nov 2020
 *      Author: Serrato
 */

#include "Bootloader_driver.h"
#include "crc.h"
#include "usart.h"


/* Function definitions */

/**
  * @brief Bootloader commands handler.
  * @retval None
  */
void BL_Process_Command(uint8_t* Pkt)
{
	uint8_t* packet = &Pkt[BL_CMDIDX_PACKET_START];
	uint8_t packet_size_no_crc = BL_CMD_PACKET_HEADER_SIZE + Pkt[BL_CMDIDX_PAYLOAD_LENGTH] - BL_CRC_LENGTH;

	uint8_t* payload = &Pkt[BL_CMDIDX_PAYLOAD_START];
	uint8_t payload_size_no_crc = Pkt[BL_CMDIDX_PAYLOAD_LENGTH] - BL_CRC_LENGTH;

	uint32_t crc_host = 0;

	/* Extract CRC value from packet */
	crc_host = BL_extract_crc(packet, packet_size_no_crc);

	/* Here I must check the CRC value. If success, send ACK and process the packet; if failure, send NACK and exit function */
	if(!BL_verify_crc(packet, packet_size_no_crc, crc_host))
	{
		BL_SendNACK();
		return;
	}
	else
	{
		BL_SendACK();
	}

	/* Checking for a correct packet header */
	if(Pkt[BL_CMDIDX_PACKET_START] != BL_CMD_PACKET_START)
	{
		BL_SendNACK();
		return;
	}

	/* Parsing command code */
	switch(Pkt[BL_CMDIDX_CMDCODE])
	{
		case BL_GET_VER:
			BL_process_BL_GET_VER(payload, payload_size_no_crc);
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
			/* TODO: replay with "invalid command" message. Implement an error message protocol with enums or something */
			BL_SendNACK();
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

uint32_t BL_extract_crc(uint8_t* pData, uint8_t len)
{
	uint32_t crc_1 = (uint32_t)pData[len];
	uint32_t crc_2 = (uint32_t)pData[len + 1];
	uint32_t crc_3 = (uint32_t)pData[len + 2];
	uint32_t crc_4 = (uint32_t)pData[len + 3];

	uint32_t temp_crc = ( (crc_1 << 24) | (crc_2 << 16) | (crc_3 << 8) | (crc_4 << 0) );

	return temp_crc;
}

