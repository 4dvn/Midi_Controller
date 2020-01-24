#include <Encoder.h>
#include <Control_Surface.h> 

USBMIDI_Interface midi;
//USBDebugMIDI_Interface midi = {115200};
const int speedMultiplier = 1;

Bank<4> bank(1); // 4 banks with 1 track per bank

// Selector that manages the bank setting
ManyButtonsSelectorLEDs<4> bankselector = {
  bank,
  {9, 13, 7, 11}, // button pins
  {8, 12, 6, 10}, // led pins
};

NoteButton buttonendecks[] = {
  { 9,{0x01, CHANNEL_1} }, // 
  {13,{0x02, CHANNEL_2} }, //
  { 7,{0x03, CHANNEL_3} }, // 
  {11,{0x04, CHANNEL_4} }, //
};

Bankable::CCRotaryEncoder enc[] = {
  {{bank, BankType::CHANGE_CHANNEL},{36, 37},0x0A,1,1,}, //JOG
  {{bank, BankType::CHANGE_CHANNEL},{46, 47},0x07,speedMultiplier,4,}, //
  {{bank, BankType::CHANGE_CHANNEL},{48, 49},0x06,speedMultiplier,4,}, //
  {{bank, BankType::CHANGE_CHANNEL},{50, 51},0x09,speedMultiplier,4,}, //
  {{bank, BankType::CHANGE_CHANNEL},{53, 52},0x08,speedMultiplier,4,}, //
};

Bankable::NoteButton buttonencoders[] = {
  {{bank, BankType::CHANGE_CHANNEL},42,{0x08, CHANNEL_1} }, // 
  {{bank, BankType::CHANGE_CHANNEL},43,{0x09, CHANNEL_1} }, //
  {{bank, BankType::CHANGE_CHANNEL},44,{0x06, CHANNEL_1} }, // 
  {{bank, BankType::CHANGE_CHANNEL},45,{0x07, CHANNEL_1} }, //
};

CD74HC4067 mux1 = {A4,{A0,A1,A2,A3} };
CCPotentiometer eqPotentiometers[] = {
  { mux1.pin(0), { 0x04, CHANNEL_4 } },
  { mux1.pin(1), { 0x03, CHANNEL_4 } },
  { mux1.pin(2), { 0x02, CHANNEL_4 } },
  { mux1.pin(3), { 0x01, CHANNEL_4 } },
  { mux1.pin(4), { 0x04, CHANNEL_3 } },
  { mux1.pin(5), { 0x03, CHANNEL_3 } },
  { mux1.pin(6), { 0x02, CHANNEL_3 } },
  { mux1.pin(7), { 0x01, CHANNEL_3 } },
  { mux1.pin(8), { 0x04, CHANNEL_2 } },
  { mux1.pin(9), { 0x03, CHANNEL_2 } },
  { mux1.pin(10), { 0x02, CHANNEL_2 } },
  { mux1.pin(11), { 0x01, CHANNEL_2 } },
  { mux1.pin(12), { 0x04, CHANNEL_1 } },
  { mux1.pin(13), { 0x03, CHANNEL_1 } },
  { mux1.pin(14), { 0x02, CHANNEL_1 } },
  { mux1.pin(15), { 0x01, CHANNEL_1 } },
};
 
CCPotentiometer cfPotentiometer = { A15, {0x00, CHANNEL_1} };

CCPotentiometer VolPotentiometer[] = {
  { A10, {0x05, CHANNEL_1} },
  { A11, {0x05, CHANNEL_2} },
  { A12, {0x05, CHANNEL_3} },
  { A13, {0x05, CHANNEL_4} },
};

