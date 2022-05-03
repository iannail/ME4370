/*
   The circuit:
 * RX is digital pin (Recieve) (connect to TX of other device)
 * TX is digital pin (Transmit) (connect to RX of other device)
 */
/* I N C L U D E S */
#include <LiquidCrystal_I2C.h>


/* D E F I N E S */
// DEFINE PIN NUMBERS
#define ADDRESS 0x27
#define COLS 16
#define ROWS 2
#define baud 9600

/* G L O B A L S */

uint8_t u8_start_byte = 193;
uint8_t u8_stop_byte = 194;
uint8_t u8_motor1_speed=50;
uint8_t u8_motor3_speed=50;
uint8_t u8_data = 192;
uint8_t i_index = 0;
uint8_t u8_command_state = 3;
uint8_t u8_motor1_state = 0;
uint8_t u8_motor2_state = 0;
char message0[] = "Motor1";
char message1[] = "Motor2";

/* S E T U P */

// CREATE LiquidCrystal OBJECT
LiquidCrystal_I2C lcd(ADDRESS, COLS, ROWS);

void setup() //run once
{

	// Start the serial connection with the HM-10 bluetooth module
	Serial1.begin(baud,SERIAL_8N1);
 
     // INITIALIZE THE LCD SCREEN
     lcd.begin();

     // PRINT MESSAGE
     lcd.print(message0);
     lcd.setCursor(0, 1);
     lcd.print(message1);
}


/* M A I N */
void loop() // run over and over
{

    if ( Serial1.available() ) {
      //read incoming from remote controller
       u8_data = Serial1.read();

       if(u8_data == u8_start_byte){
				 i_index = 1;
			 }
			 else if(i_index == 1){
				 u8_motor1_state = u8_data;
				 i_index = 2;
			 }
			 else if(i_index == 2){
				 u8_motor2_state = u8_data;
				 i_index = 3;
			 }
			 else if(i_index == 3){
				 u8_command_state = u8_data;
				 i_index = 4;
			 }
    }

		//Write to motor control
		Serial1.write(u8_motor1_speed);
		Serial1.write(u8_motor3_speed);

}


/* F U N C T I O N S */
