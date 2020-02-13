#include <Control_Surface.h>

USBMIDI_Interface midi;

Bank<8> bank(1);
//   │       └───── number of tracks per bank
//   └───────────── number of banks

// Instantiate a Bank selector to control which one of the four Banks is active.
IncrementDecrementSelector<4> selector = {
    bank,       // Bank to manage
    {17, 18},     // push button pins (increment, decrement)
    Wrap::Wrap, // Wrap around
};

// Wrapping around means that if you're in Bank 4 and you press the increment 
// button, you wrap back around to Bank 1. Similarly, if you're in Bank 1 and
// you press the decrement button, you wrap back around to Bank 4.
// The alternative to Wrap::Wrap is Wrap::Clamp. In that case, pressing the 
// increment button when you're in Bank 4 won't do anything, you'll stay in 
// Bank 4. If you're in Bank 1 and press the decrement button, you'll stay in 
// Bank 1.

// Instantiate two potentiometers for the volume controls.
Bankable::CCPotentiometer potentiometer1 = {{bank, BankType::CHANGE_CHANNEL}, A0, {MIDI_CC::Channel_Volume, CHANNEL_2},};

Bankable::CCPotentiometer potentiometer2 = {{bank, BankType::CHANGE_CHANNEL}, A1, {MIDI_CC::Channel_Volume, CHANNEL_3},};

Bankable::CCPotentiometer potentiometer3 = {{bank, BankType::CHANGE_CHANNEL}, A2, {MIDI_CC::Channel_Volume, CHANNEL_4},};

Bankable::CCPotentiometer potentiometer4 = {{bank, BankType::CHANGE_CHANNEL}, A3, {MIDI_CC::Channel_Volume, CHANNEL_5},};

Bankable::CCPotentiometer potentiometer5 = {{bank, BankType::CHANGE_CHANNEL}, A4, {MIDI_CC::Channel_Volume, CHANNEL_6},};

Bankable::CCPotentiometer potentiometer6 = {{bank, BankType::CHANGE_CHANNEL}, A5, {MIDI_CC::Channel_Volume, CHANNEL_7},};

Bankable::CCPotentiometer potentiometer7 = {{bank, BankType::CHANGE_CHANNEL}, A6, {MIDI_CC::Channel_Volume, CHANNEL_8},};

Bankable::CCPotentiometer potentiometer8 = {{bank, BankType::CHANGE_CHANNEL}, A0, {MIDI_CC::Channel_Volume, CHANNEL_9},};

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
void setup() {
  Control_Surface.begin(); // Initialize Control Surface
}

void loop() {
  Control_Surface.loop(); // Update the Control Surface
}
