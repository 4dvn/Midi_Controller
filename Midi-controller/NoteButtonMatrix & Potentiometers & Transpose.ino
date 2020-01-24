#include <Control_Surface.h>

USBMIDI_Interface midi;
CCPotentiometer potentiometer1(A0, {MIDI_CC::Channel_Volume, CHANNEL_2});
CCPotentiometer potentiometer2(A1, {MIDI_CC::Channel_Volume, CHANNEL_3});
CCPotentiometer potentiometer3(A2, {MIDI_CC::Channel_Volume, CHANNEL_4});
CCPotentiometer potentiometer4(A3, {MIDI_CC::Channel_Volume, CHANNEL_5});
// Transposer to go +1 to -1 octave
Transposer<-2, +2> transposer(16);
IncrementDecrementSelector<transposer.getNumberOfBanks()> transposeSelector = {
  transposer,
  {14, 15}, // Press push button A0 → +1 octave, A1 → -1 octave, A0+A1 → reset
  Wrap::Clamp,
};




AddressMatrix<4, 4> notes = {{
  {51, 50, 49, 48},
  {47, 46, 45, 44},
  {43, 42, 41, 40},
  {39, 38, 37, 36},
}};
 
Bankable::NoteButtonMatrix<4, 4> buttons = {
  transposer, // bank/transposer
  {2, 3, 4, 5},     // row pins (outputs, driven low-Z low !)
  {6, 7, 8, 9},  // column pins (inputs, hi-Z)
  notes,      // note numbers
  CHANNEL_1,  // MIDI channel / cable
};

void setup() {
  Control_Surface.begin();
}

void loop() {
  Control_Surface.loop();
}
