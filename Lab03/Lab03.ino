/* AUTHORS: A. LOGAN BARBER; IAN NAIL
 * FILE NAME: Lab02.ino
 * LAST UPDATED: 28 JANUARY 2022
 *
 *  PURPOSE: THIS FILE IS THE MAIN FILE FOR DISPLAYING A RECIPE ON AN LCD AND BEING ABLE TO SCROLL USING TWO BUTTONS.
 *       THIS FILE ALSO UTILIZES AND 4-7 SEGMENT DISPLAY AS A 10 MINUTE TIMER.
 */ 

/*
 * BUTTON0:
 * 
 * DIGITAL PIN: 27
 * 
 * PORT: A
 * 
 * PORT PIN: 5
 */

 /*
 * BUTTON1:
 * 
 * DIGITAL PIN: 28
 * 
 * PORT: A
 * 
 * PORT PIN: 6
 */

 /*
 * BUTTON2:
 * 
 * DIGITAL PIN: 29
 * 
 * PORT: A
 * 
 * PORT PIN: 7
 */

 /*
  * LCD 4-7 SEGMENT DISPLAY
  * 
  * PIN 1: 
  *      DIGITAL PIN: 10
  *      PORT: B
  *      PORT PIN: 4
  *      
  * PIN 2:
  *      DIGITAL PIN: 50
  *      PORT: B
  *      PORT PIN: 3
  *      
  * PIN 3:
  *      DIGITAL PIN: 13
  *      PORT: B
  *      PORT PIN: 7
  *      
  * PIN 4: 
  *      DIGITAL PIN: 51
  *      PORT: B
  *      PORT PIN: 2
  *      
  * PIN 5:
  *      DIGITAL PIN: 12
  *      PORT: B
  *      PORT PIN: 6
  *      
  * PIN 6:
  *      DIGITAL PIN: 22
  *      PORT: A
  *      PORT PIN: 0
  *      
  * PIN 7:
  *      DIGITAL PIN: 52
  *      PORT: B
  *      PORT PIN: 1
  *      
  * PIN 8:
  *      DIGITAL PIN: 23
  *      PORT: A
  *      PORT PIN: 1
  *      
  * PIN 9:
  *      DIGITAL PIN: 24
  *      PORT: A
  *      PORT PIN: 2
  *      
  * PIN 10:
  *      DIGITAL PIN: 11
  *      PORT: B
  *      PORT PIN: 5
  *      
  * PIN 11:
  *      DIGITAL PIN: 53
  *      PORT: B
  *      PORT PIN: 0
  *      
  * PIN 12:
  *      DIGITAL PIN: 25
  *      PORT: A
  *      PORT PIN: 3
  */
 
// INCLUDE LIBRARIES
#include <LiquidCrystal_I2C.h>

// DEFINE PIN NUMBERS
#define ADDRESS 0x27
<<<<<<< HEAD
#define LCDCOLS 16
#define LCDROWS 2
=======
#define 7segCOLS 16
#define 7segROWS 2
>>>>>>> 7ec69df7481a4c3090d629237903c82af18fcc0e

// TIMER PARAMTERS
uint8_t buttonState = 0;
uint8_t minutes = 10; //start time -> CAN CHANGE TO WHATEVER TIME YOU WANT
uint8_t seconds = 0;  //start time -> CAN CHANGE TO WHATEVER TIME YOU WANT
uint8_t totalMinutes = 0;
uint8_t minutesTens = 0;
uint8_t minutesOnes = 0;
uint8_t secondsTens = 0;
uint8_t secondsOnes = 0;
uint8_t secondsTemp = 0;
float totalSeconds = minutes*60 + seconds;
float totalMilliseconds = totalSeconds*1000;
float totalMicroseconds = totalMilliseconds*1000;
// Keypad Parameters
const byte ROWS = 4; // number of rows on keypad
const byte COLS = 4; // number of columns on keypad
char keys[ROWS][COLS] = { // The buttons on the keypad
{'1','2','3', 'A'},
{'4','5','6', 'B'},
{'7','8','9', 'C'},
{'*','0','#', 'D'}
};
char keyResult = 'F';

