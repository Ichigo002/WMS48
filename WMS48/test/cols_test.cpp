#include <Arduino.h>

// ROWS  // WORKING PROPERLY: 1 == turned off | 0 == turned on
// int clk = 2, latch = 5, data = 18, oe = 17;

// COLUMNS
int clk = 25, latch = 35, data = 33, oe = 32;

int led = 23, btn = 34;

void setup()
{
  pinMode(clk, OUTPUT);
  pinMode(latch, OUTPUT);
  pinMode(data, OUTPUT);
  pinMode(oe, OUTPUT);

  pinMode(btn, INPUT);
  pinMode(led, OUTPUT);

}

void loop()
{
  if (digitalRead(btn) == LOW)
  {
    digitalWrite(led, HIGH);

    digitalWrite(oe, LOW);
    digitalWrite(latch, LOW);
    digitalWrite(clk, LOW);

    shiftOut(data, clk, MSBFIRST, 0xFF);
    shiftOut(data, clk, MSBFIRST, 0xFF);
    shiftOut(data, clk, MSBFIRST, 0xFF);
    shiftOut(data, clk, MSBFIRST, 0xFF);
    shiftOut(data, clk, MSBFIRST, 0xFF);
    shiftOut(data, clk, MSBFIRST, 0xFF);

    digitalWrite(latch, HIGH);
    delayMicroseconds(1);
    digitalWrite(latch, LOW);
  }
}
