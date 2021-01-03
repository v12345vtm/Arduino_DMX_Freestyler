#define msg7RESET 12
#define msg7Strobe 13
#define msg7DCout A0
#define analogBMP A1
#define Ruisonderdrukking 10


#define pin63hz 11
#define pin160hz 10
#define pin400hz 9
#define pin1000hz 8
#define pin2500hz 7
#define pin6250hz 6
#define pin16000hz 5


//const int LEDpins[7] = {pin63hz, pin160hz, pin400hz, pin1000hz, pin2500hz, pin6250hz, pin16000hz}; // there are 5 LEDs and 7 freq bands.  So, repeat LEDs


byte band63hz ;
byte band160hz ;
byte band400hz ;
byte band1000hz ;
byte band2500hz ;
byte band6250hz ;
byte band16000hz ;
int wacht35 = 35 ; //tussentijd voor elke band te sannen
int somVanAllePWM = 0 ; //om storingen tegen te gaan op 1 band bij stiltes

byte startdrempel = 180;
 byte uitdrempel = 175; //180 ; 
 


void setup() {
  Serial.begin(115200);
  //https://www.youtube.com/watch?v=O0fz6fH3V14
  //test voor dmx audio input
  // initialize the digital pin as an output.
  for (int x = 0; x < 13; x++) {
    pinMode(x, OUTPUT);
  }
  pinMode(msg7RESET, OUTPUT);
  pinMode(msg7Strobe, OUTPUT);
  pinMode(msg7DCout, INPUT);
  pinMode(analogBMP, INPUT);
}

