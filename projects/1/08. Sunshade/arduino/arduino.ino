#include <Servo.h>
#include <SoftwareSerial.h>

SoftwareSerial serial(10, 11);
Servo servo;

const int WATER = 13;
const int LDR = 12;
const int SERVO = 4;
int pos = 0;

void setup() {
  // put your setup code here, to run once:
  serial.begin(9600);
  servo.attach(SERVO);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(LDR) && digitalRead(WATER)) {
    for (pos = 0; pos <= 360; pos += 1) {
      servo.write(pos);
      delay(1);
    }
  } else {
    pos = 0;
    servo.write(pos);
  }
  serial.println(digitalRead(WATER) + digitalRead(LDR));
}
