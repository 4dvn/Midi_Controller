#include "MIDI_Controller.h" // Include the library
const uint8_t velocity = 0b1111111; // Maximum velocity (0b1111111 = 0x7F = 127)
const uint8_t addresses[8][8] = {   // the note numbers corresponding to the buttons in the matrix
//////////////////////////////////collum {10, 11, 12, 13, A0, A1, A2, A3} (left to right)
  {64, 65, 66, 67, 96, 97, 98, 99}, // row {2, 3, 4, 5, 6, 7, 8, 9} (up to down)
  {60, 61, 62, 63, 92, 93, 94, 95},
  {56, 57, 58, 59, 88, 89, 90, 91},
  {52, 53, 54, 55, 84, 85, 86, 87},
  {48, 49, 50, 51, 80, 81, 82, 83},
  {44, 45, 46, 47, 76, 77, 78, 79},
  {40, 41, 42, 43, 72, 73, 74, 75},
  {36, 37, 38, 39, 68, 69, 70, 71}
};

// Create a new instance of the class 'ButtonMatrix', called 'buttonmatrix', with dimensions 8 rows and 8 columns, with the rows connected to pins 2, 3, 4, 5, 6, 7, 8, 9
// and the columns connected to pins 10, 11, 12, 13, A0, A1, A2, A3  that sends MIDI messages with the notes specified in 'addresses' on MIDI channel 3, with velocity 127
ButtonMatrix<8, 8> buttonmatrix({2, 3, 4, 5, 6, 7, 8, 9}, {10, 11, 12, 13, A0, A1, A2, A3}, addresses, 3, velocity);

void setup() {
  
 
}
void loop() {
  // Refresh the buttons (check whether the states have changed since last time, if so, send it over MIDI)
  MIDI_Controller.refresh();

}
