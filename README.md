# ESP LivingColors

An electronic board designed to integrate a LivingColor lamp gen1 in [HomeAssistant].
The board is based on an ESP8266 & [ESPHome] to integrate the LivingColors lamp in HomeAssistant.
The communication with the lamp is managed by an Atmega328 microcontroller & a CC2500 module (2.4ghz RF transceiver).
The ESP8266 & Atmega328 communicate through an I2C bus.

:warning: This board ONLY works with the 1st generation LivingColors.

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

### Atmega

The Atmega is controling the LivingColors via RF (like your conventional remote control).
We use Arduino bootloader. If it not already the case, you should install it on your Atmega.
To communicate in RF, we use the library made by [George Knutsel]. Thanks to him!

#### Flash the firmware

* Install the Arduino IDE.
* Put the `LivingColors` library in the right Arduino Library folder.
* Plug the board to your computer with JP1 and the [ESP/Atmega programmer] (for the Atmega, you don't need to power it).
* Open the firmware with the Arduino IDE and flash the Atmega.

Now, you can unplug the Atmega and go to the next step.

### ESP

The ESP is exposing the LivingColors in Home Assisant. To do it, we use [ESPHome].
To do so:
* Install the ESPHome module on HomeAssistant.
* Plug the board to your computer with JP3 and the [ESP/Atmega programmer]. Don't forget to power the programmer with an external power source between 3.3V and 12V.
* In the ESPHome module, create a new device.
* Put the `light_i2c_output.h` file in your HomeAssistant instance: `/config/esphome/light_i2c_output.h`.
* Update your ESPHome device with the `livingcolors.yaml` file.
* Install it on the ESP.

Now you can unplug the ESP from your computer and power the board via JP1.
ESP should boot normally and the LivingColors should be visible in HomeAssistant.

## How to use it ?

To be able to communicate with the LivingColors, you need to extract and register the remote address.

* Hold the `SW_LEARN` switch and power on the board to enter in the learning mode.
* The LED will light up for 5 seconds. During this time, place the remote control close to the card and press any button several times.

If the procedure fails, the LED will flash slowly (every 1 second). Repeat the learning procedure.
If the LED is off, the procedure was successful and the remote control address has been extracted and registered. You can now use it :)


## FAQ

**The LED will flash quickly (every 100ms)**\
The card doesn't know the remote address. You should run a learning procedure. Please see the "How to use it ?" section.

**The LED will flash slowly (every 1s)**\
The remote address learning procedure fail (no address found). You should restart a learning procedure. Place the remote control close to the card and press several buttons.

**Do I need to do a remote address learning procedure every time I launch the card?**\
No, the remote address is saved in the Atmega ROM.

**Can I continue to use the remote control?**\
Yes, you can continue to use the remote control alongside the card.

**Can I register another remote control?**\
Yes, simply launch a remote address learning procedure.
Please note that you can only register one remote control at a time.

[HomeAssistant]: https://www.home-assistant.io
[ESPHome]: https://esphome.io/
[ESP/Atmega programmer]: https://github.com/hiteule/programmer-esp-atmega
[Eagle]: https://www.autodesk.fr/products/eagle
[libraries]: https://github.com/hiteule/eagle-library
[George Knutsel]: http://www.knutsel.org/2010/04/11/using-the-cc2500-arduino-shield
