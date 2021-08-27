
int in1=3 ;
int in2=9 ;
int in3=10 ;
int in4=11 ;
void setup() {
  Serial.begin(38400);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop() {
  
tt() ;
}
void avant(void){
  analogWrite(in1, 120);
  analogWrite(in2, 0);
  analogWrite(in3, 120);
  analogWrite(in4, 0);}
  void arriere(void){
    analogWrite(in1, 0);
  analogWrite(in2, 120);
  analogWrite(in3, 0);
  analogWrite(in4, 120);}
  void droite(void){
  analogWrite(in1, 120);
  analogWrite(in2, 0);
  analogWrite(in3, 0);
  analogWrite(in4, 120);}
  void gauche(void){
     analogWrite(in1, 0);
  analogWrite(in2, 120);
  analogWrite(in3, 120);
  analogWrite(in4, 0);}

void tt(void) {  char c;
  if (Serial.available()) {
    c = Serial.read();
    Serial.println(c);
  
  if (c == 'F') {
  avant() ;
  Serial.print("avancer");
  }
  else if (c == 'B') {
  arriere() ;
   
  }
  else if (c == 'R') {
 gauche() ;
   Serial.print("droite");
  }
  else if (c == 'L') {
droite() ;
   
  }
else if(c=='S') {
  analogWrite(in1, 0);
  analogWrite(in2, 0);
  analogWrite(in3, 0);
  analogWrite(in4, 0);
 Serial.print("stop");
 }
}
}