void loop() {
  digitalWrite(msg7RESET, HIGH);      // reset the MSGEQ7's counter
  delay(5);
  digitalWrite(msg7RESET, LOW);
  somVanAllePWM = 0;

  //int anal = 75 ;
  //byte ttt = map(anal, 0, 1023, 0, 255);
  // Serial.print(analogRead(analogBMP));  Serial.print(" - ");
  // if (analogRead(analogBMP) < 350)
  //  {
  //   digitalWrite(9, HIGH);
  //  }
  //  else { digitalWrite(9, LOW);
  //    }



  //1 band63hz
  digitalWrite(msg7Strobe, LOW);    // output each DC value for each freq band
  delayMicroseconds(wacht35); // to allow the output to settle
  band63hz = map(analogRead(msg7DCout), 0, 1023, 0, 255);  // scale analogRead's value to Write's 255 max
  if (band63hz < Ruisonderdrukking + 15)
  {
    band63hz = 0 ; //ruis onderdrukken
  }
  digitalWrite(msg7Strobe, HIGH); //next band
  delayMicroseconds(20); // to allow the output to settle
  somVanAllePWM = somVanAllePWM +  band63hz ;

  //2 band160hz
  digitalWrite(msg7Strobe, LOW);    // output each DC value for each freq band
  delayMicroseconds(wacht35); // to allow the output to settle
  band160hz = map(analogRead(msg7DCout), 0, 1023, 0, 255);  // scale analogRead's value to Write's 255 max
  if (band160hz < Ruisonderdrukking + 45)
  {
    band160hz = 0 ; //laag nico dempen
  }
  digitalWrite(msg7Strobe, HIGH); //next band
  delayMicroseconds(20); // to allow the output to settle
  somVanAllePWM = somVanAllePWM +  band160hz ;

  //3 band400hz
  digitalWrite(msg7Strobe, LOW);    // output each DC value for each freq band
  delayMicroseconds(wacht35); // to allow the output to settle
  band400hz = map(analogRead(msg7DCout), 0, 1023, 0, 255);  // scale analogRead's value to Write's 255 max

  if (band400hz < Ruisonderdrukking + 50)
  {
    band400hz = 0; //ruis onderdrukken
  }
  digitalWrite(msg7Strobe, HIGH); //next band
  delayMicroseconds(20); // to allow the output to settle
  somVanAllePWM = somVanAllePWM +  band400hz ;

  //4 band1000hz
  digitalWrite(msg7Strobe, LOW);    // output each DC value for each freq band
  delayMicroseconds(wacht35); // to allow the output to settle
  band1000hz = map(analogRead(msg7DCout), 0, 1023, 0, 255);  // scale analogRead's value to Write's 255 max

  if (band1000hz < Ruisonderdrukking + 50)
  {
    band1000hz = 0 ; //ruis onderdrukken
  }
  digitalWrite(msg7Strobe, HIGH); //next band
  delayMicroseconds(20); // to allow the output to settle
  somVanAllePWM = somVanAllePWM +  band1000hz ;

  //5 band2500hz
  digitalWrite(msg7Strobe, LOW);    // output each DC value for each freq band
  delayMicroseconds(wacht35); // to allow the output to settle
  band2500hz = map(analogRead(msg7DCout), 0, 1023, 0, 255);  // scale analogRead's value to Write's 255 max

  if (band2500hz < Ruisonderdrukking + 45)
  {
    band2500hz = 0 ; //ruis onderdrukken
  }
  digitalWrite(msg7Strobe, HIGH); //next band
  delayMicroseconds(20); // to allow the output to settle
  somVanAllePWM = somVanAllePWM +  band2500hz ;

  //6 band6250hz
  digitalWrite(msg7Strobe, LOW);    // output each DC value for each freq band
  delayMicroseconds(wacht35); // to allow the output to settle
  band6250hz = map(analogRead(msg7DCout), 0, 1023, 0, 255);  // scale analogRead's value to Write's 255 max

  if (band6250hz < Ruisonderdrukking + 50)
  {
    band6250hz = 0 ; //ruis onderdrukken
  }
  digitalWrite(msg7Strobe, HIGH); //next band
  delayMicroseconds(20); // to allow the output to settle
  somVanAllePWM = somVanAllePWM +  band6250hz ;

  //7 band16000hz
  digitalWrite(msg7Strobe, LOW);    // output each DC value for each freq band
  delayMicroseconds(wacht35); // to allow the output to settle
  band16000hz = map(analogRead(msg7DCout), 0, 1023, 0, 255);  // scale analogRead's value to Write's 255 max

  if (band16000hz < Ruisonderdrukking + 45)
  {
    band16000hz = 0 ; //ruis onderdrukken
  }
  somVanAllePWM = somVanAllePWM +  band16000hz ;

  //export data from meting



  if (somVanAllePWM > 1) //enkel voldoende grote pieken doorsturen nr leds
  {
    //    analogWrite(pin63hz, band63hz); // elke band telkesn naar de pwm led uitsturen
    //    analogWrite(pin160hz, band160hz); // elke band telkesn naar de pwm led uitsturen
    //    analogWrite(pin400hz, band400hz); // elke band telkesn naar de pwm led uitsturen
    //    analogWrite(pin1000hz, band1000hz); // elke band telkesn naar de pwm led uitsturen
    //    analogWrite(pin2500hz, band2500hz); // elke band telkesn naar de pwm led uitsturen
    //    analogWrite(pin6250hz, band6250hz); // elke band telkesn naar de pwm led uitsturen
    //    analogWrite(pin16000hz, band16000hz); // elke band telkesn naar de pwm led uitsturen



    if (band63hz > startdrempel)    {
      digitalWrite(pin63hz , HIGH) ;
      Serial.print("X");  Serial.print(" ");
    }
    else {
      Serial.print("_");      Serial.print(" ");//1
    }
    if (band160hz > startdrempel)    {
      digitalWrite(pin160hz , HIGH) ;
      Serial.print("X");  Serial.print(" ");
    }
    else {
      Serial.print("_");      Serial.print(" ");//2
    }
    if (band400hz > startdrempel)    {
      digitalWrite(pin400hz , HIGH) ;
      Serial.print("X");  Serial.print(" ");
    } else {
      Serial.print("_");      Serial.print(" ");//3
    }
    if (band1000hz > startdrempel)    {
      digitalWrite(pin1000hz , HIGH) ;
      Serial.print("X");  Serial.print(" ");
    } else {
      Serial.print("_");      Serial.print(" ");//4
    }
    if (band2500hz > startdrempel)    {
      digitalWrite(pin2500hz , HIGH) ;
      Serial.print("X");  Serial.print(" ");
    } else {
      Serial.print("_");      Serial.print(" ");//5
    }
    if (band6250hz > startdrempel)    {
      digitalWrite(pin6250hz , HIGH) ;
      Serial.print("X");  Serial.print(" ");

    } else {
      Serial.print("_");      Serial.print(" ");//6
    }
    if (band16000hz > 50)    {
      digitalWrite(pin16000hz , HIGH) ;
      Serial.print("X");  Serial.print(" ");
    } else {
      Serial.print("_");      Serial.print(" ");//7
    }



    //    DMXSerial.write(1, band63hz);
    //      DMXSerial.write(2, band160hz);
    //        DMXSerial.write(3, band400hz);
    //
    //
    //            DMXSerial.write(5, band1000hz);
    //              DMXSerial.write(6, band2500hz);
    //                DMXSerial.write(7, band6250hz);
    //
    //  DMXSerial.write(4, 255); //fullbrightness
    //  DMXSerial.write(8, 255);

  }
  //next loop
  digitalWrite(msg7Strobe, HIGH); //next band
  // delayMicroseconds(200); // to allow the output to settle
  delay(30); // to allow the output to settle

//    Serial.print(band63hz);  Serial.print(" ");
//      Serial.print(band160hz);  Serial.print(" ");
//      Serial.print(band400hz);  Serial.print(" ");
//      Serial.print(band1000hz);  Serial.print(" ");
//      Serial.print(band2500hz);  Serial.print(" ");
//      Serial.print(band6250hz);  Serial.print(" ");
//      Serial.print(band16000hz);  Serial.print(" *");
    //   Serial.print(somVanAllePWM);  Serial.print(" ");

  //als de piek weg is led uit

 
  if (band63hz < uitdrempel)
  {
    digitalWrite(pin63hz , LOW) ;//1
  }
  if (band160hz < uitdrempel)
  {
    digitalWrite(pin160hz , LOW) ;//2
  }
  if (band400hz < uitdrempel)
  {
    digitalWrite(pin400hz , LOW) ;//3
  }
  if (band1000hz < uitdrempel)
  {
    digitalWrite(pin1000hz , LOW) ;//4
  }
  if (band2500hz < uitdrempel)
  {
    digitalWrite(pin2500hz , LOW) ;//5
  }
  if (band6250hz < uitdrempel)
  {
    digitalWrite(pin6250hz , LOW) ;//6
  }
  if (band16000hz < uitdrempel)
  {
    digitalWrite(pin16000hz , LOW) ;//7
  }

 // delayMicroseconds(5); // to allow the output to settle






  somVanAllePWM = 0;



  //  Serial.print("bias offset"); //Audiobias
  //  Serial.print(analogRead(Audiobias));
  Serial.println();
}
