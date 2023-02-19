#include <ctype.h>
#include <SoftwareSerial.h>

SoftwareSerial serial(12, 13);

int GREEN_LED = 5;
int RED_LED = 4;

void setup() {
  serial.begin(9600);
  Serial.begin(9600);
  pinMode(GREEN_LED , OUTPUT);
  pinMode(RED_LED, OUTPUT);
}

int number1 = NULL;
int number2 = NULL;
int result = NULL;
char op = NULL;
bool is_result = false;

void loop() {

  if (Serial.available() > 0) {
    char ch = Serial.read();

    if (isdigit(ch)) {
      if (op == NULL)
        number1 = (10 * number1) + (ch - '0');
      else if (!is_result)
        number2 = (10 * number2) + (ch - '0');
      else
        result = (10 * result) + (ch - '0');
    } else {
      if (op == NULL)
        op = ch;
      else
        is_result = true;
    }

    if (ch == ' ') {
      int output = NULL;
      switch (op) {
        case '+': output = number1 + number2; break;
        case '-': output = number1 - number2; break;
        case '*': output = number1 * number2; break;
        case '/': output = number1 / number2; break;
      }
      if (output == result) {
        digitalWrite(GREEN_LED, HIGH);
        serial.println("Yey!");
      } else {
        digitalWrite(RED_LED, HIGH);
        serial.println("Wrong!");
      }
      delay(3000);
      digitalWrite(RED_LED, LOW);
      digitalWrite(GREEN_LED, LOW);
    }
  }
}
