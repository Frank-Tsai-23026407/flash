#ifndef ERPC_HAL_UART_TRANSPORT_H_
#define ERPC_HAL_UART_TRANSPORT_H_

#include "stm32f4xx.h"

#include "erpc_framed_transport.hpp"
#include "erpc_transport_setup.h"

#include "erpc_setup_hal_uart.hpp"
namespace erpc {
class HALUARTTransport : public FramedTransport {
private:
  UART_HandleTypeDef *p_uart_instance;
  uint16_t dev_id;

  virtual erpc_status_t underlyingReceive(uint8_t *data, uint32_t size);

  virtual erpc_status_t underlyingSend(const uint8_t *data, uint32_t size);

public:
  HALUARTTransport(UART_HandleTypeDef *p_uart_instance);
  ~HALUARTTransport();
  virtual erpc_status_t init(void);
};
} // namespace erpc

#endif /* ERPC_HAL_UART_TRANSPORT_H_ */
