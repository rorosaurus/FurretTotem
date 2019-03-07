#define BASICSPIFFS
#include "GifAnim_Impl.h"

// If the matrix is a different size than the GIFs, set the offset for the upper left corner
// (negative or positive is ok).
int OFFSETX = 0;
int OFFSETY = 0;

File file;
const char *pathname = "/gifs64/200_circlesmoke.gif";

// Setup method runs once, when the sketch starts
void setup() {
    sav_setup(pathname);
}

void loop() {
    sav_loop();
}

// vim:sts=4:sw=4
