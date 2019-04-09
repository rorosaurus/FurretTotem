img.ffat: data/gifs64/*
	# Get from https://github.com/marcmerlin/esp32_fatfsimage/
	fatfsimage img.ffat 3004 data/

flash:
	# IF you aren't using a 1/3GB split, 0x111000 will need to be updated
	esptool.py --chip esp32 --port /dev/ttyUSB0 --baud 921600 write_flash  0x111000 img.ffat

