/****************************************************

The Mad Noodle | Sūji (数字)
Firmware 

(ALPHA)0.0.2
12/20/2023

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

  pinMode(calcPin, INPUT_PULLUP);
  pinMode(keyPadPin, INPUT_PULLUP);

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

  // Determine initial mode based on switch positions
  if (digitalRead(keyPadPin) == LOW) {
    switchState = 2;
  } else if (digitalRead(calcPin) == LOW) {
    switchState = 1;
  } else {
    switchState = 0;
  }
}

void loop() {
  if (digitalRead(calcPin) == LOW) {
    if (switchState != 1) {
      switchState = 1;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("   Calculator   ");
      delay(1000);
      lcd.clear();
      lcd.setCursor(0, 1);
    }
    calcFunc();
  } else if (digitalRead(keyPadPin) == LOW) {
    if (switchState != 2) {
      switchState = 2;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("   Keypad Mode   ");
      delay(1000);
      lcd.clear();
    }
    keyPadFunc();
  } else {
    if (switchState != 0) {
      switchState = 0;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("  The Mad Noodle ");
      lcd.setCursor(0, 1);
      lcd.print("     Suji-Pad    ");
    }
  }
}
