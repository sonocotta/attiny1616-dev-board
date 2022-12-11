# ATtiny 1616 Development Board

![Open Source Hardware](/doc/images/open-source-hardware-logo.png)
![Open Source Software](/doc/images/open-source-software-logo.png)

ATtiny 1616 Development Board is a small and handy development board built around new generation of ATiny series. It is pin and size compartible with Arduino Nano board and can be used as it's direct replacement (with certain limitations). It can be programmed using both Arduino IDE and Platformio IDE, as well as vanilla console tools.

## Motivation

I'm a big fan of early ATtiny series chips, I even made my own [ATtiny Flasher](https://sonocotta.com/attiny-flasher/) tool for productive development and few educational kites based on ubiquitous ATtiny85. Time has come to extend my horizons and look into modern line of ATtiny chips, specifically so called 1-series and 2-series line of MCUs. 

No need to mention that they went far ahead old series, and having resources comparable with old ATmega series. This gave me an idea to make Arduino Nano pin compatible development board, so I can start using it the projects, where I'd normally pick Arduino Nano. In my practice the best way to get familiar with new hardware is to start using it in the actual projects.

## Features

- [ATTINY1616](https://www.microchip.com/en-us/product/ATTINY1616) 8-bit MCU in a 20-pin package
- Up to 20 MHz guaranteed by manufacturer, up to 32 MHz reported by community in normal conditions 
- 16 KB Flash
- 2 KB SRAM
- 128B of EEPROM 
- UPDI interface for flashing and debugging
- Onboard 5V LDO (disconnected for low power applications)
- Flash using Arduino IDE, Platformio, or the IDE of your choice
- Onboard USB-Serial bridge (CH340E) connected to hardware Serial port
- One RGB LED (WS2812B)
- One Push button

## ATtiny1616

ATiny1616 is a mid-range chip in new [ATtiny 1-Series line](https://en.wikipedia.org/wiki/ATtiny_microcontroller_comparison_chart). Generally they offer considerably more than older Tiny-series chip, and comparable with classic ATmega AVRs, offering at the same time new MCU features, not available in older series.

|               | ATTINY88 | ATTINY1616 | ATmega168P | ATmega328P |
|---------------|----------|------------|------------|------------|
| Max Frequency |          | 20 Mhz     | 16Mhz      | 16Mhz      |
| Flash         | 8KB      | 16KB       | 16KB       | 32KB       |
| SRAM          | 512B     | 2KB        | 1KB        | 2KB        |
| EEPROM        | 64B      | 128B       | 512B       | 1024B      |
| GPIO count    | 28       | 18         | 23         | 23         |
|               |          |            |            |            |
| UART          | No       | Yes        | Yes        | Yes        |
| I2C           | Yes      | Yes        | Yes        | Yes        |
| SPI           | Yes      | Yes        | Yes        | Yes        |
| Timers        | 2        | 4          | 3          | 3          |
| PWM channels  | 2        | 4          | 6          | 6          |
| ADC pins      | 8        | 12         | 8          | 8          |

## Arduino Core

Spence Konde created and maintains [Arduino Core](https://github.com/SpenceKonde/megaTinyCore). This is a great place to start to get to know new chips better, and understand what is supported and what isn't. 

## How to flash

Spence Konde created another great [writeup](https://github.com/SpenceKonde/AVR-Guidance/blob/master/UPDI/jtag2updi.md) on the flasing routines for the new chips. Short summary below

- (a) Legacy way is to take any Arduino Nano board and use [jtag2updi](https://github.com/ElTangas/jtag2updi) project to make yourself a programmer.
- (b) Better (read recommended) way is to use SerialUPDI tooling with hardware modified serial programmer
- (c) Alternative is to use [Optiboot bootloader](https://github.com/Optiboot/optiboot) and Serial programmer interface like on Arduino boards

Method (c) is disqualified on 1-Series chip because of RESET/UPDI pin collision, and both (a) and (b) work equally well. Difference being what is easier for you: (a) dedicate Arduino Nano board for programming or (b) do solder job on your usb-serial adapter.

### Arduino IDE

 ...

### Platformio IDE
 
 ...

## Hardware

 ...

## Firmware

 ...

## Where to buy

In limited quantities possible to buy at [Tindie](https://www.tindie.com/products/sonocotta).

## Links

- [Arduino Core](https://github.com/SpenceKonde/megaTinyCore)
- [SerialUPDI guide](https://github.com/SpenceKonde/AVR-Guidance/blob/master/UPDI/jtag2updi.md)
- [Datasheet and manufacturer information](https://www.microchip.com/en-us/product/ATTINY1616#)
