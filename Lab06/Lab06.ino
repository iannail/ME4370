// AUTHORS: A. LOGAN BARBER, IAN NAIL
// FILE NAME: Lab06.ino
// LAST UPDATED: 17 APRIL 2022
/*
 * PURPOSE: THIS FILE IS OUR SOLUTION FOR ME 4370 >> LAB 6.
 */

/*
 * STEPPER MOTOR DRIVER:
 *
 * STEPPER MOTOR DRIVER PIN: IN1
 *     PORT: B
 *     PIN: PB0
 *     DIGITAL PIN: 53
 *
 * STEPPER MOTOR DRIVER PIN: IN2
 *     PORT: B
 *     PIN: PB1
 *     DIGITAL PIN: 52
 *
 * STEPPER MOTOR DRIVER PIN: IN3
 *     PORT: B
 *     PIN: PB2
 *     DIGITAL PIN: 51
 *
 * STEPPER MOTOR DRIVER PIN: IN4
 *     PORT: B
 *     PIN: PB3
 *     DIGITAL PIN: 50
 */

 /*
  * BUTTON0:
  * DIGITAL PIN: 22
  * PORT: A
  * PORT PIN: 0
  */

 /*
  * BUTTON1:
  * DIGITAL PIN: 23
  * PORT: A
  * PORT PIN: 1
  */

/********** I N C L U D E S **********/
#include <stdint.h> // ALLOWS TO SPECIFICATION OF THE BIT SIZE OF THE NUMBER


/********** D E F I N E S **********/
#define DELAY 850
uint8_t u8_state = 0;

/********** G L O B A L  V A R I A B L E S **********/


// SET UP FUNCTION
void setup()
{
    // SET UP PORT B PINS FOR OUTPUT
    DDRB = 0x0F; // 0b00001111
    PORTB = 0x00; // 0b00000000

    // SETUP BUTTON PINS AS INPUTS
    // ENABLE INTERNAL PULL-UP RESISTOR FOR BUTTONS
    DDRA = 0x00; // 0b00000000
    PORTA = 0x03; // 0b00000011
}


// RUN THIS CODE FOREVER
void loop()
{
    // IF BUTTON0 IS LOW CHANGE STATE
    if((PINA & 0x01) == 0x00)
    {
        u8_state = 1;
    }
    
    // ELSE IF BUTTON1 IS LOW CHANGE STATE
    else if((PINA & 0x02) == 0x00)
    {
        u8_state = 2;
    }
    else
    {
        u8_state = 0;
    }

    // FORWARD
    if(u8_state == 1)
    {
        // TURN ON IN1
        PORTB |= 0x01; // 0b00000001
        delayMicroseconds(DELAY);

        // TURN OFF IN4
        PORTB &= ~(0x08); // 0b11110111
        delayMicroseconds(DELAY);

        // TURN ON IN2
        PORTB |= 0x02; // 0b00000010
        delayMicroseconds(DELAY);

        // TURN OFF IN1
        PORTB &= ~(0x01); // 0b11111110
        delayMicroseconds(DELAY);

        // TURN ON IN3
        PORTB |= 0x04; // 0b00000100
        delayMicroseconds(DELAY);

        // TURN OFF IN2
        PORTB &= ~(0x02); // 0b11111101
        delayMicroseconds(DELAY);

        // TURN ON IN4
        PORTB |= 0x08; // 0b00001000
        delayMicroseconds(DELAY);

        // TURN OFF IN3
        PORTB &= ~(0x04); // 0b11111011
        delayMicroseconds(DELAY);
    }

    // BACKWARD
    else if(u8_state == 2)
    {
         // TURN ON IN4
        PORTB |= 0x08; // 0b00001000
        delayMicroseconds(DELAY);

        // TURN ON IN3
        PORTB |= 0x04; // 0b00000100
        delayMicroseconds(DELAY);

        // TURN OFF IN4
        PORTB &= ~(0x08); // 0b11110111
        delayMicroseconds(DELAY);

        // TURN ON IN2
        PORTB |= 0x02; // 0b00000010
        delayMicroseconds(DELAY);

        // TURN OFF IN3
        PORTB &= ~(0x04); // 0b11111011
        delayMicroseconds(DELAY);

         // TURN ON IN1
        PORTB |= 0x01; // 0b00000001
        delayMicroseconds(DELAY);

        // TURN OFF IN2
        PORTB &= ~(0x02); // 0b11111101
        delayMicroseconds(DELAY);

        // TURN OFF IN1
        PORTB &= ~(0x01); // 0b11111110
        delayMicroseconds(DELAY);
    }
}
