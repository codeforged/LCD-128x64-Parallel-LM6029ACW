# STM32H743VIT6 + LM6029ACW (ST7565) Parallel LCD Demo

Demo project for STM32H743VIT6 (DevEBox) with LM6029ACW 128x64 monochrome graphical LCD (ST7565 controller, 8080 parallel interface), using custom driver + Adafruit GFX for graphics and font support.

## Features
- Fast parallel 8080 interface (13 data/control pins)
- Adafruit GFX integration: draw shapes, text, custom fonts
- Example: animation, FPS counter, moving text, and bitmap logo (Adafruit)
- Supports both full buffer update and page-based update (paging)
- Easily switch between update modes for benchmarking
- Example code for drawing bitmaps (logo)

## Hardware
- MCU: STM32H743VIT6 (DevEBox)
- LCD: LM6029ACW (ST7565, 128x64, parallel 8080)
- Backlight and VDD controlled via GPIO

### Pin Mapping Example
```
LM6029ACW lcd(
  PB0,  // CS
  PB1,  // RES
  PB2,  // RS
  PB10, // WR
  PB11, // RD
  PA7,  // DB7
  PA6,  // DB6
  PA5,  // DB5
  PA4,  // DB4
  PA3,  // DB3
  PA2,  // DB2
  PA1,  // DB1
  PA0   // DB0
);
```

## How to Use
1. Clone this repo
2. Open with PlatformIO (VSCode)
3. Build & upload to STM32H743VIT6 board
4. LCD will show animation, FPS, moving text, and Adafruit logo
5. Edit `USE_PAGING` in `main.cpp` to compare full update vs paging

## Dependencies
- [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library)
- Custom LM6029ACW driver (included)
- PlatformIO, STM32 platform

## Screenshots
![Demo Screenshot](screenshot.png)

## Credits
- Adafruit GFX for graphics engine
- STM32 community for hardware support

---

Author: K1ngUn1c0rn, https://github.com/codeforged
Feel free to fork, modify, and use for your own STM32+LCD projects!
