## Power Notes

If I want to power this off a single 5V/3A USB port , this gives me 15W to work with.  Minus ~1W for the ESP32, this leaves 14W for the panels.  For 2 panels, this leaves ~7W each, giving me a max brightness of ~165/255. That brightness is suitable for sunlight conditions, but the ability to go brighter would be better.  Maybe use 2 ports and split up the power distribution for each panel?

**Actual power measurements:**
* ESP32 running basic-walk.gif: `1W`
* Bubble machine running @ 5V: `1.5-4W`
* 1x LED panel running basic-walk.gif:

Brightness | Power
-----------|------
10/255 | ~1.5W
25/255 | ~2W
50/255 | 3W
128/255 | 5.7W
165/255 | 6.8W
200/255 | 8.3W
255/255 | 10W
