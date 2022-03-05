/* AUTHORS: A. LOGAN BARBER; IAN NAIL
 * FILE NAME: Lab04.ino
 * LAST UPDATED: 3 MARCH 2022
 *
 * PURPOSE: 
 *
 */

 /********* G L O B A L  V A R I A B L E S *********/
 uint16_t valueADC0 = 0; // THE VALUE ON ANANLOG CHANNEL 0
 uint16_t valueADC1 = 0; // THE VALUE ON ANANLOG CHANNEL 1

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

    //  

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

    // READ THE INPUT FROM VRy ON ANALOG TO DIGITAL CHANNEL 1
    //ADMUX = 0x41; // 0b01000001
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("VRx: ");
    lcd.print(valueADC0);
    lcd.setCursor(0, 1);
    lcd.print("VRy: ");
    lcd.print(valueADC1);
    delay(250);
}
