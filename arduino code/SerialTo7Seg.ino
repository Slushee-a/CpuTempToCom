/*
    You will need the TM1637 library by Avishay Orpaz
    It is available in the "Manage Libraries" option here in the IDE
    Just search for TM1637 and make sure it is made by Avishay Orpaz
*/

#include <TM1637Display.h>
#define CLK 3  //Define the arduio pin for the CLK pin in the display (Use a digital pin)
#define DIO 4  //Define the arduio pin for the DIO pin in the display (Use a digital pin)

TM1637Display display = TM1637Display(CLK, DIO);  //Create display

int Temp = 0;
int LWD = 0; //(Loops Without Data)

void setup()
{
  Serial.begin(9600);
  display.setBrightness(5);  //Set the display brighness
  display.showNumberDec(1);
  delay(200);
  display.showNumberDec(2);
  delay(200);
  display.showNumberDec(3);
  delay(200);
  display.showNumberDec(4);
  delay(200);
  display.showNumberDec(5);
  delay(200);
  display.showNumberDec(6);
  delay(200);
  display.showNumberDec(7);
  delay(200);
  display.showNumberDec(8);
  delay(200);
  display.showNumberDec(9);
  delay(200);
  display.showNumberDec(10);
  display.clear();
  delay(50000);
}

void loop()
{
  display.setBrightness(5);  //Set the display brighness

  String readString;
  String SerialTemp;

  while (Serial.available())
  {
    delay(1);

    if (Serial.available() > 0)
    {
      char c = Serial.read();
      if (isControl(c))
      {
        break;
      }
      readString += c;
    }
  }

  SerialTemp = readString;
  Temp = SerialTemp.toInt();

  if (Temp >= 10) //Sometimes the display showed numbers like 2 or 4. To stop that I set it to 10 since those values are below 10 and the cpu temp will never go below 10.
  {
    display.showNumberDec(Temp);
    delay(2000);
    LWD = 0;
  }

  else if (Temp >= 10 || LWD >= 2) //I did this so if it doesen't recieve data in two loops it shuts off the display.
  { //Mainly because my computer powers USB devices when it's in sleep mode and I don't
    display.clear();               //want it to have a random number on the display while it's sleeping.
  }

  else
  {
    LWD = ++LWD;
    delay(2000);
  }

}
