#include "header.h"

// Declare result as a global variable
float result = 0;

// Declare a flag to track if 'p' key was pressed
bool pPressed = false;

void calcFunc()
{
    char key = keyMatrixPressed();

    if (key != '\0')
    {
        if (key >= '0' && key <= '9')
        {
            input += key;
            lcd.print(key);
        }
        else if (key == '.')
        {
            if (input.indexOf('.') == -1)
            {
                input += key;
                lcd.print(key);
            }
        }
        else if (key == '+' || key == '-' || key == '*' || key == '/')
        {
            if (input.length() > 0)
            {
                operand1 = input.toFloat();
                input = "";
                operation = key;
                lcd.print(key);
            }
            else
            {
                if (pPressed)
                {
                    // Update display to show "= result [operator]"
                    operation = key;
                    lcd.clear();
                    lcd.print("= ");
                    lcd.print(result);
                    lcd.print(" ");
                    lcd.print(operation);
                    pPressed = false;
                }
                else
                {
                    // If no new input, update the operation symbol
                    operation = key;
                    lcd.setCursor(0, 0);
                    lcd.print("= ");
                    lcd.print(result);
                    lcd.print(" ");
                    lcd.print(operation);
                }
            }
        }
        else if (key == '=')
        {
            if (input.length() > 0 && operation != '\0')
            {
                operand2 = input.toFloat();

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
                        lcd.clear();
                        lcd.print(" Error: Divide  ");
                        lcd.setCursor(0, 1);
                        lcd.print("   By Zero!     ");
                        delay(2000);
                        lcd.clear();
                        input = "";
                        operand1 = 0;
                        operand2 = 0;
                        operation = '\0';
                        result = 0;
                        return;
                    }
                    break;
                }

                lcd.clear();
                lcd.print("= ");
                lcd.print(result);
                operand1 = result;  // Set result as the first operand for the next calculation
                input = "";
                operation = '\0';
                lcd.setCursor(0, 1);
            }
        }
        else if (key == 'p')
        {
            // Send the result as a const char string
            char resultStr[10];
            snprintf(resultStr, sizeof(resultStr), "%.2f", result);
            Keyboard.printf(resultStr);

            // Set result as the first operand for the next calculation
            operand1 = result;
            input = "";  // Clear input to start a new calculation

            pPressed = true; // Set the flag indicating 'p' was pressed

            lcd.clear();
            lcd.print("Result sent: ");
            lcd.print(resultStr);
        }
        else if (key == 'b')
        {
            // Clear all inputs and reset calculator
            input = "";
            operand1 = 0;
            operand2 = 0;
            operation = '\0';
            result = 0;
            lcd.clear();
        }
        else if (key == 'c')
        {
            // Backspace the last character
            if (input.length() > 0)
            {
                input.remove(input.length() - 1);
                lcd.setCursor(0, 0);
                lcd.print(input);

                // Optionally, clear remaining characters on the LCD line
                for (int i = input.length(); i < LCD_COLS; i++) {
                    lcd.print(" ");
                }
                lcd.setCursor(input.length(), 0);
            }
        }
        else if (key == 'a')
        {
            // Toggle between CALCULATOR and KEYPAD modes
            if (currentMode == CALCULATOR) {
                currentMode = KEYPAD;
                lcd.clear();
                lcd.setCursor((LCD_COLS - 7) / 2, 0); // Center "Sujipad"
                lcd.print("Sujipad");
                lcd.setCursor((LCD_COLS - 11) / 2, 1); // Center "Keypad Mode"
                lcd.print("Keypad Mode");
            }
        }
    }
}