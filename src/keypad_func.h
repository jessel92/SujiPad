#include "header.h"

// KEYPAD FUNCTION ============================================================================================================

void keyPadFunc()
{

  // Scan each column for button presses
  for (byte col = 0; col < numCols; col++)
  {
    // Activate the current column
    digitalWrite(colPins[col], LOW);

    // Scan each row in the current column
    for (byte row = 0; row < numRows; row++)
    {
      // Check if the current button is pressed
      if (digitalRead(rowPins[row]) == LOW)
      {

        // Send keycode on keypress
        char numPadKey = (keyMap[row][col]);

        if (numPadKey == 'p'){Keyboard.printf("print");}
        if (numPadKey == 'C'){Keyboard.key_code_raw(KEY_BACKSPACE);}
        if (numPadKey == 'n'){Keyboard.key_code_raw(KEY_NUMLOCK);}
        if (numPadKey == '*'){Keyboard.key_code_raw(KEY_KPASTERISK);}
        if (numPadKey == '/'){Keyboard.key_code_raw(KEY_KPSLASH);}
        if (numPadKey == '-'){Keyboard.key_code_raw(KEY_KPMINUS);}
        if (numPadKey == '+'){Keyboard.key_code_raw(KEY_KPPLUS);}
        if (numPadKey == '='){Keyboard.key_code_raw(KEY_KPENTER);}
        if (numPadKey == '.'){Keyboard.key_code_raw(KEY_KPDOT);}
        if (numPadKey == '0'){Keyboard.key_code_raw(KEY_KP0);}
        if (numPadKey == '1'){Keyboard.key_code_raw(KEY_KP1);}
        if (numPadKey == '2'){Keyboard.key_code_raw(KEY_KP2);}
        if (numPadKey == '3'){Keyboard.key_code_raw(KEY_KP3);}
        if (numPadKey == '4'){Keyboard.key_code_raw(KEY_KP4);}
        if (numPadKey == '5'){Keyboard.key_code_raw(KEY_KP5);}
        if (numPadKey == '6'){Keyboard.key_code_raw(KEY_KP6);}
        if (numPadKey == '7'){Keyboard.key_code_raw(KEY_KP7);}
        if (numPadKey == '8'){Keyboard.key_code_raw(KEY_KP8);}
        if (numPadKey == '9'){Keyboard.key_code_raw(KEY_KP9);}
        if (numPadKey == 'a'){Keyboard.key_code_raw(KEY_ESC);}
        if (numPadKey == 'b'){Keyboard.key_code_raw(KEY_DELETE);}

        // Wait until the button is released
        while (digitalRead(rowPins[row]) == LOW)
        {
          // Do nothing
        }
      }
    }

    // Deactivate the current column
    digitalWrite(colPins[col], HIGH);
  }

  delay(KEYDELAY); // Add a small delay to avoid rapid button presse
}