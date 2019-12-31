/*
 * HE WALK!
 */

#define DISABLE_MATRIX_TEST
#define NEOMATRIX

#define defaultBrightness 50 // 25 is good for home testing, 50 is a good default for shows
#define minBrightness 0
#define maxBrightness 150 // 165 is roughly equivalent to 3A with 2 displays, but leave some headroom

#include <DNSServer.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include "ESPAsyncWebServer.h"
#include "secrets.h"
#include "GifAnim_Impl.h"

int currentBrightness = defaultBrightness;
bool nextFlag = false;
bool prevFlag = false;
int newIndex = -1;
int currentIndex = FIRSTINDEX;

// If the matrix is a different size than the GIFs, allow panning through the GIF
int OFFSETX = 0;
int OFFSETY = 0;
int FACTX = 0;
int FACTY = 0;

int num_files;
String filenameOptions = "";

DNSServer dnsServer;
AsyncWebServer server(80);

String processor(const String& var){
  if(var == "MIN_BRIGHTNESS") return String(minBrightness);
  if(var == "MAX_BRIGHTNESS") return String(maxBrightness);
  if(var == "CURRENT_BRIGHTNESS") return String(currentBrightness);
  if(var == "CURRENT_INDEX") return String(currentIndex);
  if(var == "LIST_FILENAME_OPTIONS") return filenameOptions;
  return String();
}

class CaptiveRequestHandler : public AsyncWebHandler {
public:
  CaptiveRequestHandler() {}
  virtual ~CaptiveRequestHandler() {}

  bool canHandle(AsyncWebServerRequest *request){
    //request->addInterestingHeader("ANY");
    return true;
  }

  void handleRequest(AsyncWebServerRequest *request) {
    // handle other file requests
    if (request->url() == "/styles.css"){
      request->send(SPIFFS, "/www/styles.css", "text/css");
    }
    else { // handle parameters
      if(request->hasParam("next")){
        Serial.println("NEXT pressed");
        nextFlag = true;
      }
      if(request->hasParam("prev")){
        Serial.println("PREVIOUS pressed");
        prevFlag = true;
      }
      if(request->hasParam("brightness")){
        AsyncWebParameter* p = request->getParam("brightness");
        currentBrightness = p->value().toInt();
        Serial.print("New brightness: ");
        Serial.println(currentBrightness);
      }
      if(request->hasParam("newFileIndex")){
        AsyncWebParameter* p = request->getParam("newFileIndex");
        newIndex = p->value().toInt();
        Serial.print("New file index: ");
        Serial.println(newIndex);
      }

      // catch everything else
      //Send index.htm with template processor function
      request->send(SPIFFS, "/www/index.htm", "text/html", false, processor);
    }
  }
};

// Setup method runs once, when the sketch starts
void setup() {
    Serial.begin(115200);
    
    Serial.println("Starting AnimatedGIFs Sketch");
    sav_setup();

    #if ENABLE_SCROLLING == 1
	  matrix.addLayer(&scrollingLayer); 
    #endif

    // Determine how many animated GIF files exist
    num_files = enumerateGIFFiles(GIF_DIRECTORY, true);

    if(num_files < 0) {
      #if ENABLE_SCROLLING == 1
      scrollingLayer.start("No gifs directory", -1);
      #endif
      die("No gifs directory");
    }

    if(!num_files) {
        #if ENABLE_SCROLLING == 1
        scrollingLayer.start("Empty gifs directory", -1);
        #endif
        die("Empty gifs directory");
    }
    
    Serial.print("Index of files: 0 to ");
    Serial.println(num_files);
    Serial.flush();
    
    // We didn't have enough DMA memory to use Wifi until I made this hack in SmartMatrix, effectively removing the double buffer:
    // https://github.com/rorosaurus/SmartMatrix/commit/c46fe8d7be686caaaa3b7198bc4b7b24c6114df8
    Serial.println("Configuring access point...");
    WiFi.softAP(ssid, password, 1, 1, 1); // channel 1 (default), hide SSID, max connected clients = 1
    
    // I also hacked the ESP32 Arduino support to reduce packet buffer size (also uses DMA memory):
    // https://github.com/espressif/arduino-esp32/blob/cec3fca4ad4a39feb463f9298ab3238819732d50/libraries/WiFi/src/WiFiUdp.cpp#L214
    // Lines 210 and 214: change 1460 -> 1200
    // Even with this, ESP32 will sometimes (randomly?) crash when dnsServer.processNextRequest() calls WiFiUDP::parsePacket()
    // Strangely, some ESP32's appear to have less DMA memory than others... Which makes this issue even less consistent to repro. Weird.
    dnsServer.start(53, "*", WiFi.softAPIP());
    
    server.addHandler(new CaptiveRequestHandler());//only when requested from AP
    server.begin();
    Serial.print("Server started. IP Address: ");
    Serial.println(WiFi.softAPIP());
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
    dnsServer.processNextRequest();

    matrixLayer.setBrightness(currentBrightness);
    
    static unsigned long lastTime = millis();
    static int index = FIRSTINDEX;
    currentIndex = index;
    static int8_t new_file = 1;
    static uint16_t frame = 0;
    // allow stalling on a picture if requested
    static uint32_t longer = 0;
    char readchar;
    // frame by frame display
    static bool debugframe = false;
    bool gotnf = false;
    // clear display before each frame
    static bool clear = false;

  if (nextFlag){
    Serial.println("Wifi => next");
    new_file = 1;  
    index++;
    nextFlag = false;
  }
  
  if (prevFlag){
    Serial.println("Wifi => previous");
    new_file = 1;  
    index--;
    prevFlag = false;
  }
  if (newIndex != -1){
      new_file = 1;
      index = newIndex;
      newIndex = -1;
  }

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

    case 'f':
	Serial.println("Serial => debug frames, press 'g' for next frame");
	debugframe = true;
	longer = 3600; //  if frame debugging, keep current gif for 1h
	break;

    case 'g':
	Serial.println("Serial => next frame");
	gotnf = true;
	break;

    case 'c':
	Serial.print("Toggle clear screen: ");
	clear = !clear;;
	Serial.println(clear);
	break;

    case '+': adjust_gamma(+0.05); break;

    case '-': adjust_gamma(-0.05); break;

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

    if (debugframe) {
	if (! gotnf) return;
    }

  if (new_file) { 
	frame = 0;
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
	    die("FATAL: failed to open file");
	}
    }

    if (clear) screenClearCallback();

    // decode the gif
    decoder.decodeFrame();
    frame++;
    if (debugframe) {
	Serial.print("Displayed frame #");
	Serial.print(frame);
	Serial.println(". Press g for next frame");
    }
#if DEBUGLINE
    delay(1000000);
#endif
}

// vim:sts=4:sw=4
