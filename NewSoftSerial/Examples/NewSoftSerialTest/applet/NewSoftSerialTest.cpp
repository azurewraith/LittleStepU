
#include <NewSoftSerial.h>

#include "WProgram.h"
void setup();
void loop();
NewSoftSerial mySerial(2, 3);

void setup()  
{
  //Serial.begin(57600);
  //Serial.println("Goodnight moon!");

  // set the data rate for the NewSoftSerial port
  mySerial.begin(2400);
  delay(100);
  mySerial.println("Hello, world?");
}

void loop()                     // run over and over again
{

  /*if (mySerial.available()) {
      Serial.print((char)mySerial.read());
  }
  if (Serial.available()) {
      mySerial.print((char)Serial.read());
  }*/
  
  char str[30];
  sprintf(str, "{A%i}", 100);
  mySerial.print(str);
  
  char str2[30];
  sprintf(str2, "{A%i}", 400);
  mySerial.print(str2);
  
  delay(20);
  mySerial.print("{A200}");
  delay(100);
  mySerial.print("{A250}");
  
  while(1)
  {
    delay(100);
  }
}

int main(void)
{
	init();

	setup();
    
	for (;;)
		loop();
        
	return 0;
}

