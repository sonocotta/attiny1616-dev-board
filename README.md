# ATtiny 1616 Development Board

![Open Source Hardware](/doc/images/open-source-hardware-logo.png)
![Open Source Software](/doc/images/open-source-software-logo.png)

ATtiny 1616 Development Board is a small and handy development board built around the new generation of the ATiny series. It is pin and size compatible with Arduino Nano board and can be used as its direct replacement (with certain limitations). It can be programmed using both Arduino IDE and Platformio IDE, as well as vanilla console tools.

![image](https://user-images.githubusercontent.com/5459747/206928962-67fdb6a5-8794-4674-a813-c9d632d3219f.png)

## Motivation

I'm a big fan of early ATtiny series chips, I even made my own [ATtiny Flasher](https://sonocotta.com/attiny-flasher/) tool for productive development and a few educational kits based on ubiquitous ATtiny85. The time has come to extend my horizons and look into the modern line of ATtiny chips, specifically so called 1-series and 2-series line of MCUs. 

No need to mention that they went far ahead old series, and have resources comparable with the old ATmega series. This gave me the idea to make an Arduino Nano pin-compatible development board, so I can start using it the projects, where I'd normally pick Arduino Nano. In my practice, the best way to get familiar with new hardware is to start using it in the actual projects.

## Features

- [ATTINY1616](https://www.microchip.com/en-us/product/ATTINY1616) 8-bit MCU in a 20-pin package
- Up to 20 MHz guaranteed by the manufacturer, up to 32 MHz reported by community in normal conditions 
- 16 KB Flash
- 2 KB SRAM
- 128B of EEPROM 
- UPDI interface for flashing and debugging
- Onboard 5V LDO (disconnected for low-power applications)
- Flash using Arduino IDE, Platformio, or the IDE of your choice
- Onboard USB-Serial bridge (CH340E) connected to hardware Serial port
- One RGB LED (WS2812B)
- One Push button

## ATtiny1616

ATiny1616 is a mid-range chip in new [ATtiny 1-Series line](https://en.wikipedia.org/wiki/ATtiny_microcontroller_comparison_chart). Generally, they offer considerably more than older Tiny-series chips, and are comparable with classic ATmega AVRs, offering at the same time new MCU features, not available in older series.

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

## Board Pinout

![image](https://user-images.githubusercontent.com/5459747/212763915-7140cad8-92b5-4af6-a9e5-c40de1467dbf.png)

Note: Revision A and B have backside pin labels rotated, big 🤦 for me. It will be fixed in the next revisions.

## MCU Pinout

![image](https://user-images.githubusercontent.com/5459747/212764127-5830f7e1-c171-413c-a362-3492247895f4.png)

## Arduino Core

Spence Konde created and maintained [Arduino Core](https://github.com/SpenceKonde/megaTinyCore). This is a great place to start to get to know new chips better and understand what is supported and what isn't. 

## How to flash

Spence Konde created another great [writeup](https://github.com/SpenceKonde/AVR-Guidance/blob/master/UPDI/jtag2updi.md) on the flashing routines for the new chips. Short summary below

- (a) Legacy way is to take any Arduino Nano board and use [jtag2updi](https://github.com/ElTangas/jtag2updi) project to make yourself a programmer.
- (b) A better (read recommended) way is to use SerialUPDI tooling with hardware-modified serial programmer
- (c) Alternative is to use [Optiboot bootloader](https://github.com/Optiboot/optiboot) and Serial programmer interface like on Arduino boards

Method (c) is disqualified on 1-Series chip because of RESET/UPDI pin collision, and both (a) and (b) work equally well. The difference is what is easier for you: (a) dedicate Arduino Nano board for programming or (b) do a solder job on your USB-serial adapter.

### Revision A (Discontinued)

| Method | Connection |
|----------|------------|
|  jtag2updi         | ![image](https://user-images.githubusercontent.com/5459747/213477557-20c45e7f-9749-4db9-b5e8-835daf2b69b4.png)
| SerialUPDI<br/>(recommended) | ![image](https://user-images.githubusercontent.com/5459747/213477231-9fa7431a-e2d6-4d7b-93d9-fbb924b21496.png)

### Revision B (Current latest)

Starting from revision B diode between TX and RX pins is included on the board, so you can use an unmodified USB-Serial adapter.

| Method | Connection |
|----------|------------|
|  jtag2updi         | ![image](https://user-images.githubusercontent.com/5459747/213477813-b20dfe72-d417-455c-b683-b1e41a4e2247.png)
| SerialUPDI<br/>(recommended) | ![image](https://user-images.githubusercontent.com/5459747/213477716-04c15d4e-4179-488a-910e-8a37a4a4ce2f.png)

### Revision C (co-exists with rev B)

While working on one of the projects, it came to me, hey, there is already a USB-Serial adapter on the board, serving Serial communication. Why not use it for flashing? So revision C came, **no external programmer needed**, plug-n-play. The drawback is that you lose Serial communication via built-in USB.

### Arduino IDE

Use Arduino 1.8.x, Core doesn't work with 2.X versions of Arduino at the moment of writing.

Add [http://drazzy.com/package_drazzy.com_index.json](http://drazzy.com/package_drazzy.com_index.json) to board manager

![image](https://user-images.githubusercontent.com/5459747/206929150-8aabfb95-e73e-4a6f-94f1-1c10b98fd951.png)

After that, you should install megaTinyCore from Board Manager

![image](https://user-images.githubusercontent.com/5459747/206929195-dfa65615-acd0-49ba-a572-25e89ce978aa.png)

Select ATtiny1616 as the target and other necessary settings in the board settings after

![image](https://user-images.githubusercontent.com/5459747/206929344-34b50378-c1a1-4dbe-bcd1-e812720bf86d.png)

### Platformio IDE
 
After installing [Plarformio IDE](https://platformio.org/platformio-ide), open [sample project](/firmware/t1616-starter). Run the `Build` command to install the necessary tools and libraries. 

Next, run the `Upload: tiny1616-jtag2updi` task if you're using the jtag2updi programmer, or the `Upload: tiny1616-serialupdi` task if using the modified Serial adapter method. In both cases, you can use the `Upload and Monitor` task.

### [Digital Safe firmware](https://github.com/sonocotta/attiny1616-dev-board/tree/main/firmware/t1616-password-entry)

[Weekend project](https://hackaday.io/project/186193-attiny1616-development-board/log/216421-digital-safe-project-based-on-attiny1616) I did for my 6-year-old son. Based on [Electronic Safe with Arduino](https://projecthub.arduino.cc/chummer1010/62207bc9-3ce8-459e-a1bf-6789ae89eaa0) project, mostly rewritten in order to add support for async execution.

![image](https://user-images.githubusercontent.com/5459747/222250919-6f6eff50-0577-4bc1-98f7-d4f109cd9de8.png)

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

As [explained](https://github.com/SpenceKonde/megaTinyCore) in many details by Spence, 1-Series chips cannot provide Arduino-like one-click-upload with Optiboot behavior without some sacrifice. The reason for that is pin collision: UPDI and RESET are the same pins, so you need to decide which you'd prefer. If you use auto-reset, you lose UPDI, specifically the possibility to change fuses easily (this is important in my opinion). If you use UPDI you need 2 connections to your MCU - one via the programming interface, and another one for Serial communication. 

Personally, I prefer to keep UPDI and use direct programming without a custom bootloader, having extra wire is a minor inconvenience for me, but losing fuses permanently is not an option.

## Where to buy

In limited quantities possible to buy at [Tindie](https://www.tindie.com/products/sonocotta/attiny1616-development-board/) and [Elecrow](https://www.elecrow.com/attiny1616-development-board.html)

## Links

- [Arduino Core](https://github.com/SpenceKonde/megaTinyCore)
- [SerialUPDI guide](https://github.com/SpenceKonde/AVR-Guidance/blob/master/UPDI/jtag2updi.md)
- [Datasheet and manufacturer information](https://www.microchip.com/en-us/product/ATTINY1616#)
