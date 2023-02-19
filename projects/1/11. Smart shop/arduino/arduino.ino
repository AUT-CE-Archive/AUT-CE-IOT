#include <Servo.h>
#include <SoftwareSerial.h>

Servo servo;
SoftwareSerial serial(12, 13);

// Variables
const int SERVO = 3;
const int BUZZER = 2;
const int FLAME_SENSOR = 4;
const int GAS_SENSOR = 11;

void setup() {
  serial.begin(9600);
  servo.attach(SERVO);

  // Pins
  pinMode(SERVO , OUTPUT);
  pinMode(FLAME_SENSOR, INPUT_PULLUP);
  pinMode(BUZZER , OUTPUT);
  pinMode(GAS_SENSOR, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(FLAME_SENSOR) == HIGH)
    flame();

  if (digitalRead(GAS_SENSOR) == HIGH)
    gas();
  else {
    digitalWrite(BUZZER, LOW);
    servo.write(0);
  }
}

void flame() {
  digitalWrite(BUZZER, HIGH); // alert

  for (int i = 0; i < 10; i++) {
    serial.println("Flame Alert #" + String(i) + "...");
    // open
    for (int pos = 0; pos <= 360; pos++) {
      servo.write(pos);
      delay(1);  // wait
    }

    // close
    for (int pos = 180; pos >= -180; pos--) {
      servo.write(pos);
      delay(1);  // wait
    }
  }
  digitalWrite(BUZZER, LOW);
  servo.write(0);
}

void gas() {
  digitalWrite(BUZZER, HIGH); // alert

  for (int pos = 0; pos <= 360; pos++) {
      servo.write(pos);
      delay(1);  // wait
  }
}
