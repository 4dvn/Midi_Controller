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

// Transposer to go +1 to -1 octave
Transposer<-2, +2> transposer(16);
IncrementDecrementSelector<transposer.getNumberOfBanks()> transposeSelector = {
  transposer,
  {15, 16}, // Press push button A0 → +1 octave, A1 → -1 octave, A0+A1 → reset
  Wrap::Clamp,
};

const AddressMatrix<8, 8> addresses = {{
  {55, 54, 53, 52, 71, 70, 69, 68}, 
  {59, 58, 57, 56, 75, 74, 73, 72},
  {63, 62, 61, 60, 79, 78, 77, 76},
  {67, 66, 65, 64, 83, 82, 81, 80},
  {39, 38, 37, 36, 23, 22, 21, 20},
  {43, 42, 41, 40, 27, 26, 25, 24},
  {47, 46, 45, 44, 31, 30, 29, 28},
  {51, 50, 49, 48, 35, 34, 33, 32}
};

NoteButtonMatrix<8, 8> buttonmatrix = {
  {0, 1, 2, 3, 4, 5, 6, 7}, // row pins
  {8, 9, 10, 11, 12, 13, 14},    // column pins
  addresses,    // address matrix
  CHANNEL_1,    // channel and cable number
};
