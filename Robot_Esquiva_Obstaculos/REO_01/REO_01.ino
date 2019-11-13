#include <AFMotor.h>

AF_DCMotor M1(1);
AF_DCMotor M2(2);

int Trig = 38;
int Echo = 36;

int cont = 0;
int aux = 0;

void setup() 
{
  //Serial.begin (9600);
  M1.setSpeed(180);
  M2.setSpeed(180);
  
  pinMode(Trig,OUTPUT);
  pinMode(Echo,INPUT);
}

void loop() 
{
  long duracion;
  long distancia;
  
  digitalWrite(Trig,LOW);
  delayMicroseconds(2);
  digitalWrite(Trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig,LOW);
  
  duracion = pulseIn(Echo,HIGH);
  distancia = (duracion/2)/29;

  //Serial.println(distancia);
  if(distancia > 10)
  {
    M1.run(FORWARD);
    M2.run(FORWARD);
  }
  else
  {
    M1.run(FORWARD);
    M2.run(BACKWARD);
  }
  delay(100);
}
