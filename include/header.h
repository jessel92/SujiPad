#ifndef HEADER_H
#define HEADER_H

#include <Arduino.h>
#include <PluggableUSBHID.h>
#include <USBKeyboard.h>
#include <Wire.h>
#include <hd44780.h>                       // Main hd44780 header
#include <hd44780ioClass/hd44780_I2Cexp.h> // I2C expander I/O class header

// Initialize USB Keyboard and LCD
USBKeyboard Keyboard;
hd44780_I2Cexp lcd;

// Constants
#define KEYDELAY 70
const int LCD_COLS = 16;
const int LCD_ROWS = 2;
const byte numRows = 6;
const byte numCols = 4;

// Pin Definitions
byte rowPins[numRows] = {1, 2, 3, 10, 11, 6}; // Row pins
byte colPins[numCols] = {14, 9, 8, 7};        // Column pins
int calcPin = 12;
int keyPadPin = 13;

// Global Variables
String input = "";   // User input string
float operand1 = 0;  // First operand
float operand2 = 0;  // Second operand
char operation = '\0'; // Current operation
int switchState = 0;

char keyMap[numRows][numCols] = {
    {'p', 'a', 'b', 'n'},
    {'C', '*', '/', '-'},
    {'7', '8', '9', '+'},
    {'4', '5', '6', '='},
    {'1', '2', '3', ' '},
    {'0', '.', ' ', ' '}};

// Function Declarations
void calcFunc();
void keyPadFunc();
char keyMatrixPressed();
void sujiIdleFunc();

#endif
