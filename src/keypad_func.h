// Example for other files
#include "header.h"

void keyPadFunc() {
  char key = keyMatrixPressed();

  if (key != '\0' && key != ' ') { // Ignore space keys
    if (key == 'a') {
      // Toggle between KEYPAD and CALCULATOR modes
      if (currentMode == KEYPAD) {
        currentMode = CALCULATOR;
        u8g2.clearBuffer();
        u8g2.drawStr((128 - 11 * 8) / 2, 10, "Calculator"); // Center "Calculator"
        u8g2.sendBuffer();
      }
      else {
        currentMode = KEYPAD;
        u8g2.clearBuffer();
        u8g2.drawStr((128 - 7 * 8) / 2, 10, "Sujipad"); // Center "Sujipad"
        u8g2.drawStr((128 - 11 * 8) / 2, 30, "Keypad Mode"); // Center "Keypad Mode"
        u8g2.sendBuffer();
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
        u8g2.drawStr(0, 20, "."); // Display dot character
        u8g2.sendBuffer();
        Keyboard.printf("."); // Send dot character
      } else if (key >= '0' && key <= '9') {
        char numStr[2] = {key, '\0'};
        u8g2.drawStr(0, 20, numStr); // Display the number
        u8g2.sendBuffer();
        Keyboard.printf("%c", key); // Sends the ASCII character
      } else if (key == 'b') {
        Keyboard.key_code_raw(KEY_DELETE);
      }
    }
  }
}