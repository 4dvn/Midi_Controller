#include <USBComposite.h>

//Note assignment 
struct Assignment {
  byte note;
  byte notePin;
//  byte ledPin;
};
struct State {
  byte currentPinStatus;
  byte prevPinStatus;
  bool tapCountFlag;
  int tapCount;
  bool heldNoteFlag;
};
struct ActionBuffer {
  Assignment assignment;
  State state;
};

//Data
const byte pinOFF = HIGH;
const byte pinON = LOW;
const byte loopDelay = 10;
const int tapDelay = 150;
const byte defaultPinValue = 2;
const byte boardLEDPin = 32;

State defaults = {defaultPinValue, defaultPinValue, false, 0, false};

//Pin 0 as LED output causes additional MIDI notes to be sent. (notes 0, 9, and 97... both ON and OFF commands are sent.)
//Pin 16 as LED output causes additional MIDI notes to be sent. (notes 0, 9, and 97... both ON and OFF commands are sent.)
//Using Pins 8, 9, 10, 17, 22, 23, 24, or 25 as LED output causes a suite of unintended MIDI notes to be sent.


Assignment assignments[] = {
  Assignment {note: 36, notePin: 0},
  Assignment {note: 37, notePin: 1},
  Assignment {note: 38, notePin: 2},
  Assignment {note: 39, notePin: 3},
  Assignment {note: 40, notePin: 4},
  Assignment {note: 41, notePin: 5},
  Assignment {note: 42, notePin: 6},
  Assignment {note: 43, notePin: 7},
  Assignment {note: 44, notePin: 8},
  Assignment {note: 45, notePin: 9},
  Assignment {note: 46, notePin: 10},
  Assignment {note: 47, notePin: 11},
  Assignment {note: 48, notePin: 12},
  Assignment {note: 49, notePin: 13},
  Assignment {note: 50, notePin: 14},
  Assignment {note: 51, notePin: 15},
};

ActionBuffer actionBuffers[sizeof(assignments)] = {};
USBMIDI midi;
void LEDOn() {
  if (digitalRead(boardLEDPin) == HIGH) {
    digitalWrite(boardLEDPin, LOW);
  }
};
void LEDOff() {
  if (digitalRead(boardLEDPin) == LOW) {
    digitalWrite(boardLEDPin, HIGH);
  }
};
void flashLED(byte qty) {
  for (int i = 0; i < qty; i++) {
    LEDOn();
    delay(10);
    LEDOff();
  }
};
void setup() {
  //From Example
  USBComposite.setProductId(0x0031);
  midi.begin();
  delay(1000);
  //Chris's Setup Code
  for (int i = 0; i < sizeof(assignments); i++) {
    Assignment thisAssignment = assignments[i];
    actionBuffers[i] = {assignments[i], defaults};
    pinMode(actionBuffers[i].assignment.notePin, INPUT_PULLUP);
//    pinMode(actionBuffers[i].assignment.ledPin, OUTPUT);
    //digitalWrite(actionBuffers[i].assignment.ledPin, LOW);
  };
  pinMode(boardLEDPin, OUTPUT);
  LEDOff();
}
void loop() {
  for (int i = 0; i < sizeof(assignments); i++) {
    //Shift existing pin value to 'previous' and check new status
    actionBuffers[i].state.prevPinStatus = actionBuffers[i].state.currentPinStatus;
    actionBuffers[i].state.currentPinStatus = digitalRead(actionBuffers[i].assignment.notePin);
    //If tap flag is on,
    if (actionBuffers[i].state.tapCountFlag == true) {
      //increment the tapDelayCount
      actionBuffers[i].state.tapCount += loopDelay;
      //if tap count is over the theshold
      if (actionBuffers[i].state.tapCount >= tapDelay) {
        //turn off the flag
        actionBuffers[i].state.tapCountFlag = false;
      };
    }
    //if tap flag is off
    if (actionBuffers[i].state.tapCountFlag == false) {
      //reset the counter
      actionBuffers[i].state.tapCount = 0;
    };

    //Skip the rest of this loop iteration if the pin has not changed
    if (actionBuffers[i].state.currentPinStatus != actionBuffers[i].state.prevPinStatus) {
      //If pin has changed to ON...
      /*else*/ if (actionBuffers[i].state.currentPinStatus == pinON) {
        //and the held note flag is off
        if (actionBuffers[i].state.heldNoteFlag == false) {
          //play note on
          midi.sendNoteOn(0, actionBuffers[i].assignment.note, 127);
          //and turn on tap count flag
          actionBuffers[i].state.tapCountFlag = true;
//         digitalWrite(actionBuffers[i].assignment.ledPin, HIGH);    
        }
        //but if the held note flag is on
        else {
          //clear the held note flag
          actionBuffers[i].state.heldNoteFlag = false;
        }
      }
      //If pin has changed from ON
      /*else*/ if (actionBuffers[i].state.prevPinStatus == pinON && actionBuffers[i].state.currentPinStatus != pinON) {
        //and if tap count flag is OFF
        if (actionBuffers[i].state.tapCountFlag == false) {
          //turn note off
          midi.sendNoteOff(0, actionBuffers[i].assignment.note, 127);
//         digitalWrite(actionBuffers[i].assignment.ledPin, LOW);    
        }
        //but if tap count flag is ON
        else {
          //throw the held note flag.
          actionBuffers[i].state.heldNoteFlag = true;
          //And clear the tap count flag
          actionBuffers[i].state.tapCountFlag = false;
          flashLED(1);
        }
      }
    }
  };
  delay(loopDelay);
  //flashLED(2);
}
