// SmartMatrix_GFX example for single NeoPixel Shield.
// By Marc MERLIN <marc_soft@merlins.org>
// Contains code (c) Adafruit, license BSD

// Please see the other demos and FastLED_NeoMatrix_SmartMatrix_LEDMatrix_GFX_Demos/neomatrix_config.h
// on how to avoid having all the config pasted in all your scripts.

#include <Adafruit_GFX.h>
#include <SmartMatrix_GFX.h>
// CHANGEME, see MatrixHardware_ESP32_V0.h in SmartMatrix/src
#define GPIOPINOUT 3
#include <SmartLEDShieldV4.h>  // comment out this line for if you're not using SmartLED Shield V4 hardware (this line needs to be before #include <SmartMatrix3.h>)
#include <SmartMatrix3.h>

// Choose your prefered pixmap
//#include "heart24.h"
//#include "yellowsmiley24.h"
//#include "bluesmiley24.h"
#include "smileytongue24.h"

#include "google32.h"
// Anything with black does not look so good with the naked eye (better on pictures)
//#include "linux32.h"

// ========================== CONFIG START ===================================================

/// SmartMatrix Defines
#define COLOR_DEPTH 24                  // known working: 24, 48 - If the sketch uses type `rgb24` directly, COLOR_DEPTH must be 24
#define kMatrixWidth  64       // known working: 32, 64, 96, 128
#define kMatrixHeight 32       // known working: 16, 32, 48, 64
const uint8_t kRefreshDepth = 24;       // known working: 24, 36, 48
const uint8_t kDmaBufferRows = 2;       // known working: 2-4, use 2 to save memory, more to keep from dropping frames and automatically lowering refresh rate
const uint8_t kPanelType = SMARTMATRIX_HUB75_32ROW_MOD16SCAN;   // use SMARTMATRIX_HUB75_16ROW_MOD8SCAN for common 16x32 panels
//const uint8_t kPanelType = SMARTMATRIX_HUB75_64ROW_MOD32SCAN;
const uint8_t kMatrixOptions = (SMARTMATRIX_OPTIONS_NONE);      // see http://docs.pixelmatix.com/SmartMatrix for options
const uint8_t kBackgroundLayerOptions = (SM_BACKGROUND_OPTIONS_NONE);

SMARTMATRIX_ALLOCATE_BUFFERS(matrixLayer, kMatrixWidth, kMatrixHeight, kRefreshDepth, kDmaBufferRows, kPanelType, kMatrixOptions);
SMARTMATRIX_ALLOCATE_BACKGROUND_LAYER(backgroundLayer, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kBackgroundLayerOptions);

const int defaultBrightness = (100*255)/100;        // full (100%) brightness
//const int defaultBrightness = (15*255)/100;       // dim: 15% brightness

#define mw kMatrixWidth
#define mh kMatrixHeight
#define NUMMATRIX (kMatrixWidth*kMatrixHeight)

CRGB *matrixleds;

void show_callback();
SmartMatrix_GFX *matrix = new SmartMatrix_GFX(matrixleds, mw, mh, show_callback);
// Sadly this callback function must be copied around with this init code
void show_callback() {
    backgroundLayer.swapBuffers(true);
    matrixleds = (CRGB *)backgroundLayer.backBuffer();
    matrix->newLedsPtr(matrixleds);
}

// ========================== CONFIG END ======================================================


// This could also be defined as matrix->color(255,0,0) but those defines
// are meant to work for adafruit_gfx backends that are lacking color()
#define LED_BLACK		0

#define LED_RED_VERYLOW 	(3 <<  11)
#define LED_RED_LOW 		(7 <<  11)
#define LED_RED_MEDIUM 		(15 << 11)
#define LED_RED_HIGH 		(31 << 11)

#define LED_GREEN_VERYLOW	(1 <<  5)   
#define LED_GREEN_LOW 		(15 << 5)  
#define LED_GREEN_MEDIUM 	(31 << 5)  
#define LED_GREEN_HIGH 		(63 << 5)  

#define LED_BLUE_VERYLOW	3
#define LED_BLUE_LOW 		7
#define LED_BLUE_MEDIUM 	15
#define LED_BLUE_HIGH 		31

#define LED_ORANGE_VERYLOW	(LED_RED_VERYLOW + LED_GREEN_VERYLOW)
#define LED_ORANGE_LOW		(LED_RED_LOW     + LED_GREEN_LOW)
#define LED_ORANGE_MEDIUM	(LED_RED_MEDIUM  + LED_GREEN_MEDIUM)
#define LED_ORANGE_HIGH		(LED_RED_HIGH    + LED_GREEN_HIGH)

