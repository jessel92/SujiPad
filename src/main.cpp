/****************************************************

The Mad Noodle | Sūji (数字)
Firmware 

(ALPHA)0.0.5
12/11/2024

Copyright Jesse Leventhal
****************************************************/
#include <Arduino.h>

#include "header.h"
#include "calc_func.h"
#include "keypad_func.h"
#include "suji_misc_funcs.h"

// put function declarations here:


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

  // Initialize LCD
  int status = lcd.begin(LCD_COLS, LCD_ROWS);
  if (status) {
    hd44780::fatalError(status);
  }

  // Display welcome message
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  The Mad Noodle ");
  lcd.setCursor(0, 1);
  lcd.print("     Suji-Pad    ");
  delay(2000);
  lcd.clear();

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
