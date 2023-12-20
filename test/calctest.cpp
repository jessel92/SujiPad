
#include <Keypad.h>

const byte ROWS = 4; // Number of rows
const byte COLS = 4; // Number of columns

// Define the key matrix layout
char keys[ROWS][COLS] = {
  {'7', '8', '9', '/'},
  {'4', '5', '6', '*'},
  {'1', '2', '3', '-'},
  {'C', '0', '=', '+'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};    // Connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2};    // Connect to the column pinouts of the keypad

// Create an instance of the Keypad class
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String input = "";  // String to store the user input
double operand1 = 0;  // First operand
double operand2 = 0;  // Second operand
char operation = ' ';  // Operation to perform

void setup() {
  Serial.begin(9600); // Initialize serial communication
}
444
void loop() {
  char key = keypad.getKey(); // Read the key pressed
  
  if (key) {
    if (key >= '0' && key <= '9') {
      input += key; // Append the digit to the input string
      Serial.print(key); // Echo the key to the Serial Monitor
    } else if (key == '+' || key == '-' || key == '*' || key == '/') {
      operand1 = input.toDouble(); // Store the first operand
      operation = key; // Store the operation
      input = ""; // Reset the input string
      Serial.print(" ");
      Serial.print(key);
      Serial.print(" ");
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
          } else {
            Serial.println("Error: Division by zero!");
            input = "";
            break;
          }
          break;
        default:
          Serial.println("Invalid operation!");
          input = "";
          break;
      }
      
      // Display the result
      Serial.print(" = ");
      Serial.println(result);
      
      input = ""; // Reset the input string
      operand1 = result; // Store the result as the new first operand
    } else if (key == 'C') {
      input = ""; // Clear the input string
      operand1 = 0; // Reset the operands and operation
      operand2 = 0;
      operation = ' ';
      Serial.println("Cleared.");
    }
  }
  
  delay(100); // Add a small delay to avoid key bouncing
}