// DEFINE LETTERS FOR 7 SEGMENT DISPLAY
const uint8_t ZERO = 0x3F;
const uint8_t ZERO_DEV = 0xBF;
const uint8_t ONE = 0x06;
const uint8_t ONE_DEC = 0x86;
const uint8_t TWO = 0x5B;
const uint8_t TWO_DEC = 0xDB;
const uint8_t THREE = 0x4F;
const uint8_t THREE_DEC = 0xCF;
const uint8_t FOUR = 0x66;
const uint8_t FOUR_DEC = 0xE6;
const uint8_t FIVE = 0x6D;
const uint8_t FIVE_DEC = 0xED;
const uint8_t SIX = 0x7D;
const uint8_t SIX_DEC = 0xFD;
const uint8_t SEVEN = 0x07;
const uint8_t SEVEND_DEC = 0x87;
const uint8_t EIGHT = 0x7F;
const uint8_t EIGHT_DEC = 0xFF;
const uint8_t NINE = 0x67;
const uint8_t NINE_DEC = 0xE7;

// DEFINE THE DISPLAY SELECTION NUMBERS
const uint8_t D1 = 0xE7; // 0b11100111
const uint8_t D2 = 0xEB; // 0b11101011
const uint8_t D3 = 0xED; // 0b11101101
const uint8_t D4 = 0xEE; // 0b11101110
const uint8_t arrD[4] = {D4, D3, D2, D1};

// MESSAGE TO PRINT
char message0[] = "Double Chocolate";
char message1[] = "Flower Brownies";
char message2[] = "1/2 Cup";
char message3[] = "Unsalted Butter";
char message4[] = "1 Gram";
char message5[] = "Flower";
char message6[] = "1/4 Cup ";
char message7[] = "Chocolate Chips";
char message8[] = "1 Tablespoon";
char message9[] = "Molasses";
char message10[] = "1 Teaspoon";
char message11[] = "Vanilla Extract";
char message12[] = "2 Large Eggs";
char message13[] = " ";
char message14[] = "1/4 Teaspoon";
char message15[] = "Kosher Salt";
char message16[] = "3/4 Cup All-";
char message17[] = "Purpose Flour";
char message18[] = "Bake for 10";
char message19[] = "minutes";
const uint8_t msgArrSize = 20;
char* msgArr[msgArrSize] = {message0, message1, message2, message3, message4,
     message5, message6, message7, message8, message9, message10, message11, message12,
     message13, message14, message15, message16, message17, message18, message19};

// INDEX VARIABLES
uint8_t index = 0; // HOLDS INDEX FOR MESSAGE
uint8_t i = 0; // HOLDS INDEX IN for LOOPS FOR SCROLLING
uint8_t t = 0; // HOLDS INDEX IN for LOOP FOR THE TIMER

// CREATE LiquidCrystal OBJECT
LiquidCrystal_I2C lcd(ADDRESS, 7segCOLS, 7segROWS);

// RUN THIS PROGRAM
void setup()
{
     // INITIALIZE THE LCD SCREEN
     lcd.begin();

     // PRINT MESSAGE
     lcd.print(msgArr[0]);
     lcd.setCursor(0, 1);
     lcd.print(msgArr[1]);
     
     // SETUP BUTTON PINS AS INPUTS
     // SETUP 7-SEGMENT SELECTOR PINS AS OUTPUT
     DDRA = 0x0F; // 0b00001111

     // ENABLE INTERNAL PULL-UP RESISTOR FOR BUTTONS
     PORTA = 0xE0; // 0b11100000

     // SETUP PORT B AS OUTPUT FOR THE LCD
     DDRB = 0xFF;
     PORTB = 0x00;

     // CALCULATE INDIVIDUAL DIGITS
     totalMinutes = totalSeconds/60;
     minutesTens = totalMinutes/10;
     minutesOnes = totalMinutes%10;
     secondsTemp = int(totalSeconds)%60;
     secondsTens = secondsTemp/10;
     secondsOnes = secondsTemp%10;
<<<<<<< HEAD
=======
     // Initialize PORTC for keypad
      DDRC =  0b00001111;
      PORTC = 0b11111111;
>>>>>>> 7ec69df7481a4c3090d629237903c82af18fcc0e
}