#define LED_PURPLE_VERYLOW	(LED_RED_VERYLOW + LED_BLUE_VERYLOW)
#define LED_PURPLE_LOW		(LED_RED_LOW     + LED_BLUE_LOW)
#define LED_PURPLE_MEDIUM	(LED_RED_MEDIUM  + LED_BLUE_MEDIUM)
#define LED_PURPLE_HIGH		(LED_RED_HIGH    + LED_BLUE_HIGH)

#define LED_CYAN_VERYLOW	(LED_GREEN_VERYLOW + LED_BLUE_VERYLOW)
#define LED_CYAN_LOW		(LED_GREEN_LOW     + LED_BLUE_LOW)
#define LED_CYAN_MEDIUM		(LED_GREEN_MEDIUM  + LED_BLUE_MEDIUM)
#define LED_CYAN_HIGH		(LED_GREEN_HIGH    + LED_BLUE_HIGH)

#define LED_WHITE_VERYLOW	(LED_RED_VERYLOW + LED_GREEN_VERYLOW + LED_BLUE_VERYLOW)
#define LED_WHITE_LOW		(LED_RED_LOW     + LED_GREEN_LOW     + LED_BLUE_LOW)
#define LED_WHITE_MEDIUM	(LED_RED_MEDIUM  + LED_GREEN_MEDIUM  + LED_BLUE_MEDIUM)
#define LED_WHITE_HIGH		(LED_RED_HIGH    + LED_GREEN_HIGH    + LED_BLUE_HIGH)

static const uint8_t PROGMEM
    mono_bmp[][8] =
    {
	{   // 0: checkered 1
	    B10101010,
	    B01010101,
	    B10101010,
	    B01010101,
	    B10101010,
	    B01010101,
	    B10101010,
	    B01010101,
			},

	{   // 1: checkered 2
	    B01010101,
	    B10101010,
	    B01010101,
	    B10101010,
	    B01010101,
	    B10101010,
	    B01010101,
	    B10101010,
			},

	{   // 2: smiley
	    B00111100,
	    B01000010,
	    B10100101,
	    B10000001,
	    B10100101,
	    B10011001,
	    B01000010,
	    B00111100 },

	{   // 3: neutral
	    B00111100,
	    B01000010,
	    B10100101,
	    B10000001,
	    B10111101,
	    B10000001,
	    B01000010,
	    B00111100 },

	{   // 4; frowny
	    B00111100,
	    B01000010,
	    B10100101,
	    B10000001,
	    B10011001,
	    B10100101,
	    B01000010,
	    B00111100 },
    };

