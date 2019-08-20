/*
 * SmartMatrix Library - Hardware-Specific Header File (for SmartMatrix Shield V4)
 *
 * Copyright (c) 2015 Louis Beaudoin (Pixelmatix)
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

 // Note: only one MatrixHardware_*.h file should be included per project

#ifndef MATRIX_HARDWARE_H
#define MATRIX_HARDWARE_H
// formula used is 80000000L/(cfg->clkspeed_hz + 1), must result in >=2.  Acceptable values 26.67MHz, 20MHz, 16MHz, 13.34MHz...
#define ESP32_I2S_CLOCK_SPEED (20000000UL)

#define ESP32_FORUM_PINOUT              0
#define ESP32_FORUM_PINOUT_WITH_LATCH   1
#define SMARTLED_SHIELD_V0_PINOUT       2
#define ESP32_JC_RIBBON_PINOUT          3

#ifndef GPIOPINOUT
#define GPIOPINOUT ESP32_FORUM_PINOUT
#endif
//#define GPIOPINOUT ESP32_FORUM_PINOUT_WITH_LATCH // note this mode is untested as of 2018-05-17 - not being used anymore now that SmartMatrix Shield is available
//#define GPIOPINOUT SMARTLED_SHIELD_V0_PINOUT

//Upper half RGB
#define BIT_R1  (1<<0)   
#define BIT_G1  (1<<1)   
#define BIT_B1  (1<<2)   
//Lower half RGB
#define BIT_R2  (1<<3)   
#define BIT_G2  (1<<4)   
#define BIT_B2  (1<<5)   

// Control Signals
#define BIT_LAT (1<<6) 
#define BIT_OE  (1<<7)  

#define BIT_A (1<<8)    
#define BIT_B (1<<9)    
#define BIT_C (1<<10)   
#define BIT_D (1<<11)   
#define BIT_E (1<<12)   


#if (GPIOPINOUT == ESP32_JC_RIBBON_PINOUT)
    #pragma message "Jason Coon ESP32 shield wiring"
// This pinout takes a ribbon cable and flattens it, pin order is 1, 9, 2, 10 ...
// it connects to https://www.tindie.com/products/jasoncoon/16-output-nodemcu-esp32-wifi-ble-led-controller/
// *** WARNING, I cut the trace on Jason's board that went to pin 3, and patched a wire
// to pin 27 so that I can use RX/TX serial debugging ****
// That shield's pinout is this for the output of the level shifters:
// 23, 22, 27 (was 3), 21, 19, 18, 5, 17,    16, 4, 0, 2, 15, 14, 12, 13

    // ADDX is output directly using GPIO
    #define CLKS_DURING_LATCH   0 
    #define MATRIX_I2S_MODE I2S_PARALLEL_BITS_16
    #define MATRIX_DATA_STORAGE_TYPE uint16_t

    /*
    HUB 75 pinout
    01 02 B0
    03 04 Gnd
    05 06 G1
    07 08 E

    09 10 B
    11 12 D
    13 14 STB/Latch
    15 16 Gnd

                        ESP32 pin / comment
    1	R0	23	Red Data (columns 1-16)
    2	G0	22   	Green Data (columns 1-16)

    3	B0	27	(was 3) Blue Data (columns 1-16)
    4	GND	21/GND	Ground

    5	R1	19	Red Data (columns 17-32)
    6	G1	18 	Green Data (columns 17-32)

    7	B1	5    	Blue Data (columns 17-32)
    8	E	17/TX2	Demux Input E for 64x64 panels

    9	A	16/RX2	Demux Input A0
    10	B	4	Demux Input A1
    
    11	C	0/Boot	Demux Input A2
    12	D	2 	Demux Input E1, E3 (32x32 panels only)

    13	CLK	15 	LED Drivers' Clock
    14	STB	14 	LED Drivers' Latch
    
    15	OE	12	LED Drivers' Output Enable
    16	GND	13/GND	Ground
    */ 
    #define R1_PIN  23
    #define G1_PIN  22
    #define B1_PIN  27
    #define R2_PIN  19
    #define G2_PIN  18
    #define B2_PIN  5

    #define A_PIN   16
    #define B_PIN   4
    #define C_PIN   0
    #define D_PIN   2
    #define E_PIN   17

    #define CLK_PIN 15
    #define LAT_PIN 14
    #define OE_PIN  12

    #define GPIO_PWM0A_OUT GPIO_NUM_32
    #define GPIO_SYNC0_IN  GPIO_NUM_34

