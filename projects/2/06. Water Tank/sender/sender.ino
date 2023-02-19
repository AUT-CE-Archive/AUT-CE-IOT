#include <SoftwareSerial.h>

SoftwareSerial xBee(3, 2);

int WATER_VOLTATE = A0;

void setup() {
  xBee.begin(9600);
  pinMode(A0 , INPUT);
}

void loop() {
  float water_level_percentage = analogRead(WATER_VOLTATE) / (float)1024 * 10;

  if (water_level_percentage >= 9)
    xBee.write("9");
  else if (water_level_percentage >= 8)
    xBee.write("8");
  else if (water_level_percentage >= 7)
    xBee.write("7");
  else if (water_level_percentage >= 6)
    xBee.write("6");
  else if (water_level_percentage >= 5)
    xBee.write("5");
  else if (water_level_percentage >= 4)
    xBee.write("4");
  else if (water_level_percentage >= 3)
    xBee.write("3");
  else if (water_level_percentage >= 2)
    xBee.write("2");
  else if (water_level_percentage >= 1)
    xBee.write("1");
  else
    xBee.write("0");
  delay(10);
}
