/*
 * Animated GIFs Display Code for SmartMatrix and 32x32 RGB LED Panels
 *
 * This file contains code to enumerate and select animated GIF files by name
 * Originally written by: Craig A. Lindley
 * Largely reworked by Marc MERLIN <marc_soft@merlins.org> to support SPIFFS and FatFS
 */
#include "animatedgif_config.h"

File file;

int numberOfFiles;

extern String filenameOptions;
bool optionsBuilt = false;

static void die(const char *mesg) {
    Serial.println(mesg);
    delay(100000); // while 1 loop only triggers watchdog on ESP chips
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

#ifdef FSOSD 
int initSdCard(int chipSelectPin) {
    // initialize the SD card at full speed
    pinMode(chipSelectPin, OUTPUT);
    if (!SD.begin(chipSelectPin)) die("SD Begin failed");
    return 0;
}

bool isAnimationFile(const char filename []) {
    String filenameString(filename);
#else
    bool isAnimationFile(String filenameString) {
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
    int i = 0;
    Serial.print("Enumerate files in dir ");
    Serial.println(directoryName);

    File directory = FSO.open(directoryName);
    if (!directory) die("Can't open directory");

    while (File file = directory.openNextFile()) {
        if (isAnimationFile(file.name())) {
            numberOfFiles++;
            if (displayFilenames) Serial.println(file.name());
            if (!optionsBuilt) filenameOptions += "<option value='" + String(i) + "'>" + file.name() + "</option>";
            i++;
        }
        file.close();
    }
    directory.close();

    optionsBuilt = true;
    return numberOfFiles;
}

// Get the full path/filename of the GIF file with specified index
void getGIFFilenameByIndex(const char *directoryName, int index, char *pnBuffer) {

    // Make sure index is in range
    if ((index < 0) || (index >= numberOfFiles)) return;

#ifndef FSOSD 
    #ifdef ESP32
	File dir = FSO.open(directoryName);
	while (File file = dir.openNextFile()) {
	    String filename = file.name();
	    if (isAnimationFile(filename)) {
    		filename.toCharArray(pnBuffer, 127);
        if (!index) break;
        index--;
	    }
	}
    #else
	Dir dir = FSO.openDir(directoryName);
	
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
            // Copy the directory name into the pathname buffer - 
	    // ESP32 SD Library includes the full path name in the filename, so no need to add the directory name
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

    if (file) file.close();

    // Attempt to open the file for reading
    #ifdef ESP8266
        if (! (file = SPIFFS.open(pathname, "r")) ) die ("Error opening GIF file");
    #else
        if (! (file = FSO.open(pathname)) ) die ("Error opening GIF file");
    #endif
    return 0;
}


// Return a random animated gif path/filename from the specified directory
void chooseRandomGIFFilename(const char *directoryName, char *pnBuffer) {

    int index = random(numberOfFiles);
    getGIFFilenameByIndex(directoryName, index, pnBuffer);
}
