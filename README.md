# wasps-badge

The [WASPS](https://wasp.systems) electronic badge.


## Hardware

CAD files for the hardware are provided in KiCad format in `wasps-badge/`.


### Connectors / Pinout

The badge features three 0.1in-pitch pin headers. Their silkscreen markings
are partially absent or obscured; Pin 1 can be recognized by its square pad.
Their locations are given as in the design files, where the mounting hole is
on top.

| Header | Location    | Notes                |
| ------ | ----------- | -------------------- |
| J1     | Bottom      | Flashing connector   |
| J2     | Bottom left | CTF breakout         |
| J3     | Top right   | Shitty Add-On Header |

Pinouts:

| Header | Pin    | MCU pin    | Description                          |
| ------ | ------ | ---------- | ------------------------------------ |
| J1     | 1      | GND        | GND                                  |
| J1     | 2      | VDD        | 3.3V                                 |
| J1     | 3      | SWIO / PD1 | SWIO (MCU flashing connection)       |
| J1     | 4      | NRST / PD7 | RST (MCU reset)                      |
| J2     | 1      | GND        | GND                                  |
| J2     | 2      | PD0        | "Press me" button (pulled up by MCU) |
| J2     | 3      | PD3        | "Now" LED                            |
| J2     | 4      | PD5        | "0" LED                              |
| J2     | 5      | PD6        | "1" LED                              |
| J3     | 1 (TL) | VDD        | 3.3V                                 |
| J3     | 2 (BL) | GND        | GND                                  |
| J3     | 3 (TC) | PC2        | I²C SCL line                         |
| J3     | 4 (BC) | PC1        | I²C SDA line                         |
| J3     | 5 (TR) | PC3        | GPIO                                 |
| J3     | 6 (BR) | PC4        | GPIO                                 |

There are two chains of WS2812B LEDs. The front LEDs are connected to pin PC6.
The reverse-mounted back LEDs (NRND) are connected to pin PC7.


## Software

A PlatformIO project for a firmware adding basic blinkenlights can be found in
`code/`. Since field testing has indicated that the through-board LEDs are a
little too focused for the intended effect, they are not driven.

The code runs the MCU in a busy loop, limiting battery life. Pull requests to
improve energy efficiency are welcome.

CTF functionality is not included, pull requests welcome.

If you have issues with compiling the firmware, a pre-compiled image is
provided at `code/firmware.bin`. It can be flashed using the tool `rvprog`
like this:

    rvprog -f code/firmware.bin
