#include <LiquidCrystal.h>

LiquidCrystal lcd(50, 51, 41, 39, 37, 35); 

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2); // LCD is column major
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.print("   Potato Cat   ");

	// set the cursor to column 0, line 1
	// (note: line 1 is the second row, since counting begins with 0):
	lcd.setCursor(0, 1);
	// Print a message to the LCD.
	lcd.print("Munching Fish :)");
  lcd.home();
}
