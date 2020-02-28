#include <Control_Surface.h>

USBMIDI_Interface midi;

// The note numbers corresponding to the buttons in the matrix
const AddressMatrix<8, 8> addresses = {{
  {71, 70, 69, 68, 87, 86, 85, 84}, 
  {75, 74, 73, 72, 91, 90, 89, 88},
  {79, 78, 77, 76, 95, 94, 93, 92},
  {83, 82, 81, 80, 99, 98, 97, 96},
  {55, 54, 53, 52, 39, 38, 37, 36},
  {59, 58, 57, 56, 43, 42, 41, 40},
  {63, 62, 61, 60, 47, 46, 45, 44},
  {67, 66, 65, 64, 51, 50, 49, 48}
}};

NoteButtonMatrix<8,8> buttonmatrix = {
  {2, 3, 4, 5, 6, 7, 8, 9}, // row pins
  {10, 14, 15, 16, A0, A1, A2, A3},    // column pins
  addresses,    // address matrix
  CHANNEL_1,    // channel and cable number
};

void setup() {
  Control_Surface.begin();
}

void loop() {
  Control_Surface.loop();
}