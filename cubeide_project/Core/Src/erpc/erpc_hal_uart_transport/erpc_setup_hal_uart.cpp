#include "stm32f4xx.h"

#include "erpc_hal_uart_transport.hpp"
#include "erpc_manually_constructed.hpp"
#include "erpc_transport_setup.h"

using namespace erpc;

static ManuallyConstructed<HALUARTTransport> s_transport;

erpc_transport_t
erpc_transport_hal_uart_init(UART_HandleTypeDef *p_uart_instance) {
  s_transport.construct(p_uart_instance);
  if (s_transport->init() == kErpcStatus_Success) {
    return reinterpret_cast<erpc_transport_t>(s_transport.get());
  }
  return NULL;
}