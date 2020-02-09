// Include the Control Surface library.
#include <Control_Surface.h>

// Instantiate a MIDI over USB interface.
USBMIDI_Interface midi;

const pin_t latchPin = 10;  // Pin connected to ST_CP of 74HC595
const pin_t dataPin  = 12;  // Pin connected to DS of 74HC595
const pin_t clockPin = 13;  // Pin connected to SH_CP of 74HC595

// Instantiate a shift register.
ShiftRegisterOut<16> sreg = { dataPin, clockPin, latchPin, MSBFIRST };

const AddressMatrix<4, 4> addresses = {{
  {48, 49, 50, 51},// Ableton drumrack map
  {44, 45, 46, 47},
  {40, 41, 42, 43},
  {36, 37, 38, 39},
}};

NoteButtonMatrix<4, 4> buttonmatrix = {
  {2, 3, 4, 5}, // row pins
  {6, 7, 8, 9},    // column pins
  addresses,    // address matrix
  CHANNEL_1,    // channel and cable number
};

// Instantiate the LEDs that will display the state of the incoming MIDI Note
// events.
MIDINoteLED leds[] = {
    { sreg.pin(0), {36, CHANNEL_1}}, // digital input pin, note number, [channel]
    { sreg.pin(1), {37, CHANNEL_1}},
    { sreg.pin(2), {38, CHANNEL_1}},
    { sreg.pin(3), {39, CHANNEL_1}},
    { sreg.pin(4), {40, CHANNEL_1}},
    { sreg.pin(5), {41, CHANNEL_1}},
    { sreg.pin(6), {42, CHANNEL_1}},
    { sreg.pin(7), {43, CHANNEL_1}},
    { sreg.pin(8), {44, CHANNEL_1}}, // digital input pin, note number, [channel]
    { sreg.pin(9), {45, CHANNEL_1}},
    { sreg.pin(10), {46, CHANNEL_1}},
    { sreg.pin(11), {47, CHANNEL_1}},
    { sreg.pin(12), {48, CHANNEL_1}},
    { sreg.pin(13), {49, CHANNEL_1}},
    { sreg.pin(14), {50, CHANNEL_1}},
    { sreg.pin(15), {51, CHANNEL_1}},
};

void setup() {
    // Initialize everything.
    Control_Surface.begin();
}

void loop() {
    // Update the control surface: read new MIDI events, and read all inputs.
    Control_Surface.loop();
}
