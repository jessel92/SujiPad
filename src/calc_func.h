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
                        if (operand1 != 0 && result != 0) {operand1 = result;} // Store the first operand as the result
                        else
                        if (operand1 == 0) {operand1 = input.toFloat();} // Store the first operand
                        operation = key;                                 // Store the operation
                        // if (operation == ' ' || key != oldOperation)
                        // {
                        //     lcd.moveCursorLeft();
                        //     lcd.moveCursorLeft();
                        //     lcd.moveCursorLeft();
                        //     oldOperation = operation; // Store the old operation
                        // }

                        input = ""; // Reset the input string
                        Serial.print(" ");
                        Serial.print(key);
                        Serial.print(" ");
                        lcd.print(" ");
                        lcd.print(key);
                        lcd.print(" ");
                        oldOperation = operation; // Store the old operation
                        
                    }
                    else if (key == '=')
                    {
                        operand2 = input.toFloat(); // Store the second operand
                        if (operand2 == 0) {result = operand1;}
                        result = 0;

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
                        Serial.println(result, 8);
                        lcd.clear();
                        lcd.setCursor(0, 0);
                        lcd.print("= ");
                        lcd.print(removeZeros(String(result, 8)));
                        resultPrint = result;

                        input = "";        // Reset the input string
                        operand1 = result; // Store the result as the new first operand
                        operation = ' ';
                        
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
                        sprintf(resultStr, "%f", resultPrint); // Convert double to string WAS % F
                        const char *resultType = resultStr;    // Now you can use resultType
                        Keyboard.printf(resultType);
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

String removeZeros(String str)
{
    // Remove trailing zeros from the string
    while (str.endsWith("0"))
    {
        str.remove(str.length() - 1);
    }

    // Remove the decimal point if the string ends with it
    if (str.endsWith("."))
    {
        str.remove(str.length() - 1);
    }

    return str;
}