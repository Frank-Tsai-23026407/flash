/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
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
#include "i2c.h"
#include "quadspi.h"
#include "usart.h"
#include "usb_otg.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "erpc_hal_uart_transport.hpp"
#include "erpc_mbf_setup.h"
#include "erpc_server_setup.h"
#include "erpc_setup_hal_uart.hpp"
#include "erpc_transport_setup.h"
#include "qspi_rad_test.h"
#include "qspi_rad_test_server.h"
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

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

//uint8_t transmitbuff[256] = {0};
uint8_t receivebuff[256] = {0};


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
  MX_USART3_UART_Init();
  MX_USB_OTG_FS_PCD_Init();
  MX_QUADSPI_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */

  erpc_transport_t transport = erpc_transport_hal_uart_init(&huart3);
    erpc_mbf_t message_buffer_factory = erpc_mbf_static_init();
    erpc_server_init(transport, message_buffer_factory);
    erpc_add_service_to_server(create_QSPIService_service());

//    int i;
//    for(i = 0; i < 256; i++){
//  	  transmitbuff[i] = 0x87;
//    }

    // ======================================================
    // initial
    // ======================================================
    if(CSP_QSPI_Init()!=HAL_OK) Error_Handler();
    // check if connect correctly
    if(CSP_SPI_ReadJEDECID(receivebuff)!=HAL_OK) Error_Handler();
    if((receivebuff[0]!=0x9D)|(receivebuff[1]!=0x60)|(receivebuff[2]!=0x19)) Error_Handler();
    // set Quad enable and non-protection
    if(CSP_SPI_ConfigStatusRegister(0x40)!=HAL_OK) Error_Handler();
    if(CSP_SPI_ReadStatusRegister(receivebuff)!=HAL_OK) Error_Handler();
    if(receivebuff[0]!=0x40) Error_Handler();
    // setExtendedReadParameters
    if(CSP_SPI_SetExtendedReadParameters(0xF0)!=HAL_OK) Error_Handler();
    // un-protected
    if(CSP_SPI_ClearDYB()!=HAL_OK) Error_Handler();
    // ======================================================
	// end initial
	// ======================================================

//    if(CSP_SPI_EraseSector_4ADDR(0x0fff000)!=HAL_OK) Error_Handler();
//
//    if(CSP_QSPI_FastReadPage_4ADDR(0x0ffff00, receivebuff)!=HAL_OK) Error_Handler();

  //  if(CSP_SPI_ReadPPB_4ADDR(0x0fff000, receivebuff)!=HAL_OK) Error_Handler();
  //  if(CSP_SPI_ReadDYB_4ADDR(0x0fff000, receivebuff)!=HAL_OK) Error_Handler();

//    if(CSP_QSPI_ProgramPage_4ADDR(0x0ffff00, 256, transmitbuff)!=HAL_OK) Error_Handler(); // write in
//
//    if(CSP_SPI_ReadExtendedReadParameter(receivebuff)!=HAL_OK) Error_Handler();			// check if there is error
//
//    if(CSP_QSPI_FastReadPage_4ADDR(0x0ffff00, receivebuff)!=HAL_OK) Error_Handler();		// read out

  //=========================================================================================================================

//    if(CSP_RealQSPI_ProgramPage_4ADDR(0x0ffff00, 256, transmitbuff)!=HAL_OK) Error_Handler(); // write in
//
//    if(CSP_SPI_ReadExtendedReadParameter(receivebuff)!=HAL_OK) Error_Handler();			// check if there is error
//
//    if(CSP_QSPI_FastReadPage_4ADDR(0x0ffff00, receivebuff)!=HAL_OK) Error_Handler();		// read out

    //=========================================================================================================================
//
//    if(CSP_SPI_ProgramPage_4ADDR(0x0ffff00, 256, transmitbuff)!=HAL_OK) Error_Handler();
//
//    if(CSP_QSPI_FastReadPage_4ADDR(0x0ffff00, receivebuff)!=HAL_OK) Error_Handler();
//
//    if(CSP_SPI_ReadExtendedReadParameter(receivebuff)!=HAL_OK) Error_Handler();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  erpc_server_poll();
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 120;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 5;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV4;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
