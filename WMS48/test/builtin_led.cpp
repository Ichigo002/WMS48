#include <Arduino.h>

int led_test = 23;
int bt_btn = 34;
void setup() {

  // put your setup code here, to run once:
  pinMode(led_test, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(bt_btn) == LOW)
  {
    digitalWrite(led_test, HIGH);
  }
  digitalWrite(led_test, HIGH);
  delay(1000);
  digitalWrite(led_test, LOW);
  delay(1000);
}