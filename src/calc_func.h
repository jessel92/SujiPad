#include "header.h"

// Calculator FUNCTION ============================================================================================================

void calcFunc()
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
                // Print the pressed key to the Serial Monitor
                Serial.println(keyMap[row][col]);

                // lcd.print(keyMap[row][col]);

                char key = (keyMap[row][col]);

                if (key)
                {
                    if ((key >= '0' && key <= '9') || key == '.')
                    {
                        input += key;      // Append the digit to the input string
                        Serial.print(key); // Echo the key to the Serial Monitor
                        lcd.print(key);
                    }
                    else if (key == '+' || key == '-' || key == '*' || key == '/')
                    {
                        operand1 = input.toDouble(); // Store the first operand
                        operation = key;             // Store the operation
                        input = "";                  // Reset the input string
                        Serial.print(" ");
                        lcd.print(" ");
                        Serial.print(key);
                        lcd.print(key);
                        Serial.print(" ");
                        lcd.print(" ");
                    }
                    else if (key == '=')
                    {
                        operand2 = input.toDouble(); // Store the second operand
                        double result = 0;

                        // Perform the selected operation
                        switch (operation)
                        {
                        case '+':
                            result = operand1 + operand2;
                            break;
                        case '-':
                            result = operand1 - operand2;
                            break;
                        case '*':
                            result = operand1 * operand2;
                            break;
                        case '/':
                            if (operand2 != 0)
                            {
                                result = operand1 / operand2;
                            }
                            else
                            {
                                Serial.println("Error: Division by zero!");
                                lcd.setCursor(6, 1);
                                lcd.print("Error!");
                                input = "";
                                break;
                            }
                            break;
                        default:
                            Serial.println("Invalid operation!");
                            lcd.setCursor(0, 1);
                            lcd.print("Invalid!");
                            input = "";
                            break;
                        }

                        // Display the result
                        Serial.print(" = ");
                        Serial.println(result);
                        lcd.setCursor(0, 2);
                        lcd.print(result);
                        resultPrint = result;

                        input = "";        // Reset the input string
                        operand1 = result; // Store the result as the new first operand
                    }
                    else if (key == 'C')
                    {
                        lcd.clear();
                        input = "";   // Clear the input string
                        operand1 = 0; // Reset the operands and operation
                        operand2 = 0;
                        operation = ' ';
                        Serial.println("Cleared.");
                    }
                    // type result
                    else if (key == 'p')
                    {
                        Serial.println(resultPrint);
                        // convert double to char
                        char resultStr[50];                    // Character array to store the converted value
                        sprintf(resultStr, "%f", resultPrint); // Convert double to string
                        const char *resultType = resultStr;    // Now you can use resultType
                        Keyboard.printf(resultStr);
                    }
                }
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
