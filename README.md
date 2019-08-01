128x64 LED Panel, playing Animated GIFs, powered by an ESP32
==================================

![Furret Walking](demo.gif)

[YouTube - Furret's debut at Above and Beyond: Group Therapy Weekender 2019](https://www.youtube.com/watch?v=Q7uGj0VHFyQ)

[YouTube - Demo of v1.0 Animations](https://www.youtube.com/watch?v=LR-oUCg1d9I)

## Special Thanks
* [@alex_illustrat](https://twitter.com/alex_illustrat) - who [originally created the 8bit pixel art for Furret Walking](https://www.youtube.com/watch?v=ylnLUMmBNKc). See more of his work on [ArtStation](https://alexillustration.artstation.com/)!
* [narpy](https://www.youtube.com/channel/UCKYFHftFxQOJghmrEaK32sg) - for [starting the most adorable, wholesome, meme](https://www.youtube.com/watch?v=xa1Zn6XrDlM)
* Sprite_tm, Craig A. Lindley, Louis Beaudoin, and Marc MERLIN - for the below libraries and helpful forum posts :)

## Software
This project was built on top of so many incredible libraries:
* https://github.com/espressif/arduino-esp32
* https://github.com/pixelmatix/SmartMatrix/tree/teensylc
* https://github.com/marcmerlin/AnimatedGIFs
* https://github.com/me-no-dev/arduino-esp32fs-plugin

## Hardware
* 128x64px, P2.5, 1/32, HUB75E purchased on [AliExpress](https://www.aliexpress.com/item/32972741517.html?spm=a2g0s.12269583.0.0.48e74198VArDtK)
* ESP32 from [Amazon](https://smile.amazon.com/gp/product/B0718T232Z/), any variant should work as long as you have all the required pins listed below

## Pins
Using `ESP32_FORUM_PINOUT` from [MatrixHardware_ESP32_V0.h](https://github.com/pixelmatix/SmartMatrix/blob/teensylc/src/MatrixHardware_ESP32_V0.h)

````
R1_PIN  2
G1_PIN  15
B1_PIN  4

R2_PIN  16
G2_PIN  27
B2_PIN  17

A_PIN   5
B_PIN   18
C_PIN   19
D_PIN   21
E_PIN   12

LAT_PIN 26
OE_PIN  25
CLK_PIN 22
````

## Power
Originally I was planning to power this off some 18650's, but I butchered a USB cable to supply the 5V power to the panel for testing, and I'm really enjoying how simple it is.  At full brightness, the panel pulls about 2 amps @ 5 volts.

If I want to power this off a single 5V/3A USB port , this gives me 15W to work with.  Minus ~1W for the ESP32, this leaves 14W for the panels.  For 2 panels, this leaves ~7W each, giving me a max brightness of ~165/255. That brightness is suitable for sunlight conditions, but the ability to go brighter would be better.  Maybe use 2 ports and split up the power distribution for each panel?

### Actual power measurements:

#### ESP32 running basic-walk.gif
`0.9W`

#### 1x LED panel running basic-walk.gif

Brightness | Power
-----------|------
10/255 | ~1.5W
25/255 | ~2W
50/255 | 3W
128/255 | 5.7W
165/255 | 6.8W
200/255 | 8.3W
255/255 | 10W
