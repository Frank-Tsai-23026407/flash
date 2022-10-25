#include <cstdint>
#include <cstring>

#include "qspi_rad_test.h"

#include "main.h"
#include "i2c.h"
#include "quadspi.h"
#include "usart.h"
#include "gpio.h"

extern QSPI_HandleTypeDef hqspi;

int32_t sectorErase(uint32_t addr) {
	uint8_t rv;

	rv = CSP_SPI_EraseSector_4ADDR(addr);
	if (rv != HAL_OK) return rv;

	return 0;
}

int32_t pageRead(uint32_t addr, uint8_t data[256]) {
	uint8_t rv;

	rv = CSP_QSPI_FastReadPage_4ADDR(addr, data);
	if (rv != HAL_OK) return rv;

	return 0;
}

int32_t pageWrite(uint32_t addr, const uint8_t data[256]) {
	uint8_t rv;

	int i;
	uint8_t data_program[256];
	for(i = 0; i < 256; i++) data_program[i] = data[i];

	rv = CSP_QSPI_ProgramPage_4ADDR(addr, 256, data_program);
	if (rv != HAL_OK) return rv;

	return 0;
}

int32_t chipSelect(uint8_t chip) {
	if(chip == 1)
	{
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_13, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_SET);	
	}
	else if(chip == 2)
	{
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_13, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_RESET);	
	}
	else if(chip == 3)
	{
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_13, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_SET);
	}
	else if(chip == 4)
	{
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_13, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_RESET);
	}
	else if(chip == 5)
	{
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_13, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_SET);
	}
	else if(chip == 6)
	{
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_13, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_RESET);
	}
	else if(chip == 7)
	{
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_13, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_SET);
	}
	else
	{	
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_13, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_RESET);
		return 1;
	}
	return 0;
}

int32_t chipInitial(uint8_t * initial_state) {
	*initial_state = 0;
	uint8_t rxbuff[3];
	if(CSP_SPI_Init()!=HAL_OK) *initial_state = 1;
	if(CSP_SPI_ReadJEDECID(rxbuff)!=HAL_OK) *initial_state = 1;
	if(rxbuff[0] != 0xEF || rxbuff[1] != 0x40 ||rxbuff[2] != 0x19)
		*initial_state = 2;
	if(CSP_SPI_ConfigStatusRegister1(0x02)!=HAL_OK) *initial_state = 1;
	return 0;
}

int32_t readCurrent(uint8_t slave_address, uint8_t memory_address, uint8_t * memory_value)
{
	I2CRead1Bytes(slave_address, memory_address, memory_value);
	return 0;
}
