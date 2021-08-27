#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
const uint64_t pipeIn = 0xDDDD10F0E1LL;
int g, d;
RF24 radio(9,10);

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
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);

  data.x1 = 127;
  data.x2 = 127;
  data.y1 = 127;
  data.y2 = 127;
  data.b1 = 0;
  data.b2 = 0;

}
void av() {
  Serial.print("av");
  d = map(data.y1, 120, 0, 0, 255);
  g = map(data.y1, 120, 0, 0, 255);
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
}
void ar() {
  Serial.print("arier");
  
    d=map(data.y1,132,255,0,255);
    g=map(data.y1,132,255,0,255);
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
}
void ga()
{
    d=map(data.x2,115,0,0,255);
    g=map(data.x2,115,0,0,255);
  Serial.print("gauche");
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
}
void da()
{
    d=map(data.x2,130,255,0,255);
    g=map(data.x2,130,255,0,255);
  Serial.print("droite");
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
}
void stp() {
  d=0;
  g=0;
  Serial.print("stp");
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
}
void setup()
{
  pinMode(5, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);


  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);

  Serial.begin(9600);
  resetData();
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(1, pipeIn);
  radio.startListening();
}



unsigned long lastRecvTime = 0;

void recvData()
{
  while ( radio.available() ) {
    radio.read(&data, sizeof(MyData));
    lastRecvTime = millis();
  }
}

int y2, y1, x1, x2;

void loop()
{
  recvData();

  unsigned long now = millis();
  if ( now - lastRecvTime > 1000 ) {
    resetData();
    stp();
    
  } else {

    if (data.x2 < 120) {
      if (data.y1 > 135) {
        da();
      }
      else if (data.y1 < 120) {
        ga();
      }
      else {
        av();
      }


    }
     else if (data.x2 > 135) {
      if (data.y1 > 135) {
        da();
      }
      else if (data.y1 < 120) {
        ga();
      }
      else {
        ar();
      }
    }
    else {
      if (data.y1 > 135) {
        da();
      }
      else if (data.y1 < 120) {
        ga();
      }
      else {
        stp();
      }
    }
/*
analogWrite(5,d);
analogWrite(6,g);



Serial.print("  d  ");
Serial.print(d);
Serial.print("  g  ");
Serial.print(g);
Serial.print("  ");
*/
 
  }
     Serial.print("  ");
    Serial.print(data.x1);
    Serial.print("  ");
    Serial.print(data.x2);
    Serial.print(" ");
    Serial.print(data.y1);
    Serial.print(" ");
    Serial.print(data.y2);
    Serial.print(" ");
 /*   Serial.print(data.b1);
    Serial.print(" ");  
    Serial.print(data.b2);
    Serial.print(" ");
    Serial.print(data.b3);
    Serial.print(" ");
    Serial.print(data.b4);*/
    Serial.println(" ");
}
