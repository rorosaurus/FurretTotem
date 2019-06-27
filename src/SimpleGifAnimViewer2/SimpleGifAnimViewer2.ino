#define BASICSPIFFS
// Use NeoMatrix API, even if it may use the SmartMatrix backend depending on the CPU
#define NEOMATRIX
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
#ifdef ESP8266
    // 32x32 GIFs on 24x32 display, hence offset of -4
    OFFSETX = -4;
    char *pathname = "/gifs/concentric_circles.gif";
#endif
    sav_setup();
    if (sav_newgif(pathname)) delay(100000); // while 1 loop only triggers watchdog on ESP chips
}

void loop() {
    sav_loop();
}

// vim:sts=4:sw=4
