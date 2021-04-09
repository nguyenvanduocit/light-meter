#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "BH1750.h"

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);
BH1750 bh1750;

// ev = log 2 ( (aperture^2) / t )
// ev2 = log 2 (lux*ISO/K)
// => t = ((aperture^2) * K)/(lux*ISO)
float lux = 0;
float iso = 200;
float aperture = 2.8;
float speed = 1 / 5;
float K = 250; // Constant

void setup()
{
    Serial.begin(115200);

    bh1750.begin(BH1750::CONTINUOUS_HIGH_RES_MODE, 0x23, &Wire);
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

    display.display();
    delay(1000);
    display.clearDisplay();
    display.display();

    display.setTextSize(1.5);
    display.setTextColor(SSD1306_WHITE);
}

void loop()
{
    if (bh1750.measurementReady())
    {
        lux = bh1750.readLightLevel();
        display.clearDisplay();
        display.setCursor(0, 0);
        display.print("Lux: ");
        display.println(lux);

        float speed = ((aperture * aperture) * K) / (lux * iso);

        display.print("Speed: ");
        display.println(speed);

        display.display();
    }

    delay(100);
}
