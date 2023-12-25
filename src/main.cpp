/****************************************************

The Mad Noodle | Sūji (数字)
Firmware 

(ALPHA)0.0.2
12/20/2023

Copyright Jesse Leventhal
****************************************************/
#include <Arduino.h>

#include "header.h"
#include "calc_func.h"
#include "keypad_func.h"
#include "suji_misc_funcs.h"

// put function declarations here:


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
  if (digitalRead(calcPin) == LOW){switchState = 1;}

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
      delay(1000);
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