static const uint16_t PROGMEM
    // These bitmaps were written for a backend that only supported
    // 4 bits per color with Blue/Green/Red ordering while neomatrix
    // uses native 565 color mapping as RGB.  
    // I'm leaving the arrays as is because it's easier to read
    // which color is what when separated on a 4bit boundary
    // The demo code will modify the arrays at runtime to be compatible
    // with the neomatrix color ordering and bit depth.
    RGB_bmp[][64] = {
      // 00: blue, blue/red, red, red/green, green, green/blue, blue, white
      {	0x100, 0x200, 0x300, 0x400, 0x600, 0x800, 0xA00, 0xF00, 
	0x101, 0x202, 0x303, 0x404, 0x606, 0x808, 0xA0A, 0xF0F, 
      	0x001, 0x002, 0x003, 0x004, 0x006, 0x008, 0x00A, 0x00F, 
	0x011, 0x022, 0x033, 0x044, 0x066, 0x088, 0x0AA, 0x0FF, 
	0x010, 0x020, 0x030, 0x040, 0x060, 0x080, 0x0A0, 0x0F0, 
	0x110, 0x220, 0x330, 0x440, 0x660, 0x880, 0xAA0, 0xFF0, 
	0x100, 0x200, 0x300, 0x400, 0x600, 0x800, 0xA00, 0xF00, 
	0x111, 0x222, 0x333, 0x444, 0x666, 0x888, 0xAAA, 0xFFF, },

      // 01: grey to white
      {	0x111, 0x222, 0x333, 0x555, 0x777, 0x999, 0xAAA, 0xFFF, 
	0x222, 0x222, 0x333, 0x555, 0x777, 0x999, 0xAAA, 0xFFF, 
	0x333, 0x333, 0x333, 0x555, 0x777, 0x999, 0xAAA, 0xFFF, 
	0x555, 0x555, 0x555, 0x555, 0x777, 0x999, 0xAAA, 0xFFF, 
	0x777, 0x777, 0x777, 0x777, 0x777, 0x999, 0xAAA, 0xFFF, 
	0x999, 0x999, 0x999, 0x999, 0x999, 0x999, 0xAAA, 0xFFF, 
	0xAAA, 0xAAA, 0xAAA, 0xAAA, 0xAAA, 0xAAA, 0xAAA, 0xFFF, 
	0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, },

      // 02: low red to high red
      {	0x001, 0x002, 0x003, 0x005, 0x007, 0x009, 0x00A, 0x00F, 
	0x002, 0x002, 0x003, 0x005, 0x007, 0x009, 0x00A, 0x00F, 
	0x003, 0x003, 0x003, 0x005, 0x007, 0x009, 0x00A, 0x00F, 
	0x005, 0x005, 0x005, 0x005, 0x007, 0x009, 0x00A, 0x00F, 
	0x007, 0x007, 0x007, 0x007, 0x007, 0x009, 0x00A, 0x00F, 
	0x009, 0x009, 0x009, 0x009, 0x009, 0x009, 0x00A, 0x00F, 
	0x00A, 0x00A, 0x00A, 0x00A, 0x00A, 0x00A, 0x00A, 0x00F, 
	0x00F, 0x00F, 0x00F, 0x00F, 0x00F, 0x00F, 0x00F, 0x00F, },

      // 03: low green to high green
      {	0x010, 0x020, 0x030, 0x050, 0x070, 0x090, 0x0A0, 0x0F0, 
	0x020, 0x020, 0x030, 0x050, 0x070, 0x090, 0x0A0, 0x0F0, 
	0x030, 0x030, 0x030, 0x050, 0x070, 0x090, 0x0A0, 0x0F0, 
	0x050, 0x050, 0x050, 0x050, 0x070, 0x090, 0x0A0, 0x0F0, 
	0x070, 0x070, 0x070, 0x070, 0x070, 0x090, 0x0A0, 0x0F0, 
	0x090, 0x090, 0x090, 0x090, 0x090, 0x090, 0x0A0, 0x0F0, 
	0x0A0, 0x0A0, 0x0A0, 0x0A0, 0x0A0, 0x0A0, 0x0A0, 0x0F0, 
	0x0F0, 0x0F0, 0x0F0, 0x0F0, 0x0F0, 0x0F0, 0x0F0, 0x0F0, },

      // 04: low blue to high blue
      {	0x100, 0x200, 0x300, 0x500, 0x700, 0x900, 0xA00, 0xF00, 
	0x200, 0x200, 0x300, 0x500, 0x700, 0x900, 0xA00, 0xF00, 
	0x300, 0x300, 0x300, 0x500, 0x700, 0x900, 0xA00, 0xF00, 
	0x500, 0x500, 0x500, 0x500, 0x700, 0x900, 0xA00, 0xF00, 
	0x700, 0x700, 0x700, 0x700, 0x700, 0x900, 0xA00, 0xF00, 
	0x900, 0x900, 0x900, 0x900, 0x900, 0x900, 0xA00, 0xF00, 
	0xA00, 0xA00, 0xA00, 0xA00, 0xA00, 0xA00, 0xA00, 0xF00, 
	0xF00, 0xF00, 0xF00, 0xF00, 0xF00, 0xF00, 0xF00, 0xF00, },

      // 05: 1 black, 2R, 2O, 2G, 1B with 4 blue lines rising right
      {	0x000, 0x200, 0x000, 0x400, 0x000, 0x800, 0x000, 0xF00, 
      	0x000, 0x201, 0x002, 0x403, 0x004, 0x805, 0x006, 0xF07, 
	0x008, 0x209, 0x00A, 0x40B, 0x00C, 0x80D, 0x00E, 0xF0F, 
	0x000, 0x211, 0x022, 0x433, 0x044, 0x855, 0x066, 0xF77, 
	0x088, 0x299, 0x0AA, 0x4BB, 0x0CC, 0x8DD, 0x0EE, 0xFFF, 
	0x000, 0x210, 0x020, 0x430, 0x040, 0x850, 0x060, 0xF70, 
	0x080, 0x290, 0x0A0, 0x4B0, 0x0C0, 0x8D0, 0x0E0, 0xFF0,
	0x000, 0x200, 0x000, 0x500, 0x000, 0x800, 0x000, 0xF00, },

      // 06: 4 lines of increasing red and then green
      { 0x000, 0x000, 0x001, 0x001, 0x002, 0x002, 0x003, 0x003, 
	0x004, 0x004, 0x005, 0x005, 0x006, 0x006, 0x007, 0x007, 
	0x008, 0x008, 0x009, 0x009, 0x00A, 0x00A, 0x00B, 0x00B, 
	0x00C, 0x00C, 0x00D, 0x00D, 0x00E, 0x00E, 0x00F, 0x00F, 
	0x000, 0x000, 0x010, 0x010, 0x020, 0x020, 0x030, 0x030, 
	0x040, 0x040, 0x050, 0x050, 0x060, 0x060, 0x070, 0x070, 
	0x080, 0x080, 0x090, 0x090, 0x0A0, 0x0A0, 0x0B0, 0x0B0, 
	0x0C0, 0x0C0, 0x0D0, 0x0D0, 0x0E0, 0x0E0, 0x0F0, 0x0F0, },

      // 07: 4 lines of increasing red and then blue
      { 0x000, 0x000, 0x001, 0x001, 0x002, 0x002, 0x003, 0x003, 
	0x004, 0x004, 0x005, 0x005, 0x006, 0x006, 0x007, 0x007, 
	0x008, 0x008, 0x009, 0x009, 0x00A, 0x00A, 0x00B, 0x00B, 
	0x00C, 0x00C, 0x00D, 0x00D, 0x00E, 0x00E, 0x00F, 0x00F, 
	0x000, 0x000, 0x100, 0x100, 0x200, 0x200, 0x300, 0x300, 
	0x400, 0x400, 0x500, 0x500, 0x600, 0x600, 0x700, 0x700, 
	0x800, 0x800, 0x900, 0x900, 0xA00, 0xA00, 0xB00, 0xB00, 
	0xC00, 0xC00, 0xD00, 0xD00, 0xE00, 0xE00, 0xF00, 0xF00, },

      // 08: criss cross of green and red with diagonal blue.
      {	0xF00, 0x001, 0x003, 0x005, 0x007, 0x00A, 0x00F, 0x000, 
	0x020, 0xF21, 0x023, 0x025, 0x027, 0x02A, 0x02F, 0x020, 
	0x040, 0x041, 0xF43, 0x045, 0x047, 0x04A, 0x04F, 0x040, 
	0x060, 0x061, 0x063, 0xF65, 0x067, 0x06A, 0x06F, 0x060, 
	0x080, 0x081, 0x083, 0x085, 0xF87, 0x08A, 0x08F, 0x080, 
	0x0A0, 0x0A1, 0x0A3, 0x0A5, 0x0A7, 0xFAA, 0x0AF, 0x0A0, 
	0x0F0, 0x0F1, 0x0F3, 0x0F5, 0x0F7, 0x0FA, 0xFFF, 0x0F0, 
	0x000, 0x001, 0x003, 0x005, 0x007, 0x00A, 0x00F, 0xF00, },

      // 09: 2 lines of green, 2 red, 2 orange, 2 green
      { 0x0F0, 0x0F0, 0x0FF, 0x0FF, 0x00F, 0x00F, 0x0F0, 0x0F0, 
	0x0F0, 0x0F0, 0x0FF, 0x0FF, 0x00F, 0x00F, 0x0F0, 0x0F0, 
	0x0F0, 0x0F0, 0x0FF, 0x0FF, 0x00F, 0x00F, 0x0F0, 0x0F0, 
	0x0F0, 0x0F0, 0x0FF, 0x0FF, 0x00F, 0x00F, 0x0F0, 0x0F0, 
	0x0F0, 0x0F0, 0x0FF, 0x0FF, 0x00F, 0x00F, 0x0F0, 0x0F0, 
	0x0F0, 0x0F0, 0x0FF, 0x0FF, 0x00F, 0x00F, 0x0F0, 0x0F0, 
	0x0F0, 0x0F0, 0x0FF, 0x0FF, 0x00F, 0x00F, 0x0F0, 0x0F0, 
	0x0F0, 0x0F0, 0x0FF, 0x0FF, 0x00F, 0x00F, 0x0F0, 0x0F0, },

      // 10: multicolor smiley face
      { 0x000, 0x000, 0x00F, 0x00F, 0x00F, 0x00F, 0x000, 0x000, 
	0x000, 0x00F, 0x000, 0x000, 0x000, 0x000, 0x00F, 0x000, 
	0x00F, 0x000, 0xF00, 0x000, 0x000, 0xF00, 0x000, 0x00F, 
	0x00F, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x00F, 
	0x00F, 0x000, 0x0F0, 0x000, 0x000, 0x0F0, 0x000, 0x00F, 
	0x00F, 0x000, 0x000, 0x0F4, 0x0F3, 0x000, 0x000, 0x00F, 
	0x000, 0x00F, 0x000, 0x000, 0x000, 0x000, 0x00F, 0x000, 
	0x000, 0x000, 0x00F, 0x00F, 0x00F, 0x00F, 0x000, 0x000, },
};

