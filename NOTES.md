## Power Notes

Powering both panels off one 5V/3A USB port, I can reach about 150/255 before nearing 3A. Some animations with more white pixels would breach 3A and significantly reduce voltage (below 4V).

It's best to power the ESP32 (~1.5W constant) separately, so that voltage sag from the panels does not cause brownouts.

For sunlight conditions, the ability to go brighter would be better.  Maybe use 2 ports and split up the power distribution for each panel?

**Actual power measurements:**
* ESP32 running basic-walk.gif: `1W`
* ESP32 with Wifi ON running basic-walk.gif: `1.5W`
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
