#pragma once

#include <Arduino.h>

#include <FastLED.h>
// #include "globals.h"

FASTLED_USING_NAMESPACE // This line defines which template is used from the library for constructor or setup

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif
#define LED_PER_SEG 1
#define TOTAL_LEDS 30
#define LEDS_IN_TPLUS 16

    class pixelSevenSegment
{

public:
    int total_leds;

    CRGBArray<TOTAL_LEDS> ledString;

    // Constructor

    pixelSevenSegment(int number_digits = 6, int leds_per_segment = 6, int extra_leds = 21) :

                                                                                              total_leds((number_digits * leds_per_segment) + extra_leds),
                                                                                              ledString()
    // tell FastLED about the LED strip configuration

    {
    }

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::: Neopixel to Seven Segment Variables :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    // The following data structures are intended to make the neopixles function effectivly like a traditional 7 segment display.

    struct digitSeg
    {              // Data Structure to contain the data for "characters" divided up into 7 segments. Each segment can be on or off.
        uint8_t A; // Segments mirror the wiring of traditional 7 segment display
        uint8_t B;
        uint8_t C;
        uint8_t D;
        uint8_t E;
        uint8_t F;
        uint8_t G;
    };

    void sevenSegSetup(byte brightness = 20);

    void setDigit(digitSeg current, int8_t digitNumber, CRGB color);

    void setDotsRGB(CRGB color); // Ignore does not work atm

    void setStringRGB(uint16_t start, uint16_t to, CRGB color); // Sets any string of LEDs to the passed colour values

    void setDigitsBlank();

    void setAllDigitsX(digitSeg X, CRGB color);

    void changeBrightness(byte bright = 255);

    // These values are passed bit arrays to print specific digits to each character in the display

    digitSeg seconds0; // Holds the current displayed least significant seconds figure
    digitSeg seconds1; // holds the current displayed most significant seconds figure

    digitSeg minutes2; // Holds the current displayed least significant minuitesfigure
    digitSeg minutes3; // holds the current displayed most significant minuites figure

    digitSeg hours4; // Holds the current displayed least significant hours figure
    digitSeg hours5; // holds the current displayed most significant hours figure

    digitSeg plusminus; // Holds the positive or negative (might be a better way of doing this as it only requires 2 bytes of data, not 7
    digitSeg dots;      // holds the values for the dots (also could be done differently, as it only needs one bit for control, but 4 LED id's

    digitSeg displayedDigits[6] = {seconds0, seconds1, minutes2, minutes3, hours4, hours5}; // holds the data values above in an array making referencing in functions and loops easier.

    // these constant data structures hold the arrays for each unique character. Bits mirror the segments of a typical 7 segment display. Other letters and Characters can be added by adding arrays

    const digitSeg zero = {1, 1, 1, 1, 1, 1, 0};
    const digitSeg one = {0, 1, 1, 0, 0, 0, 0};
    const digitSeg two = {1, 1, 0, 1, 1, 0, 1};
    const digitSeg three = {1, 1, 1, 1, 0, 0, 1};
    const digitSeg four = {0, 1, 1, 0, 0, 1, 1};
    const digitSeg five = {1, 0, 1, 1, 0, 1, 1};
    const digitSeg six = {1, 0, 1, 1, 1, 1, 1};
    const digitSeg seven = {1, 1, 1, 0, 0, 0, 0};
    const digitSeg eight = {1, 1, 1, 1, 1, 1, 1};
    const digitSeg nine = {1, 1, 1, 0, 0, 1, 1};

    digitSeg alldigits[10] = {zero, one, two, three, four, five, six, seven, eight, nine}; // array to hold data structures above. Array number matches the character being recalled.

    const digitSeg blank = {0, 0, 0, 0, 0, 0, 0};

    // This can be accessed as:

    // alldigits[0];   // contains the display data for the character 0
    // alldigits[1];   // Contains the display data for the character 1
    //  et al

    // Other Letters and characters that could be easily printed (needs arrays to be filled in);

    digitSeg A = {1, 1, 1, 0, 1, 1, 1};
    digitSeg E = {1, 0, 0, 1, 1, 1, 1};
    digitSeg i = {0, 0, 1, 0, 0, 0, 0};
    digitSeg O = {1, 1, 1, 1, 1, 1, 0};
    digitSeg o = {0, 0, 1, 1, 1, 0, 1};
    digitSeg U = {0, 1, 1, 1, 1, 1, 0};
    digitSeg u = {0, 0, 1, 1, 1, 0, 0};

    digitSeg B = {1, 1, 1, 1, 1, 1, 1};
    digitSeg C = {1, 0, 0, 1, 1, 1, 0};
    digitSeg F = {1, 0, 0, 0, 1, 1, 1};
    digitSeg H = {0, 1, 1, 0, 1, 1, 1};
    digitSeg J = {1, 1, 1, 1, 0, 0, 0};
    digitSeg L = {0, 0, 0, 1, 1, 1, 0};

    digitSeg P = {1, 1, 0, 0, 1, 1, 1};
    digitSeg S = {1, 0, 1, 1, 0, 1, 1};

    digitSeg b = {0, 0, 1, 1, 1, 1, 1};
    digitSeg c = {0, 0, 0, 1, 1, 0, 1};
    digitSeg d = {0, 1, 1, 1, 1, 0, 1};
    digitSeg g = {1, 1, 1, 1, 0, 1, 1};
    digitSeg h = {0, 0, 1, 0, 1, 1, 1};
    digitSeg l = {0, 0, 0, 0, 1, 1, 0};
    digitSeg n = {0, 0, 1, 0, 1, 0, 1};
    digitSeg p = {1, 1, 0, 0, 1, 1, 1};
    digitSeg qu = {1, 1, 1, 0, 0, 1, 1};
    digitSeg r = {0, 0, 0, 0, 1, 0, 1};
    digitSeg t = {0, 0, 0, 1, 1, 1, 1};
    digitSeg y = {0, 1, 1, 1, 0, 1, 1};
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Colour Variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Custom Colour Creator:
    // use CRGB Constructor to craete custom colours that can be passed to the display

    // Pick and Name Colours here, then add them to the colourArray to make them easily accessable

    CRGB skyBlue = CRGB(0, 80, 255); // Data structure for "skyroraBlue" colour as an RGB value

    CRGB pureBlue = CRGB(0, 0, 255);

    CRGB offWhite = CRGB(160, 255, 200); // data structure for an offwhite colour, all LEDs on max (these figures chave been calibrated to produce a cleaner white)

    CRGB yellowOrange = CRGB(255, 160, 0); // Holds Orange Colour as a nice contrast to the blue

    CRGB blackout = CRGB(0, 0, 0); // data structure holding "black" - all LEDS off.

    CRGB pureWhite = CRGB(255, 255, 255);

    CRGB currentColour; // data structure to hold the current LED colour

    CRGB colourArray[4] = {skyBlue, offWhite, yellowOrange, pureWhite}; // array to hold different colour data structures. Makes it easy to cycle through them

    uint8_t colourSelect = 0; // Variable to hold the current selected colour from colourArray

    void changeColourRGB(CRGB newColour);
    void changeColourStruc(CRGB newColour);
    void show();
    void setDigit_colourName(digitSeg input, int8_t digitNum, CRGB inputColour);
    void setDotsName(CRGB newColour);
    void setStringName(uint16_t start, uint16_t to, CRGB newColour);

    void flyingDigit(digitSeg in, CRGB inputColour, uint32_t animationDelay = 100);

    uint8_t currentBrightness;

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

private:
    uint8_t iteration = 0; // used for iterating animation effects through mulitple loops
};
