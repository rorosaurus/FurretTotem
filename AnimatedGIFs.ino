/*
 * Animated GIFs Display Code for SmartMatrix and 32x32 RGB LED Panels
 *
 * Uses SmartMatrix Library for Teensy 3.1 written by Louis Beaudoin at pixelmatix.com
 *
 * Written by: Craig A. Lindley
 *
 * Copyright (c) 2014 Craig A. Lindley
 * Refactoring by Louis Beaudoin (Pixelmatix)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * This example displays 32x32 GIF animations loaded from a SD Card connected to the Teensy 3.1
 * The GIFs can be up to 32 pixels in width and height.
 * This code has been tested with 32x32 pixel and 16x16 pixel GIFs, but is optimized for 32x32 pixel GIFs.
 *
 * Wiring is on the default Teensy 3.1 SPI pins, and chip select can be on any GPIO,
 * set by defining SD_CS in the code below
 * Function     | Pin
 * DOUT         |  11
 * DIN          |  12
 * CLK          |  13
 * CS (default) |  15
 *
 * Wiring for ESP32 follows the default for the ESP32 SD Library, see: https://github.com/espressif/arduino-esp32/tree/master/libraries/SDis is on the default Teensy 3.1 SPI pins, and chip select can be on any GPIO,
 *
 * This code first looks for .gif files in the /gifs/ directory
 * (customize below with the GIF_DIRECTORY definition) then plays random GIFs in the directory,
 * looping each GIF for DISPLAY_TIME_SECONDS
 *
 * This example is meant to give you an idea of how to add GIF playback to your own sketch.
 * For a project that adds GIF playback with other features, take a look at
 * Light Appliance and Aurora:
 * https://github.com/CraigLindley/LightAppliance
 * https://github.com/pixelmatix/aurora
 *
 * If you find any GIFs that won't play properly, please attach them to a new
 * Issue post in the GitHub repo here:
 * https://github.com/pixelmatix/AnimatedGIFs/issues
 */

/*
 * CONFIGURATION:
 *  - If you're using SmartLED Shield V4 (or above), uncomment the line that includes <SmartMatrixShieldV4.h>
 *  - update the "SmartMatrix configuration and memory allocation" section to match the width and height and other configuration of your display
 *  - Note for 128x32 and 64x64 displays with Teensy 3.2 - need to reduce RAM:
 *    set kRefreshDepth=24 and kDmaBufferRows=2 or set USB Type: "None" in Arduino,
 *    decrease refreshRate in setup() to 90 or lower to get good an accurate GIF frame rate
 *  - Set the chip select pin for your board.  On Teensy 3.5/3.6, the onboard microSD CS pin is "BUILTIN_SDCARD"
 *  - For ESP32 and large panels, you don't need to lower the refreshRate, but you can lower the frameRate (number of times the refresh buffer
 *    is updaed with new data per second), giving more time for the CPU to decode the GIF.
 *    Use matrix.setMaxCalculationCpuPercentage() or matrix.setCalcRefreshRateDivider()
 */

#include "GifAnim_Impl.h"

// If the matrix is a different size than the GIFs, set the offset for the upper left corner
// (negative or positive is ok).
int OFFSETX = 0;
int OFFSETY = 0;

int num_files;

