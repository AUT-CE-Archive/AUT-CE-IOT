#include <SoftwareSerial.h>

SoftwareSerial serial(6, 7);

const int LED = 12;
const int LDR = 4;

int last_state;

void setup() {
  serial.begin(9600);
  pinMode(LED , OUTPUT);
  pinMode(4, INPUT);
  last_state = 0;
}

void loop() {
  serial.println(digitalRead(LDR));

  if (digitalRead(LDR) == 1 && last_state == 0) {
    serial.println("!!!!!!!!!");
    if (digitalRead(LED) == HIGH)
      digitalWrite(LED, LOW);
    else
      digitalWrite(LED, HIGH);
  }
  last_state = digitalRead(LDR);
}
