AnimatedGIFs for SmartMatrix/SDcard or NeoMatrix (Neopixel/WS2812B) from SDcard or SPIFFS, on Teensy 3.x, ESP8266, or ESP32
===========================================================================================================================


Configuration
-------------
Please see config.h to select whether you're using SDcard or SPIFFS, and
NeoMatrix instead of SmartMatrix.  
For NeoMatrix you must also edit neomatrix_config.h to configure your matrix
layout, addjust OFFSETX/OFFSETY if needed, as well as matrix_brightness and
matrix_gamma.

AnimatedGIFs file browser
-------------------------
You either put your gifs inside a /gifs subdirectory on an sdcard or under /gifs in SPIFFS 

You can send the following commands over serial port (115200):
- n / p : go to next/previous gif
- \+ / \- : adjust gamma correction for NeoMatrix backend
- 1 to xx: jump to gif number xx (need newline after number)
= : display current GIF in loop for 1h instead of 10 seconds

config.h also has these compile time variables:
- #define FIRSTINDEX 0 : change which GIF is shown first
- #define DEBUGLINE 6: if defined will only decode first frame, stop, and dump to serial port the color values of the given line


NeoMatrix and SPIFFS support
----------------------------
I, Marc MERLIN <marc_soft@merlins.org>, took the excellent work
from Louis Beaudoin's GIF decoder for SmartMatrix and ported it to
https://github.com/marcmerlin/FastLED_NeoMatrix .

In the process, I also allowed it to work on SPIFFS (built in filesystem using
flash available on ESP8266 and ESP32) so that you can store your GIFS directly
on the flash and not need an sdcard at all.
Unfortunately the SPIFFS support on ESP32 and ESP8266 is not quite identical, so
the code needs to account for both APIs (ESP8266 is the odd one out, the ESP32
SPIFFS API is actually compatible with the sdcard API).

The data subdirectory allows the arduino API to automatically create a flash
filesystem and upload it to your chip, see:
- ESP8266: http://esp8266.github.io/Arduino/versions/2.3.0/doc/filesystem.html#uploading-files-to-file-system
- ESP32: https://github.com/me-no-dev/arduino-esp32fs-plugin

The gifs/ subdirectory contains animated gifs that don't long as good on
Neomatrix due to the lesser dynamic range of neopixels. Please look at
neomatrix_config.h and adjust these if needed:
- uint8_t matrix_brightness = 32;
- float matrix_gamma = 3.0;

That being said, some GIFs just don't look so good on Neomatrix while they will
look ok on SmartMatrix. Those in the gifs/ subdirectory and do not get uploaded
to ESP chips by default (although you could upload them if you actually connect
those chips to a SmartMatrix instead of a NeoMatrix).

You can get more animated GIFS here:
- https://imgur.com/a/NuFRD 
- https://imgur.com/a/HjMW0


Original SmartMatrix support from https://github.com/pixelmatix/AnimatedGIFs
----------------------------------------------------------------------------
This [SmartMatrix Library](http://docs.pixelmatix.com/SmartMatrix/index.html) example displays 32x32 GIF animations loaded from a SD Card connected to the Teensy 3.1 using the [SmartMatrix Shield](http://docs.pixelmatix.com/SmartMatrix/shieldref.html)

The GIFs can be up to 32 pixels in width and height.  This code has been tested with 32x32 pixel and 16x16 pixel GIFs, but is optimized for 32x32 pixel GIFs.

Wiring is on the default Teensy 3.1 SPI pins, and chip select can be on any GPIO (customize by defining SD_CS in the code)

Function     | Pin
-------------|----
DOUT         |  11
DIN          |  12
CLK          |  13
CS (default) |  15

This code first looks for .gif files in the /gifs/ directory (you can customize this with the GIF_DIRECTORY definition) then plays random GIFs in the directory, looping each GIF for DISPLAY_TIME_SECONDS

This example is meant to give you an idea of how to add GIF playback to your own sketch.  For a project that adds GIF playback with other features, take a look at [Light Appliance](https://github.com/CraigLindley/LightAppliance) and [Aurora](https://github.com/pixelmatix/aurora)

If you find any GIFs that won't play properly, please attach them to a new
Issue post in the GitHub repo [here](https://github.com/pixelmatix/AnimatedGIFs/issues)
