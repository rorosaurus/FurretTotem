This simple example only works with of SPIFFS on ESP32/ES8266 but could be easy changed to read out of an SDcard on another chip like teensy.  
This implementation includes the necessary functions from FilenameFunctions.cpp directly inside SimpleGifAnimViewer.ino

This version will only work with the NeoMatrix API, although it can use SmartMatrix via the NeoMatrix API as defined in neomatrix_config.h

This version also does not use GifAnim_Impl and provides the bare minimal glue to talk to GifDecoder.

-- Marc MERLIN <marc_soft@merlins.org>
