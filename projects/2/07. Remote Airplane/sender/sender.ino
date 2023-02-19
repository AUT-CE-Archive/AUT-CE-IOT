#include <Keypad.h>
#include <SoftwareSerial.h>

const byte ROWS = 4; 
const byte COLS = 3; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[ROWS] = {10, 9, 8, 7}; 
byte colPins[COLS] = {13, 12, 11}; 

Keypad pad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup() {
  Serial.begin(9600); // xBee
}

void loop() {
  char key = pad.getKey();
  if (key != NO_KEY) {
    Serial.write(key);
  }
}
