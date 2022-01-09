#ifndef _TIMERS_H_
#define _TIMERS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>


#define TIME_LED_CONNECTION       400 //ms
#define TIME_LED_UART_TX_RX        30 //ms

#define INTERVAL_LED_CONNECTION   APP_TIMER_TICKS(TIME_LED_CONNECTION)
#define INTERVAL_LED_UART_TX_RX   APP_TIMER_TICKS(TIME_LED_UART_TX_RX)

void timers_init(void);
void timers_start_connection_timer(void);
void timers_stop_connection_timer(void);
void timers_start_uart_tx_rx_timer(void);
void timers_stop_uart_tx_rx_timer(void);

#ifdef __cplusplus
}
#endif

#endif
