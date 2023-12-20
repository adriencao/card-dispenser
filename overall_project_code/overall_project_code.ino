#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>

#define SENSORPIN 30

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
int state = 0; // 0 start, 1 number of cards, 2 deal
int players = 0;
int total = 0;
int count = 0;


int sensorState = 0, lastState=0;


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
    myservo.write(0);
    

    analogWrite(13, 0);

    lcd.setCursor(0, 0);
    lcd.print("# of Players: ");
    char key = keypad.getKey();
    if (key - 48 < 6 && key - 48 >= 1){
      lcd.print(key);
      delay(800);
      players = key - 48;
      state = 1;
    }
  }

  if (state == 1) {
    lcd.clear();
    lcd.print("Cards per player");
    lcd.setCursor(0, 1);
    int cursorPos = 0;
    char key;
    int numCards = 0;
    do {
      key = keypad.getKey();
      if (key == 65) {
        reset();
        break;
      } else if (key - 48 < 10 && key - 48 >= 0) {
        numCards = 10 * numCards + (key - 48);
        lcd.print(key);
        lcd.setCursor(++cursorPos, 1);
      }
      // Serial.println((int) key);
    } while (key != 35);

    total = players * numCards;
    lcd.clear();
    
    if (total > 52) {
      total = 52;
    }
    state = 2;
  }

  if (state == 2) {
    lcd.clear();
    lcd.print("Cards dealt: ");
    // spin rc servo
    while (count < total) {
        char key = keypad.getKey();
        if (key == 65) {
          reset();
          break;
        }
        lcd.setCursor(0, 1);
        if (pos < players) {
          for (int i = 180 / (players - 1) * (pos - 1); i <= 180 / (players - 1) * pos; i += 3) { // goes from 0 degrees to 180 degrees
            // in steps of 1 degree
            myservo.write(i);              // tell servo to go to position in variable 'pos'
            delay(15);                       // waits 15ms for the servo to reach the position
          }
        } else {
          for (int i = 180; i >= 0; i -= 3) { // goes from 180 degrees to 0 degrees
            myservo.write(i);              // tell servo to go to position in variable 'pos'
            delay(15);                       // waits 15ms for the servo to reach the position
          }
          pos = 0;
        }
        lcd.print(++count);

        digitalWrite(12, HIGH);
        digitalWrite(11, LOW);
        analogWrite(13, 255);

        int time = millis();
        int curr = millis();
       
        delay(1400);
        sensorState = 0;
        lastState = 0;
        while (sensorState && !lastState) {
          // Serial.println("Unbroken");
          curr = millis();
          sensorState = digitalRead(SENSORPIN);
          if (!sensorState && lastState) {
              // Serial.println(sensorState);
              // Serial.println("Broken");
              break;
          } 
          lastState = sensorState;
        }
        sensorState = 0;
        lastState = 0;
        
        analogWrite(13, 0);

        delay(1000);

        digitalWrite(11, HIGH);
        digitalWrite(12, LOW);

        analogWrite(13, 255);

        delay(1000);
        // count++;
        pos++;
    }
    reset();
    analogWrite(13, 0);
  } 
}

void reset() {
  lcd.clear();
  cursorColumn = 0;
  state = 0; // 0 start, 1 number of cards, 2 deal
  players = 0;
  total = 0;
  count = 0;
  sensorState = 0;
  lastState=0;
  for (int i = 180 / (players - 1) * pos; i >= 0; i -= 3) { // goes from 180 degrees to 0 degrees
    myservo.write(i);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  pos = 0; // servo position
}
