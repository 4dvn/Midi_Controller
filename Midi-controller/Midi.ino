//This sketch was specially made for Orange_Murker and phanacyt youtube channels.

//MIDI Libaries
#include <MIDI_controller.h>
#include <MIDIUSB.h>

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

//Potentiometers
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
   //Initialize MIDI
  USBMidiController.blink(LED_BUILTIN);
  USBMidiController.setDelay(15);
  USBMidiController.begin();
  delay(1000);
  potent1.average(analogAverage);
  potent2.average(analogAverage);
  potent3.average(analogAverage);

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
}
