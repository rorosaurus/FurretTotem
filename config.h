#ifndef config_h
#define config_h

#define NEOMATRIX
//#define DEBUGLINE 6

// if you want to display a file and display that one first
#define FIRSTINDEX 0


#ifndef NEOMATRIX
// Neomatrix brightness is different (full brightness can use up 40A) and defined
// to a different value in neomatrix_config.h
// range 0-255
const int defaultBrightness = 255;
#endif

// Note, you can use an sdcard on ESP32 or ESP8266 if you really want,
// but if your data fits in built in flash, why not use it?
// Use built in flash via SPIFFS
// esp8266com/esp8266/libraries/SD/src/File.cpp
// ESP8266: http://esp8266.github.io/Arduino/versions/2.3.0/doc/filesystem.html#uploading-files-to-file-system
// ESP32: https://github.com/me-no-dev/arduino-esp32fs-plugin
#if defined(ESP8266)
    #include <FS.h>
    #define SPI_FFS
    #define GIF_DIRECTORY "/gifs/"
#elif defined(ESP32)
    #include <FS.h>
    #include <SPIFFS.h>
    #define SPI_FFS
    // Do NOT add a trailing slash, or things will fail
    #define GIF_DIRECTORY "/gifs"
#else
    #include <SD.h>
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
        #define GIF_DIRECTORY "/gifs"
    #else
        // Teensy SD Library requires a trailing slash in the directory name
        #define GIF_DIRECTORY "/gifs/"
    #endif
#endif

#define DISPLAY_TIME_SECONDS 10
#endif
