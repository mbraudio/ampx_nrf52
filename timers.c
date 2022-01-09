#include "timers.h"
#include "app_timer.h"
#include "ampx.h"
#include "uart.h"


APP_TIMER_DEF(timer_led_connection);
APP_TIMER_DEF(timer_led_uart_tx_rx);


void timer_create_activity_timer(void);
void activity_timer_handler(void* context);
void connection_led_timeout_handler(void* context);
void uart_rx_tx_led_timeout_handler(void* context);

// Functions
void timers_init(void)
{
    uint32_t err_code;
    // Connection LED timer
    err_code = app_timer_create(&timer_led_connection, APP_TIMER_MODE_REPEATED, connection_led_timeout_handler);
    APP_ERROR_CHECK(err_code);
    // UART Tx Rx LED timer
    err_code = app_timer_create(&timer_led_uart_tx_rx, APP_TIMER_MODE_REPEATED, uart_rx_tx_led_timeout_handler);
    APP_ERROR_CHECK(err_code);

    timers_start_uart_tx_rx_timer();
}

void connection_led_timeout_handler(void* context)
{
    ampx_led_connection_toggle();
}

void uart_rx_tx_led_timeout_handler(void* context)
{
    if (led_status.led_rx_on)
    {
        ampx_led_rx_off();
    }

    if (led_status.led_tx_on)
    {
        ampx_led_tx_off();
    }
}

inline void timers_start_connection_timer(void)
{
    uint32_t err_code;
    err_code = app_timer_start(timer_led_connection, INTERVAL_LED_CONNECTION, NULL);
    APP_ERROR_CHECK(err_code);
}

inline void timers_stop_connection_timer(void)
{
    uint32_t err_code;
    err_code = app_timer_stop(timer_led_connection);
    APP_ERROR_CHECK(err_code);
}

inline void timers_start_uart_tx_rx_timer(void)
{
    uint32_t err_code;
    err_code = app_timer_start(timer_led_uart_tx_rx, INTERVAL_LED_UART_TX_RX, NULL);
    APP_ERROR_CHECK(err_code);
}

inline void timers_stop_uart_tx_rx_timer(void)
{
    uint32_t err_code;
    err_code = app_timer_stop(timer_led_uart_tx_rx);
    APP_ERROR_CHECK(err_code);
}
