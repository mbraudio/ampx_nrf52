#ifndef _BOARD_H_
#define _BOARD_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define LED_CONNECTION_PIN_NUMBER     13
#define LED_RX_PIN_NUMBER              1
#define LED_TX_PIN_NUMBER              0

#define PIN_I2C_SDA 26
#define PIN_I2C_SCL 27
#define PIN_BT0     21
#define PIN_BT1     22

typedef enum
{
    INDICATE_IDLE = 0,
    INDICATE_ADVERTISING,
    INDICATE_CONNECTED,
    INDICATE_DISCONNECTED
} indicate_t;

typedef struct
{
    uint32_t  led_rx_on;
    uint32_t  led_tx_on;
} led_status_t;

extern led_status_t led_status;

void ampx_init(void);
void ampx_indicate(const indicate_t state);
void ampx_led_connection_on(void);
void ampx_led_connection_off(void);
void ampx_led_connection_toggle(void);
void ampx_led_rxtx_off(void);
void ampx_led_rx_on(void);
void ampx_led_rx_off(void);
void ampx_led_tx_on(void);
void ampx_led_tx_off(void);


#ifdef __cplusplus
}
#endif

#endif
