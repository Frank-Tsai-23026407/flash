/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    quadspi.c
  * @brief   This file provides code for the configuration
  *          of the QUADSPI instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "quadspi.h"

/* USER CODE BEGIN 0 */

//static uint8_t SPI_WriteFF(void);
static uint8_t SPI_WriteEnable(void);
static uint8_t SPI_AutoPollingMemReady(void);
static uint8_t SPI_ResetChip(void);

/* USER CODE END 0 */

QSPI_HandleTypeDef hqspi;

/* QUADSPI init function */
void MX_QUADSPI_Init(void)
{

  /* USER CODE BEGIN QUADSPI_Init 0 */

  /* USER CODE END QUADSPI_Init 0 */

  /* USER CODE BEGIN QUADSPI_Init 1 */

  /* USER CODE END QUADSPI_Init 1 */
  hqspi.Instance = QUADSPI;
  hqspi.Init.ClockPrescaler = 0x2;
  hqspi.Init.FifoThreshold = 4;
  hqspi.Init.SampleShifting = QSPI_SAMPLE_SHIFTING_HALFCYCLE;
  hqspi.Init.FlashSize = 24;
  hqspi.Init.ChipSelectHighTime = QSPI_CS_HIGH_TIME_4_CYCLE;
  hqspi.Init.ClockMode = QSPI_CLOCK_MODE_0;
  hqspi.Init.FlashID = QSPI_FLASH_ID_1;
  hqspi.Init.DualFlash = QSPI_DUALFLASH_DISABLE;
  if (HAL_QSPI_Init(&hqspi) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN QUADSPI_Init 2 */

  /* USER CODE END QUADSPI_Init 2 */

}

void HAL_QSPI_MspInit(QSPI_HandleTypeDef* qspiHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(qspiHandle->Instance==QUADSPI)
  {
  /* USER CODE BEGIN QUADSPI_MspInit 0 */

  /* USER CODE END QUADSPI_MspInit 0 */
    /* QUADSPI clock enable */
    __HAL_RCC_QSPI_CLK_ENABLE();

    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    /**QUADSPI GPIO Configuration
    PE2     ------> QUADSPI_BK1_IO2
    PB2     ------> QUADSPI_CLK
    PD11     ------> QUADSPI_BK1_IO0
    PD12     ------> QUADSPI_BK1_IO1
    PD13     ------> QUADSPI_BK1_IO3
    PB6     ------> QUADSPI_BK1_NCS
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_QSPI;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_QSPI;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_QSPI;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_QSPI;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN QUADSPI_MspInit 1 */

  /* USER CODE END QUADSPI_MspInit 1 */
  }
}

void HAL_QSPI_MspDeInit(QSPI_HandleTypeDef* qspiHandle)
{

  if(qspiHandle->Instance==QUADSPI)
  {
  /* USER CODE BEGIN QUADSPI_MspDeInit 0 */

  /* USER CODE END QUADSPI_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_QSPI_CLK_DISABLE();

    /**QUADSPI GPIO Configuration
    PE2     ------> QUADSPI_BK1_IO2
    PB2     ------> QUADSPI_CLK
    PD11     ------> QUADSPI_BK1_IO0
    PD12     ------> QUADSPI_BK1_IO1
    PD13     ------> QUADSPI_BK1_IO3
    PB6     ------> QUADSPI_BK1_NCS
    */
    HAL_GPIO_DeInit(GPIOE, GPIO_PIN_2);

    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_2|GPIO_PIN_6);

    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13);

  /* USER CODE BEGIN QUADSPI_MspDeInit 1 */

  /* USER CODE END QUADSPI_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

// Local function

//uint8_t SPI_WriteFF(void)
//{
//	int rv;
//	QSPI_CommandTypeDef sCommand = {0};
//
//	sCommand.Instruction = 0xFF;
//	sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
//	sCommand.AddressMode = QSPI_ADDRESS_NONE;
//	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
//	sCommand.DataMode = QSPI_DATA_NONE;
//	sCommand.NbData = 0;
//	sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
//	sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
//	sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
//	sCommand.DummyCycles = 0;
//
//	rv = HAL_QSPI_Command(&hqspi, &sCommand, HAL_QSPI_TIMEOUT_DEFAULT_VALUE);
//	if (rv != HAL_OK) {
//		return HAL_ERROR;
//	}
//
//	HAL_Delay(1);
//
//	return HAL_OK;
//}

uint8_t SPI_ResetChip()
{
    QSPI_CommandTypeDef sCommand;

    /* Erasing Sequence -------------------------------------------------- */
    sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    sCommand.AddressSize = QSPI_ADDRESS_24_BITS;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
    sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    sCommand.Instruction = 0x66;
    sCommand.AddressMode = QSPI_ADDRESS_NONE;
    sCommand.Address = 0;
    sCommand.DataMode = QSPI_DATA_NONE;
    sCommand.DummyCycles = 0;

    if (HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)
        != HAL_OK) {
        return HAL_ERROR;
    }

    sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    sCommand.AddressSize = QSPI_ADDRESS_24_BITS;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
    sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    sCommand.Instruction = 0x99;
    sCommand.AddressMode = QSPI_ADDRESS_NONE;
    sCommand.Address = 0;
    sCommand.DataMode = QSPI_DATA_NONE;
    sCommand.DummyCycles = 0;

    if (HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)
        != HAL_OK) {
        return HAL_ERROR;
    }
    return HAL_OK;
}

