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
        else if (key == 'C')
        {
            // Clear input and reset calculator
            input = "";
            operand1 = 0;
            operand2 = 0;
            operation = '\0';
            result = 0; // Reset the result
            lcd.clear();
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
            // **Send the result via Keyboard**
            const char *cstr = result;
            String resultString(cstr);
            // Now myString is "Hello"

            Keyboard.printf(String(result));
        }
    }
}