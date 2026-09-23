#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <SparkFun_VEML7700_Arduino_Library.h> // Click here to get the library: http://librarymanager/All#SparkFun_VEML7700

// ROWS  // WORKING PROPERLY: 1 == turned off | 0 == turned on
int rclk = 2, rlatch = 5, rdata = 18, roe = 17;

// COLUMNS
int clk = 25, latch = 27, data = 33, oe = 32;

int led = 23, btn = 34;

int counter = 0;
int current_hc595 = 0;

uint32_t rows_out; // 1s turned on

void refreshDisplay();

void setup()
{

  pinMode(clk, OUTPUT);
  pinMode(latch, OUTPUT);
  pinMode(data, OUTPUT);
  pinMode(oe, OUTPUT);

  pinMode(rclk, OUTPUT);
  pinMode(rlatch, OUTPUT);
  pinMode(rdata, OUTPUT);
  pinMode(roe, OUTPUT);

  pinMode(btn, INPUT);
  pinMode(led, OUTPUT);

  digitalWrite(oe, LOW);
  digitalWrite(latch, LOW);
  digitalWrite(clk, LOW);

  shiftOut(data, clk, MSBFIRST, 0); // 1 - turned on
  shiftOut(data, clk, MSBFIRST, 0);
  shiftOut(data, clk, MSBFIRST, 0);
  shiftOut(data, clk, MSBFIRST, 0);
  shiftOut(data, clk, MSBFIRST, 0);
  shiftOut(data, clk, MSBFIRST, 0);

  digitalWrite(latch, HIGH);
  delayMicroseconds(1);
  digitalWrite(latch, LOW);

  digitalWrite(roe, LOW);
  digitalWrite(rlatch, LOW);
  digitalWrite(rclk, LOW);

  shiftOut(rdata, rclk, MSBFIRST, 0xFF); // 0 - turned on
  shiftOut(rdata, rclk, MSBFIRST, 0xFF);
  shiftOut(rdata, rclk, MSBFIRST, 0xFF);
  shiftOut(rdata, rclk, MSBFIRST, 0xFF);

  digitalWrite(rlatch, HIGH);
  digitalWrite(roe, LOW);
  delayMicroseconds(1);
  digitalWrite(rlatch, LOW);
}

void loop()
{

  ///////////////////// columns START

  digitalWrite(oe, LOW);
  digitalWrite(latch, LOW);
  digitalWrite(clk, LOW);

  shiftOut(data, clk, MSBFIRST, 0); // 1 - turned on
  shiftOut(data, clk, MSBFIRST, 0b00001111);
  shiftOut(data, clk, MSBFIRST, 0);
  shiftOut(data, clk, MSBFIRST, 0);
  shiftOut(data, clk, MSBFIRST, 0b00001111);
  shiftOut(data, clk, MSBFIRST, 0);

  digitalWrite(latch, HIGH);
  delayMicroseconds(1);
  digitalWrite(latch, LOW);

  ///////////////////////// columns END

  ///////////////////////// rows START

  digitalWrite(roe, LOW);
  digitalWrite(rlatch, LOW);
  digitalWrite(rclk, LOW);

  for (size_t i = 0; i < 4; i++)
  {
    int temp_counter;
    if(current_hc595 == i)
      temp_counter = (1 << counter);
    else
      temp_counter = 0;
    
    shiftOut(rdata, rclk, MSBFIRST, ~temp_counter);
  }

  counter++;
  if (counter >= 8)
  {
    counter = 0;
    current_hc595 += 1;
    if (current_hc595 >= 4)
    {
      current_hc595 = 0;
    }
  }

  // shiftOut(rdata, rclk, MSBFIRST, ~((rows_out >> 24) & 0xFF)); // 0 - turned on
  // shiftOut(rdata, rclk, MSBFIRST, ~((rows_out >> 16) & 0xFF));
  // shiftOut(rdata, rclk, MSBFIRST, ~((rows_out >> 8)  & 0xFF)); ~(rows_out << counter)
  // shiftOut(rdata, rclk, MSBFIRST, ~(rows_out         & 0xFF));

  digitalWrite(rlatch, HIGH);
  digitalWrite(roe, LOW);
  delayMicroseconds(1);
  digitalWrite(rlatch, LOW);

  digitalWrite(led, HIGH);
  delay(100);
  digitalWrite(led, LOW);
  delay(100);

  /////////////////// rows END
}

void refreshDisplay()
{
}