uint8_t SPI_AutoPollingMemReady(void)
{

    QSPI_CommandTypeDef sCommand;
    QSPI_AutoPollingTypeDef sConfig;

    /* Configure automatic polling mode to wait for memory ready ------ */
    sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction = 0x05;
    sCommand.AddressMode = QSPI_ADDRESS_NONE;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DataMode = QSPI_DATA_1_LINE;
    sCommand.DummyCycles = 0;
    sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
    sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

    sConfig.Match = 0x00;
    sConfig.Mask = 0x01;
    sConfig.MatchMode = QSPI_MATCH_MODE_AND;
    sConfig.StatusBytesSize = 1;
    sConfig.Interval = 0x10;
    sConfig.AutomaticStop = QSPI_AUTOMATIC_STOP_ENABLE;

    if (HAL_QSPI_AutoPolling(&hqspi, &sCommand, &sConfig, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return HAL_ERROR;
    }

    return HAL_OK;
}

uint8_t SPI_WriteEnable(void)
{
    QSPI_CommandTypeDef sCommand;
    QSPI_AutoPollingTypeDef sConfig;

    /* Enable write operations ------------------------------------------ */
    sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction = 0x06;
    sCommand.AddressMode = QSPI_ADDRESS_NONE;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DataMode = QSPI_DATA_NONE;
    sCommand.DummyCycles = 0;
    sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
    sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

    if (HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)
        != HAL_OK) {
        return HAL_ERROR;
    }

    /* Configure automatic polling mode to wait for write enabling ---- */
    sConfig.Match = 0x02;
    sConfig.Mask = 0x03;
    sConfig.MatchMode = QSPI_MATCH_MODE_AND;
    sConfig.StatusBytesSize = 1;
    sConfig.Interval = 0x10;
    sConfig.AutomaticStop = QSPI_AUTOMATIC_STOP_ENABLE;

    sCommand.Instruction = 0x05;
    sCommand.DataMode = QSPI_DATA_1_LINE;
    if (HAL_QSPI_AutoPolling(&hqspi, &sCommand, &sConfig,
                             HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
        return HAL_ERROR;
    }
    return HAL_OK;
}

// global

uint8_t CSP_SPI_Init(void)
{
    //prepare QSPI peripheral for ST-Link Utility operations
    //if (SPI_WriteFF() != HAL_OK) return HAL_ERROR;
    if (SPI_ResetChip() != HAL_OK) return HAL_ERROR;
    if (SPI_AutoPollingMemReady() != HAL_OK) return HAL_ERROR;
    HAL_Delay(1);
    return HAL_OK;
}

uint8_t CSP_SPI_ReadJEDECID(uint8_t* buffer)
{
	int rv;
	QSPI_CommandTypeDef sCommand = {0};

	sCommand.Instruction = 0x9F;
	sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
	sCommand.AddressMode = QSPI_ADDRESS_NONE;
	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode = QSPI_DATA_1_LINE;
	sCommand.NbData = 3;
	sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
	sCommand.DummyCycles = 0;

	rv = HAL_QSPI_Command(&hqspi, &sCommand, HAL_QSPI_TIMEOUT_DEFAULT_VALUE);
	if (rv != HAL_OK) {
		return HAL_ERROR;
	}
	rv = HAL_QSPI_Receive(&hqspi, buffer, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
	if (rv != HAL_OK){
		return HAL_ERROR;
	}

	HAL_Delay(1);

	return HAL_OK;
}

uint8_t CSP_SPI_ReadStatusRegister(uint8_t* buffer)
{
	QSPI_CommandTypeDef sCommand;

	sCommand.Instruction = 0x05;
	sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
	sCommand.AddressMode = QSPI_ADDRESS_NONE;
	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode = QSPI_DATA_1_LINE;
	sCommand.NbData = 1;
	sCommand.DummyCycles = 0;
	sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

	if (HAL_QSPI_Command(&hqspi, &sCommand, HAL_QSPI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK){
		return HAL_ERROR;
	}

	if (HAL_QSPI_Receive(&hqspi, buffer, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK){
		return HAL_ERROR;
	}

    HAL_Delay(1);

	return HAL_OK;
}

uint8_t CSP_SPI_ReadStatusRegister1(uint8_t* buffer)
{
	QSPI_CommandTypeDef sCommand;

	sCommand.Instruction = 0x35;
	sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
	sCommand.AddressMode = QSPI_ADDRESS_NONE;
	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode = QSPI_DATA_1_LINE;
	sCommand.NbData = 1;
	sCommand.DummyCycles = 0;
	sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

	if (HAL_QSPI_Command(&hqspi, &sCommand, HAL_QSPI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK){
		return HAL_ERROR;
	}

	if (HAL_QSPI_Receive(&hqspi, buffer, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK){
		return HAL_ERROR;
	}

    HAL_Delay(1);

	return HAL_OK;
}

uint8_t CSP_SPI_ReadStatusRegister2(uint8_t* buffer)
{
	QSPI_CommandTypeDef sCommand;

	sCommand.Instruction = 0x15;
	sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
	sCommand.AddressMode = QSPI_ADDRESS_NONE;
	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode = QSPI_DATA_1_LINE;
	sCommand.NbData = 1;
	sCommand.DummyCycles = 0;
	sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

	if (HAL_QSPI_Command(&hqspi, &sCommand, HAL_QSPI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK){
		return HAL_ERROR;
	}

	if (HAL_QSPI_Receive(&hqspi, buffer, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK){
		return HAL_ERROR;
	}

    HAL_Delay(1);

	return HAL_OK;
}

uint8_t CSP_SPI_ConfigStatusRegister(uint8_t value)
{
	QSPI_CommandTypeDef sCommand;
	QSPI_AutoPollingTypeDef sConfig;

	if (SPI_WriteEnable()!=HAL_OK){
		return HAL_ERROR;
	}

	sCommand.Instruction = 0x01;
	sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
	sCommand.AddressMode = QSPI_ADDRESS_NONE;
	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode = QSPI_DATA_1_LINE;
	sCommand.NbData = 1;
	sCommand.DummyCycles = 0;
	sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

	if (HAL_QSPI_Command(&hqspi, &sCommand, HAL_QSPI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK){
		return HAL_ERROR;
	}

	if (HAL_QSPI_Transmit(&hqspi, &value, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK){
		return HAL_ERROR;
	}

	/* Configure automatic polling mode to wait for write enabling ---- */
	sConfig.Match = 0x00;
	sConfig.Mask = 0x01;
	sConfig.MatchMode = QSPI_MATCH_MODE_AND;
	sConfig.StatusBytesSize = 1;
	sConfig.Interval = 0x10;
	sConfig.AutomaticStop = QSPI_AUTOMATIC_STOP_ENABLE;

	sCommand.Instruction = 0x05;
	sCommand.DataMode = QSPI_DATA_1_LINE;
	sCommand.AddressMode = QSPI_ADDRESS_NONE;
	if (HAL_QSPI_AutoPolling(&hqspi, &sCommand, &sConfig,
							 HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
		return HAL_ERROR;
	}


	return HAL_OK;
}

uint8_t CSP_SPI_ConfigStatusRegister1(uint8_t value)
{
	QSPI_CommandTypeDef sCommand;
	QSPI_AutoPollingTypeDef sConfig;

	if (SPI_WriteEnable()!=HAL_OK){
		return HAL_ERROR;
	}

	sCommand.Instruction = 0x31;
	sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
	sCommand.AddressMode = QSPI_ADDRESS_NONE;
	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode = QSPI_DATA_1_LINE;
	sCommand.NbData = 1;
	sCommand.DummyCycles = 0;
	sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

	if (HAL_QSPI_Command(&hqspi, &sCommand, HAL_QSPI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK){
		return HAL_ERROR;
	}

	if (HAL_QSPI_Transmit(&hqspi, &value, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK){
		return HAL_ERROR;
	}

	/* Configure automatic polling mode to wait for write enabling ---- */
	sConfig.Match = 0x00;
	sConfig.Mask = 0x01;
	sConfig.MatchMode = QSPI_MATCH_MODE_AND;
	sConfig.StatusBytesSize = 1;
	sConfig.Interval = 0x10;
	sConfig.AutomaticStop = QSPI_AUTOMATIC_STOP_ENABLE;

	sCommand.Instruction = 0x05;
	sCommand.DataMode = QSPI_DATA_1_LINE;
	sCommand.AddressMode = QSPI_ADDRESS_NONE;
	if (HAL_QSPI_AutoPolling(&hqspi, &sCommand, &sConfig,
							 HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
		return HAL_ERROR;
	}


	return HAL_OK;
}

uint8_t CSP_SPI_ConfigStatusRegister2(uint8_t value)
{
	QSPI_CommandTypeDef sCommand;
	QSPI_AutoPollingTypeDef sConfig;

	if (SPI_WriteEnable()!=HAL_OK){
		return HAL_ERROR;
	}

	sCommand.Instruction = 0x11;
	sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
	sCommand.AddressMode = QSPI_ADDRESS_NONE;
	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode = QSPI_DATA_1_LINE;
	sCommand.NbData = 1;
	sCommand.DummyCycles = 0;
	sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

	if (HAL_QSPI_Command(&hqspi, &sCommand, HAL_QSPI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK){
		return HAL_ERROR;
	}

	if (HAL_QSPI_Transmit(&hqspi, &value, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK){
		return HAL_ERROR;
	}

	/* Configure automatic polling mode to wait for write enabling ---- */
	sConfig.Match = 0x00;
	sConfig.Mask = 0x01;
	sConfig.MatchMode = QSPI_MATCH_MODE_AND;
	sConfig.StatusBytesSize = 1;
	sConfig.Interval = 0x10;
	sConfig.AutomaticStop = QSPI_AUTOMATIC_STOP_ENABLE;

	sCommand.Instruction = 0x05;
	sCommand.DataMode = QSPI_DATA_1_LINE;
	sCommand.AddressMode = QSPI_ADDRESS_NONE;
	if (HAL_QSPI_AutoPolling(&hqspi, &sCommand, &sConfig,
							 HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
		return HAL_ERROR;
	}
	return HAL_OK;
}

uint8_t CSP_SPI_EraseSector_4ADDR(uint32_t address)
{
	QSPI_CommandTypeDef sCommand;
	QSPI_AutoPollingTypeDef sConfig;

	if (SPI_WriteEnable()!=HAL_OK){
		return HAL_ERROR;
	}

	sCommand.Instruction = 0x21;
	sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
	sCommand.AddressMode = QSPI_ADDRESS_1_LINE;
	sCommand.AddressSize = QSPI_ADDRESS_32_BITS;
	sCommand.Address = address;
	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode = QSPI_DATA_NONE;
	sCommand.NbData = 0;
	sCommand.DummyCycles = 0;
	sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

	if (HAL_QSPI_Command(&hqspi, &sCommand, HAL_QSPI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK){
		return HAL_ERROR;
	}

	HAL_Delay(1);

    /* Configure automatic polling mode to wait for write enabling ---- */
    sConfig.Match = 0x00;
    sConfig.Mask = 0x01;
    sConfig.MatchMode = QSPI_MATCH_MODE_AND;
    sConfig.StatusBytesSize = 1;
    sConfig.Interval = 0x10;
    sConfig.AutomaticStop = QSPI_AUTOMATIC_STOP_ENABLE;

    sCommand.Instruction = 0x05;
    sCommand.DataMode = QSPI_DATA_1_LINE;
    sCommand.AddressMode = QSPI_ADDRESS_NONE;
    if (HAL_QSPI_AutoPolling(&hqspi, &sCommand, &sConfig,
                             HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
        return HAL_ERROR;
    }

	return HAL_OK;
}

uint8_t CSP_SPI_FastReadPage_4ADDR(uint32_t address, uint8_t* buffer)
{
	QSPI_CommandTypeDef sCommand;

	sCommand.Instruction = 0x0C;
	sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
	sCommand.AddressMode = QSPI_ADDRESS_1_LINE;
	sCommand.AddressSize = QSPI_ADDRESS_32_BITS;
	sCommand.Address = address;
	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode = QSPI_DATA_1_LINE;
	sCommand.NbData = 256;
	sCommand.DummyCycles = 8;
	sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

	if (HAL_QSPI_Command(&hqspi, &sCommand, HAL_QSPI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK){
		return HAL_ERROR;
	}

	if (HAL_QSPI_Receive(&hqspi, buffer, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK){
		return HAL_ERROR;
	}

	HAL_Delay(1);

	return HAL_OK;
}

uint8_t CSP_QSPI_FastReadPage_4ADDR(uint32_t address, uint8_t* buffer)
{
	QSPI_CommandTypeDef sCommand;

	sCommand.Instruction = 0x6C;
	sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
	sCommand.AddressMode = QSPI_ADDRESS_1_LINE;
	sCommand.AddressSize = QSPI_ADDRESS_32_BITS;
	sCommand.Address = address;
	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode = QSPI_DATA_4_LINES;
	sCommand.NbData = 256;
	sCommand.DummyCycles = 8;
	sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

	if (HAL_QSPI_Command(&hqspi, &sCommand, HAL_QSPI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK){
		return HAL_ERROR;
	}

	if (HAL_QSPI_Receive(&hqspi, buffer, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK){
		return HAL_ERROR;
	}

	HAL_Delay(1);

	return HAL_OK;
}

uint8_t CSP_QSPI_FastReadPage_4ADDR_512(uint32_t address, uint8_t* buffer)
{
	QSPI_CommandTypeDef sCommand;

	sCommand.Instruction = 0x6C;
	sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
	sCommand.AddressMode = QSPI_ADDRESS_1_LINE;
	sCommand.AddressSize = QSPI_ADDRESS_32_BITS;
	sCommand.Address = address;
	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode = QSPI_DATA_4_LINES;
	sCommand.NbData = 512;
	sCommand.DummyCycles = 8;
	sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

	if (HAL_QSPI_Command(&hqspi, &sCommand, HAL_QSPI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK){
		return HAL_ERROR;
	}

	if (HAL_QSPI_Receive(&hqspi, buffer, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK){
		return HAL_ERROR;
	}

	HAL_Delay(1);

	return HAL_OK;
}

uint8_t CSP_SPI_ProgramPage_4ADDR(uint32_t address, uint32_t length, uint8_t* buffer)
{
	QSPI_CommandTypeDef sCommand;
	QSPI_AutoPollingTypeDef sConfig;

	if (SPI_WriteEnable()!=HAL_OK){
		return HAL_ERROR;
	}

	sCommand.Instruction = 0x12;
	sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
	sCommand.AddressMode = QSPI_ADDRESS_1_LINE;
	sCommand.AddressSize = QSPI_ADDRESS_32_BITS;
	sCommand.Address = address;
	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode = QSPI_DATA_1_LINE;
	sCommand.NbData = length;
	sCommand.DummyCycles = 0;
	sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

	if (HAL_QSPI_Command(&hqspi, &sCommand, HAL_QSPI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK){
		return HAL_ERROR;
	}

	if (HAL_QSPI_Transmit(&hqspi, buffer, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK){
		return HAL_ERROR;
	}

	HAL_Delay(1);

	/* Configure automatic polling mode to wait for write enabling ---- */
	sConfig.Match = 0x00;
	sConfig.Mask = 0x01;
	sConfig.MatchMode = QSPI_MATCH_MODE_AND;
	sConfig.StatusBytesSize = 1;
	sConfig.Interval = 0x10;
	sConfig.AutomaticStop = QSPI_AUTOMATIC_STOP_ENABLE;

	sCommand.Instruction = 0x05;
	sCommand.DataMode = QSPI_DATA_1_LINE;
	sCommand.AddressMode = QSPI_ADDRESS_NONE;
	if (HAL_QSPI_AutoPolling(&hqspi, &sCommand, &sConfig,
							 HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
		return HAL_ERROR;
	}

	return HAL_OK;
}

uint8_t CSP_QSPI_ProgramPage_4ADDR(uint32_t address, uint32_t length, uint8_t* buffer)
{
	QSPI_CommandTypeDef sCommand;
	QSPI_AutoPollingTypeDef sConfig;

	if (SPI_WriteEnable()!=HAL_OK){
		return HAL_ERROR;
	}

	sCommand.Instruction = 0x34;
	sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
	sCommand.AddressMode = QSPI_ADDRESS_1_LINE;
	sCommand.AddressSize = QSPI_ADDRESS_32_BITS;
	sCommand.Address = address;
	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode = QSPI_DATA_4_LINES;
	sCommand.NbData = length;
	sCommand.DummyCycles = 0;
	sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

	if (HAL_QSPI_Command(&hqspi, &sCommand, HAL_QSPI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK){
		return HAL_ERROR;
	}

	if (HAL_QSPI_Transmit(&hqspi, buffer, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK){
		return HAL_ERROR;
	}

	HAL_Delay(1);

	/* Configure automatic polling mode to wait for write enabling ---- */
	sConfig.Match = 0x00;
	sConfig.Mask = 0x01;
	sConfig.MatchMode = QSPI_MATCH_MODE_AND;
	sConfig.StatusBytesSize = 1;
	sConfig.Interval = 0x10;
	sConfig.AutomaticStop = QSPI_AUTOMATIC_STOP_ENABLE;

	sCommand.Instruction = 0x05;
	sCommand.DataMode = QSPI_DATA_1_LINE;
	sCommand.AddressMode = QSPI_ADDRESS_NONE;
	if (HAL_QSPI_AutoPolling(&hqspi, &sCommand, &sConfig,
							 HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
		return HAL_ERROR;
	}

	return HAL_OK;
}

uint8_t CSP_RealQSPI_FastReadPage_4ADDR(uint32_t address, uint8_t* buffer)
{
	QSPI_CommandTypeDef sCommand;

	sCommand.Instruction = 0xEC;
	sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
	sCommand.AddressMode = QSPI_ADDRESS_4_LINES;
	sCommand.AddressSize = QSPI_ADDRESS_32_BITS;
	sCommand.Address = address;
	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_4_LINES;
	sCommand.AlternateBytesSize = QSPI_ALTERNATE_BYTES_8_BITS;
	sCommand.AlternateBytes = 0xFA;
	sCommand.DataMode = QSPI_DATA_4_LINES;
	sCommand.NbData = 256;
	sCommand.DummyCycles = 4;
	sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

	if (HAL_QSPI_Command(&hqspi, &sCommand, HAL_QSPI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK){
		return HAL_ERROR;
	}

	if (HAL_QSPI_Receive(&hqspi, buffer, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)!=HAL_OK){
		return HAL_ERROR;
	}

	HAL_Delay(1);

	return HAL_OK;
}

/* USER CODE END 1 */
