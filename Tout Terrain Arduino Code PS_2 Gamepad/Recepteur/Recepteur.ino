#include <PS2X_lib.h> /* PS2 Controller Library http://www.billporter.info/2010/06/05/playstation-2-controller-arduino-library-v1-0/ */
PS2X ps2x; /* on crée l'instance du controleur */
const byte dataPin = 12;
const byte commandPin = 11;
const byte attentionPin = 10;
const byte clockPin = 13;
void setup() {
  Serial.begin(9600);
  pinMode(5, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);

  /* config_gamepad(clock, command, attention, data, Pressures?, Rumble?) */
  ps2x.config_gamepad(clockPin, commandPin, attentionPin, dataPin, true, true); // gardez true, true à la fin même si pas de moteurs

  if (ps2x.readType() == 1) Serial.println(F("DualShock"));
  else {
    Serial.print(F("Manette Absente - code "));
    Serial.println(ps2x.readType());
    while (true); // on meurt ici, éventuellement enlever si vous avez un autre code manette
  }

  ps2x.read_gamepad(); // initialisation des valeurs
  delay(50);
  ps2x.read_gamepad();  /* initialise les états */
}





void loop() {
  static uint32_t chrono = 0;
  const uint32_t periode = 20ul; // la manette est assez sensible, il ne faut pas lui demander les infos trop souvent. 15ms ou 20ms ça fonctionne pour moi

  if (millis() - chrono >= periode) {
    int RX = 0, RY = 0, LX = 0, LY = 0;
    static int PRX = 127, PRY = 128, PLX = 127, PLY = 128;

    chrono += periode;

    ps2x.read_gamepad();   /* on lit l'état de la manette */
    if (ps2x.Button(PSB_PAD_UP))   {
          ar();
        }
    else{
      if (ps2x.Button(PSB_PAD_RIGHT)) {
    
      ga();
       }
      else {
        if (ps2x.Button(PSB_PAD_LEFT))  {
      
      da();
          }
        else {
          if (ps2x.Button(PSB_PAD_DOWN)) {
        
      av();
          }
          else stp();
        }}}

/*    LX = ps2x.Analog(PSS_LX);          
    LY = ps2x.Analog(PSS_LY);          
    RX = ps2x.Analog(PSS_RX);          
    RY = ps2x.Analog(PSS_RY);          

    // si une des coordonnées des joystick a changé alors on imprime les nouvelles coordonnées
    if ((LX != PLX) || (LY != PLY) || (RX != PRX) || (RY != PRY)) {
      PLX = LX;
      PLY = LY;
      PRX = RX;
      PRY = RY;
      Serial.print(LX);    Serial.print(F(" ,"));
      Serial.print(LY);    Serial.print(F(" ,"));
      Serial.print(RX);    Serial.print(F(" ,"));
      Serial.println(RY);
      */
    




/*  recvData();

  unsigned long now = millis();
  if ( now - lastRecvTime > 1000 ) {
    resetData();
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





/*

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


}
void av() {
  Serial.print("av");

  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
}
void ar() {
  Serial.print("arier");

  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
}
void ga()
{

  Serial.print("gauche");
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
}
void da()
{

  Serial.print("droite");
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
}
void stp() {

  Serial.print("stp");
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
}
