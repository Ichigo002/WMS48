#include <Arduino.h>

int btn = 34;
int led = 23;

void setup() {
  pinMode(btn, INPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  digitalWrite(led, digitalRead(btn));
}
