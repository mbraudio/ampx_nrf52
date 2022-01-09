#ifndef _BLE_RWS_
#define _BLE_RWS_


#include <stdint.h>
#include <stdbool.h>
#include "sdk_config.h"
#include "ble.h"
#include "ble_srv_common.h"
#include "nrf_sdh_ble.h"
#include "ble_link_ctx_manager.h"


#ifdef __cplusplus
extern "C" {
#endif

#ifndef BLE_RWS_BLE_OBSERVER_PRIO
#define BLE_RWS_BLE_OBSERVER_PRIO 2
#endif

#define BLE_RWS_DEF(_name, _rws_max_clients)                      \
    BLE_LINK_CTX_MANAGER_DEF(CONCAT_2(_name, _link_ctx_storage),  \
                             (_rws_max_clients),                  \
                             sizeof(ble_rws_client_context_t));   \
    static ble_rws_t _name =                                      \
    {                                                             \
        .p_link_ctx_storage = &CONCAT_2(_name, _link_ctx_storage) \
    };                                                            \
    NRF_SDH_BLE_OBSERVER(_name ## _obs, BLE_RWS_BLE_OBSERVER_PRIO, ble_rws_on_ble_evt, &_name)

#define BLE_UUID_RWS_SERVICE           0x86F5

#define OPCODE_LENGTH        1
#define HANDLE_LENGTH        2


#if defined(NRF_SDH_BLE_GATT_MAX_MTU_SIZE) && (NRF_SDH_BLE_GATT_MAX_MTU_SIZE != 0)
    #define BLE_RWS_MAX_DATA_LEN (NRF_SDH_BLE_GATT_MAX_MTU_SIZE - OPCODE_LENGTH - HANDLE_LENGTH)
#else
    #define BLE_RWS_MAX_DATA_LEN (BLE_GATT_MTU_SIZE_DEFAULT - OPCODE_LENGTH - HANDLE_LENGTH)
    #warning NRF_SDH_BLE_GATT_MAX_MTU_SIZE is not defined.
#endif


typedef enum
{
    BLE_RWS_EVT_RX_DATA,      /**< Data received. */
    BLE_RWS_EVT_TX_RDY,       /**< Service is ready to accept new data to be transmitted. */
    BLE_RWS_EVT_COMM_STARTED, /**< Notification has been enabled. */
    BLE_RWS_EVT_COMM_STOPPED, /**< Notification has been disabled. */
} ble_rws_evt_type_t;


typedef struct ble_rws_s ble_rws_t;


typedef struct
{
    uint8_t const*  p_data; /**< A pointer to the buffer with received data. */
    uint16_t        length; /**< Length of received data. */
} ble_rws_evt_rx_data_t;


typedef struct
{
    bool is_notification_enabled; /**< Variable to indicate if the peer has enabled notification of the RX characteristic.*/
} ble_rws_client_context_t;


typedef struct
{
    ble_rws_evt_type_t         type;        /**< Event type. */
    ble_rws_t*                 p_rws;       /**< A pointer to the instance. */
    uint16_t                   conn_handle; /**< Connection handle. */
    ble_rws_client_context_t*  p_link_ctx;  /**< A pointer to the link context. */
    union
    {
        ble_rws_evt_rx_data_t rx_data; /**< @ref BLE_NUS_EVT_RX_DATA event data. */
    } params;
} ble_rws_evt_t;


typedef void (* ble_rws_data_handler_t) (ble_rws_evt_t* p_evt);


typedef struct
{
    ble_rws_data_handler_t data_handler; /**< Event handler to be called for handling received data. */
} ble_rws_init_t;


struct ble_rws_s
{
    uint8_t                         uuid_type;          /**< UUID type for Nordic UART Service Base UUID. */
    uint16_t                        service_handle;     /**< Handle of Nordic UART Service (as provided by the SoftDevice). */
    ble_gatts_char_handles_t        tx_handles;         /**< Handles related to the TX characteristic (as provided by the SoftDevice). */
    ble_gatts_char_handles_t        rx_handles;         /**< Handles related to the RX characteristic (as provided by the SoftDevice). */
    blcm_link_ctx_storage_t * const p_link_ctx_storage; /**< Pointer to link context storage with handles of all current connections and its context. */
    ble_rws_data_handler_t          data_handler;       /**< Event handler to be called for handling received data. */
};


uint32_t  ble_rws_init(ble_rws_t* p_rws, ble_rws_init_t const* p_rws_init);
void      ble_rws_on_ble_evt(ble_evt_t const * p_ble_evt, void* p_context);
uint32_t  ble_rws_send_data(ble_rws_t* p_rws, uint8_t* p_data, uint16_t* p_length, uint16_t conn_handle);
uint32_t  ble_rws_try_to_send(ble_rws_t* rws, uint8_t* data, uint16_t* pLength, uint16_t connHandle);

#ifdef __cplusplus
}
#endif

#endif