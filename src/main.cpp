#include <Keypad.h>
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#define ROW_NUM     4 // four rows
#define COLUMN_NUM  4 // three columns

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte pin_rows[ROW_NUM] = {19, 18, 5, 17}; // GPIO19, GPIO18_, GPIO5, GPIO17 connect to the row pins
 byte pin_column[COLUMN_NUM] = {16, 4, 26,23};  // GPIO16, GPIO4, GPIO22,GPIO23 connect to the column pins
LiquidCrystal_I2C LCD(0x27,16,2);//object lcd
Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

const String password = "2023D"; // change your password here
String input_password;//the input characterrs

void setup() {
  Serial.begin(115200);
  LCD.init();//init lcd
  LCD.backlight();
 input_password.reserve(32); // maximum input characters is 33, change if needed
}

void loop() {
  char key = keypad.getKey(); //get the key keypad

  if (key) {
    LCD.setCursor(0,0);
    LCD.print(key);
    
    if (key == '*') {
      input_password = ""; // clear input password
      LCD.clear();
    } else if (key == '#') {
      if (password == input_password) {
        LCD.println(" \n  correct ");
        
        

      } else {
        LCD.println(" \n  incorrect");
      }

      
     input_password = ""; // clear input password
    } else {
      input_password += key; // append new character to input password string
    }
  }
}
