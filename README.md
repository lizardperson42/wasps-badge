# wasps-badge

The [WASPS](https://wasp.systems) electronic badge.


## Hardware

CAD files for the hardware are provided in KiCad format in `wasps-badge/`.


## Software

A PlatformIO project for a firmware adding basic blinkenlights can be found in
`code/`. Since field testing has indicated that the through-board LEDs are a
little too focused for the intended effect, they are not driven.

CTF functionality is not included, pull requests welcome.

If you have issues with compiling the firmware, a pre-compiled image is
provided at `code/firmware.bin`. It can be flashed using the tool `rvprog`
like this:

    rvprog -f code/firmware.bin
