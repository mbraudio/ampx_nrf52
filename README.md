# ampx_nrf52
Nordic nRF52832 project which transmits data from integrated amplifier and mobile device.

Project is created in Segger Embedded Studio and uses nRF5_SDK_17.1.0_ddde560 as SDK.

nRF52 module is used as a relay for data, basically a wire replacement.
Mobile app. (AmpX) connects to this module over BLE connection and transmits data to STM32 MCU.
AmpX app can replace IR remote control and more.
