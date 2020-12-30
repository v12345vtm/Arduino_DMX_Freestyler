/*
  ASCII table

  Prints out byte values in all possible formats:
  - as raw binary values
  - as ASCII-encoded decimal, hex, octal, and binary values

  For more on ASCII, see http://www.asciitable.com and http://en.wikipedia.org/wiki/ASCII

  The circuit: No external hardware needed.

  created 2006
  by Nicholas Zambetti <http://www.zambetti.com>
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/ASCIITable
*/


byte adres  = 1;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  pinMode(A0,  INPUT_PULLUP); //dipswitch
  pinMode(A1,  INPUT_PULLUP);
  pinMode(A2,  INPUT_PULLUP);
  pinMode(A3,  INPUT_PULLUP);
  pinMode(A4,  INPUT_PULLUP);
  pinMode(A5,  INPUT_PULLUP);
  pinMode(A6,  INPUT_PULLUP);
  pinMode(A7,  INPUT_PULLUP);

  byte  pinStateA6 = analogRead(A6) > 100 ? 0 : 1; //a6 and a7 are not digitalinput
  byte  pinStateA7 = analogRead(A7) > 100 ? 0 : 1;

  bitWrite(adres, 0, !digitalRead(A0)) ;
  bitWrite(adres, 1, !digitalRead(A1)) ;
  bitWrite(adres, 2, !digitalRead(A2)) ;
  bitWrite(adres, 3, !digitalRead(A3)) ;

  bitWrite(adres, 4, !digitalRead(A4)) ;
  bitWrite(adres, 5, !digitalRead(A5)) ;
  bitWrite(adres, 6, pinStateA6) ;
  bitWrite(adres, 7, pinStateA7) ;

  // prints title with ending line break
  Serial.println("ASCII Table ~ Character Map=");
  Serial.println(adres);
  Serial.println(pinStateA6);
  Serial.println(pinStateA7);
  Serial.println("als 0 zet op 1");

  

adres < 1 ? adres=1 : 0 ; //indien dipswitch address is 0 , then set autoadres op 1

 Serial.println(adres);
  
}

// first visible ASCIIcharacter '!' is number 33:
int thisByte = 33;
// you can also write ASCII characters in single quotes.
// for example, '!' is the same as 33, so you could also use this:
// int thisByte = '!';

void loop() {
  // prints value unaltered, i.e. the raw binary version of the byte.
  // The Serial Monitor interprets all bytes as ASCII, so 33, the first number,
  // will show up as '!'

}
