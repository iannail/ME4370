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
uint8_t u8_start_byte = 193;
uint8_t u8_stop_byte = 194;

/* D E C L A R A T I O N S */

/* S E T U P */
void setup() //run once
{
    // setup timer 1
    TCCR1B = 0b00000100; // normal mode divide clock by 1
    TIMSK1 = 0b00000000; // no interrupts
  
    // Start the connection to the bluetooth module
    Serial1.begin(baud,SERIAL_8N1);

    // SET UP PINS FOR OUTPUT
    DDRB |= 1<<PB7;
    DDRH |= 1<<PH6;
    
    // USE TCNT1  
    TCCR0A = 0b10000011; // non-inverted mode, 8 bit fast PWM
    TCCR0B = 0b00001100; // (I/O clk)/256 (From prescaler) 
    
    // USE TCNT2  
    TCCR2A = 0b10000011; // non-inverted mode, 8 bit fast PWM
    TCCR2B = 0b00001100; // (I/O clk)/256 (From prescaler) 
    
    // PWM COUNTER
    OCR0A = 0; 
    OCR2B = 0;  


}

/* M A I N */
void loop() // run over and over
{

    if(Serial1.available()){
      
      if(u8_command_state=1){
        u8_motor1_speed =  Serial.read();
      }
      if(u8_command_state=2){
        u8_motor2_speed =  Serial.read();
      }
      
    }
    OCR0A = u8_motor1_speed;
    OCR2B = u8_motor2_speed;

    
   

    if( TIFR1 &= 0b00000001 ) {
    TIFR1 |= 0b000000001; // clear the TOV flag by writing a 1 to it
    Serial1.write(u8_start_byte); // Start signature
    Serial1.write(u8_motor1_state);
    Serial1.write(u8_motor2_state);

    }

}