CD74HC4067 mux2 = {A6,{A0,A1,A2,A3} };
Bankable::NoteButton button1[] = {
  {{bank, BankType::CHANGE_CHANNEL}, mux2.pin(0), { 0x0E, CHANNEL_1 } },
  {{bank, BankType::CHANGE_CHANNEL}, mux2.pin(1), { 0x0F, CHANNEL_1 } },
  {{bank, BankType::CHANGE_CHANNEL}, mux2.pin(2), { 0x10, CHANNEL_1 } },
  {{bank, BankType::CHANGE_CHANNEL}, mux2.pin(3), { 0x11, CHANNEL_1 } },
  {{bank, BankType::CHANGE_CHANNEL}, mux2.pin(4), { 0x12, CHANNEL_1 } },
  {{bank, BankType::CHANGE_CHANNEL}, mux2.pin(5), { 0x13, CHANNEL_1 } },
  {{bank, BankType::CHANGE_CHANNEL}, mux2.pin(6), { 0x14, CHANNEL_1 } },
  {{bank, BankType::CHANGE_CHANNEL}, mux2.pin(7), { 0x15, CHANNEL_1 } },
  {{bank, BankType::CHANGE_CHANNEL}, mux2.pin(8), { 0x16, CHANNEL_1 } }, //PLAY button
  {{bank, BankType::CHANGE_CHANNEL}, mux2.pin(9), { 0x17, CHANNEL_1 } }, //CUE button
  {{bank, BankType::CHANGE_CHANNEL}, mux2.pin(10), { 0x20, CHANNEL_1 } },
  {{bank, BankType::CHANGE_CHANNEL}, mux2.pin(11), { 0x21, CHANNEL_1 } },
  {{bank, BankType::CHANGE_CHANNEL}, mux2.pin(12), { 0x22, CHANNEL_1 } },
  {{bank, BankType::CHANGE_CHANNEL}, mux2.pin(13), { 0x23, CHANNEL_1 } },
  {{bank, BankType::CHANGE_CHANNEL}, mux2.pin(14), { 0x19, CHANNEL_1 } }, //CROSS button
  {{bank, BankType::CHANGE_CHANNEL}, mux2.pin(15), { 0x18, CHANNEL_1 } },
};

NoteValueLED noteLed1 [] = { 
  { 39, {0x0C, CHANNEL_1} },  // C0
  { 38, {0x0D, CHANNEL_1} },  // C#0
  { A14, {0x0E, CHANNEL_1} }, // D0
  { 39, {0x0C, CHANNEL_2} },  // C0
  { 38, {0x0D, CHANNEL_2} },  // C#0
  { A14, {0x0E, CHANNEL_2} }, // D0
  { 39, {0x0C, CHANNEL_3} },  // C0
  { 38, {0x0D, CHANNEL_3} },  // C#0
  { A14, {0x0E, CHANNEL_3} }, // D0
  { 39, {0x0C, CHANNEL_4} },  // C0
  { 38, {0x0D, CHANNEL_4} },  // C#0
  { A14, {0x0E, CHANNEL_4} }, // D0
};

CD74HC4067 mux3 = {A5,{A0,A1,A2,A3} };
Bankable::NoteButton button2[] = {
  {{bank, BankType::CHANGE_CHANNEL}, mux3.pin(0), { 0x24, CHANNEL_1 } },
  {{bank, BankType::CHANGE_CHANNEL}, mux3.pin(1), { 0x25, CHANNEL_1 } },
  {{bank, BankType::CHANGE_CHANNEL}, mux3.pin(2), { 0x26, CHANNEL_1 } },
  {{bank, BankType::CHANGE_CHANNEL}, mux3.pin(3), { 0x27, CHANNEL_1 } },
  {{bank, BankType::CHANGE_CHANNEL}, mux3.pin(4), { 0x28, CHANNEL_1 } },
  {{bank, BankType::CHANGE_CHANNEL}, mux3.pin(5), { 0x29, CHANNEL_1 } },
  {{bank, BankType::CHANGE_CHANNEL}, mux3.pin(6), { 0x2A, CHANNEL_1 } },
  {{bank, BankType::CHANGE_CHANNEL}, mux3.pin(7), { 0x2B, CHANNEL_1 } },
  {{bank, BankType::CHANGE_CHANNEL}, mux3.pin(8), { 0x2C, CHANNEL_1 } }, 
  {{bank, BankType::CHANGE_CHANNEL}, mux3.pin(9), { 0x2D, CHANNEL_1 } }, 
  {{bank, BankType::CHANGE_CHANNEL}, mux3.pin(10), { 0x2E, CHANNEL_1 } },
  {{bank, BankType::CHANGE_CHANNEL}, mux3.pin(11), { 0x2F, CHANNEL_1 } },
  {{bank, BankType::CHANGE_CHANNEL}, mux3.pin(12), { 0x30, CHANNEL_1 } },
  {{bank, BankType::CHANGE_CHANNEL}, mux3.pin(13), { 0x31, CHANNEL_1 } },
  {{bank, BankType::CHANGE_CHANNEL}, mux3.pin(14), { 0x32, CHANNEL_1 } }, 
  {{bank, BankType::CHANGE_CHANNEL}, mux3.pin(15), { 0x33, CHANNEL_1 } },
};

void setup() {
    Control_Surface.begin(); // Initialize Control Surface
  }
 
void loop() {
  Control_Surface.loop(); // Update the Control Surface
  }
