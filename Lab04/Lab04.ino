/* AUTHORS: A. LOGAN BARBER; IAN NAIL
 * FILE NAME: Lab04.ino
 * LAST UPDATED: 25 February 2022
 *
 *  PURPOSE: THIS IS THE MAIN FILE FOR TAKING AN ANOLOG INPUT FROM A IR DISTANCE SENSOR AND DISPLAYING THE DISTANCE ON THE LCD.
 *
 */
// INCLUDE LIBRARIES
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <stdio.h>
#define TRUE 0x01
#define FALSE 0x00


// Global Variables
uint32_t value_ADC0 = 0;
uint32_t Distance_ADC0 = 0;
uint32_t low = 0;
uint32_t high = 0;

// DEFINE MACROS FOR LCD SERIAL
#define ADDRESS 0x27
#define LCDCOLS 16
#define LCDROWS 2
// CREATE LiquidCrystal OBJECT
LiquidCrystal_I2C lcd(ADDRESS, LCDCOLS, LCDROWS);

void setup() {
// SETUP PORT B AS OUTPUT FOR THE LCD
  DDRB = 0x7F; // 0b01111111
  PORTB = 0x00;

// Setup ATD:
//Use AVREF as ADC reference, 10 bit reading, Set MUX 4-0 as 0 for ADC pin 0
	ADMUX = 0b01000000;

// Enable ADC
// Don't start conversions yet
// DOn't autrigger, clear flag, Dont enable interrupt
// Prescalers are 100 for divide by 16 prescale
	ADCSRA = 0b10010100;
	ADCSRB = 0b00000000; // for ADC0
//Begin serial and confirmation message
	Serial.begin(9600); // init serial
	Serial.println("Serial Connected");

    // INITIALIZE THE LCD SCREEN
  lcd.begin();
  // turn on the backlight
  lcd.backlight();
}

void loop() {
	Distance_ADC0 = average_Distance();
//Distance_ADC0 = float(16569/(value_ADC0+25)-7);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hello");
  delay(500);
	Serial.print("ADC0");
	Serial.print("\t");
	Serial.print(Distance_ADC0);
	Serial.print("\n\r");
	delay(100);
}
/*
 * TYPE: FUNCTION
 * NAME: average_Distance
 * RETURN: uint32_t
 * NUMBER OF PARAMETERS: 0
 * PARAMETER NAMES: void
 * PURPOSE: This function returns the average reading from the IR sensor
 */
uint32_t average_Distance(){
  uint32_t u32_index;
  uint32_t u32_average_distance = 0;
  for(u32_index = 0; u32_index < 5000; u32_index++) {
    ADCSRA |= 0b01000000; // Start ADC Conversion
    while((ADCSRA & 0b00010000)==0); // Stays in while loop while conversion is happening
    low  = ADCL;
    high = ADCH;
    value_ADC0 = (high << 8) | low;
    u32_average_distance = u32_average_distance + value_ADC0;
  }
  u32_average_distance = u32_average_distance/5000;
return u32_average_distance;
}
