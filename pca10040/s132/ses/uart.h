#ifndef _UART_H_
#define _UART_H_


#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define UART_BUFFER_SIZE 256

typedef struct
{
    uint32_t	enabled;
    uint16_t	uart_id;
    uint16_t	expected_ble_packet_length;
    uint8_t	buffer[UART_BUFFER_SIZE];
    uint16_t    byte_index;
    uint32_t    ble_buffer_available;
    uint32_t    tx_complete;
    uint8_t     byte;
} UartWorker;

extern UartWorker uartWorker;

void uart_init(void);
void uart_close(void);
void uart_send(const uint8_t* data, const uint16_t length);
void uart_reset_status(void);

#ifdef __cplusplus
}
#endif

#endif
