

#include "stm32f4xx.h"

#include "erpc_common.h"
#include "erpc_hal_uart_transport.hpp"
#include "erpc_manually_constructed.hpp"
#include "erpc_transport_setup.h"

namespace erpc {

HALUARTTransport::HALUARTTransport(UART_HandleTypeDef *p_uart_instance) {
  this->p_uart_instance = p_uart_instance;
}

HALUARTTransport::~HALUARTTransport() {}

erpc_status_t HALUARTTransport::underlyingReceive(uint8_t *data,
                                                  uint32_t size) {
  if (HAL_UART_Receive(this->p_uart_instance, data, size, HAL_MAX_DELAY) != HAL_OK) {
    return kErpcStatus_Fail;
  }
  return kErpcStatus_Success;
}

erpc_status_t HALUARTTransport::underlyingSend(const uint8_t *data,
                                               uint32_t size) {
  if (HAL_UART_Transmit(this->p_uart_instance, (uint8_t *)data, size, HAL_MAX_DELAY) !=
      HAL_OK) {
    return kErpcStatus_Fail;
  }
  return kErpcStatus_Success;
}

erpc_status_t HALUARTTransport::init() { return kErpcStatus_Success; }
} // namespace erpc
