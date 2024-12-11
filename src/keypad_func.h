#include "header.h"

void keyPadFunc() {
  char key = keyMatrixPressed();

  if (key != '\0') {
    // Send corresponding keycode
    if (key == 'p') {
      Keyboard.printf("print");
    } else if (key == 'C') {
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
      Keyboard.key_code_raw(KEY_KPDOT);
    } else if (key >= '0' && key <= '9') {
      Keyboard.key_code_raw(KEY_KP0 + (key - '0'));
    } else if (key == 'a') {
      Keyboard.key_code_raw(KEY_ESC);
    } else if (key == 'b') {
      Keyboard.key_code_raw(KEY_DELETE);
    }
  }
}