// LOOP FOREVER
void loop()
{
      keyReturn();
     if (keyResult != 'F')
     {
          Serial.println(keyResult);
          keyResult = 'F'; 
     }
     // ELSE IF BUTTON0 IS LOW SCROLL DOWN
     if((PINA & 0xE0) == 0xC0)
     {
          // DEBOUNCE BUTTON2
          delay(100);
          if((PINA & 0xE0) == 0xC0)
          {
            scroll_down();
          }
     }
     
     // IF BUTTON1 IS LOW THEN SCROLL UP
     else if((PINA & 0xE0) == 0xA0)
     {
          // DEBOUNCE THE BUTTON1
          delay(100);
          if((PINA & 0xE0) == 0xA0)
          {
            scroll_up();
          }
     }
     
     // IF BUTTON 2 IS LOW CHANGE THE BUTTON STATE
     else if((PINA & 0xE0) == 0x60)
     {
          delay(100);
          if((PINA & 0xE0) == 0x60)
          {
             switch(buttonState)
             {
                  case 0:
                       buttonState = 1;
                       break;
    
                  case 1:
                       buttonState = 2;
                       break;
     
                  case 2:
                       buttonState = 0;
                       
                       // RESET TIME
                       totalSeconds = minutes*60 + seconds;
                       totalMilliseconds = totalSeconds*1000;
                       totalMicroseconds = totalMilliseconds*1000;
                       
                       // CALCULATE INDIVIDUAL DIGITS
                       totalMinutes = totalSeconds/60;
                       minutesTens = totalMinutes/10;
                       minutesOnes = totalMinutes%10;
                       secondsTemp = int(totalSeconds)%60;
                       secondsTens = secondsTemp/10;
                       secondsOnes = secondsTemp%10;
                       break;
               }
          }
     }

     // RUN TIMER IF BUTTON STATE IS IN STATE 1
     if(buttonState == 1)
     {
          // TIME CALCULATIONS
          totalMicroseconds = totalMicroseconds - 2000; //totalMilliseconds++' for stopwatch
          totalMilliseconds = totalMicroseconds/1000;
          totalSeconds = (totalMilliseconds/1000+1);

          // CALCULATE INDIVIDUAL DIGITS
          totalMinutes = totalSeconds/60;
          minutesTens = totalMinutes/10;
          minutesOnes = totalMinutes%10;
          secondsTemp = int(totalSeconds)%60;
          secondsTens = secondsTemp/10;
          secondsOnes = secondsTemp%10;
     }

     // TIMER
     for(t = 0; t < 4; ++t)
     {
          switch(t)
          {
               case 0:
                    PORTA = arrD[t];
                    7seg_writeNumber(minutesTens);
                    delayMicroseconds(500);
                    break;
     
                case 1:
                     PORTA = arrD[t];
                     7seg_writeNumber(minutesOnes);
                     PORTB |= 0x80;
                     delayMicroseconds(500);
                     break;
     
                 case 2:
                      PORTA = arrD[t];
                      7seg_writeNumber(secondsTens);
                      delayMicroseconds(500);
                      break;
     
                 case 3:
                      PORTA = arrD[t];
                      7seg_writeNumber(secondsOnes);
                      delayMicroseconds(500);
                      break;
          }
     }
}

/*
 * TYPE: FUNCTION
 * NAME: scroll_up
 * RETURN: void
 * NUMBER OF PARAMETERS: 2
 * PARAMETER NAMES: char* messagePtr, uint8_t sizeOfArray
 * PURPOSE: THIS FUNCTION SCROLLS THROUGH THE RECEIPE DISPLAYED ON THE LCD
 */