// Convert a BGR 4/4/4 bitmap to RGB 5/6/5 used by Adafruit_GFX
void fixdrawRGBBitmap(int16_t x, int16_t y, const uint16_t *bitmap, int16_t w, int16_t h) {
    uint16_t RGB_bmp_fixed[w * h];
    for (uint16_t pixel=0; pixel<w*h; pixel++) {
	uint8_t r,g,b;
	uint16_t color = pgm_read_word(bitmap + pixel);

	//Serial.print(color, HEX);
	b = (color & 0xF00) >> 8;
	g = (color & 0x0F0) >> 4;
	r = color & 0x00F;
	//Serial.print(" ");
	//Serial.print(b);
	//Serial.print("/");
	//Serial.print(g);
	//Serial.print("/");
	//Serial.print(r);
	//Serial.print(" -> ");
	// expand from 4/4/4 bits per color to 5/6/5
	b = map(b, 0, 15, 0, 31);
	g = map(g, 0, 15, 0, 63);
	r = map(r, 0, 15, 0, 31);
	//Serial.print(r);
	//Serial.print("/");
	//Serial.print(g);
	//Serial.print("/");
	//Serial.print(b);
	RGB_bmp_fixed[pixel] = (r << 11) + (g << 5) + b;
	//Serial.print(" -> ");
	//Serial.println(RGB_bmp_fixed[pixel], HEX);
    }
    matrix->drawRGBBitmap(x, y, RGB_bmp_fixed, w, h);
}

