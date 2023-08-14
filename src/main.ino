#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <TimeLib.h>
#include <RTClib.h>

#include "segments.h"
// set Wi-Fi SSID and password
const char *ssid = "SSID";
const char *password = "PASSWORD";

/*

         .3.         .10              .19           .26
       2     4     9     11        18     20     25     27
       2     4     9     11   .15  18     20     25     27
         .7.         .14              .23           .30
       1     5     8     12   .16  17     21     24     28
       1     5     8     12        17     21     24     28
         .6.         .13              .22           .29    

       digit 0     digit 1          digit 2       digit 3





*/
RTC_DS3231 rtc;

bool Set_Time = false;
WiFiUDP ntpUDP;
// 'time.nist.gov' is used (default server) with +1 hour offset (3600 seconds) 60 seconds (60000 milliseconds) update interval
NTPClient timeClient(ntpUDP, "time.nist.gov", 19800, 60000); // GMT calculation >> GMT+5:30 : (5*3600)+(30*60) = 19800
uint8_t brightness = 150;
int period = 30000; // screen update interval
unsigned long time_now = -30000;
int Second, Minute, Hour;
#define TIME_FORMAT 12 // 12 = 12 hours format || 24 = 24 hours format

bool night_mode = false;
int brightness_threshold = 50;
#define LDR_PIN A0    // LDR pin
#define BUTTON_PIN 12 // Button pin

pixelSevenSegment Clock;
#define CURRENT_COLOUR Clock.currentColour // Macro to make main code more readable.
void setup()
{
    Serial.begin(115200);

    if (!rtc.begin())
    {
        Serial.println("Couldn't find RTC");
        Serial.flush();
        abort();
    }
    // attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), ISR, RISING);
    WiFi.begin(ssid, password);
    Serial.print("Connecting...");
    delay(1000);

    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("connected");

        Set_Time = true;
    }
    else
        Set_Time = false;
}

void loop()
{
    if (Set_Time)
    {
        timeClient.begin();

        // check WiFi connection status
        if (WiFi.status() == WL_CONNECTED)
        {
            timeClient.update();
            unsigned long unix_epoch = timeClient.getEpochTime(); // get UNIX Epoch time
            Second = second(unix_epoch);                          // get seconds
            Minute = minute(unix_epoch);                          // get minutes
            Hour = hour(unix_epoch);                              // get hours

            if (TIME_FORMAT == 12)
            {
                if (Hour >= 13)
                {
                    Hour = Hour - 12;
                }
                if (Hour == 00)
                {
                    Hour = 12;
                }
                else
                    Hour = Hour;
            }
            else if (TIME_FORMAT == 24)
            {
                Hour = Hour;
            }
            Serial.print(Hour);
            Serial.print(":");
            Serial.print(Minute);
            Serial.print(":");
            Serial.print(Second);
            Serial.println(" ");
            rtc.adjust(DateTime(2020, 1, 1, Hour, Minute, Second));
            Serial.println("Time Set");
            WiFi.disconnect();
            Set_Time = false;
        }
    }
    else
    {
        DateTime now = rtc.now();

        Second = now.second();
        Minute = now.minute();
        Hour = now.hour();

        if (TIME_FORMAT == 12)
        {
            if (Hour >= 13)
            {
                Hour = Hour - 12;
            }
            if (Hour == 00)
            {
                Hour = 12;
            }
            else
                Hour = Hour;
        }
        else if (TIME_FORMAT == 24)
        {
            Hour = Hour;
        }

        uint32_t sensor_val = analogRead(LDR_PIN);
        if (sensor_val < brightness_threshold)
        {
            brightness = 50;
            night_mode = true;
            time_now = -30000;
        }
        else if (sensor_val > brightness_threshold && night_mode)
        {
            ESP.restart();
        }

        while (millis() > time_now + period)
        {
            time_now = millis();
            Serial.print("Time Now : ");
            Serial.print(Hour);
            Serial.print(":");
            Serial.print(Minute);
            Serial.print(":");
            Serial.print(Second);
            Serial.println(" ");
            disp_Time(); // Show Time
        }
    }
}

void disp_Time()
{
    Clock.setDigitsBlank();
    Clock.setDigit(Clock.A, Hour / 10, Clock.currentColour);
    Clock.setDigit(Clock.B, Hour % 10, Clock.currentColour);
    Clock.setDigit(Clock.C, Minute / 10, Clock.currentColour);
    Clock.setDigit(Clock.A, Minute % 10, Clock.currentColour);
    Clock.setDigit(Clock.E, Second / 10, Clock.currentColour);
    Clock.setDigit(Clock.F, Second % 10, Clock.currentColour);
    Clock.show();
}
