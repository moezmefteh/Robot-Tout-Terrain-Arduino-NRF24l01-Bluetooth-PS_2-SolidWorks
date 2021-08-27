
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const uint64_t pipeOut = 0xDDDD10F0E1LL; //0xABDE10F0E1LL
RF24 radio(9, 10);

// The sizeof this struct should not exceed 32 bytes
// This gives us up to 32 8 bits channals
struct MyData {
  byte x1;
  byte x2;
  byte y1;
  byte y2;
  byte b1;
  byte b2;
  byte b3;
  byte b4;
};

MyData data;

void resetData()
{

  data.x1 = 127;
  data.x2 = 127;
  data.y1 = 127;
  data.y2 = 127;
  data.b1 = 1;
  data.b2 = 1;
  data.b3 = 1;
  data.b4 = 1;
}

void setup()
{
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);

  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(pipeOut);
  resetData();
}


/*
int mapJoystickValues(int val, int lower, int middle, int upper, bool reverse)
{
  val = constrain(val, lower, upper);
  if ( val < middle )
    val = map(val, lower, middle, 0, 128);
  else
    val = map(val, middle, upper, 128, 255);
  return ( reverse ? 255 - val : val );
}
*/
void loop()
{
  int x1, x2, y1, y2;


  x1 = map( analogRead(A0), 0, 1023, 0, 255);
  y1 = map( analogRead(A1), 0, 1023, 255, 0);
  x2 = map( analogRead(A2), 0, 1023, 0, 255);
  y2 = map( analogRead(A4), 0, 1023, 0, 255);

  data.x1 = x1;
  data.y1 = y1;
  data.x2 = x2;
  data.y2 = y2;
  data.b1 = digitalRead(4);
  data.b2 = digitalRead(5);
  data.b3 = digitalRead(6);
  data.b4 = digitalRead(7);

  radio.write(&data, sizeof(MyData));
  // The calibration numbers used here should be measured
  // for your joysticks till they send the correct values.

  /* data.x1 = mapJoystickValues( analogRead(A0), 0, 512, 1023, true );
    data.y1      = mapJoystickValues( analogRead(A1),  0, 512, 1023, true );
    data.x2    = mapJoyst226ickValues( analogRead(A2), 0, 512, 1023, true );
    data.y2     = mapJoystickValues( analogRead(A3), 0, 512, 1023, true );
  */



}
