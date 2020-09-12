#include <FastLED.h>
#include "Wire.h"
#include <MPU6050_light.h>

// How many leds in your strip? 28
#define NUM_LEDS 28

// For led chips like WS2812, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
// Clock pin only needed for SPI based chipsets when not using hardware SPI
#define DATA_PIN 2
#define CLOCK_PIN 13

// Define the array of leds
CRGB leds[NUM_LEDS];


MPU6050 mpu(Wire);
unsigned long timer = 0;


void setup() {
  // Uncomment/edit one of the following lines for your leds arrangement.
  // ## Clockless types ##
  Serial.begin(9600);
  Wire.begin();
  mpu.begin();
  Serial.println(F("Calculating gyro offset, do not move MPU6050"));
  delay(1000);
  mpu.calcGyroOffsets();
  Serial.println("Done!\n");
  
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);  // GRB ordering is assumed

}

void loop() {
  static uint8_t hue = 0;
  

  mpu.update();
  // y goes from -90 to 90
  

  FastLED.showColor(CHSV(map(mpu.getAngleY(), -90, 90, 0, 255), 255, 255));  
  
}
