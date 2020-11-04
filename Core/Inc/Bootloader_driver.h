/*
 * Bootloader_driver.h
 *
 *  Created on: 2 Nov 2020
 *      Author: Serrato
 */

#ifndef INC_BOOTLOADER_DRIVER_H_
#define INC_BOOTLOADER_DRIVER_H_
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes */
#include <stdint.h>

/* Bootloader commands */
/* Index positions common to all commands */
#define		BL_CMDIDX_PACKET_START			(0)
#define		BL_CMDIDX_LENGTH				(1)
#define		BL_CMDIDX_CMDCODE				(2)
#define		BL_MAX_BUFFER_SIZE				(300)

#define		BL_CMD_PACKET_HEADER_SIZE		(3)
#define		BL_CMD_PACKET_START				(0x81)

/* Commands */
#define		BL_GET_VER						(0x51)
#define		BL_GET_HELP						(0x52)
#define		BL_GET_CID						(0x53)
#define		BL_GET_RDP_STATUS				(0x54)
#define		BL_GO_TO_ADDR					(0x55)
#define		BL_FLASH_ERASE					(0x56)
#define		BL_MEM_WRITE					(0x57)
#define		BL_EN_R_W_PROTECT				(0x58)
#define		BL_MEM_READ						(0x59)
#define		BL_READ_SECTOR_STATUS			(0x5A)
#define		BL_OTP_READ						(0x5B)
#define		BL_DIS_R_W_PROTECT				(0x5C)


/* Function declarations */
void	BL_Process_Command(uint8_t* Pkt, uint16_t Size);
//void 	BL_process_BL_GET_VER(void);


#ifdef __cplusplus
}
#endif
#endif /* INC_BOOTLOADER_DRIVER_H_ */
