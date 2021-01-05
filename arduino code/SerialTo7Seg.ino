/*  
 *  You will need the TM1637 library by Avishay Orpaz
 *  It is available in the "Manage Libraries" option here in the IDE
 *  Just search for TM1637 and make sure it is made by Avishay Orpaz
 */ 

#include <TM1637Display.h>  
#define CLK 3  //Define the arduio pin for the CLK pin in the display (Use a digital pin)
#define DIO 4  //Define the arduio pin for the DIO pin in the display (Use a digital pin)

TM1637Display display = TM1637Display(CLK, DIO);  //Create display

int Temp = 0;  //Define a base int for the temperature value

void setup() 
{
  Serial.begin(9600);  //Start serial port
}

void loop() 
{
  display.setBrightness(5);  //Set the display brighness to max
  
  String readString;  //Create the stings for the serial protocol
  String SerialTemp;

  //====Serial protocol====//
  while (Serial.available())
    {
     delay(1);

     if (Serial.available()>0)
     {
        char c = Serial.read();
        if (isControl(c))
       {
          break;
        }
       readString += c;
     }
   }

  //Make the serial reading an int//
  SerialTemp = readString;
  Temp = SerialTemp.toInt(); 

  //If you have recieved anything that is above 0 in the serial port, print it//
  if (Temp >= 1)
  {
   display.showNumberDec(Temp);
   delay(2000); 
  }

}
