#include "header.h"

void keyPadFunc() {
  char key = keyMatrixPressed();

  if (key != '\0' && key != ' ') { // Ignore space keys
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
    }else if (key == '.'){
      Keyboard.printf("."); // Send dot character
      // Alternatively, use:
      // Keyboard.write('.');
    }else if (key >= '0' && key <= '9'){
      Keyboard.printf("%c", key); // Sends the ASCII character
    }else if (key == 'a') {
      Keyboard.key_code_raw(KEY_ESC);
    } else if (key == 'b') {
      Keyboard.key_code_raw(KEY_DELETE);
    }
  }
}