//7 segement count down timer

/*

    A
   ---
F |   | B
  | G |
   ---
E |   | C
  |   |
   ---  . dec
    D

*/
////////////////////////
//    Ardino pinout
//////////////////////
const int a = 9; 
const int b = 2;
const int c = 3;
const int d = 5;
const int e = 6;
const int f = 8;
const int g = 7;
const int p = 4;
int startStopReset = 18;

bool buttonState = true;
int minutes = 10; //start time -> CAN CHANGE TO WHATEVER TIME YOU WANT
int seconds = 9;  //start time -> CAN CHANGE TO WHATEVER TIME YOU WANT
int totalMinutes = 0;
float totalSeconds = minutes*60 + seconds;
float totalMilliseconds = totalSeconds*1000;
float totalMicroseconds = totalMilliseconds*1000;

const int d1 =10;
const int d2 =11;
const int d3 =12;
const int d4 =13;


int del = 2500; //delay value in microseconds
void setup()
{
  Serial.begin(9600); // open the serial port at 9600 bps:
  pinMode(d1, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d3, OUTPUT);
  pinMode(d4, OUTPUT);
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(p, OUTPUT);
  pinMode(startStopReset, INPUT); 
  digitalWrite(startStopReset, HIGH); 
}
 
void loop()
{
  digitalWrite (p, HIGH);

  clearLEDs();
  pickSegment(1);
  pickNumber(0);
  delayMicroseconds(del);
 
  clearLEDs();
  pickSegment(2);
  dispDec(2);
  pickNumber(1);
  delayMicroseconds(del);
 
  clearLEDs();
  pickSegment(3);
  pickNumber(2);
  delayMicroseconds(del);
 
  clearLEDs();
  pickSegment(4);
  pickNumber(3);
  delayMicroseconds(del);
 
  totalMicroseconds = totalMicroseconds - 10000; //totalMilliseconds++' for stopwatch
  totalMilliseconds = totalMicroseconds/1000;
  totalSeconds = int(totalMilliseconds/1000)+1;
  totalMinutes = int(totalSeconds/60)+1;
  
  Serial.println(totalSeconds+1);
  
  if (digitalRead(startStopReset)) // checks if button is pressed
  {
    delay(200);
    if (!buttonState) // check if button is false
    {
      buttonState = true;
        
      totalSeconds = minutes*60 + seconds;
      totalMilliseconds = totalSeconds*1000;
      totalMicroseconds = totalMilliseconds*1000;
    }
  }
  else buttonState = false;
        
}
 
void pickSegment(int x) //changes digit
{
  digitalWrite(d1, HIGH);
  digitalWrite(d2, HIGH);
  digitalWrite(d3, HIGH);
  digitalWrite(d4, HIGH);
 
  switch(x)
  {
  case 1: 
    digitalWrite(d1, LOW); 
    break;
  case 2: 
    digitalWrite(d2, LOW);
    digitalWrite(p, HIGH); 
    break;
  case 3: 
    digitalWrite(d3, LOW);
    break;
  default: 
    digitalWrite(d4, LOW); 
    break;
  }
}
 
void pickNumber(int x) //changes value of number
{
  switch(x)
  {
  default: 
    zero(); 
    break;
  case 1: 
    one(); 
    break;
  case 2: 
    two(); 
    break;
  case 3: 
    three(); 
    break;
  case 4: 
    four(); 
    break;
  case 5: 
    five(); 
    break;
  case 6: 
    six(); 
    break;
  case 7: 
    seven(); 
    break;
  case 8: 
    eight(); 
    break;
  case 9: 
    nine(); 
    break;
  }
}
 
void dispDec(int x)
{
  digitalWrite(p, LOW);
}
 
void clearLEDs()
{
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  digitalWrite(p, LOW);
}
 
void zero()
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, LOW);
}
 
void one()
{
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}
 
void two()
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
}
 
void three()
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
}
 
void four()
{
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}
 
void five()
{
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}
 
void six()
{
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}
 
void seven()
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}
 
void eight()
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}
 
void nine()
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}
