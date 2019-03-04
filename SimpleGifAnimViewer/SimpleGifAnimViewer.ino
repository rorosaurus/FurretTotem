#include "config.h"

// If the matrix is a different size than the GIFs, set the offset for the upper left corner
// (negative or positive is ok).
int OFFSETX = 0;
int OFFSETY = 0;

#ifdef NEOMATRIX
// select which NEOMATRIX config will be selected
    #define M16BY16T4
    #include "neomatrix_config.h"
// else use SmartMatrix as defined in config.h
#else
    SMARTMATRIX_ALLOCATE_BUFFERS(matrix, kMatrixWidth, kMatrixHeight, kRefreshDepth, kDmaBufferRows, kPanelType, kMatrixOptions);
    SMARTMATRIX_ALLOCATE_BACKGROUND_LAYER(backgroundLayer, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kBackgroundLayerOptions);
#endif // NEOMATRIX


#include "GifDecoder.h"
File file;
const char *pathname = "/gifs64/200_circlesmoke.gif";

/* template parameters are maxGifWidth, maxGifHeight, lzwMaxBits
 * 
 * The lzwMaxBits value of 12 supports all GIFs, but uses 16kB RAM
 * lzwMaxBits can be set to 10 or 11 for small displays, 12 for large displays
 * All 32x32-pixel GIFs tested work with 11, most work with 10
 */
GifDecoder<kMatrixWidth, kMatrixHeight, 12> decoder;

bool fileSeekCallback(unsigned long position) { return file.seek(position); }
unsigned long filePositionCallback(void) { return file.position(); }
int fileReadCallback(void) { return file.read(); }
int fileReadBlockCallback(void * buffer, int numberOfBytes) { return file.read((uint8_t*)buffer, numberOfBytes); }

void screenClearCallback(void) {
#ifdef NEOMATRIX
  matrix->clear();
#else
  backgroundLayer.fillScreen({0,0,0});
#endif
}

void updateScreenCallback(void) {
#ifdef NEOMATRIX
  matrix->show();
#else
  backgroundLayer.swapBuffers();
#endif
}

void drawPixelCallback(int16_t x, int16_t y, uint8_t red, uint8_t green, uint8_t blue) {
#ifdef NEOMATRIX
  CRGB color = CRGB(matrix->gamma[red], matrix->gamma[green], matrix->gamma[blue]);
  matrix->drawPixel(x+OFFSETX, y+OFFSETY, color);
#else
  backgroundLayer.drawPixel(x, y, {red, green, blue});
#endif
}

// Setup method runs once, when the sketch starts
void setup() {
    decoder.setScreenClearCallback(screenClearCallback);
    decoder.setUpdateScreenCallback(updateScreenCallback);
    decoder.setDrawPixelCallback(drawPixelCallback);

    decoder.setFileSeekCallback(fileSeekCallback);
    decoder.setFilePositionCallback(filePositionCallback);
    decoder.setFileReadCallback(fileReadCallback);
    decoder.setFileReadBlockCallback(fileReadBlockCallback);

#ifdef NEOMATRIX
    matrix_setup();
#else
    // neomatrix_config takes care of starting Serial, but we don't call it in the SMARTMATRIX code path
    Serial.begin(115200);
    Serial.println("Running on Native SmartMatrix Backend");
    // Initialize matrix
    matrix.addLayer(&backgroundLayer); 
    #if ENABLE_SCROLLING == 1
	matrix.addLayer(&scrollingLayer); 
    #endif
    matrix.setBrightness(defaultBrightness);

    #if defined(ESP32)
	#if defined(SPI_FFS)
	    matrix.begin();
	#else
	    matrix.begin(28000);
	#endif
    #else // ESP32
	matrix.begin();
    #endif // ESP32
#endif // NEOMATRIX

    SPIFFS.begin();
    file = SPIFFS.open(pathname, "r");
    if (!file) {
        Serial.print("Error opening GIF file ");
        Serial.println(pathname);
	while (1) { delay(1000); }; // while 1 loop only triggers watchdog on ESP chips
    }
    decoder.startDecoding();
}

void loop() {
    decoder.decodeFrame();
}

// vim:sts=4:sw=4