// In a case of a tile of neomatrices, this test is helpful to make sure that the
// pixels are all in sequence (to check your wiring order and the tile options you
// gave to the constructor).
// This also counts as another speed test that measures how fast matrix->show, is.
// 4096 pixels, 55 seconds, 74 frames per second.
// without the pixel copies, it takes 54 seconds, almost as fast.
void count_pixels() {
    matrix->clear();
    for (uint16_t i=0; i<mh; i++) {
	for (uint16_t j=0; j<mw; j++) {
	    matrix->drawPixel(j, i, i%3==0?(uint16_t)LED_BLUE_HIGH:i%3==1?(uint16_t)LED_RED_HIGH:(uint16_t)LED_GREEN_HIGH);
	    matrix->show();
	}
	Serial.print("Row done: ");
	Serial.println(i);
    }
}

// Fill the screen with multiple levels of white to gauge the quality
void display_four_white() {
    matrix->clear();
    matrix->fillRect(0,0, mw,mh, LED_WHITE_HIGH);
    matrix->drawRect(1,1, mw-2,mh-2, LED_WHITE_MEDIUM);
    matrix->drawRect(2,2, mw-4,mh-4, LED_WHITE_LOW);
    matrix->drawRect(3,3, mw-6,mh-6, LED_WHITE_VERYLOW);
    matrix->show();
}

void display_bitmap(uint8_t bmp_num, uint16_t color) { 
    static uint16_t bmx,bmy;

    // Clear the space under the bitmap that will be drawn as
    // drawing a single color pixmap does not write over pixels
    // that are nul, and leaves the data that was underneath
    matrix->fillRect(bmx,bmy, bmx+8,bmy+8, LED_BLACK);
    matrix->drawBitmap(bmx, bmy, mono_bmp[bmp_num], 8, 8, color);
    bmx += 8;
    if (bmx >= mw) bmx = 0;
    if (!bmx) bmy += 8;
    if (bmy >= mh) bmy = 0;
    matrix->show();
}

void display_rgbBitmap(uint8_t bmp_num) { 
    static uint16_t bmx,bmy;

    fixdrawRGBBitmap(bmx, bmy, RGB_bmp[bmp_num], 8, 8);
    bmx += 8;
    if (bmx >= mw) bmx = 0;
    if (!bmx) bmy += 8;
    if (bmy >= mh) bmy = 0;
    matrix->show();
}

