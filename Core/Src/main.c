/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "crc.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdarg.h>
#include "Bootloader_driver.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t RX_Buffer[BL_MAX_BUFFER_SIZE] = {0};
uint8_t RX_char = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_CRC_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_UART_Receive_IT(&huart2, &RX_char, 1);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  /* Branch to application or stay in bootloader based on User Button state at restart */
  if(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_RESET)
  {
	  /* Button pressed, stay in bootloader */
	  printmsg("\n\rBL_DEBUG_MSG: Button is pressed staying in Bootloader.");
  }
  else
  {
	  /* Button not pressed, jumpt to application */
	  //printmsg("\n\rBL_DEBUG_MSG: Button is not pressed jumping to application.");
	  //BL_BootApplication();
  }

  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 10;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2|RCC_PERIPHCLK_USART3;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  PeriphClkInit.Usart3ClockSelection = RCC_USART3CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
/**
  * @brief Print of formatted string to console over UART.
  * @retval None
  */
void printmsg(char *format,...)
{
#if defined(BL_DEBUG_MSG_EN) && (BL_DEBUG_MSG_EN == 1)
	unsigned char str[BL_DEBUG_MSG_MAXLEN] = {0};

	/* Extract the argument list using the VA APIs */
	va_list args;
	va_start(args, format);
	vsprintf(str, format, args);
	HAL_UART_Transmit(BL_USART_HANDLE, (uint8_t*) str, sizeof(str), HAL_MAX_DELAY);
	va_end(args);
#endif
}


/**
  * @brief Function for jumping to application.
  * @retval None
  */
void BL_BootApplication(void)
{
	/* A function pointer to hold the address of the Reset Handler of user application */
	void (*app_reset_handler)(void);
	//printmsg("\n\rBL_DEBUG_MSG: BL_BootApplication.");

	/* Configuration of the MSP by reading the value from the user application base address */
	uint32_t msp_value = *((volatile uint32_t*) FLASH_BASE_ADDRESS_APPLICATION);
	__set_MSP(msp_value);
	//printmsg("\n\rBL_DEBUG_MSG: MSP value 0x%#x at address 0x%#x.", msp_value, FLASH_BASE_ADDRESS_APPLICATION);

	/* Storing the user application Reset Handler memory address */
	uint32_t addr_reset_handler = *((volatile uint32_t*) (FLASH_BASE_ADDRESS_APPLICATION + 4));
	app_reset_handler = (void*) addr_reset_handler;
	//printmsg("\n\rBL_DEBUG_MSG: App Reset handler value 0x%#x at address 0x%#x.", addr_reset_handler, (FLASH_BASE_ADDRESS_APPLICATION + 4));

	/* Jumping to Reset Handler of user application */
	app_reset_handler();
}

/**
  * @brief USART Receive callback.
  * @retval None
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	uint8_t char_input = 0;
	uint16_t total_size = RX_Buffer[BL_CMDIDX_LENGTH] + BL_CMD_PACKET_HEADER_SIZE;
	static uint8_t index = 0;
	static uint8_t flag_header = 1;

	/* Reading received byte */
	char_input = RX_char;

	/* Parsing packet */
	if(flag_header)
	{
		if((char_input == BL_CMD_PACKET_START) && (index == BL_CMDIDX_PACKET_START))
		{
			/* Start of packet header */
			RX_Buffer[BL_CMDIDX_PACKET_START] = char_input;
			index++;
		}
		else
		{
			/* Rest of packet header */
			RX_Buffer[index] = char_input;
			if(index == BL_CMDIDX_CMDCODE)
			{
				flag_header = 0;
			}
			index++;
		}
	}
	else
	{
		/* Receiving packet body */
		if(index < total_size)
		{
			RX_Buffer[index] = char_input;
			index++;
		}
	}

	/* Packet received complete, restarting index count for receiving next packet */
	if(index >= total_size)
	{
		flag_header = 1;
		index = 0;

		/* Here you must call the Bootloader commands function handler */
		/* TODO: do not pass as argument the pointer to global variable. If another interrupt occurs while processing
		 * a previously received packet, the interrupt will modify the RX_Buffer contents and the ongoing command processing
		 * will be corrupted.
		 * Solution: disable USART2 global interrupt before entering BL_Process_Command()? And re-enable it after exiting
		 * BL_Process_Command()? Can I disable an interrupt from its Callback handler, will this break something?
		 * TODO: implement a buffer/FIFO or something so that I do not pass as argument a pointer to global variable RX_Buffer,
		 * but instead I maintain in a buffer every packet being received.
		 */
		//__disable_interrupt();
		BL_Process_Command(RX_Buffer, total_size);
		//__enable_interrupt();
	}


	/* Enabling UART receive in interrupt mode again */
	HAL_UART_Receive_IT(&huart2, &RX_char, 1);
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
