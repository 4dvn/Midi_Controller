#include <Control_Surface.h>

USBMIDI_Interface midi;

// Instantiate a CCPotentiometer object

CCPotentiometer potentiometer1 = {A0, {MIDI_CC::Channel_Volume, CHANNEL_2},};

CCPotentiometer potentiometer2 = {A1, {MIDI_CC::Channel_Volume, CHANNEL_3},};

CCPotentiometer potentiometer3 = {A2, {MIDI_CC::Channel_Volume, CHANNEL_4},};

CCPotentiometer potentiometer4 = {A3, {MIDI_CC::Channel_Volume, CHANNEL_5},};

CCPotentiometer potentiometer5 = {A4, {MIDI_CC::Channel_Volume, CHANNEL_6},};

CCPotentiometer potentiometer6 = {A5, {MIDI_CC::Channel_Volume, CHANNEL_7},};

CCPotentiometer potentiometer7 = {A6, {MIDI_CC::Channel_Volume, CHANNEL_8},};

CCPotentiometer potentiometer8 = {A7, {MIDI_CC::Channel_Volume, CHANNEL_9},};

const AddressMatrix<8, 8> addresses = {{
  {71, 70, 69, 68, 87, 86, 85, 84}, 
  {75, 74, 73, 72, 91, 90, 89, 88},
  {79, 78, 77, 76, 95, 94, 93, 92},
  {84, 82, 81, 80, 99, 98, 97, 96},
  {55, 54, 53, 52, 39, 38, 37, 36},
  {59, 58, 57, 56, 43, 42, 41, 40},
  {63, 62, 61, 60, 47, 46, 45, 44},
  {66, 66, 65, 64, 51, 50, 49, 48}
};

NoteButtonMatrix<8, 8> buttonmatrix = {
  {0, 1, 2, 3, 4, 5, 6, 7}, // row pins
  {8, 9, 10, 11, 12, 13, 14},    // column pins
  addresses,    // address matrix
  CHANNEL_1,    // channel and cable number
};
