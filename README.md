# [WIP] ESP LivingColors

An electronic board designed to integrate a LivingColor lamp gen1 in [HomeAssistant].
The board is based on an ESP8266 & [ESPHome] to integrate the LivingColors lamp in HomeAssistant.
The communication with the lamp is managed by an Atmega328 microcontroller & a CC2500 module (2.4ghz RF transceiver).
The ESP8266 & Atmega328 communicate through an I2C bus.

## PCB

The card must be powered with 5V via the J1 connector.

The Atmega328 can be flashed via JP1. The ESP8266 can be flashed via JP3.
For this, you can use my [ESP/Atmega programmer].

The card was designed with [Eagle].
The additional [libraries] used are:
* 74LVC125AD.lbr
* ATMEGA328P-AU.lbr
* CC2500.lbr
* CONNECTORS.lbr
* ESP-12F.lbr
* TXS0104EPWR.lbr
* regulator.lbr

## Software

TODO

[HomeAssistant]: https://www.home-assistant.io
[ESPHome]: https://esphome.io/
[ESP/Atmega programmer]: https://github.com/hiteule/programmer-esp-atmega
[Eagle]:     https://www.autodesk.fr/products/eagle
[libraries]: https://github.com/hiteule/eagle-library
