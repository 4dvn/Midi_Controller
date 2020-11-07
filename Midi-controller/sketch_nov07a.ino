#include <Control_Surface.h>

// Helper for using multiple banks with different offsets with
// a single selector.
template <setting_t N, size_t M>
struct MultiBank : public Selectable<N> {
  MultiBank(const Array<Bank<N>, M> &banks) : banks(banks) {}
  void select(setting_t bankSetting) override {
    for (auto &bank : banks)
      bank.select(bankSetting);
  }
  Bank<N> &operator[](size_t i) { return banks[i]; }
  const Bank<N> &operator[](size_t i) const { return banks[i]; }
  Array<Bank<N>, M> banks;
};

// Two times 4 banks, one has an offset of 4, because the addresses
// of the potentiometers go up by 4 for each bank, and the other has
// an offset of 8, because the addresses of the buttons go up by 8
// for each bank.
MultiBank<4, 2> banks = {{ 4, 8 }};

// The small back button. When pressed, it allows you to change the
// bank by pressing one of the 4 first colored buttons.
Button bankButton = 11;
// The main selector, just selects the bank of the button that's
// pressed.
ManyButtonsSelector<4> selector = {banks, {2, 3, 4, 5}};

Bankable::CCPotentiometer knobs[] = {
  {banks[0], A0, 102},
  {banks[0], A1, 103},
  {banks[0], A2, 104},
  {banks[0], A3, 105},
  
  {banks[1], A0, 106},
  {banks[1], A1, 107},
  {banks[1], A2, 108},
  {banks[1], A3, 109},

  {banks[2], A0, 110},
  {banks[2], A1, 111},
  {banks[2], A2, 112},
  {banks[2], A3, 113},

  {banks[3], A0, 114},
  {banks[3], A1, 115},
  {banks[3], A2, 116},
  {banks[3], A3, 117},
};

Bankable::NoteButton buttons[] = {
  {banks[0], 2, 52}, // Note that the first 4 NoteButtons use the
  {banks[0], 3, 53}, // same pins as the bank selector
  {banks[0], 4, 54},
  {banks[0], 5, 55},
  {banks[0], 6, 56},
  {banks[0], 7, 57},
  {banks[0], 8, 58},
  {banks[0], 9, 59},

  {banks[1], 2, 60}, // Note that the first 4 NoteButtons use the
  {banks[1], 3, 61}, // same pins as the bank selector
  {banks[1], 4, 62},
  {banks[1], 5, 63},
  {banks[1], 6, 64},
  {banks[1], 7, 65},
  {banks[1], 8, 66},
  {banks[1], 9, 67},

  {banks[2], 2, 68}, // Note that the first 4 NoteButtons use the
  {banks[2], 3, 69}, // same pins as the bank selector
  {banks[2], 4, 70},
  {banks[2], 5, 71},
  {banks[2], 6, 72},
  {banks[2], 7, 73},
  {banks[2], 8, 74},
  {banks[2], 9, 75},

  {banks[3], 2, 76}, // Note that the first 4 NoteButtons use the
  {banks[3], 3, 77}, // same pins as the bank selector
  {banks[3], 4, 78},
  {banks[3], 5, 79},
  {banks[3], 6, 80},
  {banks[3], 7, 81},
  {banks[3], 8, 82},
  {banks[3], 9, 83},
};

USBMIDI_Interface midi;

void setup() {
  bankButton.begin();
  Control_Surface.begin();
  // Disable the bank selector, by default the buttons are used for 
  // the NoteButtons
  Selector<4>::disable(selector);
}

void loop() {
  if (bankButton.update() == Button::Falling) {
    // If the small button is pressed, disable the NoteButtons, and
    // use the buttons to select the bank by enabling the selector.
    Bankable::NoteButton::disable(buttons);
    ManyButtonsSelector<4>::enable(selector);
  } else if (bankButton.getState() == Button::Rising) {
    // If the small button is released, do the reverse, disable the
    // selector and enable the NoteButtons again.
    ManyButtonsSelector<4>::disable(selector);
    Bankable::NoteButton::enable(buttons);
  }
  Control_Surface.loop();
}
