/****************************************************

The Mad Noodle | Sūji (数字)
Firmware 

(ALPHA)0.0.2
12/20/2023

Copyright Jesse Leventhal
****************************************************/


#include <Arduino.h>
#include "PluggableUSBHID.h"
#include "USBKeyboard.h"

#include <Wire.h>
#include <hd44780.h>                       // main hd44780 header
#include <hd44780ioClass/hd44780_I2Cexp.h> // i2c expander i/o class header

#include "usb_hid_keys.h"


// Bounce Delay
#define KEYDELAY 70

USBKeyboard Keyboard;

hd44780_I2Cexp lcd; // declare lcd object: auto locate & auto config expander chip
//LCD Lib Doc - https://github.com/duinoWitchery/hd44780


const int LCD_COLS = 16;
const int LCD_ROWS = 2;

const byte numRows = 6; // Number of rows
const byte numCols = 4; // Number of columns

char keyMap[numRows][numCols] = {
  {'p', 'a', 'b', 'n'},
  {'C', '*', '/', '-'},
  {'7', '8', '9', ' '},
  {'4', '5', '6', '+'},
  {'1', '2', '3', ' '},
  {'0', ' ', '.', '='}
};

byte rowPins[numRows] = {1, 2, 3, 10, 11,6};    // Connect to the row pinouts of the button matrix
byte colPins[numCols] = {14, 9, 8, 7};       // Connect to the column pinouts of the button matrix

//char keyPressed;


String input = "";  // String to store the user input
double operand1 = 0;  // First operand
double operand2 = 0;  // Second operand
char operation = ' ';  // Operation to perform

int switchState;

int calcPin = 12;
int keyPadPin = 13;

double resultPrint = 0;

// put function declarations here:
void calcFunc();
void keyPadFunc();

void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);

   pinMode(calcPin, INPUT_PULLUP);
   pinMode(keyPadPin, INPUT_PULLUP);

     // Set row pins as input and enable internal pull-up resistors
     for (byte row = 0; row < numRows; row++)
     {
       pinMode(rowPins[row], INPUT_PULLUP);
     }
  
  // Set column pins as output
  for (byte col = 0; col < numCols; col++) {
    pinMode(colPins[col], OUTPUT);
    digitalWrite(colPins[col], HIGH);
  }
 
int status;

	status = lcd.begin(LCD_COLS, LCD_ROWS);
	if(status) // non zero status means it was unsuccesful
	{
		// hd44780 has a fatalError() routine that blinks an led if possible
		// begin() failed so blink error code using the onboard LED if possible
		hd44780::fatalError(status); // does not return
	}

	// initalization was successful, the backlight should be on now

	// Print Name on LCD
  lcd.setCursor(1,0);
	lcd.print("The Mad Noodle");
  lcd.setCursor(4,2);
	lcd.print("Suji-Pad");
 
  delay(5000);

  lcd.clear();

  if (digitalRead(keyPadPin) == LOW){switchState = 2;}
  if (digitalRead(calcPin) == LOW)
    {
      switchState = 1;
      lcd.clear();
      lcd.noCursor();
      lcd.noBlink();
      lcd.setCursor(0, 0);
      lcd.print("   Calculator   ");
      delay(2000);
      lcd.clear();
    }

}


void loop() {

  if (digitalRead(calcPin) == LOW)
  {

    if (switchState == 1)
    {
      lcd.clear();
      lcd.noCursor();
      lcd.noBlink();
      lcd.setCursor(0, 0);
      lcd.print("   Calculator   ");
      delay(5000);
      lcd.clear();
      lcd.cursor();
      lcd.blink();
      lcd.lineWrap();
      switchState = 2;

      input = "";   // Clear the input string
      operand1 = 0; // Reset the operands and operation
      operand2 = 0;
      operation = ' ';
    }

    calcFunc();
  }

  if (digitalRead(keyPadPin) == LOW)
  {
    if (switchState == 2)
    {
      lcd.clear();
      lcd.noCursor();
      lcd.noBlink();
      lcd.setCursor(1, 0);
      lcd.print("The Mad Noodle");
      lcd.setCursor(4, 1);
      lcd.print("Suji-Pad");
      switchState = 1;
    }

    keyPadFunc();
  }
}




// Calculator FUNCTION ============================================================================================================

