/*
 * Animated GIFs Display Code for SmartMatrix and 32x32 RGB LED Panels
 *
 * This file contains code to enumerate and select animated GIF files by name
 *
 * Written by: Craig A. Lindley
 */
#include "config.h"

File file;

int numberOfFiles;

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

#ifndef SPI_FFS
int initSdCard(int chipSelectPin) {
    // initialize the SD card at full speed
    pinMode(chipSelectPin, OUTPUT);
    if (!SD.begin(chipSelectPin))
        return -1;
    return 0;
}
#endif

#ifdef SPI_FFS
bool isAnimationFile(String filenameString) {
#else
bool isAnimationFile(const char filename []) {
    String filenameString(filename);
#endif

#if defined(ESP32) || defined(ESP8266)
    // ESP32 filename includes the full path, so need to remove the path before looking at the filename
    int pathindex = filenameString.lastIndexOf("/");
    if(pathindex >= 0)
        filenameString.remove(0, pathindex + 1);
#endif

    //Serial.print(filenameString);

    if ((filenameString[0] == '_') || (filenameString[0] == '~') || (filenameString[0] == '.')) {
        Serial.println(" ignoring: leading _/~/. character");
        return false;
    }

    filenameString.toUpperCase();
    if (filenameString.endsWith(".GIF") != 1) {
        Serial.println(" ignoring: doesn't end of .GIF");
        return false;
    }

    return true;
}

// Enumerate and possibly display the animated GIF filenames in GIFS directory
int enumerateGIFFiles(const char *directoryName, boolean displayFilenames) {

    numberOfFiles = 0;
    Serial.print("Enumerate files in dir ");
    Serial.println(directoryName);

#ifdef SPI_FFS
    #ifdef ESP32
    // Oh boy, ESP32 SPIFFS does not even support directory objects...
    // See https://github.com/espressif/arduino-esp32/blob/master/libraries/SPIFFS/examples/SPIFFS_time/SPIFFS_time.ino
	File dir = SPIFFS.open(directoryName);
	while (File file = dir.openNextFile()) {
	    String filename = file.name();
	    if (isAnimationFile(filename)) {
		numberOfFiles++;
		if (displayFilenames) Serial.println(filename);
	    }
	}
    #else
	Dir dir = SPIFFS.openDir(directoryName);
	while (dir.next()) {
	    String filename = dir.fileName();
	    if (isAnimationFile(filename)) {
		numberOfFiles++;
		if (displayFilenames) Serial.println(filename);
	    }
	}
    #endif
#else
    File directory = SD.open(directoryName);
    if (!directory) return -1;

    File file = directory.openNextFile();
    while (file) {
        if (isAnimationFile(file.name())) {
            numberOfFiles++;
            if (displayFilenames) Serial.println(file.name());
        }
        file.close();
        file = directory.openNextFile();
    }
    file.close();
    directory.close();
#endif

    return numberOfFiles;
}

// Get the full path/filename of the GIF file with specified index
void getGIFFilenameByIndex(const char *directoryName, int index, char *pnBuffer) {

    // Make sure index is in range
    if ((index < 0) || (index >= numberOfFiles)) return;

#ifdef SPI_FFS
    #ifdef ESP32
	File dir = SPIFFS.open(directoryName);
	while (File file = dir.openNextFile()) {
	    String filename = file.name();
	    if (isAnimationFile(filename)) {
		index--;
		filename.toCharArray(pnBuffer, 127);
	    }
	    if (!index) break;
	}
    #else
	Dir dir = SPIFFS.openDir(directoryName);
	
	while (dir.next() && index >= 0) {
	    String filename = dir.fileName();
	    if (isAnimationFile(filename)) {
		index--;
		filename.toCharArray(pnBuffer, 127);
	    }
	}
    #endif
#else
    File directory = SD.open(directoryName);
    if (!directory) return;

    File file = directory.openNextFile();
    while (file && (index >= 0)) {
        char* filename = (char*)file.name();

        if (isAnimationFile(file.name())) {
            index--;

#if !defined(ESP32)
            // Copy the directory name into the pathname buffer - ESP32 SD Library includes the full path name in the filename, so no need to add the directory name
            strcpy(pnBuffer, directoryName);
            // Append the filename to the pathname
            strcat(pnBuffer, filename);
#else
            strcpy(pnBuffer, filename);
#endif
        }

        file.close();
        file = directory.openNextFile();
    }
    directory.close();
#endif

    Serial.print("Selected file ");
    Serial.println(pnBuffer);
    file.close();
}

int openGifFilenameByIndex(const char *directoryName, int index) {
    char pathname[128];

    getGIFFilenameByIndex(directoryName, index, pathname);
    
    // Pathname: /gifs/32anim_balls.gif
    //Serial.print("Pathname: ");
    //Serial.println(pathname);

    if (file)
        file.close();

    // Attempt to open the file for reading
#ifdef SPI_FFS
    file = SPIFFS.open(pathname, "r");
#else
    file = SD.open(pathname);
#endif
    if (!file) {
        Serial.println("Error opening GIF file");
        return -1;
    }

    return 0;
}


// Return a random animated gif path/filename from the specified directory
void chooseRandomGIFFilename(const char *directoryName, char *pnBuffer) {

    int index = random(numberOfFiles);
    getGIFFilenameByIndex(directoryName, index, pnBuffer);
}
