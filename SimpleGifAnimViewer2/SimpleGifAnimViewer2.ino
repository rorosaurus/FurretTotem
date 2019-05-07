#define BASICSPIFFS
#include "GifAnim_Impl.h"

// If the matrix is a different size than the GIFs, allow panning through the GIF
// while displaying it, or bouncing it around if it's smaller than the display
int OFFSETX = 0;
int OFFSETY = 0;
int FACTX = 0;
int FACTY = 0;

const char *pathname = "/gifs64/200_circlesmoke.gif";

// Setup method runs once, when the sketch starts
void setup() {
    sav_setup();
    if (sav_newgif(pathname)) delay(100000); // while 1 loop only triggers watchdog on ESP chips
}

void loop() {
    sav_loop();
}

// vim:sts=4:sw=4