void display_lines() {
    matrix->clear();

    // 4 levels of crossing red lines.
    matrix->drawLine(0,mh/2-2, mw-1,2, LED_RED_VERYLOW);
    matrix->drawLine(0,mh/2-1, mw-1,3, LED_RED_LOW);
    matrix->drawLine(0,mh/2,   mw-1,mh/2, LED_RED_MEDIUM);
    matrix->drawLine(0,mh/2+1, mw-1,mh/2+1, LED_RED_HIGH);

    // 4 levels of crossing green lines.
    matrix->drawLine(mw/2-2, 0, mw/2-2, mh-1, LED_GREEN_VERYLOW);
    matrix->drawLine(mw/2-1, 0, mw/2-1, mh-1, LED_GREEN_LOW);
    matrix->drawLine(mw/2+0, 0, mw/2+0, mh-1, LED_GREEN_MEDIUM);
    matrix->drawLine(mw/2+1, 0, mw/2+1, mh-1, LED_GREEN_HIGH);

    // Diagonal blue line.
    matrix->drawLine(0,0, mw-1,mh-1, LED_BLUE_HIGH);
    matrix->drawLine(0,mh-1, mw-1,0, LED_ORANGE_MEDIUM);
    matrix->show();
}

void display_boxes() {
    matrix->clear();
    matrix->drawRect(0,0, mw,mh, LED_BLUE_HIGH);
    matrix->drawRect(1,1, mw-2,mh-2, LED_GREEN_MEDIUM);
    matrix->fillRect(2,2, mw-4,mh-4, LED_RED_HIGH);
    matrix->fillRect(3,3, mw-6,mh-6, LED_ORANGE_MEDIUM);
    matrix->show();
}

void display_circles() {
    matrix->clear();
    matrix->drawCircle(mw/2,mh/2, 2, LED_RED_MEDIUM);
    matrix->drawCircle(mw/2-1-min(mw,mh)/8, mh/2-1-min(mw,mh)/8, min(mw,mh)/4, LED_BLUE_HIGH);
    matrix->drawCircle(mw/2+1+min(mw,mh)/8, mh/2+1+min(mw,mh)/8, min(mw,mh)/4-1, LED_ORANGE_MEDIUM);
    matrix->drawCircle(1,mh-2, 1, LED_GREEN_LOW);
    matrix->drawCircle(mw-2,1, 1, LED_GREEN_HIGH);
    if (min(mw,mh)>12) matrix->drawCircle(mw/2-1, mh/2-1, min(mh/2-1,mw/2-1), LED_CYAN_HIGH);
    matrix->show();
}

void display_resolution() {
    matrix->setTextSize(1);
    // not wide enough;
    if (mw<16) return;
    matrix->clear();
    // Font is 5x7, if display is too small
    // 8 can only display 1 char
    // 16 can almost display 3 chars
    // 24 can display 4 chars
    // 32 can display 5 chars
    matrix->setCursor(0, 0);
    matrix->setTextColor(matrix->Color(255,0,0));
    if (mw>10) matrix->print(mw/10);
    matrix->setTextColor(matrix->Color(255,128,0)); 
    matrix->print(mw % 10);
    matrix->setTextColor(matrix->Color(0,255,0));
    matrix->print('x');
    // not wide enough to print 5 chars, go to next line
    if (mw<25) {
	if (mh==13) matrix->setCursor(6, 7);
	else if (mh>=13) {
	    matrix->setCursor(mw-11, 8);
	} else {
	    // we're not tall enough either, so we wait and display
	    // the 2nd value on top.
	    matrix->show();
	    delay(2000);
	    matrix->clear();
	    matrix->setCursor(mw-11, 0);
	}   
    }
    matrix->setTextColor(matrix->Color(0,255,128)); 
    matrix->print(mh/10);
    matrix->setTextColor(matrix->Color(0,128,255));  
    matrix->print(mh % 10);
    // enough room for a 2nd line
    if ((mw>25 && mh >14) || mh>16) {
	matrix->setCursor(0, mh-7);
	matrix->setTextColor(matrix->Color(0,255,255)); 
	if (mw>16) matrix->print('*');
	matrix->setTextColor(matrix->Color(255,0,0)); 
	matrix->print('R');
	matrix->setTextColor(matrix->Color(0,255,0));
	matrix->print('G');
	matrix->setTextColor(matrix->Color(0,0,255)); 
	matrix->print("B");
	matrix->setTextColor(matrix->Color(255,255,0)); 
	// this one could be displayed off screen, but we don't care :)
	matrix->print("*");

	// We have a big array, great, let's assume 32x32 and add something in the middle
	if (mh>24 && mw>25) {
	    for (uint16_t i=0; i<mw; i+=8) fixdrawRGBBitmap(i, mh/2-7+(i%16)/8*6, RGB_bmp[10], 8, 8);
	}
    }
    
    matrix->show();
}

