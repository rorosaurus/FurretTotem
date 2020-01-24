# Limitations
* SPIFFS filenames can't be too long, or files will not upload. (Move to FatFS!)
* Seems the file order gets mixed up if we have more than ~35 gifs. Works using 649KB but doesn't at 672KB used..
  * Re-partitioning with larger SPIFFS seems to resolve this issue, strangely.
* Little color variety: due to memory constraints on ESP32 with 128x64px, use < 32 colors
* Short looped animations: due to memory constraints on ESP32 with 128x64px, use < 20 frames total (or is it < 20kB filesize?)
* Seems after I hit 84 files on SPIFFS, the files stop appearing in the right order.  SPIFFS bug? Memory issue?

# Future design philosophy
* Allow every animation to have 3 phases: 1 and 3 are optional and play once.  2 loops as long as needed.
  1. intro
  2. loop
  3. outro
* transparent backgrounds (alpha layer) are allowed so we can change/generate the backgrounds
* Pause mode, next frame advance
* Queue up animation changes? Auto detect drops?
* Mode to help people find their friends
* ability to add captions (enter text from web interface)

# Future Animation ideas
* Furret eats a berry and then his eyes change (ditto or dilated pupils?) and he grows a smile
* additional crops for furret walking video
* add a microphone and do beat analysis.  adjust frame delay until furret walking lines up with the beat.
  * neural nets to predict next drop (maybe fade out and back in)
  * And genres and beats to match animations automatically
* [HeartGold and SoulSilver](https://bulbapedia.bulbagarden.net/wiki/Walking_Pok%C3%A9mon#Pok.C3.A9mon_HeartGold_and_SoulSilver) have pixel animations for walking every pokemon...
* Furret cat bus!
* running into wobbefet and bouncing back off
* falling asleep / waking up
* glitching out with the HD version of Furret
* consent info
* hydrate info
* Celeste
* Catbug, Bugcat, Puppycat, Pusheen?
* Aperature Science Portals, Rick and Morty portals, Mario pipes

# Future background ideas
* Several solid color rainbow/palette vertical stripes scrolling across the screen.  Their widths oscillate with time.
* White stars scrolling past the screen like a galaxy moving. Random velocities are assigned to each star which adjusts the intensity of the rainbow color of the trail (which can also rotate with time?)
* match background color of stage with ESP32-CAM?

# Future effects ideas
* Rotate every pixel's hue by some variable?
* Mirror the gif on a number of axes, or flip entirely (any animation can now be upside down)
  * init some variables based on those parameters for flipping
  * use those variables for the for loops that map out the pixels
  * also change the iterator's increment to skip some lines/columns and then use mod operator to make sure we don't walk off arrays
* TRANSITIONS! fade to black?
* Change playback speed, reverse, pause, strobe
* disable reset of pixels on each frame (carry over unchanged pixels to next frame!)
* random glitches (offset entire row/column, etc.)