void calcFunc() {

  
// Scan each column for button presses
  for (byte col = 0; col < numCols; col++) {
    // Activate the current column
    digitalWrite(colPins[col], LOW);
    
    // Scan each row in the current column
    for (byte row = 0; row < numRows; row++) {
      // Check if the current button is pressed
      if (digitalRead(rowPins[row]) == LOW) {
        // Print the pressed key to the Serial Monitor
        Serial.println(keyMap[row][col]);
      
       // lcd.print(keyMap[row][col]);

        char key = (keyMap[row][col]);

  if (key) {
      if ((key >= '0' && key <= '9') || key == '.') {
        input += key; // Append the digit to the input string
        Serial.print(key); // Echo the key to the Serial Monitor
        lcd.print(key);
      } else if (key == '+' || key == '-' || key == '*' || key == '/') {
        operand1 = input.toDouble(); // Store the first operand
        operation = key; // Store the operation
        input = ""; // Reset the input string
        Serial.print(" ");
        lcd.print(" ");
        Serial.print(key);
        lcd.print(key);
        Serial.print(" ");
        lcd.print(" ");
      } else if (key == '=') {
        operand2 = input.toDouble(); // Store the second operand
        double result = 0;
        
        // Perform the selected operation
        switch (operation) {
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
            if (operand2 != 0) {
              result = operand1 / operand2;
            } 
            else {
              Serial.println("Error: Division by zero!");
              lcd.setCursor(6,1);
              lcd.print("Error!");
              input = "";
              break;
            }
            break;
          default:
            Serial.println("Invalid operation!");
            lcd.setCursor(0,1);
            lcd.print("Invalid!");            
            input = "";
            break;
        }
        
        // Display the result
        Serial.print(" = ");
        Serial.println(result);
        lcd.setCursor(0,2);
        lcd.print(result);
        resultPrint = result;

        
        input = ""; // Reset the input string
        operand1 = result; // Store the result as the new first operand
      } else if (key == 'C') {
        lcd.clear();
        input = ""; // Clear the input string
        operand1 = 0; // Reset the operands and operation
        operand2 = 0;
        operation = ' ';
        Serial.println("Cleared.");
      }
      //type result
      else if (key == 'p') {
        Serial.println(resultPrint);
        //convert double to char
        char resultStr[50]; // Character array to store the converted value
        sprintf(resultStr, "%f", resultPrint); // Convert double to string
        const char *resultType = resultStr; // Now you can use resultType
        Keyboard.printf(resultStr);
      }



    }

        
        // Wait until the button is released
        while (digitalRead(rowPins[row]) == LOW) {
          // Do nothing
        }
      }
    }
    
    // Deactivate the current column
    digitalWrite(colPins[col], HIGH);
  }
  
  




  delay(KEYDELAY); // Add a small delay to avoid rapid button presse




}

// KEYPAD FUNCTION ============================================================================================================
void keyPadFunc() {


// Scan each column for button presses
  for (byte col = 0; col < numCols; col++) {
    // Activate the current column
    digitalWrite(colPins[col], LOW);
    
    // Scan each row in the current column
    for (byte row = 0; row < numRows; row++) {
      // Check if the current button is pressed
      if (digitalRead(rowPins[row]) == LOW) {
       
        // Send keycode on keypress
        char keyPressed = (keyMap[row][col]);

        if (keyPressed == 'p'){ Keyboard.printf("print");}
        if (keyPressed == 'C'){ Keyboard.key_code_raw(KEY_BACKSPACE);}
        if (keyPressed == 'n'){ Keyboard.key_code_raw(KEY_NUMLOCK);}
        if (keyPressed == '*'){ Keyboard.key_code_raw(KEY_KPASTERISK);}
        if (keyPressed == '/'){ Keyboard.key_code_raw(KEY_KPSLASH);}
        if (keyPressed == '-'){ Keyboard.key_code_raw(KEY_KPMINUS);}
        if (keyPressed == '+'){ Keyboard.key_code_raw(KEY_KPPLUS);}
        if (keyPressed == '='){ Keyboard.key_code_raw(KEY_KPENTER);}
        if (keyPressed == '.'){ Keyboard.key_code_raw(KEY_KPDOT);}
        if (keyPressed == '0'){ Keyboard.key_code_raw(KEY_KP0);}
        if (keyPressed == '1'){ Keyboard.key_code_raw(KEY_KP1);}
        if (keyPressed == '2'){ Keyboard.key_code_raw(KEY_KP2);}
        if (keyPressed == '3'){ Keyboard.key_code_raw(KEY_KP3);}
        if (keyPressed == '4'){ Keyboard.key_code_raw(KEY_KP4);}
        if (keyPressed == '5'){ Keyboard.key_code_raw(KEY_KP5);}
        if (keyPressed == '6'){ Keyboard.key_code_raw(KEY_KP6);}
        if (keyPressed == '7'){ Keyboard.key_code_raw(KEY_KP7);}
        if (keyPressed == '8'){ Keyboard.key_code_raw(KEY_KP8);}
        if (keyPressed == '9'){ Keyboard.key_code_raw(KEY_KP9);}
        if (keyPressed == 'a'){ Keyboard.key_code_raw(KEY_ESC);}
        if (keyPressed == 'b'){ Keyboard.key_code_raw(KEY_DELETE);}
        
        // Wait until the button is released
        while (digitalRead(rowPins[row]) == LOW) {
          // Do nothing
        }
      }
    }
    
    // Deactivate the current column
    digitalWrite(colPins[col], HIGH);
  }

  
  delay(KEYDELAY); // Add a small delay to avoid rapid button presse


}

/*
char keyMatrixPressed(){
  char key = 0;
  for (byte col = 0; col < numCols; col++) {
    digitalWrite(colPins[col], LOW);
    for (byte row = 0; row < numRows; row++) {
      if (digitalRead(rowPins[row]) == LOW) {
        key = keyMap[row][col];
        while (digitalRead(rowPins[row]) == LOW) {
          // Do nothing
        }
      }
    }
    digitalWrite(colPins[col], HIGH);
  }
  return key;
}
*/