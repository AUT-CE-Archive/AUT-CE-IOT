#include <Arduino.h>
#include "HX711.h"
#include <Servo.h>
#include <SoftwareSerial.h>

HX711 scale;
Servo servo;
SoftwareSerial serial(6, 7);

// variables
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;
const int WEIGHT_THRESHOLD = 3;
const int GREEN_LED = 13;
const int RED_LED = 12;
const int SERVO = 11;
const int BUZZER = 10;
const int DOOR_OPEN_WAIT = 3000;

void setup() {
  serial.begin(9600);
  servo.attach(SERVO);

  // Scale
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(36.059);
  scale.tare(); // reset the scale to 0

  // Pins
  pinMode(GREEN_LED , OUTPUT);
  digitalWrite(GREEN_LED, LOW);
  pinMode(RED_LED , OUTPUT);
  digitalWrite(RED_LED, LOW);
  pinMode(BUZZER , OUTPUT);
}

void loop() {

  int weight = scale.get_units()/1000 + 5;

  serial.print("Weight in KG:\t");
  serial.println(weight, 1);

  if (weight < WEIGHT_THRESHOLD) {
    serial.println("Not Enough Food!");
    notEnoughFood();
  } else {
    serial.println("Enough Food! Opening Door..");
    openDoor();
    serial.println("Closing Door..");
  }

  delay(1000);
}


void notEnoughFood() {
  digitalWrite(RED_LED, HIGH);  // Turn on red LED
  digitalWrite(BUZZER, HIGH);  // Activate buzzer
  digitalWrite(GREEN_LED, LOW);  // Turn off green LED
}

void openDoor() {
  digitalWrite(RED_LED, LOW);  // Turn off red LED
  digitalWrite(BUZZER, LOW);  // Deactivate buzzer
  digitalWrite(GREEN_LED, HIGH);  // Turn on green LED

  // Open Servo door
  for (int pos = 0; pos <= 180; pos += 1) {
      servo.write(pos);
      delay(1);
  }
  delay(DOOR_OPEN_WAIT);

  // Close Servo door
  for (int pos = 180; pos >= 0; pos -= 1) {
      servo.write(pos);
      delay(1);
  }
  digitalWrite(GREEN_LED, LOW);  // Turn off green LED
}
