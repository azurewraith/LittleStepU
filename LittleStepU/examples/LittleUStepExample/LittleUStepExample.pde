#include <LittleStepU.h>
#include <NewSoftSerial.h>

#define SPEED 400

//create a new LittleUStep class
//rxPin = 2, txPin = 3, busyPin = 4
LittleStepU uStep(2, 3, 4);
LittleStepU uStep2(5, 6, 7); 

void setup() 
{
  
  delay(100);
  uStep.SetSpeed(SPEED);
  uStep2.SetSpeed(SPEED);
  uStep.GoToRelativePosition(8000);
  uStep2.GoToRelativePosition(7000);
  //uStep.WaitForBusyLow();
  //uStep2.WaitForBusyLow();
  uStep.SetSpeed(SPEED);
  uStep2.SetSpeed(SPEED);
  uStep.SetHomePosition();
  uStep2.SetHomePosition();
  uStep.SetOffStatePower(false);
  uStep2.SetOffStatePower(false);
  delay(200);
}

void loop() 
{ 
  //move ustep as desired
  uStep.GoToRelativePosition(-8000);
  uStep2.GoToRelativePosition(+5000);
  
  uStep.SetSpeed(200);
  uStep2.SetSpeed(250);
  uStep.SetSpeed(250);
  
  //halt if desired
  stop(); 
}

//indefinitely stops execution until reset button is pressed
void stop() 
{
  while(1) { }  
}


