/* @file HelloKeypad.pde
|| @version 1.0
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Demonstrates the simplest use of the matrix Keypad library.
|| #
*/
#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {2, 3, 4, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 7, 8, 9}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  
  Serial.begin(9600);
}
  
void loop(){
  // lcd.setCursor(0, 1);
  // lcd.print("Hello World");
  char key = keypad.getKey();
  
  if (key){
    Serial.println(key);
    // Serial.println(cursorColumn);
    // lcd.setCursor(cursorColumn, 0); // move cursor to   (cursorColumn, 0)
    // lcd.print(key);                 // print key at (cursorColumn, 0)

    // cursorColumn++;                 // move cursor to next position
    // if(cursorColumn == 16) {        // if reaching limit, clear LCD
    //   lcd.clear();
    //   cursorColumn = 0;
    // }
  }

}
