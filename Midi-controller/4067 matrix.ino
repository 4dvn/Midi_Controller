//#include <frequencyToNote.h>
#include <MIDIUSB.h>
//#include <pitchToFrequency.h>
//#include <pitchToNote.h>

#include <MIDI_Controller.h>

// Create an instance of 'AnalogMultiplex' with the output pin of the multiplexer connected to
// pin 2 and the address pins connected to pins 3, 4 and 5.
// AnalogMultiplex(pin_t analogPin, { pin_t addressPin1, addressPin2, ... addressPinN } )
AnalogMultiplex multiplexer(2, { 3, 4, 5 } );


const uint8_t velocity = 0b1111111; // Maximum velocity (0b1111111 = 0x7F = 127)
const uint8_t addresses[8][8] = {
  { 1,  2,  3,  4,  5,  6,  7,  8  },
  { 9,  10, 11, 12, 13, 14, 15, 16 },
  { 17, 18, 19, 20, 21, 22, 23, 24 },
  { 25, 26, 27, 28, 29, 30, 31, 32 },
  { 33, 34, 35, 36, 37, 38, 39, 40 },
  { 41, 42, 43, 44, 45, 46, 47, 48 },
  { 49, 50, 51, 52, 53, 54, 55, 56 },
  { 57, 58, 59, 60, 61, 62, 63, 64 }
};

// Create a new instance of the class 'ButtonMatrix', called 'buttonmatrix', with dimensions 8 rows and 8 columns, with the rows connected to pins 6..13
// and the columns connected to multiplexer pins 0..7, that sends MIDI messages with the notes specified in 'addresses' on MIDI channel 1, with velocity 127
ButtonMatrix<8, 8> buttonmatrix({6, 7, 8, 9, 10, 11, 12, 13}, {multiplexer.pin(0), multiplexer.pin(1), multiplexer.pin(2), multiplexer.pin(3), multiplexer.pin(4), multiplexer.pin(5), multiplexer.pin(6), multiplexer.pin(7),}, addresses, 1, velocity);

void setup() {}

void loop() {
  // Refresh the buttons and send changes over MIDI
  MIDI_Controller.refresh();
}
