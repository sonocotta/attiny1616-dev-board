# ATtiny 1616 Development Board

![Open Source Hardware](/doc/images/open-source-hardware-logo.png)
![Open Source Software](/doc/images/open-source-software-logo.png)

ATtiny 1616 Development Board is a small and handy development board built around new generation of ATiny series. It is pin and size compatible with Arduino Nano board and can be used as it's direct replacement (with certain limitations). It can be programmed using both Arduino IDE and Platformio IDE, as well as vanilla console tools.

![image](https://user-images.githubusercontent.com/5459747/206928962-67fdb6a5-8794-4674-a813-c9d632d3219f.png)

## Motivation

I'm a big fan of early ATtiny series chips, I even made my own [ATtiny Flasher](https://sonocotta.com/attiny-flasher/) tool for productive development and few educational kits based on ubiquitous ATtiny85. Time has come to extend my horizons and look into modern line of ATtiny chips, specifically so called 1-series and 2-series line of MCUs. 

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

![image](https://user-images.githubusercontent.com/5459747/206929018-e960566d-2edd-4ede-aa5d-861d47c59a57.png)

### Arduino IDE

Use Arduino 1.8.x, Core doesn't work with 2.X versions of Arduino at the moment of writing.

Add [http://drazzy.com/package_drazzy.com_index.json](http://drazzy.com/package_drazzy.com_index.json) to board manager

![image](https://user-images.githubusercontent.com/5459747/206929150-8aabfb95-e73e-4a6f-94f1-1c10b98fd951.png)

After that you should install megaTinyCore from Board Manager

![image](https://user-images.githubusercontent.com/5459747/206929195-dfa65615-acd0-49ba-a572-25e89ce978aa.png)

Select ATtiny1616 as target and other necessary settings in the board settings after

![image](https://user-images.githubusercontent.com/5459747/206929344-34b50378-c1a1-4dbe-bcd1-e812720bf86d.png)

### Platformio IDE
 
After installing [Plarformio IDE](https://platformio.org/platformio-ide), open [sample project](/firmware/t1616-starter). Run `Build` command to install necessary tools and libraries. 

Next run `Upload: tiny1616-jtag2updi` task if you're using jtag2updi programmer, or `Upload: tiny1616-serialupdi` task if using modified Serial adapter method. In both cases you can use `Upload and Monitor` task.

## Hardware

![image](https://user-images.githubusercontent.com/5459747/206929920-294f9ec9-dbf8-4ae4-8b39-6af7685821ab.png)


- ![image](https://user-images.githubusercontent.com/5459747/206929567-5a68f822-1172-459c-bb34-64ab1ee2019c.png) ATTINY1616 MCU 
- ![image](https://user-images.githubusercontent.com/5459747/206929597-8f1b7a41-9ef4-4301-9d88-fdd6952fe900.png) CH340E USB-Serial Adapter connected to Hardware Serial
- ![image](https://user-images.githubusercontent.com/5459747/206929650-72bfa8ba-716a-4830-ae14-a2c6ddff8830.png) WS2812B RGB LED
- ![image](https://user-images.githubusercontent.com/5459747/206929704-bb9a66ee-7e48-4c81-87f7-1f0c60d1a02f.png) UPDI Programming and Debug header
- ![image](https://user-images.githubusercontent.com/5459747/206929744-5f7abffb-341e-49c9-8988-01835a2045a8.png) Hardware Push button
- ![image](https://user-images.githubusercontent.com/5459747/206929801-e55e502e-bdce-4d85-a376-3268b96dc5e2.png) VIN disconnect - cut this line to disconnect LDO chip and power-on LED, recommended for low-power applications
- ![image](https://user-images.githubusercontent.com/5459747/206929866-0ef4aaad-d004-42b9-9b17-7bfbe8238634.png) RES disconnect - short this line to enable auto-RESET functionality with Optiboot bootloader (read below)

### Auto reset with Optiboot

As [explained](https://github.com/SpenceKonde/megaTinyCore) in many details by Spence, 1-Series chips cannot provide Arduino-like one-click-upload with Optiboot behavior without some sacrifice. Reason for that is pin collision: UPDI and RESET are the same pin, so you need to decide which you'd prefer. If you use auto-reset, you lose UPDI, specifically possibility to change fuses easily (this is important in my opinion). If you use UPDI you need 2 connections to your MCU - one via programming interface, another one for Serial communication. 

Personally I prefer to keep UPDI and use direct programming without custom bootloader, having extra wire is minor inconvenience for me, but losing fuses permanently is not an option.

## Where to buy

In limited quantities possible to buy at [Tindie](https://www.tindie.com/products/sonocotta).

## Links

- [Arduino Core](https://github.com/SpenceKonde/megaTinyCore)
- [SerialUPDI guide](https://github.com/SpenceKonde/AVR-Guidance/blob/master/UPDI/jtag2updi.md)
- [Datasheet and manufacturer information](https://www.microchip.com/en-us/product/ATTINY1616#)
