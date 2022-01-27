

#include <LiquidCrystal.h> // includes the LiquidCrystal Library 
LiquidCrystal lcd(1, 2, 4, 5, 6, 7); // Creates an LC object. Parameters: (rs, enable, d4, d5, d6, d7) 
const int buttonPin = 8; 

void setup() { 
 lcd.begin(16,2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display } 
 // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}

void loop() { 
  lcd.clear();
  lcd.print("Use Pushbotton"); // Prints text onto LCD
  lcd.setCursor(0,2);
  lcd.print("To begin recipe");
  
  buttonWait(8);                // waiting for button press
  lcd.print("Double Chocolate"); // Prints text onto LCD
  lcd.setCursor(0,2);
  lcd.print("Flower Brownies");

  buttonWait(8);
  lcd.clear();
  lcd.print("1/2 cup ");
  lcd.setCursor(0,2);
  lcd.print("unsalted butter");
  buttonWait(8);
  lcd.clear();
  lcd.print("1 gram");
  lcd.setCursor(0,2);
  lcd.print("flower");

  buttonWait(8);
  lcd.clear();
  lcd.print("1/4 cup ");
  lcd.setCursor(0,2);
  lcd.print("cocoa powder");
  
  buttonWait(8);
  lcd.clear();
  lcd.print("1/2 cup ");
  lcd.setCursor(0,2);
  lcd.print("chocolate chips");
  
  buttonWait(8);
  lcd.clear();
  lcd.print("1 tablespoon");
  lcd.setCursor(0,2);
  lcd.print("molasses");

  buttonWait(8);
  lcd.clear();
  lcd.print("1 teaspoon");
  lcd.setCursor(0,2);
  lcd.print("vanilla extract");
  
  buttonWait(8);
  lcd.clear();
  lcd.print("2 large eggs");

  buttonWait(8);
  lcd.clear();
  lcd.print("1/4 teaspoon");
  lcd.setCursor(0,2);
  lcd.print("kosher salt");
  
  buttonWait(8);
  lcd.clear();
  lcd.print("3/4 cup");
  lcd.setCursor(0,2);
  lcd.print("all-purpose flour");
  buttonWait(8);
}


/* function for waiting for button press*/
void buttonWait(int buttonPin){
  int buttonState = 0;
  
  while(1){
    buttonState = digitalRead(buttonPin);
    if (buttonState == HIGH) {
      delay(200);
      return;
    }
  }
}
