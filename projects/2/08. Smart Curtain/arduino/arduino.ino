/*************************************************************
  

  Rotate a servo using a slider!

  App project setup:
    Slider widget (0...180) on V3
 *************************************************************/

// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID "TMPLBy_HFKi2"
#define BLYNK_DEVICE_NAME "Smart Curtain"
#define BLYNK_AUTH_TOKEN "gyKdeFNh8aPNnKhEBu2RX5q-ilS_ma8j"

#include <SoftwareSerial.h>
SoftwareSerial serial(4, 5); // RX, TX

#include <BlynkSimpleStream.h>
#include <Servo.h>

char auth[] = BLYNK_AUTH_TOKEN;

Servo user_servo;
Servo room_servo;
Servo curtain_height_servo;
int LDR = A0;
int HEIGHT = A1;

BLYNK_WRITE(V0)
{
  int user_light = param.asInt();
  user_servo.write(user_light);
  serial.println("User: " + String(user_light));
  pinMode(LDR, INPUT);
  pinMode(HEIGHT, INPUT);
}

void setup()
{
  serial.begin(9600);

  // Blynk will work through Serial
  // Do not read or write this serial manually in your sketch
  Serial.begin(9600);
  Blynk.begin(Serial, auth);

  user_servo.attach(9);
  room_servo.attach(10);
  curtain_height_servo.attach(11);
}

void loop()
{
  Blynk.run();
  int ldr_light = analogRead(LDR);
  serial.println("Environment: " + String(ldr_light));
  room_servo.write(user_servo.read() - ldr_light / 10);
  curtain_height_servo.write(analogRead(HEIGHT));
  delay(500);
}
