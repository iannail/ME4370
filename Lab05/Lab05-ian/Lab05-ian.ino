
uint32_t u32_pos = 0;

void setup() { 

  // Set up timer to toggle OC1A (PB5, pin11) on match of OCR1A in Fast PWM mode 


}


void PWM_init()
{
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
}

void loop() {
   
  PWM_init();
  
  while(true){
  for (u32_pos = 40; u32_pos <= 160; u32_pos += 1) { // goes from 0 degrees to 180 degrees
    OCR1A = u32_pos;
    OCR4A =  u32_pos;              // tell servo to go to position in variable 'pos'
    delay(10);                       // waits 15ms for the servo to reach the position
  }
   for (u32_pos = 160; u32_pos > 40; u32_pos -= 1) { // goes from 180 degrees to 0 degrees
    OCR1A = u32_pos;
    OCR4A =  u32_pos;               // tell servo to go to position in variable 'pos'
    delay(10);                       // waits 15ms for the servo to reach the position
  }
  }
  
}
