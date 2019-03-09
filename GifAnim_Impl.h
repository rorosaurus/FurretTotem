#include "config.h"

#ifdef NEOMATRIX
// select which NEOMATRIX config will be selected
    #define M16BY16T4
    #include "neomatrix_config.h"
// else use SmartMatrix as defined in config.h
#else
    SMARTMATRIX_ALLOCATE_BUFFERS(matrix, kMatrixWidth, kMatrixHeight, kRefreshDepth, kDmaBufferRows, kPanelType, kMatrixOptions);
    SMARTMATRIX_ALLOCATE_BACKGROUND_LAYER(backgroundLayer, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kBackgroundLayerOptions);
#endif // NEOMATRIX


extern File file;
#include "GifDecoder.h"

// Used by simpleGifViewer to work without FilenameFunctions*
#ifdef BASICSPIFFS
bool fileSeekCallback(unsigned long position) { return file.seek(position); }
unsigned long filePositionCallback(void) { return file.position(); }
int fileReadCallback(void) { return file.read(); }
int fileReadBlockCallback(void * buffer, int numberOfBytes) { return file.read((uint8_t*)buffer, numberOfBytes); }
#else
#include "FilenameFunctions.h"
#endif

/* template parameters are maxGifWidth, maxGifHeight, lzwMaxBits
 * defined in config.h
 */
GifDecoder<kMatrixWidth, kMatrixHeight, lzwMaxBits> decoder;

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
#if DEBUGLINE
  if (y == DEBUGLINE) {
  Serial.print(x);
  Serial.print(",");
  Serial.print(y);
  Serial.print(">");
  Serial.print(red);
  Serial.print(",");
  Serial.print(green);
  Serial.print(",");
  Serial.print(blue);
  Serial.println("");
  }
#endif
}

// Setup method runs once, when the sketch starts
void sav_setup(const char *pathname) {
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
    matrix.setBrightness(defaultBrightness);

    // for large panels, may want to set the refresh rate lower to leave more CPU time to decoding GIFs (needed if GIFs are playing back slowly)
    //matrix.setRefreshRate(90);
    #if defined(ESP32)
	// for large panels on ESP32, may want to set the max percentage time dedicated to updating the refresh frames lower, to leave more CPU time to decoding GIFs (needed if GIFs are playing back slowly)
	//matrix.setMaxCalculationCpuPercentage(50);

	// alternatively, for large panels on ESP32, may want to set the calculation refresh rate divider lower to leave more CPU time to decoding GIFs (needed if GIFs are playing back slowly) - this has the same effect as matrix.setMaxCalculationCpuPercentage() but is set with a different parameter
	//matrix.setCalcRefreshRateDivider(4);
	#if defined(SPI_FFS)
	    matrix.begin();
	#else
	    // The ESP32 SD Card library is going to want to malloc about 28000 bytes of DMA-capable RAM
	    // make sure at least that much is left free
	    matrix.begin(28000);
	#endif
    #else // ESP32
	matrix.begin();
    #endif // ESP32
#endif // NEOMATRIX

    // If you want sdcard support send NULL and handle your own file management
    if (pathname) {
	SPIFFS.begin();
	file = SPIFFS.open(pathname, "r");
	if (!file) {
	    Serial.print("Error opening GIF file ");
	    Serial.println(pathname);
	    while (1) { delay(1000); }; // while 1 loop only triggers watchdog on ESP chips
	}
	decoder.startDecoding();
    }
}

void sav_loop() {
    static int frame = 0;
    Serial.print("Decoding Frame Start:");
    Serial.println(frame++);
    decoder.decodeFrame();
    Serial.println("Decoding Frame End");
}

// vim:sts=4:sw=4
