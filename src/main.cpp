/****************************************************

The Mad Noodle | Sūji (数字)
Firmware 

(ALPHA)0.0.2
12/20/2023

****************************************************/
#include <Arduino.h>

#include "header.h"
#include "calc_func.h"
#include "keypad_func.h"
#include "suji_misc_funcs.h"

// Define the u8g2 instance
U8G2_SSD1309_128X64_NONAME0_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE); // Corrected class name

void setup() {
  Serial.begin(9600);

  // Initialize row pins
  for (byte row = 0; row < numRows; row++) {
    pinMode(rowPins[row], INPUT_PULLUP);
  }

  // Initialize column pins
  for (byte col = 0; col < numCols; col++) {
    pinMode(colPins[col], OUTPUT);
    digitalWrite(colPins[col], HIGH);
  }

  // Initialize U8g2
  u8g2.begin();
  u8g2.enableUTF8Print(); // Enable UTF8 support for print() if needed
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr); // Choose a suitable font
  u8g2.drawStr(0, 10, "  The Mad Noodle ");
  u8g2.drawStr(0, 30, "     Suji-Pad    ");
  u8g2.sendBuffer();
  delay(2000);
  u8g2.clearBuffer();
  u8g2.sendBuffer();

  // Initialize to CALCULATOR mode
  currentMode = CALCULATOR;
}

void loop() {
  switch(currentMode){
    case CALCULATOR:
      calcFunc();
      break;
    case KEYPAD:
      keyPadFunc();
      break;
  }
}
