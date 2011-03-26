#include <stdlib.h>
/*
__extension__ typedef int __guard __attribute__((mode (__DI__)));

int __cxa_guard_acquire(__guard *g) {return !*(char *)(g);};
void __cxa_guard_release (__guard *g) {*(char *)g = 1;};
void __cxa_guard_abort (__guard *) {};

*/

void * operator new(size_t size);
void operator delete(void * ptr);

void * operator new(size_t size)
{
  return malloc(size);
}

void operator delete(void * ptr)
{
  free(ptr);
}

/*
  LittleStepU.cpp - Library for interfacing with the LittleStepU
  stepper motor controller
*/

#include "WProgram.h"
#include "LittleStepU.h"

LittleStepU::LittleStepU(int rxPin, int txPin, int busyPin) 
{
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  pinMode(busyPin, INPUT);
  m_busyPin = busyPin;
  m_ser = new NewSoftSerial(rxPin, txPin);
  m_ser->begin(2400);
}

/*
A - SET SPEED
Syntax {Axxxxx} Default value 100 steps/sec
Sets the maximum speed in steps per second for any commands that follow. The
numeric value can be any number from 1 to 5000. 
*/
void LittleStepU::SetSpeed(int stepSpeed) 
{
  char str[30];
  sprintf(str, "{A%i}", stepSpeed);
  m_ser->print(str);
  m_ser->flush();
}

/* 
E - GO TO RELATIVE POSITION
Syntax {Exxxxxx}
This command is similar to the "D" command in respect to the numeric parameter, but
commands the motor to move to a position relative to its current position. Positive
numbers are clockwise and negative numbers are counter-clockwise.
Example: If the current position is 2500, a command of {E1000} will cause the motor to
run 1000 steps clockwise to end at position 3500.
*/
void LittleStepU::GoToRelativePosition(int relativePosition) 
{
  char str[30];
  sprintf(str, "{E%i}", relativePosition);
  m_ser->print(str);
}

/*
Q - SET HOME POSITION
Syntax {Q}
This command unconditionally sets the position register to 0. All position information and
absolute moves become relative to this new home position.
Example: A drilling sequence needs to be repeated several times over a panel. The total
size of the program can be reduced by moving the offset amount, resetting the home
position with the {Q} command and repeating the same sequence.
*/
void LittleStepU::SetHomePosition() 
{
  char str[30];
  sprintf(str, "{Q}");
  m_ser->print(str);
}

/*
N - GO TO THE HOME POSITION
Syntax {N}
Sending an "N" command will cause the Little Step-U to move the motor to the 0, or
home position. The position register defaults to 0 when the device is powered on and can
be set to 0 by the "J" or "Q" commands.
Example: A Little Step-U is being used to position a print head in a dot matrix printer. At
each Carriage Return in the data being printed, an {N} command is issued to return the
head to the left margin, ready for the next line.
*/
void LittleStepU::GoToHomePosition() 
{
  char str[30];
  sprintf(str, "{N}");
  m_ser->print(str);
}

/*
P - SET OFF STATE POWER
Syntax {Px}
When the motor is not being moved, the coils can be left energised for maximum holding
torque or turned off to reduce power consumption and motor heating. This command sets
the state as off {P0} or on {P1} and will remain that way until changed with another "P"
command. Power on default is off.
Example: A motor is being used in a high vibration environment and retaining position is
more important than power consumption. The {P1} command ensures maximum holding
torque.
*/
void LittleStepU::SetOffStatePower(boolean enable) {
  char str[30];
  if (enable) {
    sprintf(str, "{P1}");
    m_ser->print(str);
  } else {
    sprintf(str, "{P0}");
    m_ser->print(str);
  }
}

/*
D - GO TO ABSOLUTE POSITION
Syntax {Dxxxxxxxx}
At anytime after powerup, the Little Step-U keeps track of its current position in steps.
This command instructs the Little Step-U to calculate the direction and number of steps
required to move to another position and then it performs the move. At the end of the
move, the position will be the number specified in this command. The value can be any
number from -10000000 to +10000000, including 0. The number may be preceded by a
"+" or "-" as required, but must not include a comma or decimal point.
Example: If the current position is 2500, a command of {D-1000} will cause the motor to
run counter-clockwise for 1500 steps, stopping at position 1000.
*/
void LittleStepU::GoToAbsolutePosition(long absolutePosition) {

  if (absolutePosition < -10000000L || absolutePosition > 10000000L) {
     return; 
  }
  
  char str[30];
  sprintf(str, "{D%l}", absolutePosition);
  m_ser->print(str);
}

void LittleStepU::WaitForBusyLow() {
  while (m_busyPin != 0) {
	delay(10);
  }
  delay(1);
}

void LittleStepU::ClearBuffer(char buffer[30]) {
  for (int i = 0; i < 30; i++) {
	buffer[i] = ' ';
  }
}
