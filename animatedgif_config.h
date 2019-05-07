#ifndef animatedgif_config
#define animatedgif_config

// control if we decode in 32x32 or 64x64, or something else
#ifdef ESP8266
#define matrix_size 32
#else
#define matrix_size 64
#endif

/* GifDecoder needs lzwMaxBits
 * The lzwMaxBits value of 12 supports all GIFs, but uses 16kB RAM
 * lzwMaxBits can be set to 10 or 11 for small displays, 12 for large displays
 * All 32x32-pixel GIFs tested work with 11, most work with 10
 */
const int lzwMaxBits = 12;

//#define NEOMATRIX // Switch to NEOMATRIX backend from native SMARTMATRIX backend
//#define NEOPIXEL_MATRIX  // If NEOMATRIX, use FastLED::NeoMatrix, not SmartMatrix_GFX

// if you want to display a file and display that one first
#define FIRSTINDEX 0
//#define DEBUGLINE 6

// Use Neomatrix backend (which in turn could be using SmartMatrix)
#ifdef NEOMATRIX
    // This doesn't work due to variables being redefined. Sigh...
    // instead it's included once from AnimatedGIFs.ino
    //#include "neomatrix_config.h"
#else // NEOMATRIX
    #pragma message "Compiling for Native SmartMatrix"
    // CHANGEME, see MatrixHardware_ESP32_V0.h in SmartMatrix/src
    #define GPIOPINOUT 3
    #define ENABLE_SCROLLING  1
    #if defined (ARDUINO)
        //#include <SmartLEDShieldV4.h>  // uncomment this line for SmartLED Shield V4 (needs to be before #include <SmartMatrix3.h>)
        #include <SmartMatrix3.h>
    #elif defined (SPARK)
        #include "application.h"
        #include "SmartMatrix3_Photon_Apa102/SmartMatrix3_Photon_Apa102.h"
    #endif

    // Neomatrix brightness is different (full brightness can use up 40A) and defined
    // to a different value in neomatrix_config.h
    // range 0-255
    const int defaultBrightness = 255;
    const uint8_t kMatrixWidth = matrix_size;        // known working: 32, 64, 96, 128
    const uint8_t kMatrixHeight = matrix_size;       // known working: 16, 32, 48, 64
    /* SmartMatrix configuration and memory allocation */
    #define COLOR_DEPTH 24                  // known working: 24, 48 - If the sketch uses type `rgb24` directly, COLOR_DEPTH must be 24
    const uint8_t kRefreshDepth = 24;       // known working: 24, 36, 48
    const uint8_t kDmaBufferRows = 2;       // known working: 2-4
    const uint8_t kPanelType = SMARTMATRIX_HUB75_32ROW_MOD16SCAN; // use SMARTMATRIX_HUB75_16ROW_MOD8SCAN for common 16x32 panels
    //const uint8_t kPanelType = SMARTMATRIX_HUB75_64ROW_MOD32SCAN;
    const uint8_t kMatrixOptions = (SMARTMATRIX_OPTIONS_NONE);    // see http://docs.pixelmatix.com/SmartMatrix for options
    const uint8_t kBackgroundLayerOptions = (SM_BACKGROUND_OPTIONS_NONE);
    const uint8_t kScrollingLayerOptions = (SM_SCROLLING_OPTIONS_NONE);
#endif

// If the matrix is a different size than the GIFs, set the offset for the upper left corner
// (negative or positive is ok).
extern int OFFSETX;
extern int OFFSETY;
extern int FACTX;
extern int FACTY;

// Note, you can use an sdcard on ESP32 or ESP8266 if you really want,
// but if your data fits in built in flash, why not use it?
// Use built in flash via SPIFFS/FATFS
// esp8266com/esp8266/libraries/SD/src/File.cpp
// ESP8266: http://esp8266.github.io/Arduino/versions/2.3.0/doc/filesystem.html#uploading-files-to-file-system
// ESP32: https://github.com/me-no-dev/arduino-esp32fs-plugin
// https://github.com/marcmerlin/esp32_fatfsimage/blob/master/README.md
#if defined(ESP8266)
    #include <FS.h>
    #define FSO SPIFFS
    #if matrix_size == 64
        #define GIF_DIRECTORY "/gifs64/"
    #else
        #define GIF_DIRECTORY "/gifs/"
    #endif
    extern "C" {
        #include "user_interface.h"
    }
#elif defined(ESP32)
    //#include <SPIFFS.h>
    //#define FSO SPIFFS
    #include "FFat.h"
    #define FSO FFat
    #define FSOFAT
    // Do NOT add a trailing slash, or things will fail
    #if matrix_size == 64
        #define GIF_DIRECTORY "/gifs64"
    #else
        #define GIF_DIRECTORY "/gifs"
    #endif
#else
    #define FSO SD
    #define FSOSD
    #if defined (ARDUINO)
    #include <SD.h>
    #elif defined (SPARK)
    #include "sd-card-library-photon-compat/sd-card-library-photon-compat.h"
    #endif
    // Chip select for SD card on the SmartMatrix Shield or Photon
    // Teensy 3.5/3.6
    #if defined(__MK64FX512__) || defined(__MK66FX1M0__)
        #define SD_CS BUILTIN_SDCARD
    #elif defined(ESP32)
        #define SD_CS 5
    #elif defined (ARDUINO)
        #define SD_CS 15
        //#define SD_CS BUILTIN_SDCARD
    #elif defined (SPARK)
        #define SD_CS SS
    #endif
    
    #if defined(ESP32)
        // ESP32 SD Library can't handle a trailing slash in the directory name
        #if matrix_size == 64
            #define GIF_DIRECTORY "/gifs64"
        #else
            #define GIF_DIRECTORY "/gifs"
        #endif
    #else
        // Teensy SD Library requires a trailing slash in the directory name
        #if matrix_size == 64
            #define GIF_DIRECTORY "/gifs64/"
        #else
            #define GIF_DIRECTORY "/gifs/"
        #endif
    #endif
#endif

#define DISPLAY_TIME_SECONDS 10
#endif