void scroll_up()
{
     // DECREMENT INDEX BY ONE
     index -= 2;

     // CHECK THE BOUNDS OF INDEX (REMEMBER index IS UNSIGNED)
     if(index > (msgArrSize - 2))
          index = 0;
          
     // CLEAR THE LCD SCREEN AND PRINT MESSAGES TO THE LCD
     lcd.clear();
     for(i = 0; i < 2; ++i)
     {
          lcd.setCursor(0, i);
          delayMicroseconds(1000);
          lcd.print(msgArr[index + i]);
          delayMicroseconds(1000);
     }
}

/*
 * TYPE: FUNCTION
 * NAME: scroll_down
 * RETURN: void
 * NUMBER OF PARAMETERS: 2
 * PARAMETER NAMES: char* messagePtr, uint8_t sizeOfArray
 * PURPOSE: THIS FUNCTION SCROLLS THROUGH THE RECEIPE DISPLAYED ON THE LCD
 */
void scroll_down()
{
     // INCREMENT INDEX
     index += 2;

     // CHECK THE BOUNDS OF INDEX
     if(index > (msgArrSize - 2))
          index = msgArrSize - 2;

     // CLEAR THE LCD SCREEN AND PRINT MESSAGES TO THE LCD
     lcd.clear();
     for(i = 0; i < 2; ++i)
     {
          lcd.setCursor(0, i);
          delayMicroseconds(1000);
          lcd.print(msgArr[index + i]);
          delayMicroseconds(1000);
     } 
}

/*
 * TYPE: FUNCTION
 * NAME: 7seg_writeNumber
 * RETURN: void
 * NUMBER OF PARAMETERS: 1
 * PARAMETER NAMES: int x
 * PURPOSE: THIS FUNCTION PICK THE NUMBER FOR THE LCD
 */
void 7seg_writeNumber(int x) //changes value of number
{
     switch(x)
     {
          default: 
               PORTB = ZERO; 
               break;
          case 1: 
               PORTB = ONE; 
               break;
          case 2: 
               PORTB = TWO; 
               break;
          case 3: 
               PORTB = THREE; 
            break;
          case 4: 
               PORTB = FOUR; 
               break;
          case 5: 
               PORTB = FIVE; 
               break;
          case 6: 
               PORTB = SIX; 
               break;
          case 7: 
               PORTB = SEVEN; 
               break;
          case 8: 
               PORTB = EIGHT; 
               break;
          case 9: 
               PORTB = NINE; 
               break;
     }
}

/*
 * TYPE: FUNCTION
 * NAME: keyReturn
 * RETURN: char
 * NUMBER OF PARAMETERS: 1
 * PARAMETER NAMES: void
 * PURPOSE: THIS returns the character value of the button pressed on the keypad
 */
char keyReturn(void)
{
  /* for loop execution */
  byte outputROWS[ROWS] = {0b00000001,0b00000010,0b00000100,0b00001000}; // last 4 bits of PORTC that will be toggled to check if a button is pressed
  byte inputCOLS[COLS] = {0b00010000,0b00100000,0b01000000,0b10000000}; // first 4 bits of PORTC that will be be read from PINC to see if the pullup resistor has been grounded 
  byte a = 0;
  byte b = 0;
  int val = 0;
  
  for (a = 0; a < 4; a = a+1) //first for loop to check the rows of the button matrix
  {
    PORTC ^=  outputROWS[a]; // toggle the bit low
  
    for (b = 0; b < 4; b = b+1) //second for loop to check the columns of the button matrix
    {
      val = (PINC & inputCOLS[b]) >> (b+4); // get value to check if the bit is low (low means a button has been pressed at row a and colomn b

      if (val != 1) //Debouncing code
      {
        delay(15); //Debouncing code
        keyResult = keys[a][b];
          while(1 != (PINC & inputCOLS[b]) >> (b+4));
          {
          val = (PINC & inputCOLS[b]) >> (b+4);
          } 
       }
      
     }
     PORTC ^= outputROWS[a]; //toggle the bit high
    }
    
  return keyResult;
  }
