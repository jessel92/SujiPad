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
            u8g2.drawStr(0, 10, input.c_str()); // Use u8g2.drawStr
            u8g2.sendBuffer();
        }
        else if (key == '.')
        {
            if (input.indexOf('.') == -1)
            {
                input += key;
                u8g2.drawStr(0, 10, input.c_str());
                u8g2.sendBuffer();
            }
        }
        else if (key == '+' || key == '-' || key == '*' || key == '/')
        {
            if (input.length() > 0)
            {
                operand1 = input.toFloat();
                input = "";
                operation = key;

                char opStr[2] = {operation, '\0'};
                u8g2.drawStr(0, 10, opStr);
                u8g2.sendBuffer();
            }
            else
            {
                if (pPressed)
                {
                    // Update display to show "= result [operator]"
                    operation = key;
                    u8g2.clearBuffer();

                    char resultStr[10];
                    snprintf(resultStr, sizeof(resultStr), "%.2f", result);

                    // Calculate positions for centering
                    int centerX = (128 - strlen("= ") * 8 - strlen(resultStr) * 8 - 8) / 2;
                    u8g2.drawStr(centerX, 20, "= ");
                    u8g2.drawStr(centerX + 16, 20, resultStr);

                    char opStr[2] = {operation, '\0'};
                    u8g2.drawStr(centerX + 32, 20, opStr);
                    u8g2.sendBuffer();

                    pPressed = false;
                }
                else
                {
                    // If no new input, update the operation symbol
                    operation = key;
                    u8g2.clearBuffer();

                    char displayStr[30];
                    snprintf(displayStr, sizeof(displayStr), "= %.2f %c", result, operation);
                    u8g2.drawStr(0, 10, displayStr);
                    u8g2.sendBuffer();
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
                        u8g2.clearBuffer();
                        u8g2.drawStr(0, 10, " Error: Divide  ");
                        u8g2.drawStr(0, 30, "   By Zero!     ");
                        u8g2.sendBuffer();
                        delay(2000);
                        u8g2.clearBuffer();
                        u8g2.sendBuffer();
                        input = "";
                        operand1 = 0;
                        operand2 = 0;
                        operation = '\0';
                        result = 0;
                        return;
                    }
                    break;
                }

                u8g2.clearBuffer();
                char resultDisplay[20];
                snprintf(resultDisplay, sizeof(resultDisplay), "= %.2f", result);
                u8g2.drawStr(0, 10, resultDisplay);
                u8g2.sendBuffer();
                operand1 = result;  // Set result as the first operand for the next calculation
                input = "";
                operation = '\0';
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

            u8g2.clearBuffer();
            u8g2.drawStr(0, 10, "Result sent:");
            u8g2.drawStr(0, 20, resultStr);
            u8g2.sendBuffer();
        }
        else if (key == 'b')
        {
            // Clear all inputs and reset calculator
            input = "";
            operand1 = 0;
            operand2 = 0;
            operation = '\0';
            result = 0;
            u8g2.clearBuffer();
            u8g2.sendBuffer();
        }
        else if (key == 'c')
        {
            // Backspace the last character
            if (input.length() > 0)
            {
                input.remove(input.length() - 1);
                u8g2.setCursor(0, 10);
                u8g2.drawStr(0, 10, input.c_str());

                // Optionally, clear remaining characters on the display
                for (int i = input.length(); i < (LCD_COLS / 8); i++) { // Assuming 8 pixels per character
                    char space = ' ';
                    u8g2.drawStr(i * 8, 10, " ");
                }
                u8g2.sendBuffer();
            }
        }
        else if (key == 'a')
        {
            // Toggle between CALCULATOR and KEYPAD modes
            if (currentMode == CALCULATOR) {
                currentMode = KEYPAD;
                u8g2.clearBuffer();
                u8g2.drawStr((128 - 7 * 8) / 2, 10, "Sujipad"); // Center "Sujipad"
                u8g2.drawStr((128 - 11 * 8) / 2, 30, "Keypad Mode"); // Center "Keypad Mode"
                u8g2.sendBuffer();
            }
            else {
                currentMode = CALCULATOR;
                u8g2.clearBuffer();
                u8g2.drawStr((128 - 11 * 8) / 2, 10, "Calculator"); // Center "Calculator"
                u8g2.sendBuffer();
            }
        }
    }
}