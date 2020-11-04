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
void BL_Process_Command(uint8_t* Pkt, uint16_t Size)
{
	/* Here I must check the CRC value. If success, send ACK and process the packet; if failure, send NACK */


	/* Checking for a correct packet header */
	if(Pkt[BL_CMDIDX_PACKET_START] != BL_CMD_PACKET_START)
		return;

	/* Checking for a correct length */
	if(Size > BL_MAX_BUFFER_SIZE)
		return;

	/* Parsing command code */
	switch(Pkt[BL_CMDIDX_CMDCODE])
	{
		case BL_GET_VER:
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
			/* TODO: replay with invalid command */
			break;
	}

}
