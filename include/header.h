

#include <Arduino.h>
#include "PluggableUSBHID.h"
#include "USBKeyboard.h"

#include <Wire.h>
#include <hd44780.h>                       // main hd44780 header
#include <hd44780ioClass/hd44780_I2Cexp.h> // i2c expander i/o class header

#include "usb_hid_keys.h"


#ifndef HEADER_H
#define HEADER_H

USBKeyboard Keyboard;

hd44780_I2Cexp lcd; // declare lcd object: auto locate & auto config expander chip
// LCD Lib Doc - https://github.com/duinoWitchery/hd44780

// Bounce Delay
#define KEYDELAY 70

const int LCD_COLS = 16;
const int LCD_ROWS = 2;

const byte numRows = 6; // Number of rows
const byte numCols = 4; // Number of columns


byte rowPins[numRows] = {1, 2, 3, 10, 11, 6}; // Connect to the row pinouts of the button matrix
byte colPins[numCols] = {14, 9, 8, 7};        // Connect to the column pinouts of the button matrix

// char numPadKey;

String input = "";    // String to store the user input
float operand1 = 0;  // First operand
float operand2 = 0;  // Second operand
char operation = ' '; // Operation
char oldOperation = ' '; // Old Operation 
float result = 0;

bool firstOP = true;

int switchState;

int calcPin = 12;
int keyPadPin = 13;

float resultPrint = 0;

char keyMap[numRows][numCols] = {
    {'p', 'a', 'b', 'n'},
    {'C', '*', '/', '-'},
    {'7', '8', '9', ' '},
    {'4', '5', '6', '+'},
    {'1', '2', '3', ' '},
    {'0', ' ', '.', '='}};

void calcFunc();
void keyPadFunc();
char keyMatrixPressed();
void keyDebounce();
String removeZeros(String str);

#endif
