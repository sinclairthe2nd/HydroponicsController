/*
 
  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 */
 
//Load RTCCode
#include <Wire.h>
#include <Rtc_Pcf8563.h>
//init the real time clock
Rtc_Pcf8563 rtc;

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Declaring a couple of Variables

int timeH = 0;
int timeM = 0;
int timeS = 0;
int temp = 0;
int level = 0;
float adc1 = 0;
float adcVoltage = 0;
float calc = 0;
void setup() {
//RTC CODE
//clear out the registers
  rtc.initClock();
//set a time to start with.
//hr, min, sec
rtc.setTime(22, 30, 0);
  
  
//Configure Some Pins for use
pinMode(6, OUTPUT);           // set pin to OUTPUT RelaypinforLight
pinMode(7, OUTPUT);           // set pin to OUTPUT TemperatureManagementOn
pinMode(8, OUTPUT);           // set pin to OUTPUT Switch from HeatingtoCooling
  
  
Serial.begin(9600); // opens serial port, sets data rate to 9600 bps

// set up the LCD's number of columns and rows: 
lcd.begin(16, 2);
}

void loop() 
{
//BASIC RTC READOUT
timeH = rtc.getHour();
timeM = rtc.getMinute();
timeS = rtc.getSecond();
Serial.println(timeH);
Serial.println(timeM);
Serial.println(timeS);


//Switch on light at appropriate time
 if (timeH>8 && timeH<22)
{
digitalWrite(6, HIGH);
}
else
{
digitalWrite(6, LOW);
}

//Get the Voltage on the Probe Input

adc1 = analogRead(A7);
adcVoltage = adc1*0.0049;
Serial.println(adcVoltage);

/*
//Decide on the Water level

if ()
{
digitalWrite(6, HIGH);
}
else
{
digitalWrite(6, LOW);
}

//WaterCoditioning

for now this is commented out since the Pt100 and Heating unit are not used
//Here I Convert the Resistance to a Temperature
//to Cold turn on heating
 if (temp<107)
{
    lcd.setCursor(5, 0);
    lcd.print(" * ");
    digitalWrite(7, HIGH); //WaterconditioningON
    digitalWrite(8, LOW); //CoolingOFF
}
else{;}
//ok do nothing
 if (temp>107&&temp<110)
{
    lcd.setCursor(5, 0);
    lcd.print(" :)");
    digitalWrite(7, LOW); //WaterconditioningON
    digitalWrite(8, LOW); //CoolingOFF
}
else{;}
//to hot! cool
 if (temp>110&&temp<113)
{
    lcd.setCursor(5, 0);
    lcd.print("HOT");
    digitalWrite(7, HIGH); //WaterconditioningON
    digitalWrite(8, HIGH); //CoolingON
}
else{;}
//too HOT!?! We fucked up.....Turn off everything
 if (temp>113)
{
    lcd.setCursor(5, 0);
    lcd.print("-.-");
    digitalWrite(7, LOW); //WaterconditioningON
    digitalWrite(8, LOW); //CoolingOFF
}
else{;}
*/
  //-----------------------------------PrintoutputBlock--------------------------------------------

  //Print Temperature
    lcd.setCursor(0, 0);
    lcd.print("Temp:");
    lcd.setCursor(5, 0);

  // Print Level
    lcd.setCursor(9, 0);
    lcd.print("Level:");
    lcd.setCursor(15, 0);
    lcd.print(level);
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the time
  lcd.print("Time:");
  //----------------Blank the last digit-------------
  if (timeH<9)
{
  lcd.setCursor(6, 1);
  lcd.print(" ");
}
else{;}
  
  //----------------DisplaytheTime----------------------------
  lcd.setCursor(5, 1);
 lcd.print(timeH);
 lcd.setCursor(9, 1);
 //-----------------Display Sun Symbol if light is on--------
 lcd.print("Light:");
 lcd.setCursor(15, 1);
 if (timeH>9&&timeH<22)
{
 lcd.print("*");
 digitalWrite(6, HIGH);
}
else
{
 lcd.print("-");
 digitalWrite(6, LOW);
}

//---------------------------------PrintoutEnd----------------------------------------
}

