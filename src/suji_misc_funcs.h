#include "header.h"

char keyMatrixPressed() {
  char keyPressed = '\0';

  // Scan each column for button presses
  for (byte col = 0; col < numCols; col++) {
    // Activate the current column
    digitalWrite(colPins[col], LOW);

    // Scan each row in the current column
    for (byte row = 0; row < numRows; row++) {
      // Check if the current button is pressed
      if (digitalRead(rowPins[row]) == LOW) {
        // Debounce
        delay(KEYDELAY);
        if (digitalRead(rowPins[row]) == LOW) {
          keyPressed = keyMap[row][col];
          // Wait until the button is released
          while (digitalRead(rowPins[row]) == LOW) {
            delay(10);
          }
          // Deactivate the current column
          digitalWrite(colPins[col], HIGH);
          return keyPressed;
        }
      }
    }
    // Deactivate the current column
    digitalWrite(colPins[col], HIGH);
  }
  return keyPressed;
}

void keyDebounce()
{
    // Debounce the key



    delay(KEYDELAY); // Add a small delay to avoid rapid button presse
}