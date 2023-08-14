
#include "segments.h"

void pixelSevenSegment::sevenSegSetup(byte brightness)
{

    FastLED.addLeds<WS2812B, 22, GRB>(ledString, TOTAL_LEDS); // This sets up our LED string object

    // set master brightness control
    FastLED.setBrightness(brightness);
    // Sets the brightness for the entire string
    currentBrightness = brightness;
}

void pixelSevenSegment::flyingDigit(digitSeg in, CRGB inputColour, uint32_t animationDelay)
{
    int iteration = 0; // this variable needs to be external
    pixelSevenSegment::setDigit_colourName(in, iteration, inputColour);
    iteration++;
}

void pixelSevenSegment::setAllDigitsX(digitSeg X, CRGB color)
{

    pixelSevenSegment::setDigit(X, 0, color);
    pixelSevenSegment::setDigit(X, 1, color);
    pixelSevenSegment::setDigit(X, 2, color);
    pixelSevenSegment::setDigit(X, 3, color);
    pixelSevenSegment::setDigit(X, 4, color);
    pixelSevenSegment::setDigit(X, 5, color);
}

void pixelSevenSegment::setDigitsBlank()
{ // Method to set all digits to black (off)

    pixelSevenSegment::setDigit(alldigits[8], 0, CRGB::Black); // Passed Arguments (digitSeg.bitarray, digitNumber, red, green, blue)
    pixelSevenSegment::setDigit(alldigits[8], 1, CRGB::Black); // Passed Arguments (digitSeg.bitarray, digitNumber, red, green, blue)
    pixelSevenSegment::setDigit(alldigits[8], 2, CRGB::Black); // Passed Arguments (digitSeg.bitarray, digitNumber, red, green, blue)
    pixelSevenSegment::setDigit(alldigits[8], 3, CRGB::Black); // Passed Arguments (digitSeg.bitarray, digitNumber, red, green, blue)
    pixelSevenSegment::setDigit(alldigits[8], 4, CRGB::Black); // Passed Arguments (digitSeg.bitarray, digitNumber, red, green, blue)
    pixelSevenSegment::setDigit(alldigits[8], 5, CRGB::Black); // Passed Arguments (digitSeg.bitarray, digitNumber, red, green, blue)
}
void pixelSevenSegment::show()
{
    FastLED.show();
}
// this function needs to be a method for a "digit" object but I couldn't work out how to do that.
// This method is slightly more inelegent but it should work (UNTESTED with more than 1 digit but confident it will function)

void pixelSevenSegment::setDigit_colourName(digitSeg input, int8_t digitNum, CRGB inputColour)
{

    pixelSevenSegment::setDigit(input, digitNum, inputColour);
}

void pixelSevenSegment::
    setDigit(digitSeg current, int8_t digitNumber, CRGB color)
{ // This function sets the first digit based on the data structure passed to it.

    // A new instance of digitSeg has been set up ready to take whatever data is placed into it
    // After this,  a variable to denote which digit we are setting is passed as an argument.
    // Also passed to function - rgb colour value, which sets the colour for the entire digit

    uint16_t q = ((digitNumber) * (LED_PER_SEG * 7)); // This variable is added onto the array numbers, advancing down the LED array as each successive digit is selected to be written to.

    // Serial.println(q);
    //  Above algorithm may need updating once dots are added, as to sync any animated lighting effects, the led addresses for the : : Dots needs to come between the ids for each digit

    int16_t s = 0; // Addr to advance the array through each segement of each digit

    if (current.A)
    {
        ledString((s + q), (s + LED_PER_SEG + q - 1)) = color;
    }
    else
    {
        ledString((s + q), (s + LED_PER_SEG + q - 1)) = CRGB::Black;
    }

    s = (LED_PER_SEG);

    if (current.B)
    {
        ledString((s + q), (s + LED_PER_SEG + q - 1)) = color;
    }
    else
    {
        ledString((s + q), (s + LED_PER_SEG + q - 1)) = CRGB::Black;
    }

    s = ((LED_PER_SEG)*2);

    if (current.C)
    {
        ledString((s + q), (s + LED_PER_SEG + q - 1)) = color;
    }
    else
    {
        ledString((s + q), (s + LED_PER_SEG + q - 1)) = CRGB::Black;
    }

    s = ((LED_PER_SEG)*3);

    if (current.D)
    {
        ledString((s + q), (s + LED_PER_SEG + q - 1)) = color;
    }
    else
    {
        ledString((s + q), (s + LED_PER_SEG + q - 1)) = CRGB::Black;
    }

    s = ((LED_PER_SEG)*4);

    if (current.E)
    {
        ledString((s + q), (s + LED_PER_SEG + q - 1)) = color;
    }
    else
    {
        ledString((s + q), (s + LED_PER_SEG + q - 1)) = CRGB::Black;
    }

    s = ((LED_PER_SEG)*5);

    if (current.F)
    {
        ledString((s + q), (s + LED_PER_SEG + q - 1)) = color;
    }
    else
    {
        ledString((s + q), (s + LED_PER_SEG + q - 1)) = CRGB::Black;
    }

    s = ((LED_PER_SEG)*6);

    if (current.G)
    {
        ledString((s + q), (s + LED_PER_SEG + q - 1)) = color;
    }
    else
    {
        ledString((s + q), (s + LED_PER_SEG + q - 1)) = CRGB::Black;
    }
}

// After all the arrays for the digits, ID for the dots starts again at ID:

//  (LED_PER_SEG * 7)* 6 to ((LED_PER_SEG * 7)* 6) + 4

void pixelSevenSegment::setDotsRGB(CRGB color)
{

    int16_t d = (LEDS_IN_TPLUS + (LED_PER_SEG * 7) * 6);

    ledString(d, (d + 4)) = color;
}

void pixelSevenSegment::setDotsName(CRGB newColour)
{

    int16_t d = (LEDS_IN_TPLUS + (LED_PER_SEG * 7) * 6);

    ledString(d, (d + 4)) = CRGB(newColour.r, newColour.g, newColour.b);
}

void pixelSevenSegment::setStringRGB(uint16_t start, uint16_t to, CRGB color)
{
    ledString(start, to) = color;
}

void pixelSevenSegment::setStringName(uint16_t start, uint16_t to, CRGB newColour)
{
    ledString(start, to) = CRGB(newColour.r, newColour.g, newColour.b);
}

void pixelSevenSegment::changeColourRGB(CRGB newColour)
{

    currentColour = newColour;
}

void pixelSevenSegment::changeColourStruc(CRGB newColour)
{

    currentColour = newColour;
}

void pixelSevenSegment::changeBrightness(byte bright)
{

    currentBrightness = bright;
    FastLED.setBrightness(bright);
}