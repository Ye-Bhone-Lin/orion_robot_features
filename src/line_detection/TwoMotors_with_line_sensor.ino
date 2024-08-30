#include <LiquidCrystal_I2C>

#include <Keypad.h>
#include <EEPROM.h>
#include <Wire.h>


// Define the number of rows and columns for the keypad matrix
const byte ROWS = 4;
const byte COLS = 4;

LiquidCrystal_I2C lcd(0x27, 16, 2);
char password[5]; // Increase by 1 to include null terminator
char initial_password[5]; // Increase by 1 to include null terminator
char new_password[5]; // Increase by 1 to include null terminator
int relay_pin = 11;
char key_pressed = 0;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte row_pins[ROWS] = {9, 8, 7, 6};
byte column_pins[COLS] = {5, 4, 3, 2};
Keypad keypad_key = Keypad(makeKeymap(hexaKeys), row_pins, column_pins, ROWS, COLS);

// Function to map keypresses to characters
char mapKeyToChar(char key) {
  switch (key) {
    case '2': return '2'; // Map '2' to 'A'
    case '5': return '5'; // Map '5' to 'B'
    case '8': return '8'; // Map '8' to 'C'
    case '0': return '0'; // Map '0' to 'D'
    default: return key;  // Return other keys as is
  }
}

void setup() {
  lcd.init(); // Use init() instead of begin()
  lcd.backlight();
  pinMode(relay_pin, OUTPUT);

  // Set the initial state of the solenoid to locked
  digitalWrite(relay_pin, LOW);

  lcd.print("   Welcome to");
  lcd.setCursor(0, 1);
  lcd.print("Orion01 Delivery");
  delay(3000);
  lcd.clear();
  lcd.print("Enter Password");
  lcd.setCursor(0, 1);
  initialpassword();
}

void loop() {
  static int i = 0; // Declare i as a static variable

  key_pressed = keypad_key.getKey();
  if (key_pressed == '#') {
    change(); // Allow password change
  } else if (key_pressed) {
    char mapped_char = mapKeyToChar(key_pressed);
    password[i++] = mapped_char;
    lcd.setCursor(i - 1, 1); // Move cursor to the correct position
    lcd.print('*'); // Print '*' for each key press
    delay(200); // Delay to avoid multiple key reads
  }

  if (i == 4) {
    delay(200);
    if (strncmp(password, initial_password, 4) == 0) {
      // Correct password entered
      lcd.clear();
      lcd.print("Door Unlocked");
      digitalWrite(relay_pin, HIGH); // Unlock the solenoid
      delay(10000); // Keep unlocked for 10 seconds
      digitalWrite(relay_pin, LOW); // Lock the solenoid again
      lcd.clear();
      lcd.print("Door Locked");
      delay(2000); // Display message for 2 seconds
    } else {
      // Incorrect password entered
      lcd.clear();
      lcd.print("Wrong Password");
      delay(2000);
      lcd.clear();
      lcd.print("Enter Password");
    }
    lcd.setCursor(0, 1);
    i = 0; // Reset the input index
    password[0] = '\0'; // Clear password array
  }
}

void change() {
  int j = 0;
  lcd.clear();
  lcd.print("Current Password");
  lcd.setCursor(0, 1);
  while (j < 4) {
    char key = keypad_key.getKey();
    if (key) {
      new_password[j++] = mapKeyToChar(key);
      lcd.print('*'); // Print '*' for each key press
      delay(200); // Delay to avoid multiple key reads
    }
  }
  delay(500);

  if (strncmp(new_password, initial_password, 4) != 0) {
    lcd.clear();
    lcd.print("Wrong Password");
    lcd.setCursor(0, 1);
    lcd.print("Try Again");
    delay(1000);
    return;
  }

  j = 0;
  lcd.clear();
  lcd.print("New Password:");
  lcd.setCursor(0, 1);

  while (j < 4) {
    char key = keypad_key.getKey();
    if (key) {
      initial_password[j] = mapKeyToChar(key);
      lcd.print('*'); // Print '*' for each key press
      EEPROM.write(j, initial_password[j]); // Save new password to EEPROM
      j++;
      delay(200); // Delay to avoid multiple key reads
    }
  }
  lcd.print("Pass Changed");
  delay(1000);

  lcd.clear();
  lcd.print("Enter Password");
  lcd.setCursor(0, 1);
}

void initialpassword() {
  for (int j = 0; j < 4; j++)
    initial_password[j] = EEPROM.read(j);
  initial_password[4] = '\0'; // Null terminator
}