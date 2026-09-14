#include <Arduino.h>

int led_test = 23;
void setup() {

  // put your setup code here, to run once:
  pinMode(led_test, OUTPUT);
}

void loop() {
  digitalWrite(led_test, HIGH);
  delay(1000);
  digitalWrite(led_test, LOW);
  delay(1000);
}