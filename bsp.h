#ifndef _BOARD_H_
#define _BOARD_H_


#ifdef __cplusplus
extern "C" {
#endif

#include "app_timer.h"

#define LED_INDICATION_TIMEOUT_MS 400
#define LED_RXTX_TIMEOUT_MS 1

#define LED_CONNECTION_PIN_NUMBER 13
#define LED_RX_PIN_NUMBER         25
#define LED_TX_PIN_NUMBER         24


typedef enum
{
    INDICATE_IDLE = 0,
    INDICATE_CONNECTED,
    INDICATE_DISCONNECTED
} indicate_t;


void ampx_init(const app_timer_id_t* indication_timer);
void ampx_indicate(const indicate_t state);
void ampx_led_rx_on(void);
void ampx_led_tx_on(void);
void ampx_led_rxtx_clear(void);


#ifdef __cplusplus
}
#endif

#endif