#elif (GPIOPINOUT == ESP32_FORUM_PINOUT)

    #pragma message "ESP32 forum wiring"

    // ADDX is output directly using GPIO
    #define CLKS_DURING_LATCH   0 
    #define MATRIX_I2S_MODE I2S_PARALLEL_BITS_16
    #define MATRIX_DATA_STORAGE_TYPE uint16_t

    /*
    HUB 75
    01 02 B0
    03 04 Gnd
    05 06 G1
    07 08 E

    09 10 B
    11 12 D
    13 14 STB/Latch
    15 16 Gnd
                        ESP32 pin / comment
    1	R0	2	Red Data (columns 1-16)
    2	G0	15	Green Data (columns 1-16)

    3	B0	4	Blue Data (columns 1-16)
    4	GND	GND	Ground
    
    5	R1	16/RX2	Red Data (columns 17-32)
    6	G1	27	Green Data (columns 17-32)
    
    7	B1	17/TX2	Blue Data (columns 17-32)
    8	E	12	Demux Input E for 64x64 panels
   
    9	A	5	Demux Input A0
    10	B	18	Demux Input A1

    11	C	19	Demux Input A2
    12	D	21	Demux Input E1, E3 (32x32 panels only)
    
    13	CLK	22	LED Drivers' Clock
    14	STB	26	LED Drivers' Latch
    
    15	OE	25	LED Drivers' Output Enable
    16	GND	GND	Ground
    */ 
    #define R1_PIN  2
    #define G1_PIN  15
    #define B1_PIN  4
    #define R2_PIN  14
    #define G2_PIN  27
    #define B2_PIN  13

    #define A_PIN   5
    #define B_PIN   18
    #define C_PIN   19
    #define D_PIN   21
    #define E_PIN   12
    #define LAT_PIN 26
    #define OE_PIN  25

    #define CLK_PIN 22

    #define GPIO_PWM0A_OUT GPIO_NUM_32
    #define GPIO_SYNC0_IN  GPIO_NUM_34

#elif (GPIOPINOUT == ESP32_FORUM_PINOUT_WITH_LATCH)
    #pragma message "ESP32 forum wiring with latch"

    // ADDX is output on RGB pins and stored in external latch (need multiple of 32-bits for full data struct, so pad 2 CLKs to 4 here)
    #define MATRIX_I2S_MODE I2S_PARALLEL_BITS_8
    #define MATRIX_DATA_STORAGE_TYPE uint8_t
    #define CLKS_DURING_LATCH   4

    #define R1_PIN  2
    #define G1_PIN  15
    #define B1_PIN  4
    #define R2_PIN  16
    #define G2_PIN  27
    #define B2_PIN  17

    #define A_PIN   5
    #define B_PIN   18
    #define C_PIN   19
    #define D_PIN   21
    #define E_PIN   12
    #define LAT_PIN 26
    #define OE_PIN  25

    #define CLK_PIN 22

    #define GPIO_PWM0A_OUT GPIO_NUM_32
    #define GPIO_SYNC0_IN  GPIO_NUM_34

#elif (GPIOPINOUT == SMARTLED_SHIELD_V0_PINOUT)

    #pragma message "ESP32 SmartLED shield V0 pinout"

    // ADDX is output on RGB pins and stored in external latch (need multiple of 32-bits for full data struct, so pad 2 CLKs to 4 here)
    #define MATRIX_I2S_MODE I2S_PARALLEL_BITS_8
    #define MATRIX_DATA_STORAGE_TYPE uint8_t
    #define CLKS_DURING_LATCH   4

    #undef BIT_A
    #undef BIT_B
    #undef BIT_C
    #undef BIT_D
    #undef BIT_E

    #define R1_PIN  4
    #define G1_PIN  21
    #define B1_PIN  22
    #define R2_PIN  2
    #define G2_PIN  25
    #define B2_PIN  0

    #define A_PIN   -1
    #define B_PIN   -1
    #define C_PIN   -1
    #define D_PIN   -1
    #define E_PIN   -1

    #define LAT_PIN 27
    #define OE_PIN  32

    #define CLK_PIN 26

    #define GPIO_PWM0A_OUT GPIO_NUM_33
    #define GPIO_SYNC0_IN  GPIO_NUM_32
#endif

//#define DEBUG_PINS_ENABLED
#define DEBUG_1_GPIO    GPIO_NUM_13
//#define DEBUG_2_GPIO    GPIO_NUM_12

#endif
