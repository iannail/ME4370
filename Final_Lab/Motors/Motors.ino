/*
 * The circuit:
 * RX is digital pin rxPin (connect to TX of other device)
 * TX is digital pin txPin (connect to RX of other device)
 *
 */

 /* I N C L U D E S */

/* D E F I N E S */

#define baud 9600
#define DELAY 500


/* G L O B A L S */
uint8_t u8_command_state = 0;
uint8_t u8_motor1_speed = 0;
uint8_t u8_motor2_speed = 0;
uint8_t u8_motor1_state = 0;
uint8_t u8_motor2_state = 0;
uint8_t u8_start_byte = 255;
uint8_t u8_stop_byte = 194;
uint8_t u8_data = 0;
uint8_t i_index = 0;

/* D E C L A R A T I O N S */

/* S E T U P */
void setup() //run once
{
    Serial.begin(baud);
    Serial2.begin(baud);
    
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
    OCR1A = 0; 
    OCR4A = 0;  
}

/* M A I N */
void loop() // run over and over
{

    if ( Serial2.available() ) 
    {
        //read incoming from remote controller
        u8_data = Serial2.read();
        //Serial.println("got bluetooth");

        if(u8_data == u8_start_byte)
        {
            i_index = 1;
        }
        else if(i_index == 1)
        {
            u8_motor1_speed = u8_data;
            i_index = 2;
        }
        else if(i_index == 2)
        {
            u8_motor2_speed = u8_data;
            i_index = 3;
        }
    }
    OCR1A = u8_motor1_speed*4;
    OCR4A = u8_motor2_speed*4;
    Serial.println(u8_motor1_speed*4);
    Serial.println(u8_motor2_speed*4);

    
//    if( TIFR1 &= 0b00000001 ) {
//    TIFR1 |= 0b000000001; // clear the TOV flag by writing a 1 to it
//    Serial2.write(u8_start_byte); // Start signature
//    Serial2.write(u8_motor1_state);
//    Serial2.write(u8_motor2_state);
//
//    }

}
