// ADC IR sensor measurement Lab04 


// Global Variables
uint32_t value_ADC0 = 0;
uint32_t Distance_ADC0 = 0;
uint32_t low = 0;
uint32_t high = 0;

void setup() {
// SEtup ATD:
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


}

void loop() {

ADCSRA |= 0b01000000; // Start ADC Conversion
while((ADCSRA & 0b00010000)==0); // Stays in while loop while conversion is happening
low  = ADCL;
high = ADCH;
value_ADC0 = (high << 8) | low;
Distance_ADC0 = float(16569/(value_ADC0+25)-7);
Serial.print("ADC0");
Serial.print("\t");
Serial.print(value_ADC0);
Serial.print("\n\r");
delay(100);
}


ADCSRA |= 0b01000000; // Start ADC Conversion
while((ADCSRA & 0b00010000)==0); // Stays in while loop while conversion is happening
low  = ADCL;
high = ADCH;
value_ADC0 = (high << 8) | low;
