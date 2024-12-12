#ifndef HEADER_H
#define HEADER_H

#include <Arduino.h>
#include <PluggableUSBHID.h>
#include <USBKeyboard.h>
#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

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
String input = "";     // User input string
float operand1 = 0;    // First operand
float operand2 = 0;    // Second operand
char operation = '\0'; // Current operation
int switchState = 0;

// Add mode enumeration and currentMode variable
enum Mode { CALCULATOR, KEYPAD };
Mode currentMode = CALCULATOR; // Initialize to CALCULATOR mode

char keyMap[numRows][numCols] = {
    {'p', 'a', 'b', 'n'},
    {'c', '*', '/', '-'},
    {'7', '8', '9', ' '},
    {'4', '5', '6', '+'},
    {'1', '2', '3', ' '},
    {'0', ' ', '.', '='}
};

// HID Key Codes for special keys
#define KEY_BACKSPACE 0x2A
#define KEY_TAB 0x2B
#define KEY_ENTER 0x28
#define KEY_ESC 0x29
#define KEY_DELETE 0x4C
#define KEY_NUMLOCK 0x53
#define KEY_KPSLASH 0x54
#define KEY_KPASTERISK 0x55
#define KEY_KPMINUS 0x56
#define KEY_KPPLUS 0x57
#define KEY_KPENTER 0x58
#define KEY_KPDOT 0x63
#define KEY_KP0 0x62
#define KEY_KP1 0x59
#define KEY_KP2 0x5A
#define KEY_KP3 0x5B
#define KEY_KP4 0x5C
#define KEY_KP5 0x5D
#define KEY_KP6 0x5E
#define KEY_KP7 0x5F
#define KEY_KP8 0x60
#define KEY_KP9 0x61

// Function Declarations
void calcFunc();
void keyPadFunc();
char keyMatrixPressed();
void sujiIdleFunc();

#endif