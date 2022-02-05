#include "uart.h"
#include "app_uart.h"
#include "ampx.h"
#include "nrf_log.h"
#include "nrf52_bitfields.h"


#define UART_RX_PIN_NUMBER    8
#define UART_TX_PIN_NUMBER    6
#define UART_CTS_PIN_NUMBER   5
#define UART_RTS_PIN_NUMBER   7
#define UART_HWFC             APP_UART_FLOW_CONTROL_ENABLED
#define UART_PARITY           false
#define UART_TX_BUFFER_SIZE   256
#define UART_RX_BUFFER_SIZE   256
#define UART_BAUDRATE         UART_BAUDRATE_BAUDRATE_Baud115200

UartWorker uartWorker;

void uart_event_handle(app_uart_evt_t * p_event)
{
    switch (p_event->evt_type)
    {
        case APP_UART_DATA_READY:
        {

        } break;

        case APP_UART_COMMUNICATION_ERROR: 
        {
          // Shendlaj ovo sa resartom ili clearanjem UART-a!
          //APP_ERROR_HANDLER(p_event->data.error_communication);
          NRF_LOG_ERROR("APP_UART_COMMUNICATION_ERROR");
          uartWorker.enabled = 0;
          uart_reset_status();
          uartWorker.enabled = 1;
        } break;

        case APP_UART_FIFO_ERROR:
        {
          // Shendlaj ovo sa resartom ili clearanjem UART-a!
          //APP_ERROR_HANDLER(p_event->data.error_code);
          NRF_LOG_ERROR("APP_UART_FIFO_ERROR");
          uartWorker.enabled = 0;
          uart_reset_status();
          uartWorker.enabled = 1;
        } break;
            

        default:
        {
        
        } break;
    }
}

void uart_init(void)
{
    uint32_t err_code;
    app_uart_comm_params_t const comm_params =
    {
        .rx_pin_no    = UART_RX_PIN_NUMBER,
        .tx_pin_no    = UART_TX_PIN_NUMBER,
        .rts_pin_no   = UART_RTS_PIN_NUMBER,
        .cts_pin_no   = UART_CTS_PIN_NUMBER,
        .flow_control = UART_HWFC,
        .use_parity   = UART_PARITY,
        .baud_rate    = UART_BAUDRATE
    };

    APP_UART_FIFO_INIT(&comm_params, UART_RX_BUFFER_SIZE, UART_TX_BUFFER_SIZE, uart_event_handle, APP_IRQ_PRIORITY_MID/*APP_IRQ_PRIORITY_LOWEST*/, err_code);
    APP_ERROR_CHECK(err_code);

    uart_reset_status();
}

void uart_close(void)
{
    uartWorker.enabled = 0;
    app_uart_close();
}

void uart_reset_status(void)
{
    uint32_t err_code;

    uartWorker.byte = 0xFF;
    uartWorker.byte_index = 0;
    uartWorker.ble_buffer_available = 1;
    uartWorker.tx_complete = 0;

    err_code = app_uart_flush();
    APP_ERROR_CHECK(err_code);
}

void uart_send(const uint8_t* data, const uint16_t length)
{
    uint32_t err_code, i;
    for (i = 0; i < length; i++)
    {
        do
        {
            ampx_led_tx_on();
            err_code = app_uart_put(data[i]);
            if ((err_code != NRF_SUCCESS) && (err_code != NRF_ERROR_BUSY))
            {
                NRF_LOG_ERROR("Failed receiving RWS message. Error 0x%x. ", err_code);
                APP_ERROR_CHECK(err_code);
            }
        } while (err_code == NRF_ERROR_BUSY);
    }
}