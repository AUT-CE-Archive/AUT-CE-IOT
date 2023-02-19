#include <Keypad.h>
#include <SoftwareSerial.h>

const byte ROWS = 4; 
const byte COLS = 4; 

char hexaKeys[ROWS][COLS] = {
  {'7', '8', '9', '/'},
  {'4', '5', '6', '*'},
  {'1', '2', '3', '-'},
  {' ', '0', '=', '+'}
};

byte rowPins[ROWS] = {6, 7, 8, 9}; 
byte colPins[COLS] = {10, 11, 12, 13}; 

Keypad pad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
SoftwareSerial xBee(3, 2);

void setup() {
  xBee.begin(9600);
}

void loop() {
  char key = pad.getKey();
  if (key != NO_KEY) {
    xBee.write(key);
  }
}
