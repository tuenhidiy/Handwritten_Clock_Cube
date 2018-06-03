/*
Name    : myCUBE_UNO_16x8x8_03062018.ino
Project : LED CUBE 16x8x8 (8x8x8 RED & 8x8x8 GREEN)
Version : 1.0
Date    : 03.06.2018
Author  : tuenhidiy
Email   : tuenhi.n2012@gmail.com
*/

#include "myCUBE.h"
#include "myCUBEClass.h"
#include "Wire.h"

#define RowA_Pin  2
#define RowB_Pin  3
#define RowC_Pin  4
#define RowD_Pin  5 
#define OE_Pin    6 
#define DATA_Pin  10  
#define CLOCK_Pin 12  
#define STB_Pin   8

// For DS3231
#define DS3231_I2C_ADDRESS 0x68
unsigned long samplingtime = 0;   

void setup () 
{
     myCUBE.Init(DATA_Pin, CLOCK_Pin, RowA_Pin, RowB_Pin, RowC_Pin, RowD_Pin, OE_Pin, STB_Pin);
     Wire.begin();
}    

void loop()
{
Display_H();
Display_M_S();
}

void ReadDS3231Time(byte *second, byte *minute, byte *hour, byte *dayOfWeek, byte *dayOfMonth, byte *month, byte *year)
{
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // Set DS3231 register pointer to 00h
  Wire.endTransmission();

  // Request seven bytes of data from DS3231 starting from register 00h
  Wire.requestFrom(DS3231_I2C_ADDRESS, 7);
  *second = (Wire.read() & 0x7f);
  *minute = (Wire.read());
  *hour = (Wire.read() & 0x3f);
  //*dayOfWeek = (Wire.read());
  //*dayOfMonth = (Wire.read());
  //*month = (Wire.read());
  //*year = (Wire.read());
}

void Display_M_S()
{
  if ( (unsigned long) (millis() - samplingtime) > 1000  )
  {
    byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  
  // Read data from DS3231
    ReadDS3231Time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);
    myCUBE.HandwrittenNumber(AXIS_Z, 7, 0, (minute >> 4 & 0x0f), 1);              
    myCUBE.HandwrittenNumber(AXIS_Z, 7, 8, (minute & 0x0f), 1); 
    myCUBE.HandwrittenNumber(AXIS_X, 0, 0, (second >> 4 & 0x0f), 1);              
    myCUBE.HandwrittenNumber(AXIS_X, 0, 8, (second & 0x0f), 1); 
    delay(1000);

  if (rand()%2 ==0)
    {
      myCUBE.TransitionShift(AXIS_Z, NEGATIVE, 100);
    }
    
    else
    {
    myCUBE.Eraser(AXIS_X, 0, 0); 
    myCUBE.Eraser(AXIS_Z, 7, 0);   
    myCUBE.Eraser(AXIS_X, 0, 8);
    myCUBE.Eraser(AXIS_Z, 7, 8);
    }   
       
  samplingtime = micros();
  }
}
void Display_H()
{  
  {
  if ( (unsigned long) (millis() - samplingtime) > 3333  )
  {
    byte second, minute, hour, dayOfWeek, dayOfMonth, month, year, dir;
  
  // Read data from DS3231
    ReadDS3231Time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);            
    
    myCUBE.HandwrittenNumber(AXIS_X, 0, 0, (hour >> 4 & 0x0f), 1); 
    myCUBE.HandwrittenNumber(AXIS_X, 0, 8, (hour & 0x0f), 1);              
    delay(1000);
    if (rand()%3 ==0)
    {
      myCUBE.TransitionShift(AXIS_Z, POSITIVE, 100);
    }
    else if(rand()%3 ==1)
    {
      byte AXIS1 = random(1,3);
      int POLAR1 = random(0,2);
      
      myCUBE.TransitionScroll(AXIS1, POLAR1, 100);// OK
      myCUBE.TransitionScroll(AXIS1, POLAR1, 100);// OK
      myCUBE.TransitionScroll(AXIS1, POLAR1, 100);// OK
      myCUBE.TransitionScroll(AXIS1, POLAR1, 100);// OK
      
      byte AXIS2 = random(1,3);
      int POLAR2 = random(0,2);
      
      myCUBE.TransitionScroll(AXIS2, POLAR2, 100);// OK
      myCUBE.TransitionScroll(AXIS2, POLAR2, 100);// OK
      myCUBE.TransitionScroll(AXIS2, POLAR2, 100);// OK
      myCUBE.TransitionScroll(AXIS2, POLAR2, 100);// OK
      delay(500);
      
      myCUBE.TransitionShift(AXIS_Z, POLAR2, 100);
    }
    else
    {
    myCUBE.Eraser(AXIS_X, 0, 0);
    myCUBE.Eraser(AXIS_X, 0, 8);
    }   
  samplingtime = micros();
  }
}
}


