#include <ctype.h>
#include <SoftwareSerial.h>

SoftwareSerial serial(3, 2);

int GREEN_LED = 5;
int RED_LED = 4;
int BUZZER = 13;

void setup() {
  serial.begin(9600);
  Serial.begin(9600);
  pinMode(BUZZER , OUTPUT);
  digitalWrite(BUZZER, LOW);
}

void loop() {
  if (Serial.available()) {
    int waterLevel = Serial.read() - '0';

    if (waterLevel == 9) {
      serial.println("Water level too high!");
      digitalWrite(BUZZER, HIGH);
    } else if (waterLevel == 0) {
      serial.println("Water level too low!");
      digitalWrite(BUZZER, HIGH);
    } else {
      digitalWrite(BUZZER, LOW);
    }
  }
}
