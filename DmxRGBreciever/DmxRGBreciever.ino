// - - - - -
// DmxSerial - A hardware supported interface to DMX.
// address 1 (red) -> PWM Port 5
// address 2 (green) -> PWM Port 6
// address 3 (blue) -> PWM Port 9
// 
// Copyright (c) 2011-2015 by Matthias Hertel, http://www.mathertel.de
// This work is licensed under a BSD style license. See http://www.mathertel.de/License.aspx
// 
// Documentation and samples are available at http://www.mathertel.de/Arduino
// 25.07.2011 creation of the DmxSerial library.
// 10.09.2011 fully control the serial hardware register
//            without using the Arduino Serial (HardwareSerial) class to avoid ISR implementation conflicts.
// 01.12.2011 include file and extension changed to work with the Arduino 1.0 environment
// 28.12.2011 changed to channels 1..3 (RGB) for compatibility with the DmxSerialSend sample.
// 10.05.2012 added some lines to loop to show how to fall back to a default color when no data was received since some time.
// - - - - -

#include <DMXSerial.h>

// Constants for demo program

byte DMXchannel ;  // lowest DMX address RGB lamp with 6channels via DIPswitch instelbaar op A0 tem. A7

const int RedPin =    11;  // PWM output pin for Red Light.
const int GreenPin =  10;  // PWM output pin for Green Light.
const int BluePin =   9;  // PWM output pin for Blue Light.

const int Redled =    6;  // PWM output pin for Red Light.
const int Greenled =  5;  // PWM output pin for Green Light.
const int Blueled =   3;  // PWM output pin for Blue Light.

#define RedDefaultLevel   255 //red toont blauw
#define GreenDefaultLevel 0
#define BlueDefaultLevel  0

void setup () {


  DMXSerial.init(DMXReceiver);
  
  // set some default values
   

    DMXSerial.write(1, 0);
   DMXSerial.write(2, 0);
    DMXSerial.write(3, 255);
  delay(500);
  // enable pwm outputs
  pinMode(RedPin,   OUTPUT); // sets the digital pin5 as output pwm led A
  pinMode(GreenPin, OUTPUT);//sets the digital pin6 as output
  pinMode(BluePin,  OUTPUT);//sets the digital pin9 as output

  pinMode(Redled,   OUTPUT); // sets the digital pin5 as output pwm led B
  pinMode(Greenled, OUTPUT);//sets the digital pin6 as output
  pinMode(Blueled,  OUTPUT);//sets the digital pin9 as output
  

//enable optional dipswitch to set differant dmx address then 1
  pinMode(A0,  INPUT_PULLUP); 
  pinMode(A1,  INPUT_PULLUP);
  pinMode(A2,  INPUT_PULLUP);
  pinMode(A3,  INPUT_PULLUP);
  pinMode(A4,  INPUT_PULLUP);
  pinMode(A5,  INPUT_PULLUP);
  pinMode(A6,  INPUT_PULLUP);
  pinMode(A7,  INPUT_PULLUP);
  byte  pinStateA6 = analogRead(A6) > 100 ? 0 : 1; //a6 and a7 are not digitalinput
  byte  pinStateA7 = analogRead(A7) > 100 ? 0 : 1;
  bitWrite(DMXchannel, 0, !digitalRead(A0)) ;
  bitWrite(DMXchannel, 1, !digitalRead(A1)) ;
  bitWrite(DMXchannel, 2, !digitalRead(A2)) ;
  bitWrite(DMXchannel, 3, !digitalRead(A3)) ;
  bitWrite(DMXchannel, 4, !digitalRead(A4)) ;
  bitWrite(DMXchannel, 5, !digitalRead(A5)) ;
  bitWrite(DMXchannel, 6, pinStateA6) ;
  bitWrite(DMXchannel, 7, pinStateA7) ;
DMXchannel < 1 ? DMXchannel=1 : 0 ; //indien DIP switch dmx address is 0 , then set autoadres op 1

//uncomment to set DMX address  hardcoded
  // DMXchannel  =  4;            
}


void loop() {
  // Calculate how long no data backet was received
  unsigned long lastPacket = DMXSerial.noDataSince();
  
  if (lastPacket < 1500) {
    // read recent DMX values and set pwm levels 
    analogWrite(RedPin,   DMXSerial.read(DMXchannel +0 ));//channel 4 5 6 address of dmx universe
    analogWrite(GreenPin, DMXSerial.read(DMXchannel +1));
    analogWrite(BluePin,  DMXSerial.read(DMXchannel +2));
    
    analogWrite(Redled,  DMXSerial.read(DMXchannel +3));
    analogWrite(Greenled,  DMXSerial.read(DMXchannel +4));
    analogWrite(Blueled,  DMXSerial.read(DMXchannel +5));

  } else {
    // Show pure red color, when no data was received since 5 seconds or more.
 
    analogWrite(RedPin,   RedDefaultLevel);
    analogWrite(GreenPin, GreenDefaultLevel);
    analogWrite(BluePin,  BlueDefaultLevel);
    
     analogWrite(Redled,  255);
      analogWrite(Greenled,  0);
       analogWrite(Blueled,  0);
  } // if
}

// End.
