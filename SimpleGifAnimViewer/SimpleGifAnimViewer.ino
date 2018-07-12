#include "neomatrix_config.h"
#include "GifDecoder.h"

#ifdef ESP8266
#include <FS.h>
#else
#include <SPIFFS.h>
#endif
File file;

char *pathname = "/gifs/concentric_circles.gif";

const uint8_t kMatrixWidth = 32;        // known working: 32, 64, 96, 128
const uint8_t kMatrixHeight = 32;       // known working: 16, 32, 48, 64`
/* template parameters are maxGifWidth, maxGifHeight, lzwMaxBits
 * 
 * The lzwMaxBits value of 12 supports all GIFs, but uses 16kB RAM
 * lzwMaxBits can be set to 10 or 11 for small displays, 12 for large displays
 * All 32x32-pixel GIFs tested work with 11, most work with 10
 */
GifDecoder<kMatrixWidth, kMatrixHeight, 12> decoder;

void screenClearCallback(void) {
  matrix_clear();
}

void updateScreenCallback(void) {
  matrix_show();
}

void drawPixelCallback(int16_t x, int16_t y, uint8_t red, uint8_t green, uint8_t blue) {
  CRGB color = CRGB(matrix->gamma[red], matrix->gamma[green], matrix->gamma[blue]);
  // This works but does not handle out of bounds pixels well (it writes to the last pixel)
  // matrixleds[XY(x+OFFSETX,y+OFFSETY)] = color;
  matrix->setPassThruColor(color.red*65536 + color.green*256 + color.blue);
  // drawPixel ensures we don't write out of bounds
  matrix->drawPixel(x+OFFSETX, y+OFFSETY, 0);
}

bool fileSeekCallback(unsigned long position) {
    return file.seek(position);
}

unsigned long filePositionCallback(void) {
    return file.position();
}

int fileReadCallback(void) {
    return file.read();
}

int fileReadBlockCallback(void * buffer, int numberOfBytes) {
    return file.read((uint8_t*)buffer, numberOfBytes);
}

// Setup method runs once, when the sketch starts
void setup() {
    // Wait for teensy to be ready
    delay(3000);
    decoder.setScreenClearCallback(screenClearCallback);
    decoder.setUpdateScreenCallback(updateScreenCallback);
    decoder.setDrawPixelCallback(drawPixelCallback);

    decoder.setFileSeekCallback(fileSeekCallback);
    decoder.setFilePositionCallback(filePositionCallback);
    decoder.setFileReadCallback(fileReadCallback);
    decoder.setFileReadBlockCallback(fileReadBlockCallback);

    Serial.begin(115200);
    Serial.println("Starting AnimatedGIFs Sketch");


    matrix_setup();

    SPIFFS.begin();
    file = SPIFFS.open(pathname, "r");
    if (!file) {
        Serial.print("Error opening GIF file ");
        Serial.println(pathname);
	delay(1000000);
    }
    decoder.startDecoding();
}

void loop() {
    decoder.decodeFrame();
}

// vim:sts=4:sw=4
