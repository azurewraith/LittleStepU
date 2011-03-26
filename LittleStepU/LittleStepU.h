/*
  LittleStepU.h - Library for interfacing with the LittleStepU
  stepper motor controller
*/

#ifndef LittleStepU_h
#define LittleStepU_h

#include "WProgram.h"
//#include "../SoftwareSerial/SoftwareSerial.h"
#include "../NewSoftSerial/NewSoftSerial.h"

class LittleStepU
{
  public:
    LittleStepU(int rxPin, int txPin, int busyPin);
	void SetSpeed(int stepSpeed);
	void GoToRelativePosition(int relativePosition);
	void SetHomePosition();
	void SetOffStatePower(boolean enable);
	void GoToAbsolutePosition(long absolutePosition);
	void WaitForBusyLow();
	void GoToHomePosition();
	void ClearBuffer(char buffer[30]);
  private:
	int m_busyPin;
	NewSoftSerial *m_ser;
	//char buffer[30];
};

#endif

