#include "header.h"

// Read Matrix Keypad ============================================================================================================

char keyMatrixPressed()
{
    char keyPressed = 0;

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
                // Define the key pressed
                keyPressed = keyMap[row][col];

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
    // Return the key pressed
    Serial.println(keyPressed);
    return keyPressed;
}

void keyDebounce()
{
    // Debounce the key



    delay(KEYDELAY); // Add a small delay to avoid rapid button presse
}