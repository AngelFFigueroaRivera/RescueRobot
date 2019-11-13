#include "Robotec.h"
Robotec ROB;
char serialCharacter;

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
        ROB.MoveRobot(0, 0);
}
  /* add main program code here */


void loop()
{	
  if(Serial.available()>0)
  {
    serialCharacter=Serial.read();
    switch(serialCharacter)
    {
               //a: Si la mano esta en la derecha
      case 'a':   
              ROB.MoveRobotRight(1,0);
                break;
              
                //b:Si la mano esta en la izquierda
      case 'b': 
              ROB.MoveRobotLeft(0,1);
                break;
              
                //c: Si la mano esta arriba
      case 'c': 
               ROB.MoveRobotStraight(1,1);
               break;
              
                //d: Si la mano esta abajo
      case 'd': 
               ROB.MoveRobotBack(-1,-1);
                 break;
      //Los motores no se mueven e
      case 'e': 
               ROB.StopRobotMove(0,0);
               
               
                 break;      
                //Cualquier otra cosa 
      case 'f':
        ROB.TurnOnOffLED1(0);
                 ROB.TurnOnOffLED2(0);
                 ROB.TurnOnOffLED3(0);
                 ROB.TurnOnOffLED4(0);
                 ROB.MoveRobot(0, 0);
                 break;
      default:   ROB.TurnOnOffLED1(1);
                 ROB.TurnOnOffLED2(0);
                 ROB.TurnOnOffLED3(0);
                 ROB.TurnOnOffLED4(1);
                 ROB.MoveRobot(0, 0);
                 break;
    }
  }
}
