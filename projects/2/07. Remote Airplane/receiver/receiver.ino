#include <ctype.h>
#include <Servo.h>

Servo horizontal_stablizer;
Servo vertical_stablizer;

#define HORIZONTAL_STABLIZER_PIN 2 // Horizontal Stablizer Pin
#define VERTICAL_STABLIZER_PIN 3 // Vertical Stablizer Pin
#define ENGINE_PIN 13 // Motor

#define STABLIZER_SHIFT 5
int horizontal_deg = 90;
int vertical_deg = 90;

void setup() {
  Serial.begin(9600);
  horizontal_stablizer.attach(HORIZONTAL_STABLIZER_PIN);
  vertical_stablizer.attach(VERTICAL_STABLIZER_PIN);
  pinMode(ENGINE_PIN, INPUT);
}

void loop() {

  if (digitalRead(ENGINE_PIN) == 0) {
    horizontal_deg = 90;
    vertical_deg = 90;
  } else {
    if (Serial.available()) {
      int action = Serial.read() - '0';
  
      switch (action) {
        case 4: horizontal_deg -= STABLIZER_SHIFT; break;  // Turn Left
        case 6: horizontal_deg += STABLIZER_SHIFT; break;  // Turn Right
        case 2: vertical_deg += STABLIZER_SHIFT; break;  // Climb
        case 8: vertical_deg -= STABLIZER_SHIFT; break;  // Dive
      }
    }
  }

  horizontal_stablizer.write(horizontal_deg);
  vertical_stablizer.write(vertical_deg);
}
