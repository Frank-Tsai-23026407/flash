/**
  ******************************************************************************
  * @file    quadspi.h
  * @brief   This file contains all the function prototypes for
  *          the quadspi.c file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __QUADSPI_H__
#define __QUADSPI_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern QSPI_HandleTypeDef hqspi;

/* USER CODE BEGIN Private defines */

uint8_t CSP_QSPI_Init(void);
uint8_t CSP_SPI_ReadExtendedReadParameter(uint8_t* buffer);
uint8_t CSP_SPI_ReadJEDECID(uint8_t* buffer);
uint8_t CSP_SPI_ReadStatusRegister(uint8_t* buffer);
uint8_t CSP_SPI_ReadReadRegister(uint8_t* buffer);
uint8_t CSP_SPI_ConfigStatusRegister(uint8_t value);
uint8_t CSP_SPI_ConfigReadRegister(uint8_t value);
uint8_t CSP_SPI_SetExtendedReadParameters(uint8_t value);
uint8_t CSP_SPI_EraseSector_4ADDR(uint32_t address);
uint8_t CSP_SPI_FastReadPage_4ADDR(uint32_t address, uint8_t* buffer);
uint8_t CSP_DSPI_FastReadPage_4ADDR(uint32_t address, uint8_t* buffer);
uint8_t CSP_SPI_ProgramPage_4ADDR(uint32_t address, uint32_t length, uint8_t* buffer);
uint8_t CSP_QSPI_ProgramPage_4ADDR(uint32_t address, uint32_t length, uint8_t* buffer);
uint8_t CSP_QSPI_FastReadPage_4ADDR(uint32_t address, uint8_t* buffer);
uint8_t CSP_SPI_ClearDYB();
uint8_t CSP_SPI_ReadDYB_4ADDR(uint32_t address, uint8_t* buffer);
uint8_t CSP_SPI_ReadPPB_4ADDR(uint32_t address, uint8_t* buffer);
uint8_t CSP_RealQSPI_ProgramPage_4ADDR(uint32_t address, uint32_t length, uint8_t* buffer);

/* USER CODE END Private defines */

void MX_QUADSPI_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __QUADSPI_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