void display_scrollText() {
    uint8_t size = max(int(mw/8), 1);
    matrix->clear();
    matrix->setTextWrap(false);  // we don't wrap text so it scrolls nicely
    matrix->setTextSize(1);
    matrix->setRotation(0);
    for (int8_t x=7; x>=-42; x--) {
	yield();
	matrix->clear();
	matrix->setCursor(x,0);
	matrix->setTextColor(LED_GREEN_HIGH);
	matrix->print("Hello");
	if (mh>11) {
	    matrix->setCursor(-20-x,mh-7);
	    matrix->setTextColor(LED_ORANGE_HIGH);
	    matrix->print("World");
	}
	matrix->show();
       delay(50);
    }

    matrix->setRotation(3);
    matrix->setTextSize(size);
    matrix->setTextColor(LED_BLUE_HIGH);
    for (int16_t x=8*size; x>=-6*8*size; x--) {
	yield();
	matrix->clear();
	matrix->setCursor(x,mw/2-size*4);
	matrix->print("Rotate");
	matrix->show();
	// note that on a big array the refresh rate from show() will be slow enough that
	// the delay become irrelevant. This is already true on a 32x32 array.
        delay(50/size);
    }
    matrix->setRotation(0);
    matrix->setCursor(0,0);
    matrix->show();
}

// Scroll within big bitmap so that all if it becomes visible or bounce a small one.
// If the bitmap is bigger in one dimension and smaller in the other one, it will
// be both panned and bounced in the appropriate dimensions.
void display_panOrBounceBitmap (uint8_t bitmapSize) {
    // keep integer math, deal with values 16 times too big
    // start by showing upper left of big bitmap or centering if the display is big
    int16_t xf = max(0, (mw-bitmapSize)/2) << 4;
    int16_t yf = max(0, (mh-bitmapSize)/2) << 4;
    // scroll speed in 1/16th
    int16_t xfc = 6;
    int16_t yfc = 3;
    // scroll down and right by moving upper left corner off screen 
    // more up and left (which means negative numbers)
    int16_t xfdir = -1;
    int16_t yfdir = -1;

    for (uint16_t i=1; i<200; i++) {
	bool updDir = false;

	// Get actual x/y by dividing by 16.
	int16_t x = xf >> 4;
	int16_t y = yf >> 4;

	matrix->clear();
	// bounce 8x8 tri color smiley face around the screen
	if (bitmapSize == 8) fixdrawRGBBitmap(x, y, RGB_bmp[10], 8, 8);
	// pan 24x24 pixmap
	if (bitmapSize == 24) matrix->drawRGBBitmap(x, y, (const uint16_t *) bitmap24, bitmapSize, bitmapSize);
	if (bitmapSize == 32) matrix->drawRGBBitmap(x, y, (const uint16_t *) bitmap32, bitmapSize, bitmapSize);
	matrix->show();
	 
	// Only pan if the display size is smaller than the pixmap
	// but not if the difference is too small or it'll look bad.
	if (bitmapSize-mw>2) {
	    xf += xfc*xfdir;
	    if (xf >= 0)                      { xfdir = -1; updDir = true ; };
	    // we don't go negative past right corner, go back positive
	    if (xf <= ((mw-bitmapSize) << 4)) { xfdir = 1;  updDir = true ; };
	}
	if (bitmapSize-mh>2) {
	    yf += yfc*yfdir;
	    // we shouldn't display past left corner, reverse direction.
	    if (yf >= 0)                      { yfdir = -1; updDir = true ; };
	    if (yf <= ((mh-bitmapSize) << 4)) { yfdir = 1;  updDir = true ; };
	}
	// only bounce a pixmap if it's smaller than the display size
	if (mw>bitmapSize) {
	    xf += xfc*xfdir;
	    // Deal with bouncing off the 'walls'
	    if (xf >= (mw-bitmapSize) << 4) { xfdir = -1; updDir = true ; };
	    if (xf <= 0)           { xfdir =  1; updDir = true ; };
	}
	if (mh>bitmapSize) {
	    yf += yfc*yfdir;
	    if (yf >= (mh-bitmapSize) << 4) { yfdir = -1; updDir = true ; };
	    if (yf <= 0)           { yfdir =  1; updDir = true ; };
	}
	
	if (updDir) {
	    // Add -1, 0 or 1 but bind result to 1 to 1.
	    // Let's take 3 is a minimum speed, otherwise it's too slow.
	    xfc = constrain(xfc + random(-1, 2), 3, 16);
	    yfc = constrain(xfc + random(-1, 2), 3, 16);
	}
	delay(10);
    }
}


