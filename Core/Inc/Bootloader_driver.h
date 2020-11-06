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

 /* Bootloader version */
#define		BL_VERSION						(1)

/* Bootloader commands */
/* Index definitions por commands and replays */
#define		BL_CMDIDX_PACKET_START			(0)
#define		BL_CMDIDX_PAYLOAD_LENGTH		(1)
#define		BL_CMDIDX_CMDCODE				(2)
#define		BL_CMDIDX_PAYLOAD_START			(3)
#define		BL_MAX_PACKET_SIZE				(258)
#define		BL_CMD_PACKET_HEADER_SIZE		(3)
#define		BL_CMD_PACKET_START				(0x81)

#define		BL_RPLIDX_PACKET_START			(0)
#define		BL_RPLIDX_PAYLOAD_LENGTH		(1)
#define		BL_RPLIDX_PAYLOAD_START			(2)
#define		BL_RPL_PACKET_START				(0x97)

#define		BL_ACK							(0xDC)
#define		BL_NACK							(0xFE)

#define		BL_CRC_LENGTH					(4)

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
void	BL_Process_Command(uint8_t* Pkt);
void	BL_process_BL_GET_VER(uint8_t* payload, uint8_t payload_size);
void	BL_process_BL_GET_HELP(void);
void	BL_process_BL_GET_CID(void);
void	BL_process_BL_GET_RDP_STATUS(void);
void	BL_process_BL_GO_TO_ADDR(void);
void	BL_process_BL_FLASH_ERASE(void);
void	BL_process_BL_MEM_WRITE(void);
void	BL_process_BL_EN_R_W_PROTECT(void);
void	BL_process_BL_MEM_READ(void);
void	BL_process_BL_READ_SECTOR_STATUS(void);
void	BL_process_BL_OTP_READ(void);
void	BL_process_BL_DIS_R_W_PROTECT(void);

uint8_t BL_get_bootloader_version(void);
uint8_t BL_send_replay(void);
uint32_t BL_extract_crc(uint8_t* pData, uint8_t len);

#ifdef __cplusplus
}
#endif
#endif /* INC_BOOTLOADER_DRIVER_H_ */
