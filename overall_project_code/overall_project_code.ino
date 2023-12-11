#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>

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
LiquidCrystal lcd(50, 51, 41, 39, 37, 35); 
Servo myservo;

int cursorColumn = 0;
int state = 0; // 0 start, 1 deal
int players = 0;
int total = 0;
int count = 0;

int pos = 0; // servo position

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  lcd.clear();
  myservo.attach(10);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (state == 0) {
    lcd.setCursor(0, 0);
    lcd.print("# of Players: ");
    char key = keypad.getKey();
    if (key - 48 < 4 && key - 48 >= 1){
      lcd.print(key);
      players = key - 48;
      state = 1;
    }
  }

  if (state == 1) {
    lcd.clear();
    lcd.print("Cards per player");
    lcd.setCursor(0, 1);
    char key;
    do {
      key = keypad.getKey();
    } while (!(key - 48 < 10 && key - 48 >= 0));
   
    lcd.print(key);                 // print key at (cursorColumn, 0)
    total = players * (key - 48);
    if (total > 52) {
      total = 52;
    }
    state = 2;
  }

  if (state == 2) {
    // spin rc servo
    for (int i = 0; i < players; i++) {
      if (count < total) {
        myservo.write(i * 90);
        delay(15);

        delay(1000);
        count++;
      }  
    }

  }
  
}
