/*************************************************************
  

  You’ll need:
   - Blynk IoT app (download from App Store or Google Play)
   - Arduino Uno board
   - Decide how to connect to Blynk
     (USB, Ethernet, Wi-Fi, Bluetooth, ...)

  There is a bunch of great example sketches included to show you how to get
  started. Think of them as LEGO bricks  and combine them as you wish.
  For example, take the Ethernet Shield sketch and combine it with the
  Servo example, or choose a USB sketch and add a code from SendData
  example.
 *************************************************************/

// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID "TMPLJX46241D"
#define BLYNK_DEVICE_NAME "Smart Car Remote"
#define BLYNK_AUTH_TOKEN "sSp_6UQ3POKiXLBgbFWsZ3RYLIZNm-Nf"

#include <SoftwareSerial.h>
#include <Servo.h>
#include <BlynkSimpleStream.h>

char auth[] = BLYNK_AUTH_TOKEN;

SoftwareSerial serial(2, 3);
Servo doors;
Servo headlights;

// Pins
const int ALERT_SYSTEM_LED_PIN = 4;
const int ALERT_BUZZER_PIN = 5;
const int DOORS_SERVO_PIN = 7;
const int HEADLIGHTS_SERVO_PIN = 9;
const int LDR_LIGHT_PIN = A0;
const int WATER_LEVEL_PIN = A1;

// Variables
bool ALERTING_ONLINE = false;
bool DOOR_OPEN = false;
int ENV_LIGHT = 0;
bool IS_DAY = false;
int WATER_LEVEL = 0;


BLYNK_WRITE(V0)
{
  int user_light = param.asInt();
  if (!IS_DAY)
    headlights.write(user_light);
  else
    turnOffHeadLights();
}


void setup()
{
  Serial.begin(9600); // Blynk
  serial.begin(9600);
  Blynk.begin(Serial, auth);

  pinMode(ALERT_SYSTEM_LED_PIN, OUTPUT);
  pinMode(ALERT_BUZZER_PIN, OUTPUT);
  pinMode(DOORS_SERVO_PIN, OUTPUT);
  pinMode(LDR_LIGHT_PIN, INPUT);

  doors.attach(DOORS_SERVO_PIN);
  headlights.attach(HEADLIGHTS_SERVO_PIN);

  turnOffHeadLights();
}

void loop()
{
  Blynk.run();
  ALERTING_ONLINE = bool(digitalRead(ALERT_SYSTEM_LED_PIN));  // Is Alerting System online?
  DOOR_OPEN = bool(digitalRead(6) > 0);                       // Is Door open?
  ENV_LIGHT = analogRead(LDR_LIGHT_PIN) / 45;                 // Light in the environment (1-6)
  IS_DAY = bool(ENV_LIGHT >= 3);                              // Is it daylight?
  WATER_LEVEL = analogRead(WATER_LEVEL_PIN) / 10;             // Water levels in the car water tank


  serial.println(WATER_LEVEL);

  // Open/Close doors with alerting
  if (DOOR_OPEN && ALERTING_ONLINE)
    alert();
  else if (!DOOR_OPEN && !ALERTING_ONLINE)
    closeDoors();
  else if (DOOR_OPEN && !ALERTING_ONLINE)
    openDoors();

  // Zero headlight brightness in days
  if (IS_DAY)
    turnOffHeadLights();

  // Send water level to Blynk
  Blynk.virtualWrite(V1, WATER_LEVEL);
}

void openDoors() {
  doors.write(180); // +90
}

void closeDoors() {
  doors.write(0);   // -90
}

void turnOffHeadLights() {
  headlights.write(0);   // -90
}

void alert() {
  digitalWrite(ALERT_BUZZER_PIN, HIGH);
  delay(1000);
  digitalWrite(ALERT_BUZZER_PIN, LOW);
}
