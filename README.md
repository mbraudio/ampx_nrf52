# ampx_nrf52
Nordic nRF52832 project which transmits data from integrated amplifier and mobile device.

SDK: nRF5_SDK_17.1.0_ddde560

nRF52 module is used as a relay for data, basically a wire replacement.
Mobile application AmpX connects to this module over BLE connection and transmits data to STM32 MCU.
Mobile application can replace IR remote control and more.
