/*
   The circuit:
 * RX is digital pin (Recieve) (connect to TX of other device)
 * TX is digital pin (Transmit) (connect to RX of other device)
 */
/* I N C L U D E S */
//#include <SoftwareSerial.h> // On ATmega 328(Uno) based Arduinos AltSoftSerial uses pin 8 for RX and pin 9 for TX


/* D E F I N E S */

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




unsigned int calibrate_x = 175;
unsigned int calibrate_y = 120;
unsigned int calibrate_area = calibrate_y *  calibrate_x;


/* S E T U P */
void setup() //run once
{

	// Start the serial connection with the HM-10 bluetooth module
	Serial1.begin(baud,SERIAL_8N1);

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
		Serial2.write(u8_motor1_speed);
		Serial2.write(u8_motor3_speed);

}


/* F U N C T I O N S */
