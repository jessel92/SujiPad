#include "header.h"

void keyPadFunc() {
  char key = keyMatrixPressed();

  if (key != '\0' && key != ' ') { // Ignore space keys
    if (key == 'a') {
      // Toggle between KEYPAD and CALCULATOR modes
      if (currentMode == KEYPAD) {
        currentMode = CALCULATOR;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("   Calculator   ");
        delay(1000);
        lcd.clear();
      }
      else {
        currentMode = KEYPAD;
        lcd.clear();
        lcd.setCursor((LCD_COLS - 7) / 2, 0); // Center "Sujipad"
        lcd.print("Sujipad");
        lcd.setCursor((LCD_COLS - 11) / 2, 1); // Center "Keypad Mode"
        lcd.print("Keypad Mode");

      }
    }
    else {
      // Send corresponding keycode
      if (key == 'p') {
        Keyboard.printf("print");
      } else if (key == 'c') {
        Keyboard.key_code_raw(KEY_BACKSPACE);
      } else if (key == 'n') {
        Keyboard.key_code_raw(KEY_NUMLOCK);
      } else if (key == '*') {
        Keyboard.key_code_raw(KEY_KPASTERISK);
      } else if (key == '/') {
        Keyboard.key_code_raw(KEY_KPSLASH);
      } else if (key == '-') {
        Keyboard.key_code_raw(KEY_KPMINUS);
      } else if (key == '+') {
        Keyboard.key_code_raw(KEY_KPPLUS);
      } else if (key == '=') {
        Keyboard.key_code_raw(KEY_KPENTER);
      } else if (key == '.') {
        Keyboard.printf("."); // Send dot character
        // Alternatively, use:
        // Keyboard.write('.');
      } else if (key >= '0' && key <= '9') {
        Keyboard.printf("%c", key); // Sends the ASCII character
      } else if (key == 'b') {
        Keyboard.key_code_raw(KEY_DELETE);
      }
    }
  }
}