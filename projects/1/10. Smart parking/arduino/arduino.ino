#include <Keypad.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

const int PARKING_SLOT_SENSOR_1 = 8;
const int PARKING_SLOT_SENSOR_2 = 9;
const int PARKING_SLOT_SENSOR_3 = 10;

const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'*','0','#'}
};

byte rowPins[ROWS] = {24, 25, 26, 27};
byte colPins[COLS] = {30, 29, 28};

SoftwareSerial serial(22, 23);
Keypad pad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
LiquidCrystal lcd(43, 42, 34, 33, 32, 31);

int available_slots = 3;
String lcd_msg = "User?";
int username = -1;
bool parked_1 = false;
bool parked_2 = false;
bool parked_3 = false;

int cost_1 = 0;
int cost_2 = 0;
int cost_3 = 0;


void setup() {
  serial.begin(9600);

  // Initialize
  pinMode(PARKING_SLOT_SENSOR_1 , INPUT);
  pinMode(PARKING_SLOT_SENSOR_2 , INPUT);
  pinMode(PARKING_SLOT_SENSOR_3 , INPUT);
}

void loop() {

  lcd.begin(16, 2);
  lcd.print("Slots: ");
  lcd.print(available_slots);
  lcd.setCursor(0,1);
  lcd.print(lcd_msg);
//  delay(100);

  int current_state_sensor_1 = digitalRead(PARKING_SLOT_SENSOR_1);
  int current_state_sensor_2 = digitalRead(PARKING_SLOT_SENSOR_2);
  int current_state_sensor_3 = digitalRead(PARKING_SLOT_SENSOR_3);
  char key = pad.getKey();

  if (key != NO_KEY) {

    if (username == -1) {
      if (key - '0' >= 1 && key - '0' <= 3) {
        if (available_slots == 0)
          lcd_msg = "Full! User?";
        else {
          username = key - '0';
          lcd_msg = "Pass?";
        }
      } else
        lcd_msg = "Invalid! User?";
    } else {
      if (key - '0' == username + 6) {
        if (username == 1) {
          if (parked_1 == true)
            unpark_1();
          else
            park_1();
        } else if (username == 2) {
          if (parked_2 == true)
            unpark_2();
          else
            park_2();
        } else {
          if (parked_3 == true)
            unpark_3();
          else
            park_3();
        }
      } else
        lcd_msg = "Wrong! User?";
      username = -1;
    }
  }

  if (parked_1)
    cost_1++;
  if (parked_2)
    cost_2++;
  if (parked_3)
    cost_3++;
}

void park_1() {
  lcd_msg = "1 parked! User?";
  digitalWrite(7, HIGH);
  parked_1 = true;
  available_slots--;
  cost_1 = 0;
}

void park_2() {
  lcd_msg = "2 parked! User?";
  digitalWrite(6, HIGH);
  parked_2 = true;
  available_slots--;
  cost_2 = 0;
}

void park_3() {
  lcd_msg = "3 parked! User?";
  digitalWrite(5, HIGH);
  parked_3 = true;
  available_slots--;
  cost_3 = 0;
}

void unpark_1() {
  digitalWrite(7, LOW);
  lcd_msg = "1 left! " + String(cost_1 / 10) + "$. User?";
  parked_1 = false;
  available_slots++;
}

void unpark_2() {
  lcd_msg = "2 left! " + String(cost_2 / 10) + "$. User?";
  digitalWrite(6, LOW);
  parked_2 = false;
  available_slots++;
}

void unpark_3() {
  lcd_msg = "3 left! " + String(cost_3 / 10) + "$. User?";
  digitalWrite(5, LOW);
  parked_3 = false;
  available_slots++;
}
