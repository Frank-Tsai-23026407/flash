#include <cstdint>
#include <cstring>

#include "qspi_rad_test.h"

#include "main.h"
#include "i2c.h"
#include "quadspi.h"
#include "usart.h"
#include "usb_otg.h"
#include "gpio.h"

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

	rv = CSP_SPI_ProgramPage_4ADDR(addr, 256, data_program);
	if (rv != HAL_OK) return rv;

	return 0;
}

int32_t chipSelect(uint8_t chip) {

}

int32_t chipInitial(uint8_t * result) {

}

int32_t readCurrent(float * current) {

}
