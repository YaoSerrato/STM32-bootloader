/*
 * Bootloader_driver.h
 *
 *  Created on: 2 Nov 2020
 *      Author: Serrato
 */

#ifndef INC_BOOTLOADER_DRIVER_H_
#define INC_BOOTLOADER_DRIVER_H_

/* Bootloader commands */
/* Index positions common to all commands */
#define		BL_CMDIDX_PACKET_START			(0)
#define		BL_CMDIDX_LENGTH				(1)
#define		BL_CMDIDX_CMDCODE				(2)

#define		BL_CMD_PACKET_HEADER_SIZE		(3)
#define		BL_CMD_PACKET_START				(0x81)
//#define		BL_CMDIDX_PACKET_END			(0x81)

/*
 * BL_GET_VER	Command sent by the host asking for the bootloader version.
 * */

#endif /* INC_BOOTLOADER_DRIVER_H_ */
