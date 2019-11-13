#include "Robotec.h"
void setup()
{
	Serial.begin(9600);
	pinMode(2, OUTPUT);
	pinMode(4, OUTPUT);
	pinMode(6, OUTPUT);
	pinMode(7, OUTPUT);
	pinMode(8, OUTPUT);
	pinMode(9, OUTPUT);
	pinMode(10, OUTPUT);
	pinMode(11, OUTPUT);
	pinMode(12, OUTPUT);
	pinMode(13, OUTPUT);
}
  /* add main program code here */
Robotec ROB;
double TEM;
int distance;
int senluzizq, senluzder, AceX, AceY, AceZ;

void loop()
{
	ROB.OnOffLed3Switch();
	ROB.OnOffLed2Switch();
		ROB.OnOffLed1Switch();
	ROB.OnOffLed4Switch();
	//ROB.SoundOn(1, 1000);
	ROB.SoundOff();
	TEM=ROB.GetTemp();
	senluzizq= ROB.LightSensorLeft();
	senluzder= ROB.LightSensorRight();
	TEM= ROB.GetTemp();
	AceX= ROB.GetXPosition();
	AceY= ROB.GetYPosition();
	AceZ= ROB.GetZPosition();
	distance= ROB.GetDistance();
	int lectura=ROB.LeeSwitch();
	delay(200);
	ROB.MoveRobot(0,0);
	//delay(1000);
	//ROB.MoveRobot(-255,-255);
	//delay(1000);
	//ROB.MoveRobot(255,-255);
	//delay(1000);
	//ROB.MoveRobot(-255,255);
	//delay(1000);
	Serial.print("Temperatura ext: ");
	Serial.print(TEM);
	Serial.print(" Sensor luz izq-der: ");
	Serial.print(senluzizq);
	Serial.print(" ");
	Serial.print(senluzder);
	Serial.print(" ");
	Serial.print(" Distancia: ");
	Serial.print(distance);
	Serial.print(" ");
	Serial.print("X: ");
	Serial.print(AceX);
	Serial.print(" ");
	Serial.print("Y: ");
	Serial.print(AceY);
	Serial.print(" ");
	Serial.print("Z: ");
	Serial.print(AceZ);
	Serial.print("Lectura: ");
	Serial.print(lectura);
	Serial.println(" ");
	ROB.ColorRGB(1,0,1);
    ROB.TurnOnOffLED4(0);
	ROB.TurnOnOffLED3(0);
	ROB.TurnOnOffLED2(0);
	ROB.TurnOnOffLED1(0);
}
