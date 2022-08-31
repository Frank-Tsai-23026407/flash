#ifndef ERPC_SETUP_HAL_UART_H_
#define ERPC_SETUP_HAL_UART_H_
#include "erpc_transport_setup.h"

erpc_transport_t
erpc_transport_hal_uart_init(UART_HandleTypeDef *p_uart_instance);

#endif /* ERPC_SETUP_HAL_UART_H_ */
