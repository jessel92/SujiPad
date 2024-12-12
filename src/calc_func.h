#include "header.h"

// Declare result as a global variable
float result = 0;

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
                operand1 = result;
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
                for (int i = input.length(); i < 16; i++) {
                    lcd.print(" ");
                }
                lcd.setCursor(input.length(), 0);
            }
        }
    }
}