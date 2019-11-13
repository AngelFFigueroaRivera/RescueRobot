// Robotec.h
#ifndef _ROBOTEC_h
#define _ROBOTEC_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif


class Robotec
{
private:
	int ROBOTEC;
public:
	Robotec();
	void InitWireless();
    void SoundOn(int Frequency, int Duration);
	void SoundOff();
	double GetTemp();
	int GetDistance();
	void Setup();
	void MoveRobot(int SpeedWheelLeft, int SpeedWheelRight);
	void MoveRoboTime(int SpeedWheelLeft, int SpeedWheelRight, int time);
	double GetSpacePosition();
	int GetXPosition();
	int GetYPosition();	
	int GetZPosition();
	bool Switch1();
	bool Switch2();
	bool Switch3();
	bool Switch4();
	int LightSensorRight();
	int LightSensorLeft();
	void ColorRGB (int Red, int Green, int Blue );
	void TurnOnOffLED1(int OnOff);
	void TurnOnOffLED2(int OnOff);
	void TurnOnOffLED3(int OnOff);
	void TurnOnOffLED4(int OnOff);
	void OnOffLed1Switch();
	void OnOffLed2Switch();
	void OnOffLed3Switch();
	void OnOffLed4Switch();
	int LeeSwitch();
	int ReadExtSensor1();
        void MoveRobotBack(int SpeedWheelLeft, int SpeedWheelRight);
        void MoveRobotStraight(int SpeedWheelLeft, int SpeedWheelRight);
        void MoveRobotLeft(int SpeedWheelLeft, int SpeedWheelRight);
        void MoveRobotRight(int SpeedWheelLeft, int SpeedWheelRight);
        void StopRobotMove(int SpeedWheelLeft, int SpeedWheelRight);
};
extern Robotec ROBOTEC;

#endif

