### Rave Furret is a totem for music festivals! He uses two 128x64px LED panels to loop animated gifs! Powered by an ESP32, controlled by my phone, and using a custom PCB!

## FAQ

* Yes, he's built using "Arduino"! No, it's not Neopixel LEDs!  Yes, he is adorable!
* Furret uses a [custom PCB I designed](https://github.com/rorosaurus/esp32-hub75-driver) to drive HUB75 panels with an ESP32!
* The LED panels were $25 each and the microcontroller was $5. It's powered by a USB battery pack!
* The original pixel art animation was done by the extremely talented [Alex Illustration](https://www.artstation.com/alexillustration)! My wife and I modified the basic animation in Photoshop to make all the other animations!

## Animations
[Click here to see all the animations!](animations)

## Social

* [@ravefurret](https://www.instagram.com/ravefurret/) on Instagram!  Share your pics and videos with us!
* [ravefurret.com](https://ravefurret.com) redirects to the Github page, with all the code and technical information!

## Videos

* [YouTube - Furret's debut at Above and Beyond: Group Therapy Weekender 2019](https://www.youtube.com/watch?v=Q7uGj0VHFyQ)
* [YouTube - Demo of v1.0 Animations](https://www.youtube.com/watch?v=LR-oUCg1d9I)

## Special Thanks
* [@alex_illustrat](https://twitter.com/alex_illustrat) - who [originally created the 8bit pixel art for Furret Walking](https://www.youtube.com/watch?v=ylnLUMmBNKc). See more of his work on [ArtStation](https://alexillustration.artstation.com/)!
* [narpy](https://www.youtube.com/channel/UCKYFHftFxQOJghmrEaK32sg) - for [starting the most adorable, wholesome, meme](https://www.youtube.com/watch?v=xa1Zn6XrDlM)
* Sprite_tm, Craig A. Lindley, Louis Beaudoin, and Marc Merlin - for the below libraries and helpful forum posts :)
* [bigclive](https://www.youtube.com/channel/UCtM5z2gkrGRuWd0JQMx76qA) for showing me the [perfect bubble blowing mechanism](https://www.youtube.com/watch?v=BvQtl3ciGcA)!

## Software
This repository isn't meant to be a good sample project, it's just my personal project. It was built on top of so many incredible libraries:
* [Arduino core for the ESP32](https://github.com/espressif/arduino-esp32)
* [SmartMatrix Library for ESP32](https://github.com/pixelmatix/SmartMatrix/tree/teensylc)
  * I did a [dirty hack](https://github.com/rorosaurus/SmartMatrix/commit/c46fe8d7be686caaaa3b7198bc4b7b24c6114df8) to free up some DMA memory to enable Wifi for this project.
* [Animated GIFs on ESP32](https://github.com/marcmerlin/AnimatedGIFs)
* [Arduino plugin for uploading files to ESP32 file system](https://github.com/me-no-dev/arduino-esp32fs-plugin)

We used Photoshop to create the animations!

## Hardware
* [PCB I designed](https://github.com/rorosaurus/esp32-hub75-driver) to drive HUB75 panels with an ESP32: [Buy on Tindie!](https://www.tindie.com/products/18357/)
  * This part is optional, but *greatly* simplifies your wiring!
* ESP32-DEVKIT-V1: [Amazon ($14 for 2)](https://smile.amazon.com/gp/product/B07Q576VWZ/)
  * You can use a different ESP32 if you don't use my PCB. Just remember to verify it has the required pins mentioned below!
* 128x64px, P2.5, 1/32, HUB75E purchased on [AliExpress](https://www.aliexpress.com/item/32972741517.html?spm=a2g0s.12269583.0.0.48e74198VArDtK)
* Bubble machine extracted from children's bubble wand toy, purchased on [eBay](https://www.ebay.com/itm/332880742452)

## Power
I butchered a USB cable to supply the 5V power from a large USB battery bank. At full brightness, one panel pulls about 2 amps @ 5 volts. Since the displays are so hungry, I recommend running the ESP32 from a separate 5V power source to avoid brownouts due to voltage sag.
