#include <Control_Surface.h> // Include the Control Surface library

// Instantiate a MIDI over USB interface.
USBMIDI_Interface midi;

// Instantiate a CCPotentiometer object
CCPotentiometer fader1 = {A0,{MIDI_CC::Channel_Volume, CHANNEL_1},};
CCPotentiometer fader2 = {A1,{MIDI_CC::Channel_Volume, CHANNEL_2},};
CCPotentiometer fader3 = {A2,{MIDI_CC::Channel_Volume, CHANNEL_3},};
CCPotentiometer fader4 = {A3,{MIDI_CC::Channel_Volume, CHANNEL_4},};
CCPotentiometer fader5 = {A4,{MIDI_CC::Channel_Volume, CHANNEL_5},};
CCPotentiometer fader6 = {A5,{MIDI_CC::Channel_Volume, CHANNEL_6},};
CCPotentiometer fader7 = {A6,{MIDI_CC::Channel_Volume, CHANNEL_7},};
CCPotentiometer fader8 = {A7,{MIDI_CC::Channel_Volume, CHANNEL_8},};
void setup() {
  Control_Surface.begin(); // Initialize Control Surface
}

void loop() {
  Control_Surface.loop(); // Update the Control Surface
}
