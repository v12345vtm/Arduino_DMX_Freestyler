// (Heavily) adapted from https://github.com/G6EJD/ESP32-8266-Audio-Spectrum-Display/blob/master/ESP32_Spectrum_Display_02.ino
// Adjusted to allow brightness changes on press+hold, Auto-cycle for 3 button presses within 2 seconds


#include <arduinoFFT.h>

#define SAMPLES         1024          // Must be a power of 2
#define SAMPLING_FREQ   40000         // Hz, must be 40000 or less due to ADC conversion time. Determines maximum frequency that can be analysed by the FFT Fmax=sampleF/2.
#define AMPLITUDE       1          // Depending on your audio source level, you may need to alter this value. Can be used as a 'sensitivity' control.
#define AUDIO_IN_PIN    35            // Signal in on this pin
#define NUM_BANDS       16            // To change this, you will need to change the bunch of if statements describing the mapping from bins to bands
#define NOISE           1000           // Used as a crude noise filter, values below this are ignored

// Sampling and FFT stuff
unsigned int sampling_period_us;
int bandValues[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
double vReal[SAMPLES];
double vImag[SAMPLES];
unsigned long newTime;
arduinoFFT FFT = arduinoFFT(vReal, vImag, SAMPLES, SAMPLING_FREQ);

void setup() {
  Serial.begin(115200);
  sampling_period_us = round(1000000 * (1.0 / SAMPLING_FREQ));
}

void loop() {
  // Reset bandValues[]
  for (int i = 0; i < NUM_BANDS; i++) {
    bandValues[i] = 0;
  }

  // Sample the audio pin
  for (int i = 0; i < SAMPLES; i++) {
    newTime = micros();
    vReal[i] = analogRead(AUDIO_IN_PIN); // A conversion takes about 9.7uS on an ESP32
    vImag[i] = 0;
    while ((micros() - newTime) < sampling_period_us) {
      /* chill */
    }
  }

  // Compute FFT
  FFT.DCRemoval();
  FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(FFT_FORWARD);
  FFT.ComplexToMagnitude();

  // Analyse FFT results
  for (int i = 2; i < (SAMPLES / 2); i++) {    // Don't use sample 0 and only first SAMPLES/2 are usable. Each array element represents a frequency bin and its value the AMPLITUDE.
    if (vReal[i] > NOISE) {                    // Add a crude noise filter
      //16 bands, 20kHz top band
      if (i > 2   && i <= 3 ) bandValues[0]  +=  vReal[i] / AMPLITUDE;
      if (i > 3   && i <= 4  ) bandValues[1]  +=  vReal[i] / AMPLITUDE;
      if (i > 4   && i <= 5  ) bandValues[2]  +=  vReal[i] / AMPLITUDE;
      if (i > 5   && i <= 8  ) bandValues[3]  +=  vReal[i] / AMPLITUDE;
      if (i > 8   && i <= 11  ) bandValues[4]  +=  vReal[i] / AMPLITUDE;
      if (i > 11   && i <= 16 ) bandValues[5]  +=  vReal[i] / AMPLITUDE;
      if (i > 16  && i <= 23 ) bandValues[6]  +=  vReal[i] / AMPLITUDE;
      if (i > 23  && i <= 33 ) bandValues[7]  +=  vReal[i] / AMPLITUDE;
      if (i > 33  && i <= 48 ) bandValues[8]  +=  vReal[i] / AMPLITUDE;
      if (i > 48  && i <= 69 ) bandValues[9]  +=  vReal[i] / AMPLITUDE;
      if (i > 69  && i <= 99 ) bandValues[10] +=  vReal[i] / AMPLITUDE;
      if (i > 99  && i <= 144 ) bandValues[11] +=  vReal[i] / AMPLITUDE;
      if (i > 144  && i <= 207) bandValues[12] +=  vReal[i] / AMPLITUDE;
      if (i > 207 && i <= 300) bandValues[13] +=  vReal[i] / AMPLITUDE;
      if (i > 300 && i <= 433) bandValues[14] +=  vReal[i] / AMPLITUDE;
      if (i > 433          ) bandValues[15] += vReal[i] / AMPLITUDE;
    }
  }


 
//https://i.imgur.com/RcU7dLG.png
  for (int x = 0 ; x <  15  ; x ++)
  {

  //  Serial.print(  bandValues[x]   );
   // Serial.print(" ");


       Serial.print((int)bandValues[x]  );
    Serial.print(" ");
  }

  Serial.println(" ");
}
