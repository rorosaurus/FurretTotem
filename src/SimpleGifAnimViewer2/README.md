This 2nd simple example works with of SPIFFS on ESP32/ES8266 but could be easy
changed to read out of an SDcard on another chip like teensy by removing the
stubs from FilenameFunctions.  
This implementation includes uses the minimal necessary functions from
FilenameFunctions.cpp for SPIFFS directly inside GifAnim_Impl.h.

This version will work with both the native SmartMatrix and NeoMatrix APIs as defined in neomatrix_config.h

-- Marc MERLIN <marc_soft@merlins.org>