// Setup method runs once, when the sketch starts
void setup() {
    sav_setup(NULL);

    // Seed the random number generator
    // This breaks SmartMatrix output on ESP32
    //randomSeed(analogRead(14));

#ifdef NEOMATRIX
    #if defined(ESP8266)
	Serial.println();
	Serial.print( F("Heap: ") ); Serial.println(system_get_free_heap_size());
	Serial.print( F("Boot Vers: ") ); Serial.println(system_get_boot_version());
	Serial.print( F("CPU: ") ); Serial.println(system_get_cpu_freq());
	Serial.print( F("SDK: ") ); Serial.println(system_get_sdk_version());
	Serial.print( F("Chip ID: ") ); Serial.println(system_get_chip_id());
	Serial.print( F("Flash ID: ") ); Serial.println(spi_flash_get_id());
	Serial.print( F("Flash Size: ") ); Serial.println(ESP.getFlashChipRealSize());
	Serial.print( F("Vcc: ") ); Serial.println(ESP.getVcc());
	Serial.println();
    #endif
#else
    #if ENABLE_SCROLLING == 1
	SMARTMATRIX_ALLOCATE_SCROLLING_LAYER(scrollingLayer, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kScrollingLayerOptions);
	matrix.addLayer(&scrollingLayer); 
    #endif
#endif // NEOMATRIX
Serial.println("Starting AnimatedGIFs Sketch");

#ifdef SPI_FFS
    SPIFFS.begin();
    Serial.println("SPIFFS Directory listing:");
    #ifdef ESP8266
	Dir dir = SPIFFS.openDir("/");
	while (dir.next()) {
	    String fileName = dir.fileName();
	    size_t fileSize = dir.fileSize();
	    Serial.printf("FS File: %s, size: %s\n", fileName.c_str(), String(fileSize).c_str());
	}
    #else
    // ESP32 SPIFFS does not support directory objects
    // See https://github.com/espressif/arduino-esp32/blob/master/libraries/SPIFFS/examples/SPIFFS_time/SPIFFS_time.ino
	File dir = SPIFFS.open("/");
	while (File file = dir.openNextFile()) {
	    Serial.print("FS File: ");
	    Serial.print(file.name());
	    Serial.print(" Size: ");
	    Serial.println(file.size());
	}
    #endif
    Serial.println();
#else
    if(initSdCard(SD_CS) < 0) {
	#if ENABLE_SCROLLING == 1
	    scrollingLayer.start("No SD card", -1);
	#endif
	Serial.println("No SD card");
	while(1);
    }
#endif

    // for ESP32 we need to allocate SmartMatrix DMA buffers after initializing
    // the SD card to avoid using up too much memory
    // Determine how many animated GIF files exist
    num_files = enumerateGIFFiles(GIF_DIRECTORY, true);

    if(num_files < 0) {
#if ENABLE_SCROLLING == 1
        scrollingLayer.start("No gifs directory", -1);
#endif
        Serial.println("No gifs directory");
	// while(1) trips the watchdog on ESP8266
        delay(100000000);
    }

    if(!num_files) {
#if ENABLE_SCROLLING == 1
        scrollingLayer.start("Empty gifs directory", -1);
#endif
        Serial.println("Empty gifs directory");
        delay(100000000);
    }
    Serial.print("Index of files: 0 to ");
    Serial.println(num_files);
    Serial.flush();
    // At least on teensy, due to some framework bug it seems, early
    // serial output gets looped back into serial input
    // Hence, flush input.
    while(Serial.available() > 0) { char t = Serial.read(); t=t; }
}

void adjust_gamma(float change) {
#ifdef NEOMATRIX
    matrix_gamma += change;
    matrix->precal_gamma(matrix_gamma);
    Serial.print("Change gamma to: "); 
    Serial.println(matrix_gamma); 
#else
    Serial.println("Gamma changing not supported in SmartMatrix lib"); 
#endif
}

void loop() {
    static unsigned long lastTime = millis();
    static int index = FIRSTINDEX;
    static int8_t new_file = 1;
    // allow stalling on a picture if requested
    static uint32_t longer = 0;
    char readchar;

    if (Serial.available()) readchar = Serial.read(); else readchar = 0;


    switch(readchar) {
    case 'n': 
	Serial.println("Serial => next"); 
	new_file = 1;  
	index++;
	break;

    case 'p':
	Serial.println("Serial => previous");
	new_file = 1;
	index--;
	break;

    case '+': adjust_gamma(+0.2); break;

    case '-': adjust_gamma(-0.2); break;

    // = allows staying on a single picture for up to 1H instead of a few seconds
    case '=':
	longer = longer?0:3600;
	Serial.print("Image display time: "); 
	Serial.println(longer + DISPLAY_TIME_SECONDS); 
	break;

    default:
	// BUG: this does not work for index '0', just type '1', and 'p'
	if (readchar) {
	    while ((readchar >= '0') && (readchar <= '9')) {
		new_file = 10 * new_file + (readchar - '0');
		readchar = 0;
		if (Serial.available()) readchar = Serial.read();
	    }

	    if (new_file) {
		Serial.print("Got new file via serial ");
		Serial.println(new_file);
		index = new_file;
	    } else {
		Serial.print("Got serial char ");
		Serial.println(readchar);
	    }
	}
    }

    if (millis() - lastTime > ((DISPLAY_TIME_SECONDS + longer) * 1000)) {
	new_file = 1;
	index++;
    }

    if (new_file) { 
	new_file = 0;
	lastTime = millis();
	if (index >= num_files) index = 0;
	if (index <= -1) index = num_files - 1;
        Serial.print("Fetching file index #");
        Serial.println(index);

        if (openGifFilenameByIndex(GIF_DIRECTORY, index) >= 0) {
            // Can clear screen for new animation here, but this might cause flicker with short animations
	    // matrix->clear();

            decoder.startDecoding();
        } else {
	    Serial.println("FATAL: failed to open file");
	    delay(1000000);
	}
    }
    decoder.decodeFrame();
#if DEBUGLINE
    delay(1000000);
#endif
}

// vim:sts=4:sw=4
