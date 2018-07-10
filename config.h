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

#ifdef ESP8266
// Use built in flash via SPIFFS
// http://esp8266.github.io/Arduino/versions/2.3.0/doc/filesystem.html#uploading-files-to-file-system
// esp8266com/esp8266/libraries/SD/src/File.cpp
#include <FS.h>
extern "C" {
#include "user_interface.h"
}
#define SPI_FFS
#else
#include <SD.h>
#endif

#define DISPLAY_TIME_SECONDS 10
#endif
