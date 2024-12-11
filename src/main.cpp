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
  }
  else if (digitalRead(keyPadPin) == LOW)
  {
    // **Keypad mode**
    if (switchState != 2)
    {
      switchState = 2;
      lcd.clear();

      // **Display "Sujipad" centered on the first line**
      lcd.setCursor((16 - 7) / 2, 0); // (16 - length of "Sujipad") / 2
      lcd.print("Sujipad");

      // **Display "Keypad Mode" centered on the second line**
      lcd.setCursor((16 - 11) / 2, 1); // (16 - length of "Keypad Mode") / 2
      lcd.print("Keypad Mode");
    }
    keyPadFunc();
  }
  else
  {
    // Idle mode
    if (switchState != 0)
    {
      switchState = 0;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("  The Mad Noodle ");
      lcd.setCursor(0, 1);
      lcd.print("     Suji-Pad    ");
    }
  }
}
