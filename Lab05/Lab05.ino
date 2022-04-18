/* AUTHORS: A. LOGAN BARBER; IAN NAIL
 * FILE NAME: Lab05.ino
 * LAST UPDATED: 4 MARCH 2022
 *
 * PURPOSE: MOVE TWO SERVO MOTORS WITH PWM FROM A JOYSTICK 
 *
 */

 /********* G L O B A L  V A R I A B L E S *********/
 uint16_t valueADC0 = 0; // THE VALUE ON ANANLOG CHANNEL 0
 uint16_t valueADC1 = 0; // THE VALUE ON ANANLOG CHANNEL 1
 uint8_t servo1 = 25; // HOLDS THE POSITION FOR SERVO 1
 uint8_t servo2 = 32; // HOLDS THE POSITION FOR SERVO 2

// INCLUDE LIBRARIES
#include <LiquidCrystal_I2C.h>

// DEFINE MACROS FOR LCD SERIAL
#define ADDRESS 0x27
#define LCDCOLS 16
#define LCDROWS 2

// CREATE LiquidCrystal OBJECT
LiquidCrystal_I2C lcd(ADDRESS, LCDCOLS, LCDROWS);

void setup() 
{   
    // DISABLE DIGITAL BUFFER FOR ALL ANALOG PINS
    DIDR0 = 0xFF;
    DIDR2 = 0xFF;
    
    // SET UP ANALOG TO DIGITIAL CONVERSION IN FREE RUNNING MODE
    ADCSRB = 0x00; // 0b00000000

    // SET UP PINS FOR OUTPUT
    DDRB |= 1<<PB5;
    DDRH |= 1<<PH3;
    
    // USE TCNT1  
    TCCR1A = 0b10000011; // non-inverted mode, 10bit fast pWM
    TCCR1B = 0b00001100; // (I/O clk)/256 (From prescaler) 
    
    // USE TCNT2  
    TCCR4A = 0b10000011; // non-inverted mode, 10bit fast pWM
    TCCR4B = 0b00001100; // (I/O clk)/256 (From prescaler) 
    OCR1A = 40; 
    OCR4A = 40;  

    // INITIALIZE THE LCD SCREEN
    lcd.begin();
}

void loop() 
{   
    // READ THE INPUT ON ANALOG CHANNEL 0
    ADMUX = 0x40; // 0b01000000

    // ENABLE THE ADC, RESET ADIF, AND SET SAMPLING RATE TO 125 kHz
    ADCSRA = 0x97; // 0b10010111

    // START THE CONVERSION
    ADCSRA = 0xD7; // 0b11010111

    // WAIT HERE DURING THE CONVERSION
    while((ADCSRA & 0x10) == 0x00)
    {
        asm("NOP");
    }

    // IF THE CONVERSION IS COMPLETE
    if((ADCSRA & 0x10) == 0x10)
    {
        // DISABLE THE ADC, RESET ADIF, AND SET SAMPLING RATE TO 125 kHz
        ADCSRA = 0x17; // 0b00010111
        
        // READ THE ADC VALUE
        valueADC0 = ADCL;
        valueADC0 += (ADCH << 8);
    }

    
    // READ THE INPUT ON ANALOG CHANNEL 1
    ADMUX = 0x41; // 0b01000001

    // ENABLE THE ADC, RESET ADIF, AND SET SAMPLING RATE TO 125 kHz
    ADCSRA = 0x97; // 0b10010111

    // START THE CONVERSION
    ADCSRA = 0xD7; // 0b11010111

    // WAIT HERE DURING THE CONVERSION
    while((ADCSRA & 0x10) == 0x00)
    {
        asm("NOP");
    }

    // READ THE CONVERSION VALUE
    if((ADCSRA & 0x10) == 0x10)
    {
        // DISABLE THE ADC, AND RESET ADIF, AND SET SAMPLING RATE TO 125 kHz
        ADCSRA = 0x17; // 0b00010111
        
        // GET THE HIGH BITS
        valueADC1 = ADCL;
        valueADC1 += (ADCH << 8);
    }

    // IF THE VALUE ON A1 IS LESS THAN 101, MOVE THE FIRST ARM FORWARD
    if((valueADC1 < 101) && (servo1 > 25))
    {
        servo1 -= 1;
        OCR1A = servo1;
    }
    // IF THE VALUE ON A1 IS GREATER THAN 899, MOVE THE FIRST ARM BACKWARD
    else if((valueADC1 > 899) && (servo1 < 150))
    {
        servo1 += 1;
        OCR1A = servo1;
    }
    
    // IF THE VALUE ON A0 IS LESS THAN 101, MOVE THE SECOND ARM COUNTER CLOCKWISE
    if((valueADC0 < 101) && (servo2 > 32))
    {
        servo2 -= 1;
        OCR4A = servo2;
    }
    // IF THE VALUE ON A0 IS GREATER THAN 899, MOVE THE SECOND ARM CLOCKWISE
    else if((valueADC0 > 899) && (servo2 < 150))
    {
        servo2 += 1;
        OCR4A = servo2;
    }
    

    //ADMUX = 0x41; // 0b01000001
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("servo1: ");
    lcd.print(servo1);
    lcd.setCursor(0, 1);
    lcd.print("servo2: ");
    lcd.print(servo2);
    delay(10);
}
