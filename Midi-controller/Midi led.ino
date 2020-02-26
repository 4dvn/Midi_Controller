//This sketch was specially made for Orange_Murker and phanacyt youtube channels.
//This sketch has the backlight suport

//MIDI Libaries
#include <MIDI_controller.h>
#include <MIDIUSB.h>

//Backlight Setup
#include <Adafruit_NeoPixel.h>
#define PIN 15
#define NUMPIXELS 1
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//Buttons
const static byte velocity = 127;
const static byte C4 = 60;

Digital button1(14, C4, 1, velocity);
Digital button2(4, C4+1, 1, velocity);
Digital button3(5, C4+2, 1, velocity);
Digital button4(6, C4+3, 1, velocity);
Digital button5(7, C4+4, 1, velocity);
Digital button6(8, C4+5, 1, velocity);
Digital button7(9, C4+6, 1, velocity);
Digital button8(10, C4+7, 1, velocity);
Digital button9(16, C4+8, 1, velocity);

//Potentioeters
const static byte Channel_Volume = 0x7;
const static size_t analogAverage = 8;

Analog potent1(A0, Channel_Volume, 1);
Analog potent2(A1, Channel_Volume, 2);
Analog potent3(A2, Channel_Volume, 3);

//Encoder
const byte Channel = 1;
const byte Controller = 0x14;
const int speedMultiply = 1;
RotaryEncoder enc(2, 3, Controller, Channel, speedMultiply, JOG, POS1_NEG127);


void setup(){
  //Initialize Backlight
  pixels.begin(); // This initializes the NeoPixel library.
  pixels.setBrightness(255); // Set brightness

  //Initialize MIDI
  USBMidiController.blink(LED_BUILTIN);
  USBMidiController.setDelay(15);
  USBMidiController.begin();
  delay(1000);
  potent1.average(analogAverage);
  potent2.average(analogAverage);
  potent3.average(analogAverage);

}


// Converts a color from HSV to RGB.
// h is hue, as a number between 0 and 360.
// s is the saturation, as a number between 0 and 255.
// v is the value, as a number between 0 and 255.
uint32_t hsvToRgb(uint16_t h, uint8_t s, uint8_t v)
{
    uint8_t f = (h % 60) * 255 / 60;
    uint8_t p = (255 - s) * (uint16_t)v / 255;
    uint8_t q = (255 - f * (uint16_t)s / 255) * (uint16_t)v / 255;
    uint8_t t = (255 - (255 - f) * (uint16_t)s / 255) * (uint16_t)v / 255;
    uint8_t r = 0, g = 0, b = 0;
    switch((h / 60) % 6){
        case 0: r = v; g = t; b = p; break;
        case 1: r = q; g = v; b = p; break;
        case 2: r = p; g = v; b = t; break;
        case 3: r = p; g = q; b = v; break;
        case 4: r = t; g = p; b = v; break;
        case 5: r = v; g = p; b = q; break;
    }
    return pixels.Color(r, g, b);
}

void loop(){
//Refreshes all of the controls
  button1.refresh();
  button2.refresh();
  button3.refresh();
  button4.refresh();
  button5.refresh();
  button6.refresh();
  button7.refresh();
  button8.refresh();
  button9.refresh();

  potent1.refresh();
  potent2.refresh();
  potent3.refresh();

  enc.refresh();

   // Backlight Update
  uint16_t time = millis() >> 4;
  for(int i=0;i<NUMPIXELS;i++){
    byte x = (time >> 2) - (i << 3);
    pixels.setPixelColor(i, hsvToRgb((uint32_t)x * 359 / 256, 255, 255));
  pixels.show(); // This sends the updated pixel color to the hardware.
  }
}
