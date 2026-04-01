# SuperSimpleClock

A big-font digital clock on a 1602 LCD using an ATMEGA8 microcontroller — no I2C, no RTC module, no bootloader.

![Clock Preview](images/clock.jpg)

---

## Features

- Large custom font digits filling the entire LCD
- Blinking colon separator
- Two push buttons to set hours and minutes
- Runs on ATMEGA8 with external 8MHz crystal
- No I2C module, no RTC — minimal components

---

## Components

| Component | Quantity |
|-----------|----------|
| ATMEGA8 | 1 |
| LCD 1602 | 1 |
| Crystal 8MHz | 1 |
| Push button | 2 |
| Potentiometer 10K (contrast) | 1 |

> No capacitors were used on the crystal and the clock runs accurately.
> For a final PCB product, adding 2x 22pF capacitors is recommended.

---

## Pin Connections

### LCD 1602 → ATMEGA8

| LCD Pin | Name | ATMEGA8 Pin |
|---------|------|-------------|
| 1 | VSS | GND |
| 2 | VDD | 5V |
| 3 | V0 | Potentiometer wiper |
| 4 | RS | D8 |
| 5 | RW | GND |
| 6 | EN | D9 |
| 7-10 | D0-D3 | Not connected |
| 11 | D4 | D4 |
| 12 | D5 | D5 |
| 13 | D6 | D6 |
| 14 | D7 | D7 |
| 15 | A (LED+) | 5V |
| 16 | K (LED-) | GND |

### Contrast Potentiometer (10K)

| Pot Pin | Connect to |
|---------|-----------|
| Left | GND |
| Middle (wiper) | LCD pin 3 (V0) |
| Right | 5V |

### Buttons

| Button | ATMEGA8 Pin | Other pin |
|--------|-------------|-----------|
| Hours (+1) | D2 | GND |
| Minutes (+1) | D3 | GND |

> Buttons use internal pull-up resistors — no external resistors needed.

---

## Upload

Compiled and uploaded using **MiniCore** with the following settings:

| Setting | Value |
|---------|-------|
| Clock | Internal 8 MHz |
| Bootloader | No bootloader |
| BOD | 2.7V |
| EEPROM | Retained |
| Compiler LTO | Enabled |

Programmer: **USBASP**

---

## How to Set the Time

- Press **Hours button** → hours +1
- Press **Minutes button** → minutes +1
- Hold either button → fast advance (every 200ms)

---

## Power Consumption

| Component | Current |
|-----------|---------|
| ATMEGA8 @ 8MHz | ~6mA |
| LCD backlight | ~25mA |
| **Total** | **~40mA** |

On a 1000mAh battery: ~20 hours.

---

## Libraries

- [LiquidCrystal](https://github.com/arduino-libraries/LiquidCrystal) (built-in Arduino library)

No external libraries required. The big font is implemented directly using custom characters.
