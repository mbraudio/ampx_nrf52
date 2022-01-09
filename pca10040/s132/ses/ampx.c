#include "ampx.h"
#include "nrf_gpio.h"
#include "timers.h"

led_status_t led_status;

void ampx_init(void)
{
    nrf_gpio_cfg_output(LED_CONNECTION_PIN_NUMBER);
    nrf_gpio_cfg_output(LED_RX_PIN_NUMBER);
    nrf_gpio_cfg_output(LED_TX_PIN_NUMBER);
}

void ampx_indicate(const indicate_t state)
{
    switch (state)
    {
        case INDICATE_IDLE:
        {
            ampx_led_connection_off();
            ampx_led_rxtx_off();
        } break;

        case INDICATE_ADVERTISING:
        {
            timers_start_connection_timer();
            ampx_led_rxtx_off();
        } break;

        case INDICATE_CONNECTED:
        {
            timers_stop_connection_timer();
            timers_start_uart_tx_rx_timer();
            ampx_led_connection_on();
        } break;

        case INDICATE_DISCONNECTED:
        {
            timers_stop_uart_tx_rx_timer();
            ampx_led_rxtx_off();
        } break;
    }
}

inline void ampx_led_connection_on(void)
{
    nrf_gpio_pin_set(LED_CONNECTION_PIN_NUMBER);
}

inline void ampx_led_connection_off(void)
{
    nrf_gpio_pin_clear(LED_CONNECTION_PIN_NUMBER);
}

inline void ampx_led_connection_toggle(void)
{
    nrf_gpio_pin_toggle(LED_CONNECTION_PIN_NUMBER);
}

inline void ampx_led_rxtx_off(void)
{
    ampx_led_rx_off();
    ampx_led_tx_off();
}

inline void ampx_led_rx_on(void)
{
    nrf_gpio_pin_set(LED_RX_PIN_NUMBER);
    led_status.led_rx_on = 1;
}

inline void ampx_led_rx_off(void)
{
    nrf_gpio_pin_clear(LED_RX_PIN_NUMBER);
    led_status.led_rx_on = 0;
}

inline void ampx_led_tx_on(void)
{
    nrf_gpio_pin_set(LED_TX_PIN_NUMBER);
    led_status.led_tx_on = 1;
}

inline void ampx_led_tx_off(void)
{
    nrf_gpio_pin_clear(LED_TX_PIN_NUMBER);
    led_status.led_tx_on = 0;
}