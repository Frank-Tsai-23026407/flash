#include <cstdint>
#include <cstring>

#include "qspi_rad_test.h"

static uint8_t mock_mem_page[256] = {0};

int32_t sectorErase(uint32_t addr) { return 0; }

int32_t pageRead(uint32_t addr, uint8_t data[256]) {
  for (int i=0;i<256;i++) {
    data[i] = mock_mem_page[i];
  }
  return 0;
}

int32_t pageWrite(uint32_t addr, const uint8_t data[256]) {
  for (int i=0;i<256;i++) {
    mock_mem_page[i] = data[i];
  }
  return 0;
}
