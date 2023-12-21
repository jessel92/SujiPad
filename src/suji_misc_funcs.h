#include "header.h"

// Read Matrix Keypad ============================================================================================================

char keyMatrixPressed()
{
  char keyPressed = 0;
  for (byte col = 0; col < numCols; col++)
  {
    digitalWrite(colPins[col], LOW);
    for (byte row = 0; row < numRows; row++)
    {
      if (digitalRead(rowPins[row]) == LOW)
      {
        keyPressed = keyMap[row][col];
        while (digitalRead(rowPins[row]) == LOW)
        {
          // Do nothing
        }
      }
    }
    digitalWrite(colPins[col], HIGH);
  }
  return keyPressed;
}