void loop() {
    // clear the screen after X bitmaps have been displayed and we
    // loop back to the top left corner
    // 8x8 => 1, 16x8 => 2, 17x9 => 6
    static uint8_t pixmap_count = ((mw+7)/8) * ((mh+7)/8);

    display_four_white();
    delay(3000);

    Serial.print("Screen pixmap capacity: ");
    Serial.println(pixmap_count);

    // multicolor bitmap sent as many times as we can display an 8x8 pixmap
    for (uint8_t i=0; i<=pixmap_count; i++)
    {
	display_rgbBitmap(0);
    }
    delay(1000);

    Serial.println("Display Resolution");
    display_resolution();
    delay(3000);

    Serial.println("Display bitmaps");
    // Cycle through red, green, blue, display 2 checkered patterns
    // useful to debug some screen types and alignment.
    uint16_t bmpcolor[] = { LED_GREEN_HIGH, LED_BLUE_HIGH, LED_RED_HIGH };
    for (uint8_t i=0; i<3; i++)
    {
	display_bitmap(0, bmpcolor[i]);
 	delay(500);
	display_bitmap(1, bmpcolor[i]);
 	delay(500);
    }

    Serial.println("Display smileys");
    // Display 3 smiley faces.
    for (uint8_t i=2; i<=4; i++)
    {
	display_bitmap(i, bmpcolor[i-2]);
	// If more than one pixmap displayed per screen, display more quickly.
	delay(mw>8?500:1500);
    }
    // If we have multiple pixmaps displayed at once, wait a bit longer on the last.
    delay(mw>8?1000:500);

    Serial.println("Display lines, boxes and circles");
    display_lines();
    delay(3000);

    display_boxes();
    delay(3000);

    display_circles();
    delay(3000);
    matrix->clear();

    Serial.println("Display RGB bitmaps");
    for (uint8_t i=0; i<=(sizeof(RGB_bmp)/sizeof(RGB_bmp[0])-1); i++)
    {
	display_rgbBitmap(i);
	delay(mw>8?500:1500);
    }
    // If we have multiple pixmaps displayed at once, wait a bit longer on the last.
    delay(mw>8?1000:500);

    Serial.println("Scrolltext");
    display_scrollText();

    Serial.println("bounce 32 bitmap");
    display_panOrBounceBitmap(32);
    // pan a big pixmap
    Serial.println("pan/bounce 24 bitmap");
    display_panOrBounceBitmap(24);
    // bounce around a small one
    Serial.println("pan/bounce 8 bitmap");
    display_panOrBounceBitmap(8);

    Serial.println("Demo loop done, starting over");
}

void setup() {
    matrixLayer.addLayer(&backgroundLayer); 
    matrixLayer.begin();
    matrixLayer.setBrightness(defaultBrightness);
    // This sets the neomatrix and LEDMatrix pointers
    show_callback();
    matrixLayer.setRefreshRate(240);
    backgroundLayer.enableColorCorrection(true);

    // Time for serial port to work?
    delay(1000);
    backgroundLayer.fillScreen( {0x80, 0x80, 0x80} );
    backgroundLayer.swapBuffers();

    Serial.begin(115200);
    Serial.print("Matrix Size: ");
    Serial.print(mw);
    Serial.print(" ");
    Serial.println(mh);
    matrix->begin();
    matrix->setTextWrap(false);
    Serial.println("If the code crashes here, decrease the brightness or turn off the all white display below");
    // Test full bright of all LEDs. If brightness is too high
    // for your current limit (i.e. USB), decrease it.
//#define DISABLE_WHITE
#ifndef DISABLE_WHITE
    matrix->fillScreen(LED_WHITE_HIGH);
    matrix->show();
    delay(3000);
    matrix->clear();
#endif
    Serial.println("Running blue/red speed test");
// You can't use millis to time frame fresh rate because it uses cli() which breaks millis()
// So I use my stopwatch to count 1000 displays and that's good enough
// 500 loops of 2 updates each is 13.3s for 1000 updates or 75 updates per second for 4096 LEDs
// for ESP32
// For some reason it's much faster on teensy 3.6, 18 seconds or 228fps
    for (uint16_t i=0; i<500; i++) { 
	matrix->fillScreen(LED_BLUE_HIGH);
	matrix->show();
	matrix->fillScreen(LED_RED_HIGH);
	matrix->show();
    }
    Serial.println("Done running blue/red speed test");

    // This counts but also shows bleeding between pixels and lines.
    Serial.println("Count pixels. This is slow, you may want to comment me out");
    count_pixels();
    Serial.println("Count pixels done");
    delay(1000);
}

// vim:sts=4:sw=4
