
 *   - 10: 74HC595 ST_CP
 *   - 12: 74HC595 DS
 *   - 13: 74HC595 SH_CP
 *   - 18: 74HC4051 A (COM OUT/IN)
 *   - 19: 74HC4051 S0
 *   - 20: 74HC4051 S1
 *   - 21: 74HC4051 S2


// Include the Control Surface library.
#include <Control_Surface.h>

// Instantiate a MIDI over USB interface.
USBMIDI_Interface midi;

const pin_t latchPin = 10;  // Pin connected to ST_CP of 74HC595
const pin_t dataPin  = 12;  // Pin connected to DS of 74HC595
const pin_t clockPin = 13;  // Pin connected to SH_CP of 74HC595

// Instantiate a shift register.
ShiftRegisterOut<8> sreg = { dataPin, clockPin, latchPin, MSBFIRST };

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
    { sreg.pin(0), MCU::MUTE_1 }, // digital input pin, note number, [channel]
    { sreg.pin(1), MCU::MUTE_2 },
    { sreg.pin(2), MCU::MUTE_3 },
    { sreg.pin(3), MCU::MUTE_4 },
    { sreg.pin(4), MCU::MUTE_5 },
    { sreg.pin(5), MCU::MUTE_6 },
    { sreg.pin(6), MCU::MUTE_7 },
    { sreg.pin(7), MCU::MUTE_8 },
};

void setup() {
    // Initialize everything.
    Control_Surface.begin();
}

void loop() {
    // Update the control surface: read new MIDI events, and read all inputs.
    Control_Surface.loop();
}
