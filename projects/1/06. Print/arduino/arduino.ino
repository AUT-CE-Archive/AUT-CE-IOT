#include <SoftwareSerial.h>

SoftwareSerial serial(9, 10);

void setup() {
  serial.begin(9600);
  serial.write("Keivan Ipchi Hagh - 9831073");
}

void loop() {
}
